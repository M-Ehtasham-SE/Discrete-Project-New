#ifndef INDUCTIONENGINEWIDGET_H
#define INDUCTIONENGINEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTabWidget>
#include <QSplitter>

class InductionEngineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InductionEngineWidget(QWidget *parent = nullptr);

private slots:
    void verifyPrerequisiteChain();
    void strongInductionVerification();
    void mathematicalInductionExample();
    void customInductionProof();
    void clearResults();
    void exportResults();
    void loadExample();

private:
    void setupUI();
    void displayInductionStep(const QString &title, const QString &content, bool isValid = true);
    void addProofStep(const QString &stepName, const QString &content, bool isValid = true);

    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Simple Induction Tab
    QWidget *m_simpleTab;
    QPushButton *m_verifyChainBtn;
    
    // Strong Induction Tab
    QWidget *m_strongTab;
    QPushButton *m_strongVerifyBtn;
    
    // Mathematical Induction Tab
    QWidget *m_mathTab;
    QComboBox *m_formulaCombo;
    QSpinBox *m_baseCase;
    QPushButton *m_proveMathBtn;
    
    // Custom Induction Tab
    QWidget *m_customTab;
    QLineEdit *m_customTheorem;
    QLineEdit *m_customBase;
    QTextEdit *m_customHypothesis;
    QPushButton *m_proveCustomBtn;
    
    // Results display
    QTextEdit *m_resultsDisplay;
    
    // Control buttons
    QPushButton *m_clearBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_exampleBtn;
    
    QString m_currentProof;
};

#endif // INDUCTIONENGINEWIDGET_H