#ifndef COURSEPREREQUISITEWIDGET_H
#define COURSEPREREQUISITEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTreeWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSplitter>
#include <QGroupBox>
#include <QTabWidget>
#include <QProgressBar>
#include "CoursePrerequisiteManager.h"

class CoursePrerequisiteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoursePrerequisiteWidget(QWidget *parent = nullptr);

private slots:
    void loadCurriculum();
    void displayAllCourses();
    void displayPrerequisites();
    void generateValidOrder();
    void checkPrerequisites();
    void addNewCourse();
    void addNewPrerequisite();
    void onCourseSelected();
    void searchCourses();
    void showSemesterView();
    void showDependencyGraph();

private:
    void setupUI();
    void updateCourseList();
    void populateTree();
    void showPrerequisiteChain(const QString &course);
    void highlightPrerequisites(const QString &course);
    void addPrerequisitesToTree(QTreeWidgetItem *parent, const QString &course, int level);
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    QSplitter *m_mainSplitter;
    
    // Course Management Tab
    QTreeWidget *m_courseTree;
    QListWidget *m_courseList;
    QTextEdit *m_detailsDisplay;
    QLineEdit *m_searchBox;
    QPushButton *m_loadButton;
    QPushButton *m_addCourseButton;
    QPushButton *m_addPrereqButton;
    QComboBox *m_semesterFilter;
    
    // Prerequisites Tab
    QTreeWidget *m_prereqTree;
    QTextEdit *m_prereqDetails;
    QLineEdit *m_courseSearch;
    QPushButton *m_checkButton;
    QPushButton *m_generateButton;
    
    // Visualization Tab
    QTextEdit *m_visualDisplay;
    QPushButton *m_showGraphButton;
    QPushButton *m_showSemesterButton;
    QProgressBar *m_progressBar;
    
    // Backend
    CoursePrerequisiteManager *m_manager;
    
    // Data storage
    QStringList m_allCourses;
    QMap<QString, QStringList> m_prerequisites;
    QMap<QString, int> m_semesterMap;
};

#endif // COURSEPREREQUISITEWIDGET_H