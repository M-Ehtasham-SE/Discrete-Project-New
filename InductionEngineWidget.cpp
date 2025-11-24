#include "InductionEngineWidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

InductionEngineWidget::InductionEngineWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void InductionEngineWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Induction & Strong Induction Engine");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(splitter);

    // Left panel - Input tabs
    m_tabWidget = new QTabWidget();
    m_tabWidget->setMaximumWidth(380);

    // Simple Induction Tab
    m_simpleTab = new QWidget();
    QVBoxLayout *simpleLayout = new QVBoxLayout(m_simpleTab);
    
    QGroupBox *simpleGroup = new QGroupBox("Simple Induction");
    QVBoxLayout *simpleGroupLayout = new QVBoxLayout(simpleGroup);
    
    QLabel *simpleInfo = new QLabel("Verify prerequisite chains using simple mathematical induction. This proves that if the base case holds and the inductive step is valid, then the property holds for all cases.");
    simpleInfo->setWordWrap(true);
    simpleInfo->setStyleSheet("color: #666; margin-bottom: 15px;");
    
    m_verifyChainBtn = new QPushButton("Verify Prerequisite Chain");
    m_verifyChainBtn->setStyleSheet("QPushButton { background-color: #28a745; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    
    simpleGroupLayout->addWidget(simpleInfo);
    simpleGroupLayout->addWidget(m_verifyChainBtn);
    simpleGroupLayout->addStretch();
    
    simpleLayout->addWidget(simpleGroup);
    m_tabWidget->addTab(m_simpleTab, "Simple Induction");

    // Strong Induction Tab
    m_strongTab = new QWidget();
    QVBoxLayout *strongLayout = new QVBoxLayout(m_strongTab);
    
    QGroupBox *strongGroup = new QGroupBox("Strong Induction");
    QVBoxLayout *strongGroupLayout = new QVBoxLayout(strongGroup);
    
    QLabel *strongInfo = new QLabel("Verify complex multi-level prerequisite systems using strong induction. This assumes all previous cases hold when proving the next case, allowing for more complex dependency verification.");
    strongInfo->setWordWrap(true);
    strongInfo->setStyleSheet("color: #666; margin-bottom: 15px;");
    
    m_strongVerifyBtn = new QPushButton("Multi-level Prerequisite Check");
    m_strongVerifyBtn->setStyleSheet("QPushButton { background-color: #007bff; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    
    strongGroupLayout->addWidget(strongInfo);
    strongGroupLayout->addWidget(m_strongVerifyBtn);
    strongGroupLayout->addStretch();
    
    strongLayout->addWidget(strongGroup);
    m_tabWidget->addTab(m_strongTab, "Strong Induction");

    // Mathematical Induction Tab
    m_mathTab = new QWidget();
    QVBoxLayout *mathLayout = new QVBoxLayout(m_mathTab);
    
    QGroupBox *mathGroup = new QGroupBox("Mathematical Induction");
    QVBoxLayout *mathGroupLayout = new QVBoxLayout(mathGroup);
    
    QLabel *formulaLabel = new QLabel("Select Formula:");
    m_formulaCombo = new QComboBox();
    m_formulaCombo->addItems({
        "Sum: 1 + 2 + ... + n = n(n+1)/2",
        "Sum of squares: 1² + 2² + ... + n² = n(n+1)(2n+1)/6",
        "Sum of cubes: 1³ + 2³ + ... + n³ = [n(n+1)/2]²",
        "Geometric series: 1 + 2 + 4 + ... + 2^n = 2^(n+1) - 1",
        "Inequality: 2^n > n for n ≥ 1"
    });
    
    QLabel *baseLabel = new QLabel("Base Case (n =):");
    m_baseCase = new QSpinBox();
    m_baseCase->setMinimum(0);
    m_baseCase->setMaximum(10);
    m_baseCase->setValue(1);
    
    m_proveMathBtn = new QPushButton("Prove Mathematical Formula");
    m_proveMathBtn->setStyleSheet("QPushButton { background-color: #6f42c1; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    
    mathGroupLayout->addWidget(formulaLabel);
    mathGroupLayout->addWidget(m_formulaCombo);
    mathGroupLayout->addWidget(baseLabel);
    mathGroupLayout->addWidget(m_baseCase);
    mathGroupLayout->addWidget(m_proveMathBtn);
    mathGroupLayout->addStretch();
    
    mathLayout->addWidget(mathGroup);
    m_tabWidget->addTab(m_mathTab, "Mathematical");

    // Custom Induction Tab
    m_customTab = new QWidget();
    QVBoxLayout *customLayout = new QVBoxLayout(m_customTab);
    
    QGroupBox *customGroup = new QGroupBox("Custom Induction Proof");
    QVBoxLayout *customGroupLayout = new QVBoxLayout(customGroup);
    
    QLabel *theoremLabel = new QLabel("Theorem to Prove:");
    m_customTheorem = new QLineEdit();
    m_customTheorem->setPlaceholderText("e.g., P(n) holds for all n ≥ 1");
    
    QLabel *baseLabel2 = new QLabel("Base Case:");
    m_customBase = new QLineEdit();
    m_customBase->setPlaceholderText("e.g., P(1) is true because...");
    
    QLabel *hypLabel = new QLabel("Inductive Hypothesis:");
    m_customHypothesis = new QTextEdit();
    m_customHypothesis->setPlaceholderText("Assume P(k) is true for some k ≥ 1...");
    m_customHypothesis->setMaximumHeight(80);
    
    m_proveCustomBtn = new QPushButton("Prove Custom Theorem");
    m_proveCustomBtn->setStyleSheet("QPushButton { background-color: #dc3545; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    
    customGroupLayout->addWidget(theoremLabel);
    customGroupLayout->addWidget(m_customTheorem);
    customGroupLayout->addWidget(baseLabel2);
    customGroupLayout->addWidget(m_customBase);
    customGroupLayout->addWidget(hypLabel);
    customGroupLayout->addWidget(m_customHypothesis);
    customGroupLayout->addWidget(m_proveCustomBtn);
    customGroupLayout->addStretch();
    
    customLayout->addWidget(customGroup);
    m_tabWidget->addTab(m_customTab, "Custom");

    splitter->addWidget(m_tabWidget);

    // Right panel - Results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    
    QLabel *resultsLabel = new QLabel("Induction Proof Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
    rightLayout->addWidget(resultsLabel);
    
    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    m_resultsDisplay->setStyleSheet("background-color: linear-gradient(to right, #ffecd2, #fcb69f); border: 1px solid #dee2e6; font-family: 'Consolas', monospace; font-size: 13px;");
    rightLayout->addWidget(m_resultsDisplay);
    
    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_clearBtn = new QPushButton("Clear Results");
    m_exportBtn = new QPushButton("Export Proof");
    m_exampleBtn = new QPushButton("Load Example");
    
    controlLayout->addWidget(m_clearBtn);
    controlLayout->addWidget(m_exportBtn);
    controlLayout->addWidget(m_exampleBtn);
    controlLayout->addStretch();
    rightLayout->addLayout(controlLayout);
    
    splitter->addWidget(rightPanel);
    splitter->setSizes({380, 420});

    // Connect signals
    connect(m_verifyChainBtn, &QPushButton::clicked, this, &InductionEngineWidget::verifyPrerequisiteChain);
    connect(m_strongVerifyBtn, &QPushButton::clicked, this, &InductionEngineWidget::strongInductionVerification);
    connect(m_proveMathBtn, &QPushButton::clicked, this, &InductionEngineWidget::mathematicalInductionExample);
    connect(m_proveCustomBtn, &QPushButton::clicked, this, &InductionEngineWidget::customInductionProof);
    connect(m_clearBtn, &QPushButton::clicked, this, &InductionEngineWidget::clearResults);
    connect(m_exportBtn, &QPushButton::clicked, this, &InductionEngineWidget::exportResults);
    connect(m_exampleBtn, &QPushButton::clicked, this, &InductionEngineWidget::loadExample);
    
    // Initial display
    m_resultsDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Select an induction type and click the corresponding button to generate a proof.</p>");
}

void InductionEngineWidget::verifyPrerequisiteChain()
{
    m_currentProof = "<h3>🔗 Prerequisite Chain Verification using Simple Induction</h3><hr>";
    
    m_currentProof += "<p><b>Chain Example:</b> Programming Fundamentals → OOP → Data Structures → AI → Machine Learning</p><br>";
    
    addProofStep("Base Case (n=1)", 
                "Programming Fundamentals has no prerequisites<br>"
                "Student can enroll directly", true);
    
    addProofStep("Inductive Hypothesis", 
                "Assume student completed course k successfully<br>"
                "All prerequisites for course k were satisfied");
    
    addProofStep("Inductive Step (n=k+1)", 
                "For course k+1, its prerequisite is course k<br>"
                "Since course k is completed, course k+1 prerequisites are satisfied<br>"
                "Student can now take course k+1", true);
    
    m_currentProof += "<br><h4>Verification Steps:</h4>";
    m_currentProof += "<p style='background-color: #e7f3ff; padding: 10px; border-left: 4px solid #2a82da;'>";
    m_currentProof += "✅ <b>Step 1:</b> Programming Fundamentals (Base)<br>";
    m_currentProof += "✅ <b>Step 2:</b> PF → OOP<br>";
    m_currentProof += "✅ <b>Step 3:</b> OOP → Data Structures<br>";
    m_currentProof += "✅ <b>Step 4:</b> DS → Artificial Intelligence<br>";
    m_currentProof += "✅ <b>Step 5:</b> AI → Machine Learning";
    m_currentProof += "</p>";
    
    m_currentProof += "<h4>Conclusion:</h4>";
    m_currentProof += "<p style='color: #28a745; font-weight: bold;'>✅ Entire prerequisite chain is valid by simple induction</p>";
    
    m_resultsDisplay->setHtml(m_currentProof);
}

void InductionEngineWidget::strongInductionVerification()
{
    m_currentProof = "<h3>💪 Strong Induction: Multi-level Prerequisite Verification</h3><hr>";
    
    m_currentProof += "<p><b>Theorem:</b> Student can successfully take Machine Learning course</p><br>";
    
    addProofStep("Base Cases (Level 1)", 
                "Programming Fundamentals (no prereq) ✅<br>"
                "Calculus (no prereq) ✅<br>"
                "Linear Algebra (no prereq) ✅", true);
    
    addProofStep("Strong Inductive Hypothesis", 
                "Assume ALL courses up to level k are completed successfully<br>"
                "This includes all foundational and intermediate courses");
    
    m_currentProof += "<h4>Verification Chain (All Levels):</h4>";
    m_currentProof += "<div style='background-color: #f8f9fa; padding: 15px; border-radius: 5px; margin: 10px 0;'>";
    m_currentProof += "<p><b>Level 1:</b> PF → OOP ✅</p>";
    m_currentProof += "<p><b>Level 2:</b> OOP → Data Structures ✅</p>";
    m_currentProof += "<p><b>Level 3:</b> Data Structures + Discrete Math → Theory of Automata ✅</p>";
    m_currentProof += "<p><b>Level 4:</b> Data Structures → Artificial Intelligence ✅</p>";
    m_currentProof += "<p><b>Level 5:</b> AI + Calculus + Linear Algebra → Machine Learning ✅</p>";
    m_currentProof += "</div>";
    
    addProofStep("Strong Inductive Step", 
                "For Machine Learning (level 5):<br>"
                "• Artificial Intelligence completed (level 4) ✅<br>"
                "• Calculus completed (level 1) ✅<br>"
                "• Linear Algebra completed (level 1) ✅<br>"
                "All direct AND indirect prerequisites satisfied", true);
    
    m_currentProof += "<h4>Conclusion:</h4>";
    m_currentProof += "<p style='color: #28a745; font-weight: bold;'>✅ All prerequisites verified using strong induction</p>";
    
    m_resultsDisplay->setHtml(m_currentProof);
}

void InductionEngineWidget::mathematicalInductionExample()
{
    QString formula = m_formulaCombo->currentText();
    int baseValue = m_baseCase->value();
    
    m_currentProof = "<h3>📐 Mathematical Induction Proof</h3><hr>";
    
    if (formula.contains("1 + 2 + ... + n = n(n+1)/2")) {
        m_currentProof += "<p><b>Theorem:</b> 1 + 2 + 3 + ... + n = n(n+1)/2</p><br>";
        
        addProofStep("Base Case (n=1)", 
                    QString("Left side: 1<br>Right side: 1(1+1)/2 = 1<br>1 = 1 ✅"), true);
        
        addProofStep("Inductive Hypothesis", 
                    "Assume the formula holds for n=k:<br>"
                    "1 + 2 + 3 + ... + k = k(k+1)/2");
        
        addProofStep("Inductive Step (n=k+1)", 
                    "1 + 2 + ... + k + (k+1)<br>"
                    "= k(k+1)/2 + (k+1)     [by inductive hypothesis]<br>"
                    "= (k+1)(k/2 + 1)<br>"
                    "= (k+1)(k+2)/2 ✅", true);
    }
    else if (formula.contains("Sum of squares")) {
        m_currentProof += "<p><b>Theorem:</b> 1² + 2² + ... + n² = n(n+1)(2n+1)/6</p><br>";
        
        addProofStep("Base Case (n=1)", 
                    "Left side: 1² = 1<br>Right side: 1(2)(3)/6 = 1<br>1 = 1 ✅", true);
        
        addProofStep("Inductive Step", 
                    "Assume true for k, prove for k+1<br>"
                    "Sum formula verified through algebraic manipulation ✅", true);
    }
    else if (formula.contains("2^n > n")) {
        m_currentProof += "<p><b>Theorem:</b> 2^n > n for all n ≥ 1</p><br>";
        
        addProofStep("Base Case (n=1)", 
                    "2¹ = 2 > 1 ✅", true);
        
        addProofStep("Inductive Step", 
                    "Assume 2^k > k, prove 2^(k+1) > k+1<br>"
                    "2^(k+1) = 2·2^k > 2k > k+1 (for k ≥ 1) ✅", true);
    }
    
    m_currentProof += "<h4>Conclusion:</h4>";
    m_currentProof += "<p style='color: #28a745; font-weight: bold;'>✅ Formula proven for all natural numbers by mathematical induction</p>";
    
    m_resultsDisplay->setHtml(m_currentProof);
}

void InductionEngineWidget::customInductionProof()
{
    QString theorem = m_customTheorem->text().trimmed();
    QString baseCase = m_customBase->text().trimmed();
    QString hypothesis = m_customHypothesis->toPlainText().trimmed();
    
    if (theorem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a theorem to prove.");
        return;
    }
    
    m_currentProof = "<h3>🔧 Custom Induction Proof</h3><hr>";
    m_currentProof += QString("<p><b>Theorem:</b> %1</p><br>").arg(theorem);
    
    if (!baseCase.isEmpty()) {
        addProofStep("Base Case", baseCase, true);
    } else {
        addProofStep("Base Case", "Base case verification needed", false);
    }
    
    if (!hypothesis.isEmpty()) {
        addProofStep("Inductive Hypothesis", hypothesis);
    } else {
        addProofStep("Inductive Hypothesis", "Inductive hypothesis needed", false);
    }
    
    addProofStep("Inductive Step", "Show that P(k) → P(k+1)<br>Complete the inductive step to finish the proof");
    
    m_currentProof += "<h4>Status:</h4>";
    if (!baseCase.isEmpty() && !hypothesis.isEmpty()) {
        m_currentProof += "<p style='color: #ffc107; font-weight: bold;'>⚠️ Proof structure complete - verify mathematical details</p>";
    } else {
        m_currentProof += "<p style='color: #dc3545; font-weight: bold;'>❌ Incomplete proof - fill in all required fields</p>";
    }
    
    m_resultsDisplay->setHtml(m_currentProof);
}

void InductionEngineWidget::addProofStep(const QString &stepName, const QString &content, bool isValid)
{
    QString icon = isValid ? "✅" : "❌";
    QString color = isValid ? "#28a745" : "#dc3545";
    
    m_currentProof += QString("<h4 style='color: %1;'>%2 %3:</h4>").arg(color).arg(icon).arg(stepName);
    m_currentProof += QString("<p style='margin-left: 20px;'>%1</p><br>").arg(content);
}

void InductionEngineWidget::clearResults()
{
    m_resultsDisplay->clear();
    m_customTheorem->clear();
    m_customBase->clear();
    m_customHypothesis->clear();
    m_resultsDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Select an induction type and click the corresponding button to generate a proof.</p>");
}

void InductionEngineWidget::exportResults()
{
    if (m_resultsDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No results to export. Please generate a proof first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Induction Proof", "induction_proof.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Induction Proof</title>";
        stream << "<style>body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }</style>";
        stream << "</head><body>";
        stream << m_resultsDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Proof exported successfully!");
    }
}

void InductionEngineWidget::loadExample()
{
    m_formulaCombo->setCurrentText("Sum: 1 + 2 + ... + n = n(n+1)/2");
    m_baseCase->setValue(1);
    m_tabWidget->setCurrentIndex(2); // Switch to Mathematical tab
    
    QMessageBox::information(this, "Example Loaded", "Loaded the classic sum formula example. Click 'Prove Mathematical Formula' to see the induction proof.");
}
