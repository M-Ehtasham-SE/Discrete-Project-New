#ifndef LOGICINFERENCEWIDGET_H
#define LOGICINFERENCEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QGroupBox>
#include <QListWidget>
#include <QSplitter>
#include <QMessageBox>

class LogicInferenceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogicInferenceWidget(QWidget *parent = nullptr);

private slots:
    void addRule();
    void removeRule();
    void clearRules();
    void addFact();
    void removeFact();
    void clearFacts();
    void runInference();
    void loadExample();
    void exportResults();
    void clearResults();

private:
    void setupUI();
    void updateInferenceResults();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;
    
    // Rules section
    QGroupBox *m_rulesGroup;
    QLineEdit *m_premiseInput;
    QLineEdit *m_conclusionInput;
    QPushButton *m_addRuleBtn;
    QPushButton *m_removeRuleBtn;
    QPushButton *m_clearRulesBtn;
    QTableWidget *m_rulesTable;
    
    // Facts section
    QGroupBox *m_factsGroup;
    QLineEdit *m_factInput;
    QPushButton *m_addFactBtn;
    QPushButton *m_removeFactBtn;
    QPushButton *m_clearFactsBtn;
    QListWidget *m_factsList;
    
    // Control buttons
    QPushButton *m_runInferenceBtn;
    QPushButton *m_loadExampleBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_clearResultsBtn;
    
    // Results display
    QTextEdit *m_resultsDisplay;
    
    // Data storage
    QList<QPair<QString, QString>> m_rules; // premise -> conclusion
    QStringList m_facts;
    QStringList m_inferredFacts;
};

#endif // LOGICINFERENCEWIDGET_H