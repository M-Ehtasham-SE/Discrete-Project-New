#include "RelationPropertiesWidget.h"
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>

RelationPropertiesWidget::RelationPropertiesWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void RelationPropertiesWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Relation Properties Checker");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(m_mainSplitter);

    // Left panel - Input section
    QWidget *leftPanel = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Set input group
    m_setGroup = new QGroupBox("Set Elements");
    QVBoxLayout *setLayout = new QVBoxLayout(m_setGroup);
    
    QHBoxLayout *setInputLayout = new QHBoxLayout();
    m_setElementInput = new QLineEdit();
    m_setElementInput->setPlaceholderText("Enter set element (e.g., a, b, c, 1, 2, 3)");
    m_addSetBtn = new QPushButton("Add Element");
    m_removeSetBtn = new QPushButton("Remove Selected");
    m_clearSetBtn = new QPushButton("Clear All");
    
    setInputLayout->addWidget(m_setElementInput);
    setInputLayout->addWidget(m_addSetBtn);
    setLayout->addLayout(setInputLayout);
    
    QHBoxLayout *setButtonsLayout = new QHBoxLayout();
    setButtonsLayout->addWidget(m_removeSetBtn);
    setButtonsLayout->addWidget(m_clearSetBtn);
    setButtonsLayout->addStretch();
    setLayout->addLayout(setButtonsLayout);
    
    m_setList = new QListWidget();
    m_setList->setMaximumHeight(120);
    setLayout->addWidget(m_setList);
    
    leftLayout->addWidget(m_setGroup);

    // Relations input group
    m_relationsGroup = new QGroupBox("Relations (Ordered Pairs)");
    QVBoxLayout *relLayout = new QVBoxLayout(m_relationsGroup);
    
    QHBoxLayout *relInputLayout = new QHBoxLayout();
    m_relationFromInput = new QLineEdit();
    m_relationFromInput->setPlaceholderText("From element");
    QLabel *arrowLabel = new QLabel("→");
    arrowLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    m_relationToInput = new QLineEdit();
    m_relationToInput->setPlaceholderText("To element");
    m_addRelationBtn = new QPushButton("Add Relation");
    
    relInputLayout->addWidget(m_relationFromInput);
    relInputLayout->addWidget(arrowLabel);
    relInputLayout->addWidget(m_relationToInput);
    relInputLayout->addWidget(m_addRelationBtn);
    relLayout->addLayout(relInputLayout);
    
    QHBoxLayout *relButtonsLayout = new QHBoxLayout();
    m_removeRelationBtn = new QPushButton("Remove Selected");
    m_clearRelationsBtn = new QPushButton("Clear All");
    relButtonsLayout->addWidget(m_removeRelationBtn);
    relButtonsLayout->addWidget(m_clearRelationsBtn);
    relButtonsLayout->addStretch();
    relLayout->addLayout(relButtonsLayout);
    
    m_relationsTable = new QTableWidget(0, 2);
    QStringList headers;
    headers << "From" << "To";
    m_relationsTable->setHorizontalHeaderLabels(headers);
    m_relationsTable->horizontalHeader()->setStretchLastSection(true);
    m_relationsTable->setMaximumHeight(150);
    relLayout->addWidget(m_relationsTable);
    
    leftLayout->addWidget(m_relationsGroup);

    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_checkAllBtn = new QPushButton("Check All Properties");
    m_checkAllBtn->setStyleSheet("QPushButton { background-color: linear-gradient(to right, #ffecd2, #fcb69f); color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_exampleBtn = new QPushButton("Load Example");
    m_exportBtn = new QPushButton("Export Results");
    
    controlLayout->addWidget(m_checkAllBtn);
    controlLayout->addWidget(m_exampleBtn);
    controlLayout->addWidget(m_exportBtn);
    leftLayout->addLayout(controlLayout);
    
    leftLayout->addStretch();
    m_mainSplitter->addWidget(leftPanel);

    // Right panel - Analysis and results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    // Properties display
    QGroupBox *propsGroup = new QGroupBox("Properties Analysis");
    QGridLayout *propsLayout = new QGridLayout(propsGroup);
    
    m_reflexiveCheck = new QCheckBox("Reflexive");
    m_symmetricCheck = new QCheckBox("Symmetric");
    m_transitiveCheck = new QCheckBox("Transitive");
    m_antisymmetricCheck = new QCheckBox("Anti-symmetric");
    
    // Make checkboxes read-only
    m_reflexiveCheck->setEnabled(false);
    m_symmetricCheck->setEnabled(false);
    m_transitiveCheck->setEnabled(false);
    m_antisymmetricCheck->setEnabled(false);
    
    propsLayout->addWidget(m_reflexiveCheck, 0, 0);
    propsLayout->addWidget(m_symmetricCheck, 0, 1);
    propsLayout->addWidget(m_transitiveCheck, 1, 0);
    propsLayout->addWidget(m_antisymmetricCheck, 1, 1);
    
    rightLayout->addWidget(propsGroup);

    // Results display
    QLabel *resultsLabel = new QLabel("Analysis Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    rightLayout->addWidget(resultsLabel);
    
    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    m_resultsDisplay->setStyleSheet("background-color: linear-gradient(to right, #ffecd2, #fcb69f); border: 1px solid #dee2e6; font-family: 'Consolas', monospace;");
    rightLayout->addWidget(m_resultsDisplay);
    
    m_mainSplitter->addWidget(rightPanel);
    m_mainSplitter->setSizes({350, 450});

    // Connect signals
    connect(m_addSetBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::addSetElement);
    connect(m_removeSetBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::removeSetElement);
    connect(m_clearSetBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::clearSet);
    connect(m_addRelationBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::addRelationPair);
    connect(m_removeRelationBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::removeRelationPair);
    connect(m_clearRelationsBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::clearRelations);
    connect(m_checkAllBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::checkAllProperties);
    connect(m_exportBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::exportResults);
    connect(m_exampleBtn, &QPushButton::clicked, this, &RelationPropertiesWidget::generateExample);
    
    // Allow Enter key to add elements
    connect(m_setElementInput, &QLineEdit::returnPressed, this, &RelationPropertiesWidget::addSetElement);
    connect(m_relationFromInput, &QLineEdit::returnPressed, this, &RelationPropertiesWidget::addRelationPair);
    connect(m_relationToInput, &QLineEdit::returnPressed, this, &RelationPropertiesWidget::addRelationPair);
}

void RelationPropertiesWidget::addSetElement()
{
    QString element = m_setElementInput->text().trimmed();
    if (element.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a set element.");
        return;
    }
    
    if (m_setElements.contains(element)) {
        QMessageBox::warning(this, "Warning", "Element already exists in the set.");
        return;
    }
    
    m_setElements.append(element);
    m_setList->addItem(element);
    m_setElementInput->clear();
    m_setElementInput->setFocus();
}

void RelationPropertiesWidget::removeSetElement()
{
    int currentRow = m_setList->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select an element to remove.");
        return;
    }
    
    m_setElements.removeAt(currentRow);
    delete m_setList->takeItem(currentRow);
}

void RelationPropertiesWidget::clearSet()
{
    m_setElements.clear();
    m_setList->clear();
    m_resultsDisplay->clear();
    updatePropertiesDisplay();
}

void RelationPropertiesWidget::addRelationPair()
{
    QString fromElement = m_relationFromInput->text().trimmed();
    QString toElement = m_relationToInput->text().trimmed();
    
    if (fromElement.isEmpty() || toElement.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both elements of the relation.");
        return;
    }
    
    // Check if elements are in the set
    if (!m_setElements.contains(fromElement) || !m_setElements.contains(toElement)) {
        QMessageBox::warning(this, "Warning", "Both elements must be in the set. Add them to the set first.");
        return;
    }
    
    QPair<QString, QString> relation(fromElement, toElement);
    if (m_relations.contains(relation)) {
        QMessageBox::warning(this, "Warning", "This relation already exists.");
        return;
    }
    
    m_relations.append(relation);
    
    int row = m_relationsTable->rowCount();
    m_relationsTable->insertRow(row);
    m_relationsTable->setItem(row, 0, new QTableWidgetItem(fromElement));
    m_relationsTable->setItem(row, 1, new QTableWidgetItem(toElement));
    
    m_relationFromInput->clear();
    m_relationToInput->clear();
    m_relationFromInput->setFocus();
}

void RelationPropertiesWidget::removeRelationPair()
{
    int currentRow = m_relationsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a relation to remove.");
        return;
    }
    
    m_relations.removeAt(currentRow);
    m_relationsTable->removeRow(currentRow);
}

void RelationPropertiesWidget::clearRelations()
{
    m_relations.clear();
    m_relationsTable->setRowCount(0);
    m_resultsDisplay->clear();
    updatePropertiesDisplay();
}

void RelationPropertiesWidget::checkAllProperties()
{
    if (m_setElements.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add elements to the set first.");
        return;
    }
    
    QString results = "<h3>Relation Properties Analysis</h3>";
    results += "<hr>";
    
    // Display set
    results += "<p><b>Set:</b> {";
    for (int i = 0; i < m_setElements.size(); ++i) {
        results += m_setElements[i];
        if (i < m_setElements.size() - 1) results += ", ";
    }
    results += "}</p>";
    
    // Display relation
    results += "<p><b>Relation R:</b> {";
    for (int i = 0; i < m_relations.size(); ++i) {
        results += QString("(%1,%2)").arg(m_relations[i].first).arg(m_relations[i].second);
        if (i < m_relations.size() - 1) results += ", ";
    }
    results += "}</p><br>";
    
    // Check properties
    bool reflexive = isReflexive();
    bool symmetric = isSymmetric();
    bool transitive = isTransitive();
    bool antisymmetric = isAntiSymmetric();
    
    results += "<h4>Properties:</h4>";
    results += QString("<p>• <b>Reflexive:</b> %1</p>").arg(reflexive ? "<span style='color: green;'>YES</span>" : "<span style='color: red;'>NO</span>");
    results += QString("<p>• <b>Symmetric:</b> %1</p>").arg(symmetric ? "<span style='color: green;'>YES</span>" : "<span style='color: red;'>NO</span>");
    results += QString("<p>• <b>Transitive:</b> %1</p>").arg(transitive ? "<span style='color: green;'>YES</span>" : "<span style='color: red;'>NO</span>");
    results += QString("<p>• <b>Anti-symmetric:</b> %1</p>").arg(antisymmetric ? "<span style='color: green;'>YES</span>" : "<span style='color: red;'>NO</span>");
    
    // Determine relation type
    QString relationType = getRelationType();
    results += QString("<br><h4>Relation Type:</h4><p style='color: #2a82da; font-weight: bold;'>%1</p>").arg(relationType);
    
    m_resultsDisplay->setHtml(results);
    updatePropertiesDisplay();
}

void RelationPropertiesWidget::updatePropertiesDisplay()
{
    if (m_setElements.isEmpty() || m_relations.isEmpty()) {
        m_reflexiveCheck->setChecked(false);
        m_symmetricCheck->setChecked(false);
        m_transitiveCheck->setChecked(false);
        m_antisymmetricCheck->setChecked(false);
        return;
    }
    
    m_reflexiveCheck->setChecked(isReflexive());
    m_symmetricCheck->setChecked(isSymmetric());
    m_transitiveCheck->setChecked(isTransitive());
    m_antisymmetricCheck->setChecked(isAntiSymmetric());
}

bool RelationPropertiesWidget::isReflexive()
{
    for (const QString &element : m_setElements) {
        bool found = false;
        for (const auto &relation : m_relations) {
            if (relation.first == element && relation.second == element) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool RelationPropertiesWidget::isSymmetric()
{
    for (const auto &relation : m_relations) {
        bool found = false;
        QPair<QString, QString> symmetric(relation.second, relation.first);
        if (m_relations.contains(symmetric)) {
            found = true;
        }
        if (!found) return false;
    }
    return true;
}

bool RelationPropertiesWidget::isTransitive()
{
    for (const auto &rel1 : m_relations) {
        for (const auto &rel2 : m_relations) {
            if (rel1.second == rel2.first) {
                QPair<QString, QString> transitive(rel1.first, rel2.second);
                if (!m_relations.contains(transitive)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool RelationPropertiesWidget::isAntiSymmetric()
{
    for (const auto &relation : m_relations) {
        QPair<QString, QString> symmetric(relation.second, relation.first);
        if (m_relations.contains(symmetric)) {
            if (relation.first != relation.second) {
                return false;
            }
        }
    }
    return true;
}

QString RelationPropertiesWidget::getRelationType()
{
    bool reflexive = isReflexive();
    bool symmetric = isSymmetric();
    bool transitive = isTransitive();
    bool antisymmetric = isAntiSymmetric();
    
    if (reflexive && symmetric && transitive) {
        return "EQUIVALENCE RELATION";
    } else if (reflexive && antisymmetric && transitive) {
        return "PARTIAL ORDER RELATION";
    } else {
        return "GENERAL RELATION";
    }
}

void RelationPropertiesWidget::exportResults()
{
    if (m_resultsDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No results to export. Please run the analysis first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Results", "relation_analysis.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Relation Properties Analysis</title></head><body>";
        stream << m_resultsDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Results exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save file.");
    }
}

void RelationPropertiesWidget::generateExample()
{
    clearSet();
    clearRelations();
    
    // Add example set elements
    m_setElements << "a" << "b" << "c";
    m_setList->addItems(m_setElements);
    
    // Add example relations for equivalence relation
    m_relations.append(QPair<QString, QString>("a", "a"));
    m_relations.append(QPair<QString, QString>("b", "b"));
    m_relations.append(QPair<QString, QString>("c", "c"));
    m_relations.append(QPair<QString, QString>("a", "b"));
    m_relations.append(QPair<QString, QString>("b", "a"));
    
    // Update relations table
    m_relationsTable->setRowCount(0);
    for (int i = 0; i < m_relations.size(); ++i) {
        m_relationsTable->insertRow(i);
        m_relationsTable->setItem(i, 0, new QTableWidgetItem(m_relations[i].first));
        m_relationsTable->setItem(i, 1, new QTableWidgetItem(m_relations[i].second));
    }
    
    QMessageBox::information(this, "Example Loaded", "Loaded an example relation. Click 'Check All Properties' to analyze it.");
}
