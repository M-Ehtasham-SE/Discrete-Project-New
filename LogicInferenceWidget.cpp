#include "LogicInferenceWidget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>

LogicInferenceWidget::LogicInferenceWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void LogicInferenceWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Logic Inference Engine");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(m_mainSplitter);

    // Left panel - Input sections
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Rules section
    m_rulesGroup = new QGroupBox("Inference Rules (IF-THEN)");
    QVBoxLayout *rulesLayout = new QVBoxLayout(m_rulesGroup);
    
    QGridLayout *ruleInputLayout = new QGridLayout();
    ruleInputLayout->addWidget(new QLabel("IF (Premise):"), 0, 0);
    m_premiseInput = new QLineEdit();
    m_premiseInput->setPlaceholderText("e.g., it is raining");
    ruleInputLayout->addWidget(m_premiseInput, 0, 1);
    
    ruleInputLayout->addWidget(new QLabel("THEN (Conclusion):"), 1, 0);
    m_conclusionInput = new QLineEdit();
    m_conclusionInput->setPlaceholderText("e.g., ground is wet");
    ruleInputLayout->addWidget(m_conclusionInput, 1, 1);
    
    rulesLayout->addLayout(ruleInputLayout);
    
    QHBoxLayout *ruleButtonsLayout = new QHBoxLayout();
    m_addRuleBtn = new QPushButton("Add Rule");
    m_addRuleBtn->setStyleSheet("QPushButton { background-color: #28a745; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_removeRuleBtn = new QPushButton("Remove Selected");
    m_clearRulesBtn = new QPushButton("Clear All");
    
    ruleButtonsLayout->addWidget(m_addRuleBtn);
    ruleButtonsLayout->addWidget(m_removeRuleBtn);
    ruleButtonsLayout->addWidget(m_clearRulesBtn);
    rulesLayout->addLayout(ruleButtonsLayout);
    
    m_rulesTable = new QTableWidget(0, 2);
    QStringList ruleHeaders;
    ruleHeaders << "Premise (IF)" << "Conclusion (THEN)";
    m_rulesTable->setHorizontalHeaderLabels(ruleHeaders);
    m_rulesTable->horizontalHeader()->setStretchLastSection(true);
    m_rulesTable->setMaximumHeight(150);
    rulesLayout->addWidget(m_rulesTable);
    
    leftLayout->addWidget(m_rulesGroup);

    // Facts section
    m_factsGroup = new QGroupBox("Known Facts");
    QVBoxLayout *factsLayout = new QVBoxLayout(m_factsGroup);
    
    QHBoxLayout *factInputLayout = new QHBoxLayout();
    m_factInput = new QLineEdit();
    m_factInput->setPlaceholderText("e.g., it is raining");
    m_addFactBtn = new QPushButton("Add Fact");
    m_addFactBtn->setStyleSheet("QPushButton { background-color: #007bff; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    
    factInputLayout->addWidget(m_factInput);
    factInputLayout->addWidget(m_addFactBtn);
    factsLayout->addLayout(factInputLayout);
    
    QHBoxLayout *factButtonsLayout = new QHBoxLayout();
    m_removeFactBtn = new QPushButton("Remove Selected");
    m_clearFactsBtn = new QPushButton("Clear All");
    factButtonsLayout->addWidget(m_removeFactBtn);
    factButtonsLayout->addWidget(m_clearFactsBtn);
    factButtonsLayout->addStretch();
    factsLayout->addLayout(factButtonsLayout);
    
    m_factsList = new QListWidget();
    m_factsList->setMaximumHeight(120);
    factsLayout->addWidget(m_factsList);
    
    leftLayout->addWidget(m_factsGroup);

    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_runInferenceBtn = new QPushButton("Run Inference Engine");
    m_runInferenceBtn->setStyleSheet("QPushButton { background-color: #dc3545; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    m_loadExampleBtn = new QPushButton("Load Example");
    
    controlLayout->addWidget(m_runInferenceBtn);
    controlLayout->addWidget(m_loadExampleBtn);
    leftLayout->addLayout(controlLayout);
    
    leftLayout->addStretch();
    m_mainSplitter->addWidget(leftPanel);

    // Right panel - Results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    
    QLabel *resultsLabel = new QLabel("Inference Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
    rightLayout->addWidget(resultsLabel);
    
    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    m_resultsDisplay->setStyleSheet("background-color: #2b2b2b; color: #ffffff; border: 1px solid #555; font-family: 'Consolas', monospace; font-size: 13px;");
    rightLayout->addWidget(m_resultsDisplay);
    
    // Export buttons
    QHBoxLayout *exportLayout = new QHBoxLayout();
    m_exportBtn = new QPushButton("Export Results");
    m_clearResultsBtn = new QPushButton("Clear Results");
    exportLayout->addWidget(m_clearResultsBtn);
    exportLayout->addWidget(m_exportBtn);
    exportLayout->addStretch();
    rightLayout->addLayout(exportLayout);
    
    m_mainSplitter->addWidget(rightPanel);
    m_mainSplitter->setSizes({400, 400});

    // Connect signals
    connect(m_addRuleBtn, &QPushButton::clicked, this, &LogicInferenceWidget::addRule);
    connect(m_removeRuleBtn, &QPushButton::clicked, this, &LogicInferenceWidget::removeRule);
    connect(m_clearRulesBtn, &QPushButton::clicked, this, &LogicInferenceWidget::clearRules);
    connect(m_addFactBtn, &QPushButton::clicked, this, &LogicInferenceWidget::addFact);
    connect(m_removeFactBtn, &QPushButton::clicked, this, &LogicInferenceWidget::removeFact);
    connect(m_clearFactsBtn, &QPushButton::clicked, this, &LogicInferenceWidget::clearFacts);
    connect(m_runInferenceBtn, &QPushButton::clicked, this, &LogicInferenceWidget::runInference);
    connect(m_loadExampleBtn, &QPushButton::clicked, this, &LogicInferenceWidget::loadExample);
    connect(m_exportBtn, &QPushButton::clicked, this, &LogicInferenceWidget::exportResults);
    connect(m_clearResultsBtn, &QPushButton::clicked, this, &LogicInferenceWidget::clearResults);
    
    // Allow Enter key to add items
    connect(m_premiseInput, &QLineEdit::returnPressed, this, &LogicInferenceWidget::addRule);
    connect(m_conclusionInput, &QLineEdit::returnPressed, this, &LogicInferenceWidget::addRule);
    connect(m_factInput, &QLineEdit::returnPressed, this, &LogicInferenceWidget::addFact);
    
    // Initial display
    m_resultsDisplay->setHtml("<p style='color: #cccccc; text-align: center; margin-top: 50px;'>Add inference rules and known facts, then click 'Run Inference Engine' to see the logical deductions.</p>");
}

void LogicInferenceWidget::addRule()
{
    QString premise = m_premiseInput->text().trimmed();
    QString conclusion = m_conclusionInput->text().trimmed();
    
    if (premise.isEmpty() || conclusion.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both premise and conclusion.");
        return;
    }
    
    QPair<QString, QString> rule(premise, conclusion);
    if (m_rules.contains(rule)) {
        QMessageBox::warning(this, "Warning", "This rule already exists.");
        return;
    }
    
    m_rules.append(rule);
    
    int row = m_rulesTable->rowCount();
    m_rulesTable->insertRow(row);
    m_rulesTable->setItem(row, 0, new QTableWidgetItem(premise));
    m_rulesTable->setItem(row, 1, new QTableWidgetItem(conclusion));
    
    m_premiseInput->clear();
    m_conclusionInput->clear();
    m_premiseInput->setFocus();
}

void LogicInferenceWidget::removeRule()
{
    int currentRow = m_rulesTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a rule to remove.");
        return;
    }
    
    m_rules.removeAt(currentRow);
    m_rulesTable->removeRow(currentRow);
}

void LogicInferenceWidget::clearRules()
{
    m_rules.clear();
    m_rulesTable->setRowCount(0);
}

void LogicInferenceWidget::addFact()
{
    QString fact = m_factInput->text().trimmed();
    if (fact.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a fact.");
        return;
    }
    
    if (m_facts.contains(fact)) {
        QMessageBox::warning(this, "Warning", "This fact already exists.");
        return;
    }
    
    m_facts.append(fact);
    m_factsList->addItem(fact);
    m_factInput->clear();
    m_factInput->setFocus();
}

void LogicInferenceWidget::removeFact()
{
    int currentRow = m_factsList->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a fact to remove.");
        return;
    }
    
    m_facts.removeAt(currentRow);
    delete m_factsList->takeItem(currentRow);
}

void LogicInferenceWidget::clearFacts()
{
    m_facts.clear();
    m_factsList->clear();
}

void LogicInferenceWidget::runInference()
{
    if (m_rules.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add some inference rules first.");
        return;
    }
    
    if (m_facts.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add some known facts first.");
        return;
    }
    
    QString results = "<div style='background-color: #2b2b2b; color: #ffffff; padding: 15px;'>";
    results += "<h3 style='color: #4CAF50;'>🧠 Logic Inference Engine Results</h3>";
    results += "<hr style='border-color: #555;'>";
    
    // Display initial facts
    results += "<h4 style='color: #2196F3;'>Initial Known Facts:</h4>";
    results += "<ul style='color: #cccccc;'>";
    for (const QString &fact : m_facts) {
        results += QString("<li>%1</li>").arg(fact);
    }
    results += "</ul>";
    
    // Display rules
    results += "<h4 style='color: #2196F3;'>Inference Rules:</h4>";
    results += "<ul style='color: #cccccc;'>";
    for (const auto &rule : m_rules) {
        results += QString("<li><b>IF</b> %1 <b>THEN</b> %2</li>").arg(rule.first).arg(rule.second);
    }
    results += "</ul>";
    
    // Run inference
    QStringList allFacts = m_facts;
    QStringList newlyInferred;
    
    results += "<h4 style='color: #FF9800;'>Inference Process:</h4>";
    results += "<div style='background-color: #1e1e1e; padding: 10px; border-radius: 4px; margin: 10px 0;'>";
    
    bool changed = true;
    int iteration = 1;
    
    while (changed) {
        changed = false;
        results += QString("<p style='color: #FFC107;'><b>Iteration %1:</b></p>").arg(iteration);
        
        for (const auto &rule : m_rules) {
            if (allFacts.contains(rule.first)) {  // If premise is known
                if (!allFacts.contains(rule.second)) {  // And conclusion is not yet known
                    allFacts.append(rule.second);
                    newlyInferred.append(rule.second);
                    changed = true;
                    results += QString("<p style='color: #4CAF50; margin-left: 20px;'>✅ Applied rule: <b>IF</b> %1 <b>THEN</b> %2</p>")
                               .arg(rule.first).arg(rule.second);
                    results += QString("<p style='color: #8BC34A; margin-left: 40px;'>→ Inferred: <b>%1</b></p>").arg(rule.second);
                }
            }
        }
        
        if (!changed) {
            results += "<p style='color: #9E9E9E; margin-left: 20px;'>No new facts can be inferred.</p>";
        }
        
        iteration++;
        if (iteration > 10) break; // Prevent infinite loops
    }
    
    results += "</div>";
    
    // Final results
    results += "<h4 style='color: #4CAF50;'>Final Results:</h4>";
    results += QString("<p style='color: #cccccc;'><b>Total facts discovered:</b> %1</p>").arg(allFacts.size());
    results += QString("<p style='color: #cccccc;'><b>Newly inferred facts:</b> %1</p>").arg(newlyInferred.size());
    
    if (!newlyInferred.isEmpty()) {
        results += "<h5 style='color: #4CAF50;'>Newly Inferred Facts:</h5>";
        results += "<ul style='color: #8BC34A;'>";
        for (const QString &fact : newlyInferred) {
            results += QString("<li><b>%1</b></li>").arg(fact);
        }
        results += "</ul>";
    }
    
    results += "<h5 style='color: #2196F3;'>All Known Facts (Original + Inferred):</h5>";
    results += "<ul style='color: #cccccc;'>";
    for (const QString &fact : allFacts) {
        QString style = newlyInferred.contains(fact) ? "color: #8BC34A; font-weight: bold;" : "color: #cccccc;";
        results += QString("<li style='%1'>%2</li>").arg(style).arg(fact);
    }
    results += "</ul>";
    
    results += "</div>";
    
    m_inferredFacts = newlyInferred;
    m_resultsDisplay->setHtml(results);
}

void LogicInferenceWidget::loadExample()
{
    clearRules();
    clearFacts();
    
    // Add example rules
    m_rules.append(QPair<QString, QString>("it is raining", "ground is wet"));
    m_rules.append(QPair<QString, QString>("ground is wet", "cannot play football"));
    m_rules.append(QPair<QString, QString>("student studies hard", "student passes exam"));
    m_rules.append(QPair<QString, QString>("student passes exam", "student graduates"));
    
    // Update rules table
    for (int i = 0; i < m_rules.size(); ++i) {
        m_rulesTable->insertRow(i);
        m_rulesTable->setItem(i, 0, new QTableWidgetItem(m_rules[i].first));
        m_rulesTable->setItem(i, 1, new QTableWidgetItem(m_rules[i].second));
    }
    
    // Add example facts
    m_facts << "it is raining" << "student studies hard";
    m_factsList->addItems(m_facts);
    
    QMessageBox::information(this, "Example Loaded", "Loaded example inference rules and facts. Click 'Run Inference Engine' to see the logical deductions.");
}

void LogicInferenceWidget::exportResults()
{
    if (m_resultsDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No results to export. Please run inference first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Inference Results", "logic_inference.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Logic Inference Results</title>";
        stream << "<style>body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; background-color: #2b2b2b; color: #ffffff; }</style>";
        stream << "</head><body>";
        stream << m_resultsDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Results exported successfully!");
    }
}

void LogicInferenceWidget::clearResults()
{
    m_resultsDisplay->clear();
    m_inferredFacts.clear();
    m_resultsDisplay->setHtml("<p style='color: #cccccc; text-align: center; margin-top: 50px;'>Add inference rules and known facts, then click 'Run Inference Engine' to see the logical deductions.</p>");
}