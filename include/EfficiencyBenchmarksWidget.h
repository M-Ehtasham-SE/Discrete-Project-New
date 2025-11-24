#ifndef EFFICIENCYBENCHMARKSWIDGET_H
#define EFFICIENCYBENCHMARKSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QGroupBox>
#include <QComboBox>
#include <QTabWidget>
#include <QTimer>
#include <QElapsedTimer>
// Custom chart display using text representation

class EfficiencyBenchmarksWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EfficiencyBenchmarksWidget(QWidget *parent = nullptr);
    ~EfficiencyBenchmarksWidget();

private slots:
    void testRecursion();
    void testMemoization();
    void testBitOperations();
    void testSortingAlgorithms();
    void runComparisonBenchmark();
    void loadExample();
    void exportResults();
    void clearResults();

private:
    void setupUI();
    void setupRecursionTab();
    void setupBitOperationsTab();
    void setupSortingTab();
    void setupComparisonTab();
    void setupResultsTab();
    void connectSignals();
    void initializeBenchmarks();
    void updateChart();
    int fibRecursive(int n);
    int fibMemoized(int n, QVector<int> &memo);
    void bubbleSort(QVector<int> &arr);
    void quickSort(QVector<int> &arr, int low, int high);
    int partition(QVector<int> &arr, int low, int high);

    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Recursion Tab
    QWidget *m_recursionTab;
    QSpinBox *m_recursionInput;
    QPushButton *m_testRecursionBtn;
    QPushButton *m_testMemoBtn;
    
    // Bit Operations Tab
    QWidget *m_bitTab;
    QSpinBox *m_bitNumberInput;
    QPushButton *m_testBitBtn;
    
    // Sorting Tab
    QWidget *m_sortingTab;
    QSpinBox *m_arraySizeInput;
    QComboBox *m_sortingAlgoCombo;
    QPushButton *m_testSortingBtn;
    
    // Comparison Tab
    QWidget *m_comparisonTab;
    QPushButton *m_runComparisonBtn;
    QTextEdit *m_chartDisplay;
    
    // Results display
    QTextEdit *m_resultsDisplay;
    QProgressBar *m_progressBar;
    
    // Control buttons
    QPushButton *m_loadExampleBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_clearResultsBtn;
    
    // Data
    QElapsedTimer *m_timer;
    QVector<QPair<QString, qint64>> m_benchmarkResults;
};

#endif // EFFICIENCYBENCHMARKSWIDGET_H