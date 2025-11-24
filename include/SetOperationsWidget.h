#ifndef SETOPERATIONSWIDGET_H
#define SETOPERATIONSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QProgressBar>
#include "SetOperationsManager.h"

class SetOperationsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetOperationsWidget(QWidget *parent = nullptr);

private slots:
    void addElementToSetA();
    void addElementToSetB();
    void removeFromSetA();
    void removeFromSetB();
    void clearSetA();
    void clearSetB();
    void calculateUnion();
    void calculateIntersection();
    void calculateDifference();
    void calculateSymmetricDifference();
    void calculateComplement();
    void performAllOperations();
    void generateRandomSets();
    void loadPresetSets();
    void exportResults();
    void showVennDiagram();
    void checkSetProperties();
    void onSetAChanged();
    void onSetBChanged();

private:
    void setupUI();
    void updateSetDisplays();
    void updateOperationResults();
    void showSetInList(const QStringList &set, QListWidget *listWidget);
    void displayOperationResult(const QString &operation, const QStringList &result);
    QStringList performUnion(const QStringList &setA, const QStringList &setB);
    QStringList performIntersection(const QStringList &setA, const QStringList &setB);
    QStringList performDifference(const QStringList &setA, const QStringList &setB);
    QStringList performSymmetricDifference(const QStringList &setA, const QStringList &setB);
    QStringList performComplement(const QStringList &set, const QStringList &universe);
    QString generateVennDiagramText(const QStringList &setA, const QStringList &setB);
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Set Input Tab
    QListWidget *m_setAList;
    QListWidget *m_setBList;
    QLineEdit *m_elementInputA;
    QLineEdit *m_elementInputB;
    QPushButton *m_addToAButton;
    QPushButton *m_addToBButton;
    QPushButton *m_removeFromAButton;
    QPushButton *m_removeFromBButton;
    QPushButton *m_clearAButton;
    QPushButton *m_clearBButton;
    QLabel *m_setALabel;
    QLabel *m_setBLabel;
    
    // Operations Tab
    QPushButton *m_unionButton;
    QPushButton *m_intersectionButton;
    QPushButton *m_differenceButton;
    QPushButton *m_symDifferenceButton;
    QPushButton *m_complementButton;
    QPushButton *m_allOperationsButton;
    QTextEdit *m_operationResults;
    
    // Visualization Tab
    QTextEdit *m_vennDisplay;
    QPushButton *m_showVennButton;
    QPushButton *m_generateRandomButton;
    QPushButton *m_loadPresetButton;
    QComboBox *m_presetComboBox;
    
    // Properties Tab
    QTextEdit *m_propertiesDisplay;
    QPushButton *m_checkPropertiesButton;
    QCheckBox *m_showStepsCheckBox;
    
    // Universe Definition
    QListWidget *m_universeList;
    QLineEdit *m_universeInput;
    QPushButton *m_addToUniverseButton;
    QPushButton *m_clearUniverseButton;
    
    // Export/Import
    QPushButton *m_exportButton;
    QProgressBar *m_progressBar;
    
    // Backend
    SetOperationsManager *m_manager;
    
    // Data
    QStringList m_setA;
    QStringList m_setB;
    QStringList m_universe;
    QMap<QString, QStringList> m_cachedResults;
};

#endif // SETOPERATIONSWIDGET_H