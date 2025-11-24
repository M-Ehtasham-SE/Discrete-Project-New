#ifndef PROOFENGINEWIDGET_H
#define PROOFENGINEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QSplitter>
#include <QMessageBox>

class ProofEngineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProofEngineWidget(QWidget *parent = nullptr);

private slots:
    void provePrerequisiteChain();
    void proveLogicRule();
    void proveMathematicalInduction();
    void clearResults();
    void exportProof();
    void loadExample();

private:
    void setupUI();
    void displayProofStep(const QString &title, const QString &content);
    void addProofStep(const QString &step, const QString &explanation, bool isValid = true);

    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Logic Rules Tab
    QWidget *m_logicTab;
    QComboBox *m_logicRuleCombo;
    QLineEdit *m_premiseInput;
    QPushButton *m_proveLogicBtn;
    
    // Mathematical Proofs Tab
    QWidget *m_mathTab;
    QComboBox *m_proofTypeCombo;
    QLineEdit *m_theoremInput;
    QPushButton *m_proveMathBtn;
    
    // Prerequisite Chain Tab
    QWidget *m_chainTab;
    QPushButton *m_proveChainBtn;
    
    // Results display
    QTextEdit *m_proofDisplay;
    
    // Control buttons
    QPushButton *m_clearBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_exampleBtn;
    
    // Current proof tracking
    QString m_currentProof;
    int m_stepCounter;
};

#endif // PROOFENGINEWIDGET_H