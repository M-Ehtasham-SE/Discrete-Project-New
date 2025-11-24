#ifndef CONSISTENCYCHECKERWIDGET_H
#define CONSISTENCYCHECKERWIDGET_H

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
#include <QTabWidget>
#include <QComboBox>
#include <QMessageBox>

class ConsistencyCheckerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConsistencyCheckerWidget(QWidget *parent = nullptr);

private slots:
    void addCourseTime();
    void removeCourseTime();
    void clearCourseTimes();
    void checkTimeConflicts();
    void addPrerequisite();
    void removePrerequisite();
    void clearPrerequisites();
    void checkPrerequisiteViolations();
    void addFacultyAssignment();
    void removeFacultyAssignment();
    void clearFacultyAssignments();
    void checkFacultyConflicts();
    void runAllChecks();
    void loadExample();
    void exportResults();
    void clearResults();

private:
    void setupUI();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    
    // Course Time Conflicts Tab
    QWidget *m_timeTab;
    QLineEdit *m_courseNameInput;
    QLineEdit *m_timeSlotInput;
    QPushButton *m_addCourseTimeBtn;
    QPushButton *m_removeCourseTimeBtn;
    QPushButton *m_clearCourseTimesBtn;
    QPushButton *m_checkTimeConflictsBtn;
    QTableWidget *m_courseTimesTable;
    
    // Prerequisites Tab
    QWidget *m_prereqTab;
    QLineEdit *m_courseInput;
    QLineEdit *m_prerequisiteInput;
    QPushButton *m_addPrereqBtn;
    QPushButton *m_removePrereqBtn;
    QPushButton *m_clearPrereqBtn;
    QPushButton *m_checkPrereqBtn;
    QTableWidget *m_prerequisitesTable;
    
    // Faculty Assignments Tab
    QWidget *m_facultyTab;
    QLineEdit *m_facultyNameInput;
    QLineEdit *m_assignedCourseInput;
    QLineEdit *m_roomInput;
    QPushButton *m_addFacultyBtn;
    QPushButton *m_removeFacultyBtn;
    QPushButton *m_clearFacultyBtn;
    QPushButton *m_checkFacultyBtn;
    QTableWidget *m_facultyTable;
    
    // Results display
    QTextEdit *m_resultsDisplay;
    
    // Control buttons
    QPushButton *m_runAllBtn;
    QPushButton *m_loadExampleBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_clearResultsBtn;
    
    // Data storage
    QList<QPair<QString, QString>> m_courseTimes; // course -> time
    QList<QPair<QString, QString>> m_prerequisites; // course -> prerequisite
    QList<QStringList> m_facultyAssignments; // [faculty, course, room, time]
};

#endif // CONSISTENCYCHECKERWIDGET_H