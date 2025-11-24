#include "EfficiencyBenchmarksWidget.h"
#include "EfficiencyBenchmarks.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QApplication>
#include <QProgressDialog>
#include <QTimer>
#include <QTableWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>

EfficiencyBenchmarksWidget::EfficiencyBenchmarksWidget(QWidget *parent)
    : QWidget(parent)
    , m_timer(new QElapsedTimer())
{
    setupUI();
    connectSignals();
    initializeBenchmarks();
}

EfficiencyBenchmarksWidget::~EfficiencyBenchmarksWidget()
{
    delete m_timer;
}

void EfficiencyBenchmarksWidget::setupUI()
{
    setStyleSheet(R"(
        QWidget { 
            background-color: #2b2b2b; 
            color: #ffffff; 
            font-family: 'Consolas', 'Monaco', monospace;
        }
        QTabWidget::pane { 
            border: 1px solid #555555; 
            background-color: #2b2b2b; 
        }
        QTabBar::tab { 
            background-color: #3c3c3c; 
            color: #ffffff; 
            padding: 8px 16px; 
            margin-right: 2px; 
            border-top-left-radius: 4px; 
            border-top-right-radius: 4px; 
        }
        QTabBar::tab:selected { 
            background-color: #0078d4; 
        }
        QPushButton { 
            background-color: #0078d4; 
            color: white; 
            border: none; 
            padding: 8px 16px; 
            border-radius: 4px; 
            font-weight: bold; 
        }
        QPushButton:hover { 
            background-color: #106ebe; 
        }
        QPushButton:pressed { 
            background-color: #005a9e; 
        }
        QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox { 
            background-color: #404040; 
            color: #ffffff; 
            border: 1px solid #555555; 
            padding: 6px; 
            border-radius: 4px; 
        }
        QTextEdit { 
            background-color: #1e1e1e; 
            color: #ffffff; 
            border: 1px solid #555555; 
            font-family: 'Consolas', 'Monaco', monospace; 
            font-size: 12px; 
        }
        QTableWidget { 
            background-color: #1e1e1e; 
            color: #ffffff; 
            gridline-color: #555555; 
            border: 1px solid #555555; 
        }
        QHeaderView::section { 
            background-color: #3c3c3c; 
            color: #ffffff; 
            border: 1px solid #555555; 
            padding: 6px; 
        }
        QSplitter::handle { 
            background-color: #555555; 
        }
        QProgressBar {
            border: 1px solid #555555;
            border-radius: 4px;
            text-align: center;
            background-color: #404040;
            color: #ffffff;
        }
        QProgressBar::chunk {
            background-color: #0078d4;
            border-radius: 3px;
        }
        QGroupBox {
            font-weight: bold;
            color: #ffffff;
            border: 1px solid #555555;
            margin: 5px;
            padding: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
        }
    )");

    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    auto* titleLabel = new QLabel("Efficiency Benchmarks & Performance Analysis");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffffff; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Create tab widget
    m_tabWidget = new QTabWidget();
    m_mainLayout->addWidget(m_tabWidget);

    setupRecursionTab();
    setupBitOperationsTab();
    setupSortingTab();
    setupComparisonTab();
    setupResultsTab();
}

void EfficiencyBenchmarksWidget::setupRecursionTab()
{
    m_recursionTab = new QWidget();
    auto* layout = new QVBoxLayout(m_recursionTab);

    // Recursion controls
    auto* controlGroup = new QGroupBox("Recursion Tests");
    auto* controlLayout = new QGridLayout(controlGroup);

    controlLayout->addWidget(new QLabel("Fibonacci Number:"), 0, 0);
    m_recursionInput = new QSpinBox();
    m_recursionInput->setRange(1, 45);
    m_recursionInput->setValue(20);
    controlLayout->addWidget(m_recursionInput, 0, 1);

    m_testRecursionBtn = new QPushButton("Test Recursive Fibonacci");
    controlLayout->addWidget(m_testRecursionBtn, 0, 2);

    m_testMemoBtn = new QPushButton("Test Memoized Fibonacci");
    controlLayout->addWidget(m_testMemoBtn, 1, 2);

    layout->addWidget(controlGroup);

    m_tabWidget->addTab(m_recursionTab, "Recursion Analysis");
}

void EfficiencyBenchmarksWidget::setupBitOperationsTab()
{
    m_bitTab = new QWidget();
    auto* layout = new QVBoxLayout(m_bitTab);

    // Bit operations controls
    auto* controlGroup = new QGroupBox("Bit Operations Tests");
    auto* controlLayout = new QGridLayout(controlGroup);

    controlLayout->addWidget(new QLabel("Number:"), 0, 0);
    m_bitNumberInput = new QSpinBox();
    m_bitNumberInput->setRange(1, 1000000);
    m_bitNumberInput->setValue(1000);
    controlLayout->addWidget(m_bitNumberInput, 0, 1);

    m_testBitBtn = new QPushButton("Test Bit Operations");
    controlLayout->addWidget(m_testBitBtn, 0, 2);

    layout->addWidget(controlGroup);

    m_tabWidget->addTab(m_bitTab, "Bit Operations");
}

void EfficiencyBenchmarksWidget::setupSortingTab()
{
    m_sortingTab = new QWidget();
    auto* layout = new QVBoxLayout(m_sortingTab);

    // Sorting controls
    auto* controlGroup = new QGroupBox("Sorting Algorithm Tests");
    auto* controlLayout = new QGridLayout(controlGroup);

    controlLayout->addWidget(new QLabel("Array Size:"), 0, 0);
    m_arraySizeInput = new QSpinBox();
    m_arraySizeInput->setRange(10, 50000);
    m_arraySizeInput->setValue(1000);
    controlLayout->addWidget(m_arraySizeInput, 0, 1);

    controlLayout->addWidget(new QLabel("Algorithm:"), 1, 0);
    m_sortingAlgoCombo = new QComboBox();
    m_sortingAlgoCombo->addItems({"Bubble Sort", "Quick Sort", "Merge Sort", "Standard Sort"});
    controlLayout->addWidget(m_sortingAlgoCombo, 1, 1);

    m_testSortingBtn = new QPushButton("Test Sorting Algorithm");
    controlLayout->addWidget(m_testSortingBtn, 0, 2, 2, 1);

    layout->addWidget(controlGroup);

    m_tabWidget->addTab(m_sortingTab, "Sorting Algorithms");
}

void EfficiencyBenchmarksWidget::setupComparisonTab()
{
    m_comparisonTab = new QWidget();
    auto* layout = new QVBoxLayout(m_comparisonTab);

    // Comparison controls
    auto* controlGroup = new QGroupBox("Algorithm Comparison");
    auto* controlLayout = new QHBoxLayout(controlGroup);

    m_runComparisonBtn = new QPushButton("Run Complete Benchmark Suite");
    controlLayout->addWidget(m_runComparisonBtn);

    layout->addWidget(controlGroup);

    // Chart display (text-based)
    auto* chartGroup = new QGroupBox("Performance Visualization");
    auto* chartLayout = new QVBoxLayout(chartGroup);

    m_chartDisplay = new QTextEdit();
    m_chartDisplay->setReadOnly(true);
    m_chartDisplay->setMinimumHeight(300);
    chartLayout->addWidget(m_chartDisplay);

    layout->addWidget(chartGroup);

    m_tabWidget->addTab(m_comparisonTab, "Comparison & Charts");
}

void EfficiencyBenchmarksWidget::setupResultsTab()
{
    auto* tab = new QWidget();
    auto* layout = new QVBoxLayout(tab);

    // Control buttons
    auto* buttonGroup = new QGroupBox("Results Management");
    auto* buttonLayout = new QHBoxLayout(buttonGroup);

    m_loadExampleBtn = new QPushButton("Load Example Data");
    m_exportBtn = new QPushButton("Export Results");
    m_clearResultsBtn = new QPushButton("Clear All Results");

    buttonLayout->addWidget(m_loadExampleBtn);
    buttonLayout->addWidget(m_exportBtn);
    buttonLayout->addWidget(m_clearResultsBtn);

    layout->addWidget(buttonGroup);

    // Progress bar
    m_progressBar = new QProgressBar();
    m_progressBar->setVisible(false);
    layout->addWidget(m_progressBar);

    // Results display
    auto* resultsGroup = new QGroupBox("Benchmark Results");
    auto* resultsLayout = new QVBoxLayout(resultsGroup);

    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    resultsLayout->addWidget(m_resultsDisplay);

    layout->addWidget(resultsGroup);

    m_tabWidget->addTab(tab, "Results & Export");
}

void EfficiencyBenchmarksWidget::connectSignals()
{
    connect(m_testRecursionBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::testRecursion);
    connect(m_testMemoBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::testMemoization);
    connect(m_testBitBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::testBitOperations);
    connect(m_testSortingBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::testSortingAlgorithms);
    connect(m_runComparisonBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::runComparisonBenchmark);
    connect(m_loadExampleBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::loadExample);
    connect(m_exportBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::exportResults);
    connect(m_clearResultsBtn, &QPushButton::clicked, this, &EfficiencyBenchmarksWidget::clearResults);
}

void EfficiencyBenchmarksWidget::initializeBenchmarks()
{
    m_resultsDisplay->append("=== Efficiency Benchmarks System Initialized ===\n");
    m_resultsDisplay->append("Ready to run performance tests.\n");
    m_resultsDisplay->append("Select a tab above to begin testing specific algorithms.\n\n");
}

void EfficiencyBenchmarksWidget::testRecursion()
{
    int n = m_recursionInput->value();
    
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 0); // Indeterminate progress
    
    QString result = QString("=== Recursive Fibonacci Test (n=%1) ===\n").arg(n);
    
    m_timer->start();
    int fibResult = fibRecursive(n);
    qint64 recursiveTime = m_timer->elapsed();
    
    result += QString("Recursive Result: %1\n").arg(fibResult);
    result += QString("Recursive Time: %1 ms\n").arg(recursiveTime);
    
    // Estimate complexity
    double estimatedOps = std::pow(1.618, n); // Fibonacci sequence complexity
    result += QString("Estimated Operations: ~%1\n").arg(estimatedOps, 0, 'e', 2);
    result += QString("Time Complexity: O(φ^n) where φ ≈ 1.618\n");
    result += QString("Space Complexity: O(n) due to recursion stack\n\n");

    m_resultsDisplay->append(result);
    m_benchmarkResults.append({QString("Recursive Fibonacci (%1)").arg(n), recursiveTime});
    
    m_progressBar->setVisible(false);
    updateChart();
}

void EfficiencyBenchmarksWidget::testMemoization()
{
    int n = m_recursionInput->value();
    
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 0);
    
    QString result = QString("=== Memoized Fibonacci Test (n=%1) ===\n").arg(n);
    
    QVector<int> memo(n + 1, -1);
    m_timer->start();
    int fibResult = fibMemoized(n, memo);
    qint64 memoizedTime = m_timer->elapsed();
    
    result += QString("Memoized Result: %1\n").arg(fibResult);
    result += QString("Memoized Time: %1 ms\n").arg(memoizedTime);
    result += QString("Time Complexity: O(n)\n");
    result += QString("Space Complexity: O(n) for memoization table\n");
    
    // Compare with previous recursive result if available
    if (!m_benchmarkResults.isEmpty()) {
        auto lastResult = m_benchmarkResults.last();
        if (lastResult.first.contains("Recursive Fibonacci")) {
            double speedup = (double)lastResult.second / memoizedTime;
            result += QString("Speedup vs Recursive: %.2fx faster\n").arg(speedup);
        }
    }
    
    result += "\n";
    m_resultsDisplay->append(result);
    m_benchmarkResults.append({QString("Memoized Fibonacci (%1)").arg(n), memoizedTime});
    
    m_progressBar->setVisible(false);
    updateChart();
}

void EfficiencyBenchmarksWidget::testBitOperations()
{
    int number = m_bitNumberInput->value();
    
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 0);
    
    QString result = QString("=== Bit Operations Test (n=%1) ===\n").arg(number);
    
    // Test bit counting
    m_timer->start();
    int bitCount = 0;
    for (int i = 1; i <= number; ++i) {
        bitCount += __builtin_popcount(i); // Count set bits
    }
    qint64 bitTime = m_timer->elapsed();
    
    result += QString("Total set bits from 1 to %1: %2\n").arg(number).arg(bitCount);
    result += QString("Bit counting time: %1 ms\n").arg(bitTime);
    
    // Test bit operations vs arithmetic
    m_timer->start();
    int sum = 0;
    for (int i = 1; i <= number; ++i) {
        sum += (i << 1); // Multiply by 2 using bit shift
    }
    qint64 bitShiftTime = m_timer->elapsed();
    
    m_timer->start();
    int sum2 = 0;
    for (int i = 1; i <= number; ++i) {
        sum2 += (i * 2); // Regular multiplication
    }
    qint64 multTime = m_timer->elapsed();
    
    result += QString("Bit shift (x2) time: %1 ms\n").arg(bitShiftTime);
    result += QString("Multiplication (x2) time: %1 ms\n").arg(multTime);
    
    if (bitShiftTime > 0) {
        double speedup = (double)multTime / bitShiftTime;
        result += QString("Bit shift speedup: %.2fx\n").arg(speedup);
    }
    
    result += "\n";
    m_resultsDisplay->append(result);
    m_benchmarkResults.append({QString("Bit Operations (%1)").arg(number), bitTime});
    
    m_progressBar->setVisible(false);
    updateChart();
}

void EfficiencyBenchmarksWidget::testSortingAlgorithms()
{
    int arraySize = m_arraySizeInput->value();
    QString algorithm = m_sortingAlgoCombo->currentText();
    
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 0);
    
    QString result = QString("=== Sorting Algorithm Test: %1 (size=%2) ===\n").arg(algorithm).arg(arraySize);
    
    // Generate random data
    QVector<int> data;
    data.reserve(arraySize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    
    for (int i = 0; i < arraySize; ++i) {
        data.append(dis(gen));
    }
    
    QVector<int> dataCopy = data; // Keep original for verification
    
    m_timer->start();
    
    if (algorithm == "Bubble Sort") {
        bubbleSort(data);
        result += "Time Complexity: O(n²)\nSpace Complexity: O(1)\n";
    } else if (algorithm == "Quick Sort") {
        quickSort(data, 0, data.size() - 1);
        result += "Time Complexity: O(n log n) avg, O(n²) worst\nSpace Complexity: O(log n)\n";
    } else if (algorithm == "Standard Sort") {
        std::sort(data.begin(), data.end());
        result += "Time Complexity: O(n log n)\nSpace Complexity: O(log n)\n";
    }
    
    qint64 sortTime = m_timer->elapsed();
    
    // Verify sorting
    bool isSorted = std::is_sorted(data.begin(), data.end());
    
    result += QString("Sorting time: %1 ms\n").arg(sortTime);
    result += QString("Result: %1\n").arg(isSorted ? "CORRECTLY SORTED" : "SORTING FAILED");
    result += QString("Array size: %1 elements\n").arg(arraySize);
    
    if (arraySize <= 20) {
        result += "Original: [";
        for (int i = 0; i < std::min(10, (int)dataCopy.size()); ++i) {
            result += QString::number(dataCopy[i]);
            if (i < std::min(9, (int)dataCopy.size() - 1)) result += ", ";
        }
        if (dataCopy.size() > 10) result += "...";
        result += "]\n";
        
        result += "Sorted:   [";
        for (int i = 0; i < std::min(10, (int)data.size()); ++i) {
            result += QString::number(data[i]);
            if (i < std::min(9, (int)data.size() - 1)) result += ", ";
        }
        if (data.size() > 10) result += "...";
        result += "]\n";
    }
    
    result += "\n";
    m_resultsDisplay->append(result);
    m_benchmarkResults.append({QString("%1 (%2)").arg(algorithm).arg(arraySize), sortTime});
    
    m_progressBar->setVisible(false);
    updateChart();
}

void EfficiencyBenchmarksWidget::runComparisonBenchmark()
{
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 100);
    
    QString result = "=== Complete Benchmark Suite ===\n\n";
    m_resultsDisplay->append(result);
    
    // Test different sizes for sorting algorithms
    QVector<int> sizes = {100, 500, 1000, 2000, 5000};
    QStringList algorithms = {"Bubble Sort", "Quick Sort", "Standard Sort"};
    
    result = "Sorting Algorithm Comparison:\n";
    result += QString("%-15s").arg("Size");
    for (const QString& algo : algorithms) {
        result += QString("%15s").arg(algo);
    }
    result += "\n" + QString("-").repeated(70) + "\n";
    
    int progress = 0;
    int totalTests = sizes.size() * algorithms.size();
    
    for (int size : sizes) {
        result += QString("%-15d").arg(size);
        
        for (const QString& algorithm : algorithms) {
            // Generate data
            QVector<int> data;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 10000);
            
            for (int i = 0; i < size; ++i) {
                data.append(dis(gen));
            }
            
            m_timer->start();
            
            if (algorithm == "Bubble Sort") {
                bubbleSort(data);
            } else if (algorithm == "Quick Sort") {
                quickSort(data, 0, data.size() - 1);
            } else if (algorithm == "Standard Sort") {
                std::sort(data.begin(), data.end());
            }
            
            qint64 time = m_timer->elapsed();
            result += QString("%12d ms").arg(time);
            
            progress++;
            m_progressBar->setValue((progress * 100) / totalTests);
            QApplication::processEvents();
        }
        result += "\n";
    }
    
    result += "\n";
    m_resultsDisplay->append(result);
    
    // Test fibonacci comparison
    result = "Fibonacci Algorithm Comparison:\n";
    result += QString("%-8s%15s%15s%15s\n").arg("n").arg("Recursive").arg("Memoized").arg("Speedup");
    result += QString("-").repeated(50) + "\n";
    
    QVector<int> fibSizes = {10, 15, 20, 25, 30};
    for (int n : fibSizes) {
        result += QString("%-8d").arg(n);
        
        // Recursive
        m_timer->start();
        fibRecursive(n);
        qint64 recTime = m_timer->elapsed();
        result += QString("%12d ms").arg(recTime);
        
        // Memoized
        QVector<int> memo(n + 1, -1);
        m_timer->start();
        fibMemoized(n, memo);
        qint64 memoTime = m_timer->elapsed();
        result += QString("%12d ms").arg(memoTime);
        
        double speedup = recTime > 0 ? (double)recTime / memoTime : 0;
        result += QString("%12.1fx").arg(speedup);
        
        result += "\n";
        
        progress++;
        m_progressBar->setValue((progress * 100) / totalTests);
        QApplication::processEvents();
    }
    
    m_resultsDisplay->append(result + "\n");
    
    m_progressBar->setVisible(false);
    updateChart();
}

void EfficiencyBenchmarksWidget::updateChart()
{
    if (m_benchmarkResults.isEmpty()) {
        m_chartDisplay->clear();
        return;
    }

    QString chart = "Performance Chart (Recent Results):\n\n";
    
    // Find max time for scaling
    qint64 maxTime = 0;
    for (const auto& result : m_benchmarkResults) {
        maxTime = std::max(maxTime, result.second);
    }
    
    // Show last 10 results
    int startIdx = std::max(0, (int)m_benchmarkResults.size() - 10);
    
    for (int i = startIdx; i < m_benchmarkResults.size(); ++i) {
        const auto& result = m_benchmarkResults[i];
        QString name = result.first;
        qint64 time = result.second;
        
        // Truncate long names
        if (name.length() > 25) {
            name = name.left(22) + "...";
        }
        
        // Create text bar
        int barLength = maxTime > 0 ? (time * 40) / maxTime : 0;
        QString bar = QString("█").repeated(barLength);
        
        chart += QString("%-25s │%1 %2ms\n").arg(name).arg(bar).arg(time);
    }
    
    chart += "\nLegend: Each █ represents " + QString::number(maxTime / 40.0, 'f', 1) + "ms\n";
    
    m_chartDisplay->setText(chart);
}

int EfficiencyBenchmarksWidget::fibRecursive(int n)
{
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int EfficiencyBenchmarksWidget::fibMemoized(int n, QVector<int>& memo)
{
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibMemoized(n - 1, memo) + fibMemoized(n - 2, memo);
    return memo[n];
}

void EfficiencyBenchmarksWidget::bubbleSort(QVector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void EfficiencyBenchmarksWidget::quickSort(QVector<int>& arr, int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int EfficiencyBenchmarksWidget::partition(QVector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void EfficiencyBenchmarksWidget::loadExample()
{
    QString exampleText = R"(=== Example Benchmark Results ===

Algorithm Performance Comparison:
• Bubble Sort (1000 elements): 45ms - O(n²)
• Quick Sort (1000 elements): 2ms - O(n log n)
• Standard Sort (1000 elements): 1ms - O(n log n)

Fibonacci Sequence Comparison:
• Recursive F(25): 1250ms - O(φⁿ)
• Memoized F(25): 1ms - O(n)
• Speedup: 1250x faster with memoization

Bit Operations vs Arithmetic:
• Bit shifting (x2): 0.5ms
• Multiplication (x2): 0.8ms
• Bit operations 60% faster

Key Insights:
1. Memoization dramatically improves recursive algorithms
2. Efficient algorithms (O(n log n)) vastly outperform naive ones (O(n²))
3. Bit operations can provide significant speedups for simple arithmetic
4. Algorithm choice becomes critical with larger datasets

)";

    m_resultsDisplay->append(exampleText);
}

void EfficiencyBenchmarksWidget::exportResults()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Export Benchmark Results",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/benchmark_results.txt",
        "Text Files (*.txt);;CSV Files (*.csv)");
        
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "Efficiency Benchmarks Report\n";
            out << "Generated: " << QDateTime::currentDateTime().toString() << "\n\n";
            out << m_resultsDisplay->toPlainText();
            
            QMessageBox::information(this, "Success", "Results exported successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Could not save file!");
        }
    }
}

void EfficiencyBenchmarksWidget::clearResults()
{
    m_resultsDisplay->clear();
    m_chartDisplay->clear();
    m_benchmarkResults.clear();
    initializeBenchmarks();
}