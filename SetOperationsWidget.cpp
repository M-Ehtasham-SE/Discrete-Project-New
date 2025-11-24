#include "SetOperationsWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QRandomGenerator>
#include <algorithm>

SetOperationsWidget::SetOperationsWidget(QWidget *parent)
    : QWidget(parent)
    , m_manager(new SetOperationsManager())
{
    setupUI();
    
    // Initialize with sample data
    m_setA << "1" << "2" << "3" << "4" << "5";
    m_setB << "4" << "5" << "6" << "7" << "8";
    m_universe << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10";
    
    updateSetDisplays();
}

void SetOperationsWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Set Operations Manager");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Create tab widget
    m_tabWidget = new QTabWidget();
    
    // Tab 1: Set Input and Management
    QWidget *inputTab = new QWidget();
    QHBoxLayout *inputLayout = new QHBoxLayout(inputTab);
    
    // Set A
    QVBoxLayout *setALayout = new QVBoxLayout();
    m_setALabel = new QLabel("Set A = { }");
    m_setALabel->setStyleSheet("font-weight: bold; color: #4fc3f7;");
    setALayout->addWidget(m_setALabel);
    
    m_setAList = new QListWidget();
    m_setAList->setMaximumHeight(150);
    setALayout->addWidget(m_setAList);
    
    QHBoxLayout *inputALayout = new QHBoxLayout();
    m_elementInputA = new QLineEdit();
    m_elementInputA->setPlaceholderText("Enter element for Set A...");
    connect(m_elementInputA, &QLineEdit::returnPressed, this, &SetOperationsWidget::addElementToSetA);
    m_addToAButton = new QPushButton("Add to A");
    connect(m_addToAButton, &QPushButton::clicked, this, &SetOperationsWidget::addElementToSetA);
    inputALayout->addWidget(m_elementInputA);
    inputALayout->addWidget(m_addToAButton);
    setALayout->addLayout(inputALayout);
    
    QHBoxLayout *controlALayout = new QHBoxLayout();
    m_removeFromAButton = new QPushButton("Remove Selected");
    m_clearAButton = new QPushButton("Clear A");
    connect(m_removeFromAButton, &QPushButton::clicked, this, &SetOperationsWidget::removeFromSetA);
    connect(m_clearAButton, &QPushButton::clicked, this, &SetOperationsWidget::clearSetA);
    controlALayout->addWidget(m_removeFromAButton);
    controlALayout->addWidget(m_clearAButton);
    setALayout->addLayout(controlALayout);
    
    inputLayout->addLayout(setALayout);
    
    // Set B
    QVBoxLayout *setBLayout = new QVBoxLayout();
    m_setBLabel = new QLabel("Set B = { }");
    m_setBLabel->setStyleSheet("font-weight: bold; color: #81c784;");
    setBLayout->addWidget(m_setBLabel);
    
    m_setBList = new QListWidget();
    m_setBList->setMaximumHeight(150);
    setBLayout->addWidget(m_setBList);
    
    QHBoxLayout *inputBLayout = new QHBoxLayout();
    m_elementInputB = new QLineEdit();
    m_elementInputB->setPlaceholderText("Enter element for Set B...");
    connect(m_elementInputB, &QLineEdit::returnPressed, this, &SetOperationsWidget::addElementToSetB);
    m_addToBButton = new QPushButton("Add to B");
    connect(m_addToBButton, &QPushButton::clicked, this, &SetOperationsWidget::addElementToSetB);
    inputBLayout->addWidget(m_elementInputB);
    inputBLayout->addWidget(m_addToBButton);
    setBLayout->addLayout(inputBLayout);
    
    QHBoxLayout *controlBLayout = new QHBoxLayout();
    m_removeFromBButton = new QPushButton("Remove Selected");
    m_clearBButton = new QPushButton("Clear B");
    connect(m_removeFromBButton, &QPushButton::clicked, this, &SetOperationsWidget::removeFromSetB);
    connect(m_clearBButton, &QPushButton::clicked, this, &SetOperationsWidget::clearSetB);
    controlBLayout->addWidget(m_removeFromBButton);
    controlBLayout->addWidget(m_clearBButton);
    setBLayout->addLayout(controlBLayout);
    
    inputLayout->addLayout(setBLayout);
    
    // Universe Set
    QVBoxLayout *universeLayout = new QVBoxLayout();
    QLabel *universeLabel = new QLabel("Universe U = { }");
    universeLabel->setStyleSheet("font-weight: bold; color: #ffb74d;");
    universeLayout->addWidget(universeLabel);
    
    m_universeList = new QListWidget();
    m_universeList->setMaximumHeight(100);
    universeLayout->addWidget(m_universeList);
    
    QHBoxLayout *universeInputLayout = new QHBoxLayout();
    m_universeInput = new QLineEdit();
    m_universeInput->setPlaceholderText("Universe element...");
    m_addToUniverseButton = new QPushButton("Add to U");
    m_clearUniverseButton = new QPushButton("Clear U");
    connect(m_addToUniverseButton, &QPushButton::clicked, this, [this]() {
        QString element = m_universeInput->text().trimmed();
        if (!element.isEmpty() && !m_universe.contains(element)) {
            m_universe.append(element);
            m_universeInput->clear();
            updateSetDisplays();
        }
    });
    connect(m_clearUniverseButton, &QPushButton::clicked, this, [this]() {
        m_universe.clear();
        updateSetDisplays();
    });
    universeInputLayout->addWidget(m_universeInput);
    universeInputLayout->addWidget(m_addToUniverseButton);
    universeInputLayout->addWidget(m_clearUniverseButton);
    universeLayout->addLayout(universeInputLayout);
    
    inputLayout->addLayout(universeLayout);
    
    m_tabWidget->addTab(inputTab, "Set Management");
    
    // Tab 2: Operations
    QWidget *operationsTab = new QWidget();
    QVBoxLayout *opsLayout = new QVBoxLayout(operationsTab);
    
    // Operation buttons
    QGridLayout *buttonGrid = new QGridLayout();
    
    m_unionButton = new QPushButton("A ∪ B (Union)");
    m_unionButton->setToolTip("Elements in A or B or both");
    connect(m_unionButton, &QPushButton::clicked, this, &SetOperationsWidget::calculateUnion);
    buttonGrid->addWidget(m_unionButton, 0, 0);
    
    m_intersectionButton = new QPushButton("A ∩ B (Intersection)");
    m_intersectionButton->setToolTip("Elements in both A and B");
    connect(m_intersectionButton, &QPushButton::clicked, this, &SetOperationsWidget::calculateIntersection);
    buttonGrid->addWidget(m_intersectionButton, 0, 1);
    
    m_differenceButton = new QPushButton("A - B (Difference)");
    m_differenceButton->setToolTip("Elements in A but not in B");
    connect(m_differenceButton, &QPushButton::clicked, this, &SetOperationsWidget::calculateDifference);
    buttonGrid->addWidget(m_differenceButton, 1, 0);
    
    m_symDifferenceButton = new QPushButton("A ⊕ B (Symmetric Difference)");
    m_symDifferenceButton->setToolTip("Elements in A or B but not in both");
    connect(m_symDifferenceButton, &QPushButton::clicked, this, &SetOperationsWidget::calculateSymmetricDifference);
    buttonGrid->addWidget(m_symDifferenceButton, 1, 1);
    
    m_complementButton = new QPushButton("A' (Complement)");
    m_complementButton->setToolTip("Elements in Universe but not in A");
    connect(m_complementButton, &QPushButton::clicked, this, &SetOperationsWidget::calculateComplement);
    buttonGrid->addWidget(m_complementButton, 2, 0);
    
    m_allOperationsButton = new QPushButton("All Operations");
    m_allOperationsButton->setToolTip("Perform all set operations");
    connect(m_allOperationsButton, &QPushButton::clicked, this, &SetOperationsWidget::performAllOperations);
    buttonGrid->addWidget(m_allOperationsButton, 2, 1);
    
    opsLayout->addLayout(buttonGrid);
    
    // Results display
    m_operationResults = new QTextEdit();
    m_operationResults->setReadOnly(true);
    opsLayout->addWidget(m_operationResults);
    
    m_tabWidget->addTab(operationsTab, "Operations");
    
    // Tab 3: Visualization
    QWidget *visualTab = new QWidget();
    QVBoxLayout *visualLayout = new QVBoxLayout(visualTab);
    
    QHBoxLayout *visualControls = new QHBoxLayout();
    m_showVennButton = new QPushButton("Show Venn Diagram");
    m_generateRandomButton = new QPushButton("Generate Random Sets");
    m_loadPresetButton = new QPushButton("Load Preset");
    m_presetComboBox = new QComboBox();
    m_presetComboBox->addItems({"Numbers 1-10", "Letters A-J", "Programming Languages", "Mathematics Topics"});
    
    connect(m_showVennButton, &QPushButton::clicked, this, &SetOperationsWidget::showVennDiagram);
    connect(m_generateRandomButton, &QPushButton::clicked, this, &SetOperationsWidget::generateRandomSets);
    connect(m_loadPresetButton, &QPushButton::clicked, this, &SetOperationsWidget::loadPresetSets);
    
    visualControls->addWidget(m_showVennButton);
    visualControls->addWidget(m_generateRandomButton);
    visualControls->addWidget(m_loadPresetButton);
    visualControls->addWidget(m_presetComboBox);
    visualControls->addStretch();
    visualLayout->addLayout(visualControls);
    
    m_vennDisplay = new QTextEdit();
    m_vennDisplay->setReadOnly(true);
    m_vennDisplay->setFont(QFont("Consolas", 10));
    visualLayout->addWidget(m_vennDisplay);
    
    m_tabWidget->addTab(visualTab, "Visualization");
    
    // Tab 4: Properties
    QWidget *propertiesTab = new QWidget();
    QVBoxLayout *propsLayout = new QVBoxLayout(propertiesTab);
    
    QHBoxLayout *propsControls = new QHBoxLayout();
    m_checkPropertiesButton = new QPushButton("Check Set Properties");
    m_showStepsCheckBox = new QCheckBox("Show Detailed Steps");
    m_showStepsCheckBox->setChecked(true);
    connect(m_checkPropertiesButton, &QPushButton::clicked, this, &SetOperationsWidget::checkSetProperties);
    
    propsControls->addWidget(m_checkPropertiesButton);
    propsControls->addWidget(m_showStepsCheckBox);
    propsControls->addStretch();
    propsLayout->addLayout(propsControls);
    
    m_propertiesDisplay = new QTextEdit();
    m_propertiesDisplay->setReadOnly(true);
    propsLayout->addWidget(m_propertiesDisplay);
    
    m_tabWidget->addTab(propertiesTab, "Properties");
    
    // Export controls
    QHBoxLayout *exportLayout = new QHBoxLayout();
    m_exportButton = new QPushButton("Export Results");
    connect(m_exportButton, &QPushButton::clicked, this, &SetOperationsWidget::exportResults);
    m_progressBar = new QProgressBar();
    m_progressBar->setVisible(false);
    
    exportLayout->addWidget(m_exportButton);
    exportLayout->addWidget(m_progressBar);
    exportLayout->addStretch();
    
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addLayout(exportLayout);
}

void SetOperationsWidget::addElementToSetA()
{
    QString element = m_elementInputA->text().trimmed();
    if (!element.isEmpty() && !m_setA.contains(element)) {
        m_setA.append(element);
        m_elementInputA->clear();
        updateSetDisplays();
        onSetAChanged();
    }
}

void SetOperationsWidget::addElementToSetB()
{
    QString element = m_elementInputB->text().trimmed();
    if (!element.isEmpty() && !m_setB.contains(element)) {
        m_setB.append(element);
        m_elementInputB->clear();
        updateSetDisplays();
        onSetBChanged();
    }
}

void SetOperationsWidget::removeFromSetA()
{
    int row = m_setAList->currentRow();
    if (row >= 0) {
        m_setA.removeAt(row);
        updateSetDisplays();
        onSetAChanged();
    }
}

void SetOperationsWidget::removeFromSetB()
{
    int row = m_setBList->currentRow();
    if (row >= 0) {
        m_setB.removeAt(row);
        updateSetDisplays();
        onSetBChanged();
    }
}

void SetOperationsWidget::clearSetA()
{
    m_setA.clear();
    updateSetDisplays();
    onSetAChanged();
}

void SetOperationsWidget::clearSetB()
{
    m_setB.clear();
    updateSetDisplays();
    onSetBChanged();
}

void SetOperationsWidget::updateSetDisplays()
{
    // Update Set A
    m_setALabel->setText(QString("Set A = { %1 }").arg(m_setA.join(", ")));
    showSetInList(m_setA, m_setAList);
    
    // Update Set B
    m_setBLabel->setText(QString("Set B = { %1 }").arg(m_setB.join(", ")));
    showSetInList(m_setB, m_setBList);
    
    // Update Universe
    showSetInList(m_universe, m_universeList);
}

void SetOperationsWidget::showSetInList(const QStringList &set, QListWidget *listWidget)
{
    listWidget->clear();
    for (const QString &element : set) {
        listWidget->addItem(element);
    }
}

void SetOperationsWidget::calculateUnion()
{
    QStringList result = performUnion(m_setA, m_setB);
    displayOperationResult("Union (A ∪ B)", result);
    m_cachedResults[QString("Union")] = result;
}

void SetOperationsWidget::calculateIntersection()
{
    QStringList result = performIntersection(m_setA, m_setB);
    displayOperationResult("Intersection (A ∩ B)", result);
    m_cachedResults[QString("Intersection")] = result;
}

void SetOperationsWidget::calculateDifference()
{
    QStringList result = performDifference(m_setA, m_setB);
    displayOperationResult("Difference (A - B)", result);
    m_cachedResults[QString("Difference")] = result;
}

void SetOperationsWidget::calculateSymmetricDifference()
{
    QStringList result = performSymmetricDifference(m_setA, m_setB);
    displayOperationResult("Symmetric Difference (A ⊕ B)", result);
    m_cachedResults[QString("SymmetricDifference")] = result;
}

void SetOperationsWidget::calculateComplement()
{
    QStringList result = performComplement(m_setA, m_universe);
    displayOperationResult("Complement (A')", result);
    m_cachedResults[QString("Complement")] = result;
}

void SetOperationsWidget::performAllOperations()
{
    QString allResults = "<h2>🔄 Complete Set Operations Analysis</h2>";
    allResults += QString("<p><b>Set A:</b> { %1 }</p>").arg(m_setA.join(", "));
    allResults += QString("<p><b>Set B:</b> { %1 }</p>").arg(m_setB.join(", "));
    allResults += QString("<p><b>Universe U:</b> { %1 }</p><br>").arg(m_universe.join(", "));
    
    // Union
    QStringList unionResult = performUnion(m_setA, m_setB);
    allResults += QString("<h3>1. Union (A ∪ B)</h3>");
    allResults += QString("<p><b>Result:</b> { %1 }</p>").arg(unionResult.join(", "));
    allResults += "<p><b>Definition:</b> All elements that are in A or B (or both)</p><br>";
    
    // Intersection
    QStringList intersectionResult = performIntersection(m_setA, m_setB);
    allResults += QString("<h3>2. Intersection (A ∩ B)</h3>");
    allResults += QString("<p><b>Result:</b> { %1 }</p>").arg(intersectionResult.join(", "));
    allResults += "<p><b>Definition:</b> Elements that are in both A and B</p><br>";
    
    // Difference
    QStringList differenceResult = performDifference(m_setA, m_setB);
    allResults += QString("<h3>3. Difference (A - B)</h3>");
    allResults += QString("<p><b>Result:</b> { %1 }</p>").arg(differenceResult.join(", "));
    allResults += "<p><b>Definition:</b> Elements in A but not in B</p><br>";
    
    // Symmetric Difference
    QStringList symDiffResult = performSymmetricDifference(m_setA, m_setB);
    allResults += QString("<h3>4. Symmetric Difference (A ⊕ B)</h3>");
    allResults += QString("<p><b>Result:</b> { %1 }</p>").arg(symDiffResult.join(", "));
    allResults += "<p><b>Definition:</b> Elements in A or B but not in both</p><br>";
    
    // Complement
    if (!m_universe.isEmpty()) {
        QStringList complementResult = performComplement(m_setA, m_universe);
        allResults += QString("<h3>5. Complement (A')</h3>");
        allResults += QString("<p><b>Result:</b> { %1 }</p>").arg(complementResult.join(", "));
        allResults += "<p><b>Definition:</b> Elements in Universe but not in A</p><br>";
    }
    
    // Set relationships
    allResults += "<h3>📊 Set Relationships:</h3>";
    allResults += "<ul>";
    if (intersectionResult.isEmpty()) {
        allResults += "<li>A and B are <b>disjoint</b> (no common elements)</li>";
    } else {
        allResults += QString("<li>A and B have <b>%1 common element(s)</b></li>").arg(intersectionResult.size());
    }
    
    if (unionResult.size() == m_setA.size() + m_setB.size()) {
        allResults += "<li>A and B are completely separate (no overlap)</li>";
    }
    
    allResults += QString("<li>Cardinality |A| = %1, |B| = %2</li>").arg(m_setA.size()).arg(m_setB.size());
    allResults += QString("<li>|A ∪ B| = %1, |A ∩ B| = %2</li>").arg(unionResult.size()).arg(intersectionResult.size());
    allResults += "</ul>";
    
    m_operationResults->setHtml(allResults);
}

QStringList SetOperationsWidget::performUnion(const QStringList &setA, const QStringList &setB)
{
    QStringList result = setA;
    for (const QString &element : setB) {
        if (!result.contains(element)) {
            result.append(element);
        }
    }
    result.sort();
    return result;
}

QStringList SetOperationsWidget::performIntersection(const QStringList &setA, const QStringList &setB)
{
    QStringList result;
    for (const QString &element : setA) {
        if (setB.contains(element)) {
            result.append(element);
        }
    }
    result.sort();
    return result;
}

QStringList SetOperationsWidget::performDifference(const QStringList &setA, const QStringList &setB)
{
    QStringList result;
    for (const QString &element : setA) {
        if (!setB.contains(element)) {
            result.append(element);
        }
    }
    result.sort();
    return result;
}

QStringList SetOperationsWidget::performSymmetricDifference(const QStringList &setA, const QStringList &setB)
{
    QStringList result;
    
    // Elements in A but not in B
    for (const QString &element : setA) {
        if (!setB.contains(element)) {
            result.append(element);
        }
    }
    
    // Elements in B but not in A
    for (const QString &element : setB) {
        if (!setA.contains(element)) {
            result.append(element);
        }
    }
    
    result.sort();
    return result;
}

QStringList SetOperationsWidget::performComplement(const QStringList &set, const QStringList &universe)
{
    QStringList result;
    for (const QString &element : universe) {
        if (!set.contains(element)) {
            result.append(element);
        }
    }
    result.sort();
    return result;
}

void SetOperationsWidget::displayOperationResult(const QString &operation, const QStringList &result)
{
    QString display = QString("<h3>%1</h3>").arg(operation);
    display += QString("<p><b>Result:</b> { %1 }</p>").arg(result.join(", "));
    display += QString("<p><b>Cardinality:</b> %1</p>").arg(result.size());
    
    m_operationResults->setHtml(display);
}

void SetOperationsWidget::generateRandomSets()
{
    // Generate random sets with numbers
    m_setA.clear();
    m_setB.clear();
    
    // Generate Set A with 5-8 random numbers from 1-15
    int sizeA = QRandomGenerator::global()->bounded(5, 9);
    while (m_setA.size() < sizeA) {
        int num = QRandomGenerator::global()->bounded(1, 16);
        QString element = QString::number(num);
        if (!m_setA.contains(element)) {
            m_setA.append(element);
        }
    }
    
    // Generate Set B with 5-8 random numbers from 1-15
    int sizeB = QRandomGenerator::global()->bounded(5, 9);
    while (m_setB.size() < sizeB) {
        int num = QRandomGenerator::global()->bounded(1, 16);
        QString element = QString::number(num);
        if (!m_setB.contains(element)) {
            m_setB.append(element);
        }
    }
    
    m_setA.sort();
    m_setB.sort();
    updateSetDisplays();
}

void SetOperationsWidget::loadPresetSets()
{
    QString preset = m_presetComboBox->currentText();
    
    if (preset == "Numbers 1-10") {
        m_setA = QStringList{"1", "2", "3", "4", "5"};
        m_setB = QStringList{"4", "5", "6", "7", "8"};
        m_universe = QStringList{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    } else if (preset == "Letters A-J") {
        m_setA = QStringList{"A", "B", "C", "D"};
        m_setB = QStringList{"C", "D", "E", "F"};
        m_universe = QStringList{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    } else if (preset == "Programming Languages") {
        m_setA = QStringList{"C++", "Java", "Python", "JavaScript"};
        m_setB = QStringList{"Python", "JavaScript", "Go", "Rust"};
        m_universe = QStringList{"C++", "Java", "Python", "JavaScript", "Go", "Rust", "C#", "PHP", "Swift", "Kotlin"};
    } else if (preset == "Mathematics Topics") {
        m_setA = QStringList{"Algebra", "Geometry", "Calculus"};
        m_setB = QStringList{"Calculus", "Statistics", "Probability"};
        m_universe = QStringList{"Algebra", "Geometry", "Calculus", "Statistics", "Probability", "Discrete Math", "Linear Algebra"};
    }
    
    updateSetDisplays();
}

void SetOperationsWidget::showVennDiagram()
{
    QString diagram = generateVennDiagramText(m_setA, m_setB);
    m_vennDisplay->setHtml(diagram);
}

QString SetOperationsWidget::generateVennDiagramText(const QStringList &setA, const QStringList &setB)
{
    QString diagram = "<h2>📊 Venn Diagram Representation</h2>";
    diagram += "<div style='font-family: monospace; background-color: #1e1e1e; padding: 15px; border-radius: 8px;'>";
    
    // ASCII-style Venn diagram
    diagram += "<pre style='color: #4fc3f7;'>";
    diagram += "    Universe U\n";
    diagram += "   ┌─────────────────┐\n";
    diagram += "   │                 │\n";
    diagram += "   │  Set A      Set B │\n";
    diagram += "   │ ┌─────┐ ┌─────┐ │\n";
    diagram += "   │ │     │ │     │ │\n";
    diagram += "   │ │  A  │ │  B  │ │\n";
    diagram += "   │ │ only│∩│only │ │\n";
    diagram += "   │ │     │ │     │ │\n";
    diagram += "   │ └─────┘ └─────┘ │\n";
    diagram += "   │                 │\n";
    diagram += "   └─────────────────┘\n";
    diagram += "</pre>";
    
    diagram += "</div>";
    
    // Set content analysis
    QStringList onlyA = performDifference(m_setA, m_setB);
    QStringList onlyB = performDifference(m_setB, m_setA);
    QStringList intersection = performIntersection(m_setA, m_setB);
    QStringList complement = performComplement(performUnion(m_setA, m_setB), m_universe);
    
    diagram += "<h3>🔍 Venn Diagram Analysis:</h3>";
    diagram += "<table border='1' style='border-collapse: collapse; width: 100%;'>";
    diagram += "<tr style='background-color: #2a82da; color: white;'>";
    diagram += "<th>Region</th><th>Elements</th><th>Count</th></tr>";
    
    diagram += "<tr><td><b>Only in A (A - B)</b></td>";
    diagram += QString("<td>{ %1 }</td>").arg(onlyA.join(", "));
    diagram += QString("<td>%1</td></tr>").arg(onlyA.size());
    
    diagram += "<tr><td><b>Only in B (B - A)</b></td>";
    diagram += QString("<td>{ %1 }</td>").arg(onlyB.join(", "));
    diagram += QString("<td>%1</td></tr>").arg(onlyB.size());
    
    diagram += "<tr><td><b>In both A and B (A ∩ B)</b></td>";
    diagram += QString("<td>{ %1 }</td>").arg(intersection.join(", "));
    diagram += QString("<td>%1</td></tr>").arg(intersection.size());
    
    if (!m_universe.isEmpty()) {
        diagram += "<tr><td><b>Outside both (in U only)</b></td>";
        diagram += QString("<td>{ %1 }</td>").arg(complement.join(", "));
        diagram += QString("<td>%1</td></tr>").arg(complement.size());
    }
    
    diagram += "</table>";
    
    return diagram;
}

void SetOperationsWidget::checkSetProperties()
{
    QString properties = "<h2>🔍 Set Properties Analysis</h2>";
    
    // Basic properties
    properties += QString("<h3>Basic Properties:</h3>");
    properties += QString("<p><b>|A|</b> (Cardinality of A): %1</p>").arg(m_setA.size());
    properties += QString("<p><b>|B|</b> (Cardinality of B): %1</p>").arg(m_setB.size());
    
    if (!m_universe.isEmpty()) {
        properties += QString("<p><b>|U|</b> (Cardinality of Universe): %1</p>").arg(m_universe.size());
    }
    
    // Relationship properties
    properties += "<h3>Relationship Properties:</h3>";
    
    QStringList intersection = performIntersection(m_setA, m_setB);
    QStringList unionSet = performUnion(m_setA, m_setB);
    
    // Disjoint check
    if (intersection.isEmpty()) {
        properties += "<p>✅ <b>Disjoint Sets:</b> A and B have no common elements (A ∩ B = ∅)</p>";
    } else {
        properties += QString("<p>❌ <b>Not Disjoint:</b> A and B share %1 element(s)</p>").arg(intersection.size());
    }
    
    // Subset relationships
    bool aSubsetB = true, bSubsetA = true;
    for (const QString &element : m_setA) {
        if (!m_setB.contains(element)) {
            aSubsetB = false;
            break;
        }
    }
    
    for (const QString &element : m_setB) {
        if (!m_setA.contains(element)) {
            bSubsetA = false;
            break;
        }
    }
    
    if (aSubsetB && bSubsetA) {
        properties += "<p>✅ <b>Equal Sets:</b> A = B (same elements)</p>";
    } else if (aSubsetB) {
        properties += "<p>✅ <b>Subset:</b> A ⊆ B (A is a subset of B)</p>";
    } else if (bSubsetA) {
        properties += "<p>✅ <b>Subset:</b> B ⊆ A (B is a subset of A)</p>";
    } else {
        properties += "<p>❌ <b>No Subset Relationship:</b> Neither set is a subset of the other</p>";
    }
    
    // Mathematical laws verification
    if (m_showStepsCheckBox->isChecked()) {
        properties += "<h3>Set Theory Laws Verification:</h3>";
        
        // Commutative Law
        QStringList unionAB = performUnion(m_setA, m_setB);
        QStringList unionBA = performUnion(m_setB, m_setA);
        bool commutativeUnion = (unionAB == unionBA);
        
        QStringList intersectionAB = performIntersection(m_setA, m_setB);
        QStringList intersectionBA = performIntersection(m_setB, m_setA);
        bool commutativeIntersection = (intersectionAB == intersectionBA);
        
        properties += QString("<p><b>Commutative Law:</b></p>");
        properties += QString("<p>• Union: A ∪ B = B ∪ A → %1</p>").arg(commutativeUnion ? "✅ Verified" : "❌ Failed");
        properties += QString("<p>• Intersection: A ∩ B = B ∩ A → %1</p>").arg(commutativeIntersection ? "✅ Verified" : "❌ Failed");
    }
    
    m_propertiesDisplay->setHtml(properties);
}

void SetOperationsWidget::exportResults()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Set Operations Results", 
                                                   "set_operations.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 100);
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<html><head><title>Set Operations Analysis</title></head><body>";
        stream << "<h1>Set Operations Analysis Results</h1>";
        
        m_progressBar->setValue(25);
        
        stream << QString("<h2>Input Sets:</h2>");
        stream << QString("<p><b>Set A:</b> { %1 }</p>").arg(m_setA.join(", "));
        stream << QString("<p><b>Set B:</b> { %1 }</p>").arg(m_setB.join(", "));
        stream << QString("<p><b>Universe U:</b> { %1 }</p>").arg(m_universe.join(", "));
        
        m_progressBar->setValue(50);
        
        stream << "<h2>Operation Results:</h2>";
        stream << m_operationResults->toHtml();
        
        m_progressBar->setValue(75);
        
        stream << "<h2>Properties Analysis:</h2>";
        stream << m_propertiesDisplay->toHtml();
        
        stream << "</body></html>";
        
        m_progressBar->setValue(100);
        QMessageBox::information(this, "Export Complete", "Results exported successfully!");
    }
    
    m_progressBar->setVisible(false);
}

void SetOperationsWidget::onSetAChanged()
{
    // Auto-update operations if both sets have elements
    if (!m_setA.isEmpty() && !m_setB.isEmpty()) {
        updateOperationResults();
    }
}

void SetOperationsWidget::onSetBChanged()
{
    // Auto-update operations if both sets have elements
    if (!m_setA.isEmpty() && !m_setB.isEmpty()) {
        updateOperationResults();
    }
}

void SetOperationsWidget::updateOperationResults()
{
    // Optional: Auto-update basic operations
    // performAllOperations();
}