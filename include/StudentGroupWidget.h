#ifndef STUDENTGROUPWIDGET_H
#define STUDENTGROUPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QComboBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QProgressBar>
#include <QSlider>
#include <QLineEdit>
#include "StudentGroup.h"

class StudentGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentGroupWidget(QWidget *parent = nullptr);

private slots:
    void calculateCombinations();
    void calculatePermutations();
    void assignProjectGroups();
    void planEvent();
    void addStudent();
    void removeStudent();
    void clearStudents();
    void exportResults();
    void showCombinationFormula();
    void onStudentCountChanged();
    void onGroupSizeChanged();

private:
    void setupUI();
    void updateCombinationDisplay();
    void showCalculationSteps(long long result, int n, int r, const QString &type);
    long long factorial(int n);
    long long combination(int n, int r);
    long long permutation(int n, int r);
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Combinations Tab
    QSpinBox *m_totalStudentsSpinBox;
    QSpinBox *m_groupSizeSpinBox;
    QPushButton *m_calculateButton;
    QTextEdit *m_resultDisplay;
    QLabel *m_formulaLabel;
    QLabel *m_resultLabel;
    
    // Students Management Tab
    QListWidget *m_studentsList;
    QLineEdit *m_studentNameEdit;
    QPushButton *m_addStudentButton;
    QPushButton *m_removeStudentButton;
    QPushButton *m_clearStudentsButton;
    QLabel *m_studentCountLabel;
    
    // Project Assignment Tab
    QComboBox *m_projectComboBox;
    QSpinBox *m_membersPerGroupSpinBox;
    QPushButton *m_assignButton;
    QTableWidget *m_assignmentTable;
    QTextEdit *m_assignmentDetails;
    
    // Event Planning Tab
    QSpinBox *m_eventAttendeesSpinBox;
    QSpinBox *m_committeeStzeSpinBox;
    QPushButton *m_planEventButton;
    QTextEdit *m_eventResults;
    
    // Visualization Tab
    QTextEdit *m_visualizationDisplay;
    QSlider *m_nSlider;
    QSlider *m_rSlider;
    QLabel *m_nLabel;
    QLabel *m_rLabel;
    QPushButton *m_showFormulaButton;
    QPushButton *m_exportButton;
    
    // Backend
    StudentGroup *m_manager;
    
    // Data
    QStringList m_students;
    QStringList m_projects;
    QMap<QString, QStringList> m_groupAssignments;
};

#endif // STUDENTGROUPWIDGET_H