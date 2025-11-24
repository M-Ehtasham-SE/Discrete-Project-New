#ifndef FUNCTIONSMANAGERWIDGET_H
#define FUNCTIONSMANAGERWIDGET_H

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
#include <QCheckBox>
#include <QSplitter>
#include <QComboBox>

class FunctionsManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionsManagerWidget(QWidget *parent = nullptr);

private slots:
    void addMapping();
    void removeMapping();
    void clearMappings();
    void checkInjective();
    void checkSurjective();
    void checkBijective();
    void checkAllProperties();
    void generateExample();
    void exportResults();

private:
    void setupUI();
    void updatePropertiesDisplay();
    void displayFunctionAnalysis();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;
    
    // Input section
    QGroupBox *m_inputGroup;
    QLineEdit *m_domainInput;
    QLineEdit *m_codomainInput;
    QPushButton *m_addMappingBtn;
    QPushButton *m_removeMappingBtn;
    QPushButton *m_clearBtn;
    QTableWidget *m_mappingsTable;
    
    // Analysis section
    QGroupBox *m_analysisGroup;
    QPushButton *m_checkAllBtn;
    QPushButton *m_generateExampleBtn;
    QPushButton *m_exportBtn;
    
    // Properties display
    QCheckBox *m_injectiveCheck;
    QCheckBox *m_surjectiveCheck;
    QCheckBox *m_bijectiveCheck;
    
    // Results display
    QTextEdit *m_resultsDisplay;
    
    // Data storage
    QList<QPair<QString, QString>> m_mappings;
    QStringList m_domainSet;
    QStringList m_codomainSet;
};

#endif // FUNCTIONSMANAGERWIDGET_H