#include "FunctionsManagerWidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>

FunctionsManagerWidget::FunctionsManagerWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void FunctionsManagerWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Functions & Mappings Manager");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(m_mainSplitter);

    // Left panel - Input section
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Input group
    m_inputGroup = new QGroupBox("Function Mappings");
    QVBoxLayout *inputLayout = new QVBoxLayout(m_inputGroup);
    
    // Domain and codomain input
    QGridLayout *mappingLayout = new QGridLayout();
    mappingLayout->addWidget(new QLabel("Domain (from):"), 0, 0);
    m_domainInput = new QLineEdit();
    m_domainInput->setPlaceholderText("e.g., student1, x, a");
    mappingLayout->addWidget(m_domainInput, 0, 1);
    
    mappingLayout->addWidget(new QLabel("Codomain (to):"), 1, 0);
    m_codomainInput = new QLineEdit();
    m_codomainInput->setPlaceholderText("e.g., course1, y, b");
    mappingLayout->addWidget(m_codomainInput, 1, 1);
    
    inputLayout->addLayout(mappingLayout);
    
    // Control buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_addMappingBtn = new QPushButton("Add Mapping");
    m_addMappingBtn->setStyleSheet("QPushButton { background-color: #28a745; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_removeMappingBtn = new QPushButton("Remove Selected");
    m_clearBtn = new QPushButton("Clear All");
    
    buttonLayout->addWidget(m_addMappingBtn);
    buttonLayout->addWidget(m_removeMappingBtn);
    buttonLayout->addWidget(m_clearBtn);
    inputLayout->addLayout(buttonLayout);
    
    // Mappings table
    m_mappingsTable = new QTableWidget(0, 2);
    QStringList headers;
    headers << "Domain (From)" << "Codomain (To)";
    m_mappingsTable->setHorizontalHeaderLabels(headers);
    m_mappingsTable->horizontalHeader()->setStretchLastSection(true);
    m_mappingsTable->setMaximumHeight(200);
    inputLayout->addWidget(m_mappingsTable);
    
    leftLayout->addWidget(m_inputGroup);

    // Analysis group
    m_analysisGroup = new QGroupBox("Function Analysis");
    QVBoxLayout *analysisLayout = new QVBoxLayout(m_analysisGroup);
    
    m_checkAllBtn = new QPushButton("Analyze Function Properties");
    m_checkAllBtn->setStyleSheet("QPushButton { background-color: #2a82da; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    analysisLayout->addWidget(m_checkAllBtn);
    
    // Properties checkboxes
    QLabel *propsLabel = new QLabel("Function Properties:");
    propsLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    analysisLayout->addWidget(propsLabel);
    
    m_injectiveCheck = new QCheckBox("Injective (One-to-One)");
    m_surjectiveCheck = new QCheckBox("Surjective (Onto)");
    m_bijectiveCheck = new QCheckBox("Bijective (One-to-One & Onto)");
    
    m_injectiveCheck->setEnabled(false);
    m_surjectiveCheck->setEnabled(false);
    m_bijectiveCheck->setEnabled(false);
    
    analysisLayout->addWidget(m_injectiveCheck);
    analysisLayout->addWidget(m_surjectiveCheck);
    analysisLayout->addWidget(m_bijectiveCheck);
    
    // Additional buttons
    QHBoxLayout *extraButtonsLayout = new QHBoxLayout();
    m_generateExampleBtn = new QPushButton("Load Example");
    m_exportBtn = new QPushButton("Export Analysis");
    extraButtonsLayout->addWidget(m_generateExampleBtn);
    extraButtonsLayout->addWidget(m_exportBtn);
    analysisLayout->addLayout(extraButtonsLayout);
    
    leftLayout->addWidget(m_analysisGroup);
    leftLayout->addStretch();
    
    m_mainSplitter->addWidget(leftPanel);

    // Right panel - Results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    
    QLabel *resultsLabel = new QLabel("Function Analysis Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
    rightLayout->addWidget(resultsLabel);
    
    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    m_resultsDisplay->setStyleSheet("background-color: linear-gradient(to right, #ffecd2, #fcb69f); border: 1px solid #dee2e6; font-family: 'Consolas', monospace; font-size: 13px;");
    rightLayout->addWidget(m_resultsDisplay);
    
    m_mainSplitter->addWidget(rightPanel);
    m_mainSplitter->setSizes({400, 400});

    // Connect signals
    connect(m_addMappingBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::addMapping);
    connect(m_removeMappingBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::removeMapping);
    connect(m_clearBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::clearMappings);
    connect(m_checkAllBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::checkAllProperties);
    connect(m_generateExampleBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::generateExample);
    connect(m_exportBtn, &QPushButton::clicked, this, &FunctionsManagerWidget::exportResults);
    
    // Allow Enter key to add mappings
    connect(m_domainInput, &QLineEdit::returnPressed, this, &FunctionsManagerWidget::addMapping);
    connect(m_codomainInput, &QLineEdit::returnPressed, this, &FunctionsManagerWidget::addMapping);
    
    // Initial display
    m_resultsDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Add function mappings and click 'Analyze Function Properties' to see the analysis.</p>");
}

void FunctionsManagerWidget::addMapping()
{
    QString domain = m_domainInput->text().trimmed();
    QString codomain = m_codomainInput->text().trimmed();
    
    if (domain.isEmpty() || codomain.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both domain and codomain elements.");
        return;
    }
    
    // Check for duplicate mappings
    QPair<QString, QString> mapping(domain, codomain);
    if (m_mappings.contains(mapping)) {
        QMessageBox::warning(this, "Warning", "This mapping already exists.");
        return;
    }
    
    m_mappings.append(mapping);
    
    // Update domain and codomain sets
    if (!m_domainSet.contains(domain)) {
        m_domainSet.append(domain);
    }
    if (!m_codomainSet.contains(codomain)) {
        m_codomainSet.append(codomain);
    }
    
    // Add to table
    int row = m_mappingsTable->rowCount();
    m_mappingsTable->insertRow(row);
    m_mappingsTable->setItem(row, 0, new QTableWidgetItem(domain));
    m_mappingsTable->setItem(row, 1, new QTableWidgetItem(codomain));
    
    m_domainInput->clear();
    m_codomainInput->clear();
    m_domainInput->setFocus();
}

void FunctionsManagerWidget::removeMapping()
{
    int currentRow = m_mappingsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a mapping to remove.");
        return;
    }
    
    m_mappings.removeAt(currentRow);
    m_mappingsTable->removeRow(currentRow);
    
    // Rebuild domain and codomain sets
    m_domainSet.clear();
    m_codomainSet.clear();
    for (const auto &mapping : m_mappings) {
        if (!m_domainSet.contains(mapping.first)) {
            m_domainSet.append(mapping.first);
        }
        if (!m_codomainSet.contains(mapping.second)) {
            m_codomainSet.append(mapping.second);
        }
    }
}

void FunctionsManagerWidget::clearMappings()
{
    m_mappings.clear();
    m_domainSet.clear();
    m_codomainSet.clear();
    m_mappingsTable->setRowCount(0);
    m_resultsDisplay->clear();
    updatePropertiesDisplay();
    m_resultsDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Add function mappings and click 'Analyze Function Properties' to see the analysis.</p>");
}

void FunctionsManagerWidget::checkInjective()
{
    // Check if function is injective (one-to-one)
    QMap<QString, int> codomainCount;
    for (const auto &mapping : m_mappings) {
        codomainCount[mapping.second]++;
        if (codomainCount[mapping.second] > 1) {
            return; // Not injective
        }
    }
}

void FunctionsManagerWidget::checkSurjective()
{
    // Check if function is surjective (onto)
    // Every element in codomain must be mapped to
    for (const QString &codomainElement : m_codomainSet) {
        bool found = false;
        for (const auto &mapping : m_mappings) {
            if (mapping.second == codomainElement) {
                found = true;
                break;
            }
        }
        if (!found) {
            return; // Not surjective
        }
    }
}

void FunctionsManagerWidget::checkBijective()
{
    checkInjective();
    checkSurjective();
}

void FunctionsManagerWidget::checkAllProperties()
{
    if (m_mappings.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add some mappings first.");
        return;
    }
    
    QString results = "<h3>🔍 Function Analysis</h3><hr>";
    
    // Display function
    results += "<h4>Function Definition:</h4>";
    results += "<p><b>Domain:</b> {";
    for (int i = 0; i < m_domainSet.size(); ++i) {
        results += m_domainSet[i];
        if (i < m_domainSet.size() - 1) results += ", ";
    }
    results += "}</p>";
    
    results += "<p><b>Codomain:</b> {";
    for (int i = 0; i < m_codomainSet.size(); ++i) {
        results += m_codomainSet[i];
        if (i < m_codomainSet.size() - 1) results += ", ";
    }
    results += "}</p>";
    
    results += "<p><b>Mappings:</b></p>";
    results += "<div style='background-color: #f8f9fa; padding: 10px; margin: 10px 0; border-radius: 4px;'>";
    for (const auto &mapping : m_mappings) {
        results += QString("f(%1) = %2<br>").arg(mapping.first).arg(mapping.second);
    }
    results += "</div>";
    
    // Check properties
    bool injective = true;
    bool surjective = true;
    
    // Check injective (one-to-one)
    QMap<QString, QStringList> codomainTodomains;
    for (const auto &mapping : m_mappings) {
        codomainTodomains[mapping.second].append(mapping.first);
    }
    
    for (auto it = codomainTodomains.begin(); it != codomainTodomains.end(); ++it) {
        if (it.value().size() > 1) {
            injective = false;
            break;
        }
    }
    
    // Check surjective (onto)
    for (const QString &codomainElement : m_codomainSet) {
        if (!codomainTodomains.contains(codomainElement)) {
            surjective = false;
            break;
        }
    }
    
    bool bijective = injective && surjective;
    
    // Display results
    results += "<h4>Function Properties:</h4>";
    results += QString("<p>• <b>Injective (One-to-One):</b> %1</p>")
               .arg(injective ? "<span style='color: #28a745;'>YES</span>" : "<span style='color: #dc3545;'>NO</span>");
    results += QString("<p>• <b>Surjective (Onto):</b> %1</p>")
               .arg(surjective ? "<span style='color: #28a745;'>YES</span>" : "<span style='color: #dc3545;'>NO</span>");
    results += QString("<p>• <b>Bijective:</b> %1</p>")
               .arg(bijective ? "<span style='color: #28a745;'>YES</span>" : "<span style='color: #dc3545;'>NO</span>");
    
    // Explanation
    results += "<br><h4>Analysis:</h4>";
    if (!injective) {
        results += "<p style='color: #dc3545;'>❌ <b>Not Injective:</b> Multiple domain elements map to the same codomain element.</p>";
    } else {
        results += "<p style='color: #28a745;'>✅ <b>Injective:</b> Each domain element maps to a unique codomain element.</p>";
    }
    
    if (!surjective) {
        results += "<p style='color: #dc3545;'>❌ <b>Not Surjective:</b> Some codomain elements are not mapped to by any domain element.</p>";
    } else {
        results += "<p style='color: #28a745;'>✅ <b>Surjective:</b> Every codomain element is mapped to by at least one domain element.</p>";
    }
    
    if (bijective) {
        results += "<p style='color: #2a82da; font-weight: bold;'>🎯 <b>Bijective Function:</b> This function has an inverse!</p>";
    }
    
    m_resultsDisplay->setHtml(results);
    updatePropertiesDisplay();
}

void FunctionsManagerWidget::updatePropertiesDisplay()
{
    if (m_mappings.isEmpty()) {
        m_injectiveCheck->setChecked(false);
        m_surjectiveCheck->setChecked(false);
        m_bijectiveCheck->setChecked(false);
        return;
    }
    
    // Check properties
    bool injective = true;
    bool surjective = true;
    
    QMap<QString, int> codomainCount;
    for (const auto &mapping : m_mappings) {
        codomainCount[mapping.second]++;
        if (codomainCount[mapping.second] > 1) {
            injective = false;
        }
    }
    
    for (const QString &codomainElement : m_codomainSet) {
        if (codomainCount[codomainElement] == 0) {
            surjective = false;
        }
    }
    
    m_injectiveCheck->setChecked(injective);
    m_surjectiveCheck->setChecked(surjective);
    m_bijectiveCheck->setChecked(injective && surjective);
}

void FunctionsManagerWidget::generateExample()
{
    clearMappings();
    
    // Add example mappings for a bijective function
    m_mappings.append(QPair<QString, QString>("student1", "course1"));
    m_mappings.append(QPair<QString, QString>("student2", "course2"));
    m_mappings.append(QPair<QString, QString>("student3", "course3"));
    
    m_domainSet << "student1" << "student2" << "student3";
    m_codomainSet << "course1" << "course2" << "course3";
    
    // Update table
    for (int i = 0; i < m_mappings.size(); ++i) {
        m_mappingsTable->insertRow(i);
        m_mappingsTable->setItem(i, 0, new QTableWidgetItem(m_mappings[i].first));
        m_mappingsTable->setItem(i, 1, new QTableWidgetItem(m_mappings[i].second));
    }
    
    QMessageBox::information(this, "Example Loaded", "Loaded an example bijective function. Click 'Analyze Function Properties' to see the analysis.");
}

void FunctionsManagerWidget::exportResults()
{
    if (m_resultsDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No results to export. Please run the analysis first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Function Analysis", "function_analysis.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Function Analysis</title>";
        stream << "<style>body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }</style>";
        stream << "</head><body>";
        stream << m_resultsDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Analysis exported successfully!");
    }
}
