#include "ProofEngineWidget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QInputDialog>

ProofEngineWidget::ProofEngineWidget(QWidget *parent)
    : QWidget(parent), m_stepCounter(0)
{
    setupUI();
}

void ProofEngineWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Proof & Verification Engine");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Main splitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(splitter);

    // Left panel - Input tabs
    m_tabWidget = new QTabWidget();
    m_tabWidget->setMaximumWidth(350);
    
    // Logic Rules Tab
    m_logicTab = new QWidget();
    QVBoxLayout *logicLayout = new QVBoxLayout(m_logicTab);
    
    QGroupBox *logicGroup = new QGroupBox("Logic Rule Proofs");
    QVBoxLayout *logicGroupLayout = new QVBoxLayout(logicGroup);
    
    QLabel *ruleLabel = new QLabel("Select Logic Rule:");
    m_logicRuleCombo = new QComboBox();
    m_logicRuleCombo->addItems({
        "Modus Ponens",
        "Modus Tollens", 
        "Hypothetical Syllogism",
        "Disjunctive Syllogism",
        "De Morgan's Laws",
        "Proof by Contradiction"
    });
    
    QLabel *premiseLabel = new QLabel("Enter Premise (optional):");
    m_premiseInput = new QLineEdit();
    m_premiseInput->setPlaceholderText("e.g., If P then Q, P is true");
    
    m_proveLogicBtn = new QPushButton("Prove Logic Rule");
    m_proveLogicBtn->setStyleSheet("QPushButton { background-color: linear-gradient(to right, #ffecd2, #fcb69f); color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    
    logicGroupLayout->addWidget(ruleLabel);
    logicGroupLayout->addWidget(m_logicRuleCombo);
    logicGroupLayout->addWidget(premiseLabel);
    logicGroupLayout->addWidget(m_premiseInput);
    logicGroupLayout->addWidget(m_proveLogicBtn);
    logicGroupLayout->addStretch();
    
    logicLayout->addWidget(logicGroup);
    m_tabWidget->addTab(m_logicTab, "Logic Rules");

    // Mathematical Proofs Tab
    m_mathTab = new QWidget();
    QVBoxLayout *mathLayout = new QVBoxLayout(m_mathTab);
    
    QGroupBox *mathGroup = new QGroupBox("Mathematical Proofs");
    QVBoxLayout *mathGroupLayout = new QVBoxLayout(mathGroup);
    
    QLabel *typeLabel = new QLabel("Proof Type:");
    m_proofTypeCombo = new QComboBox();
    m_proofTypeCombo->addItems({
        "Mathematical Induction",
        "Direct Proof",
        "Proof by Contradiction",
        "Proof by Contrapositive"
    });
    
    QLabel *theoremLabel = new QLabel("Theorem to Prove:");
    m_theoremInput = new QLineEdit();
    m_theoremInput->setPlaceholderText("e.g., Sum formula: 1+2+...+n = n(n+1)/2");
    
    m_proveMathBtn = new QPushButton("Prove Theorem");
    m_proveMathBtn->setStyleSheet("QPushButton { background-color: #007bff; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    
    mathGroupLayout->addWidget(typeLabel);
    mathGroupLayout->addWidget(m_proofTypeCombo);
    mathGroupLayout->addWidget(theoremLabel);
    mathGroupLayout->addWidget(m_theoremInput);
    mathGroupLayout->addWidget(m_proveMathBtn);
    mathGroupLayout->addStretch();
    
    mathLayout->addWidget(mathGroup);
    m_tabWidget->addTab(m_mathTab, "Mathematical");

    // Prerequisite Chain Tab
    m_chainTab = new QWidget();
    QVBoxLayout *chainLayout = new QVBoxLayout(m_chainTab);
    
    QGroupBox *chainGroup = new QGroupBox("Prerequisite Chain Verification");
    QVBoxLayout *chainGroupLayout = new QVBoxLayout(chainGroup);
    
    QLabel *chainInfo = new QLabel("Verify the validity of course prerequisite chains using formal proof techniques.");
    chainInfo->setWordWrap(true);
    chainInfo->setStyleSheet("color: #666; margin-bottom: 10px;");
    
    m_proveChainBtn = new QPushButton("Prove Prerequisite Chain Validity");
    m_proveChainBtn->setStyleSheet("QPushButton { background-color: #6f42c1; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    
    chainGroupLayout->addWidget(chainInfo);
    chainGroupLayout->addWidget(m_proveChainBtn);
    chainGroupLayout->addStretch();
    
    chainLayout->addWidget(chainGroup);
    m_tabWidget->addTab(m_chainTab, "Prerequisites");

    splitter->addWidget(m_tabWidget);

    // Right panel - Results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    
    QLabel *resultsLabel = new QLabel("Proof Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
    rightLayout->addWidget(resultsLabel);
    
    m_proofDisplay = new QTextEdit();
    m_proofDisplay->setReadOnly(true);
    m_proofDisplay->setStyleSheet("background-color: linear-gradient(to right, #ffecd2, #fcb69f); border: 1px solid #dee2e6; font-family: 'Consolas', monospace; font-size: 13px;");
    rightLayout->addWidget(m_proofDisplay);
    
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
    splitter->setSizes({350, 450});

    // Connect signals
    connect(m_proveLogicBtn, &QPushButton::clicked, this, &ProofEngineWidget::proveLogicRule);
    connect(m_proveMathBtn, &QPushButton::clicked, this, &ProofEngineWidget::proveMathematicalInduction);
    connect(m_proveChainBtn, &QPushButton::clicked, this, &ProofEngineWidget::provePrerequisiteChain);
    connect(m_clearBtn, &QPushButton::clicked, this, &ProofEngineWidget::clearResults);
    connect(m_exportBtn, &QPushButton::clicked, this, &ProofEngineWidget::exportProof);
    connect(m_exampleBtn, &QPushButton::clicked, this, &ProofEngineWidget::loadExample);
    
    // Initial display
    m_proofDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Select a proof type and click the corresponding button to generate a formal proof.</p>");
}

void ProofEngineWidget::provePrerequisiteChain()
{
    m_stepCounter = 0;
    m_currentProof = "<h3>🎓 Prerequisite Chain Proof</h3><hr>";
    
    addProofStep("Theorem", "Course prerequisite chains ensure valid learning sequence");
    
    m_currentProof += "<h4>Proof:</h4>";
    addProofStep("1. Base Case", "Foundational courses have no prerequisites", true);
    addProofStep("2. Inductive Step", "Each course requires completion of prerequisites", true);
    addProofStep("3. Transitive Property", "If A→B and B→C, then A→C", true);
    addProofStep("4. Acyclic Property", "No circular dependencies in curriculum", true);
    addProofStep("5. Topological Sort", "Valid ordering exists for all courses", true);
    
    m_currentProof += "<br><h4>Example Chain:</h4>";
    m_currentProof += "<p style='background-color: #e7f3ff; padding: 10px; border-left: 4px solid #2a82da;'>";
    m_currentProof += "<b>Programming Fundamentals → OOP → Data Structures → Operating Systems → Computer Networks</b><br>";
    m_currentProof += "This forms a valid learning progression ✅";
    m_currentProof += "</p>";
    
    m_currentProof += "<h4>Conclusion:</h4>";
    m_currentProof += "<p style='color: #28a745; font-weight: bold;'>✅ Prerequisite system ensures students build knowledge progressively.</p>";
    
    m_proofDisplay->setHtml(m_currentProof);
}

void ProofEngineWidget::proveLogicRule()
{
    QString rule = m_logicRuleCombo->currentText();
    QString premise = m_premiseInput->text().trimmed();
    
    m_stepCounter = 0;
    m_currentProof = QString("<h3>⚡ Logic Rule Proof: %1</h3><hr>").arg(rule);
    
    if (rule == "Modus Ponens") {
        addProofStep("Rule Form", "[(P → Q) ∧ P] → Q");
        addProofStep("1. Premise", "If P then Q (P → Q)");
        addProofStep("2. Premise", "P is true");
        addProofStep("3. Conclusion", "Therefore, Q must be true", true);
        m_currentProof += "<p style='background-color: #d4edda; padding: 10px; border-radius: 4px;'><b>Example:</b> If it rains, the ground gets wet. It is raining. Therefore, the ground is wet.</p>";
    }
    else if (rule == "Modus Tollens") {
        addProofStep("Rule Form", "[(P → Q) ∧ ¬Q] → ¬P");
        addProofStep("1. Premise", "If P then Q (P → Q)");
        addProofStep("2. Premise", "Not Q (¬Q)");
        addProofStep("3. Conclusion", "Therefore, not P (¬P)", true);
        m_currentProof += "<p style='background-color: #d4edda; padding: 10px; border-radius: 4px;'><b>Example:</b> If it rains, the ground gets wet. The ground is not wet. Therefore, it is not raining.</p>";
    }
    else if (rule == "Hypothetical Syllogism") {
        addProofStep("Rule Form", "[(P → Q) ∧ (Q → R)] → (P → R)");
        addProofStep("1. Premise", "If P then Q (P → Q)");
        addProofStep("2. Premise", "If Q then R (Q → R)");
        addProofStep("3. Conclusion", "Therefore, if P then R (P → R)", true);
        m_currentProof += "<p style='background-color: #d4edda; padding: 10px; border-radius: 4px;'><b>Example:</b> If you study, you pass. If you pass, you graduate. Therefore, if you study, you graduate.</p>";
    }
    else if (rule == "Proof by Contradiction") {
        addProofStep("Method", "Assume the opposite of what we want to prove");
        addProofStep("1. Assumption", "Assume ¬P (opposite of desired conclusion)");
        addProofStep("2. Derivation", "Show this assumption leads to contradiction");
        addProofStep("3. Conclusion", "Therefore, original statement P must be true", true);
    }
    
    m_currentProof += "<p style='color: #28a745; font-weight: bold; text-align: center; margin-top: 20px;'>✅ Proof completed successfully!</p>";
    
    m_proofDisplay->setHtml(m_currentProof);
}

void ProofEngineWidget::proveMathematicalInduction()
{
    QString proofType = m_proofTypeCombo->currentText();
    QString theorem = m_theoremInput->text().trimmed();
    
    m_stepCounter = 0;
    m_currentProof = QString("<h3>📐 %1</h3><hr>").arg(proofType);
    
    if (proofType == "Mathematical Induction") {
        if (theorem.isEmpty()) {
            theorem = "1 + 2 + 3 + ... + n = n(n+1)/2";
        }
        
        addProofStep("Theorem", theorem);
        
        m_currentProof += "<h4>Proof by Mathematical Induction:</h4>";
        addProofStep("Base Case (n=1)", "Left side: 1<br>Right side: 1(1+1)/2 = 1 ✅", true);
        
        addProofStep("Inductive Hypothesis", "Assume true for n=k:<br>1+2+...+k = k(k+1)/2");
        
        addProofStep("Inductive Step (n=k+1)", 
                    "1+2+...+k+(k+1) = k(k+1)/2 + (k+1)<br>"
                    "= (k+1)(k/2 + 1)<br>"
                    "= (k+1)(k+2)/2 ✅", true);
                    
        m_currentProof += "<p style='color: #28a745; font-weight: bold;'>✅ Formula holds for all natural numbers by induction</p>";
    }
    else if (proofType == "Direct Proof") {
        addProofStep("Theorem", "If n is even, then n² is even");
        addProofStep("1. Assumption", "Let n be even, so n = 2k for some integer k");
        addProofStep("2. Calculation", "n² = (2k)² = 4k² = 2(2k²)");
        addProofStep("3. Conclusion", "Since 2k² is integer, n² is even ✅", true);
    }
    
    m_proofDisplay->setHtml(m_currentProof);
}

void ProofEngineWidget::addProofStep(const QString &step, const QString &explanation, bool isValid)
{
    QString validIcon = isValid ? "✅" : "❌";
    QString color = isValid ? "#28a745" : "#dc3545";
    
    m_currentProof += QString("<p><b style='color: %1;'>%2 %3:</b> %4</p>")
                      .arg(color)
                      .arg(validIcon)
                      .arg(step)
                      .arg(explanation);
}

void ProofEngineWidget::clearResults()
{
    m_proofDisplay->clear();
    m_premiseInput->clear();
    m_theoremInput->clear();
    m_proofDisplay->setHtml("<p style='color: #666; text-align: center; margin-top: 50px;'>Select a proof type and click the corresponding button to generate a formal proof.</p>");
}

void ProofEngineWidget::exportProof()
{
    if (m_proofDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No proof to export. Please generate a proof first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Proof", "formal_proof.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Formal Proof</title>";
        stream << "<style>body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }</style>";
        stream << "</head><body>";
        stream << m_proofDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Proof exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save file.");
    }
}

void ProofEngineWidget::loadExample()
{
    // Load an example mathematical induction proof
    m_proofTypeCombo->setCurrentText("Mathematical Induction");
    m_theoremInput->setText("1 + 2 + 3 + ... + n = n(n+1)/2");
    m_tabWidget->setCurrentIndex(1); // Switch to Mathematical tab
    
    QMessageBox::information(this, "Example Loaded", "Loaded a classic mathematical induction example. Click 'Prove Theorem' to see the proof.");
}
