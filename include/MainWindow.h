#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>
#include <QSplashScreen>
#include <QTimer>

// Include all widget headers
#include "CoursePrerequisiteWidget.h"
#include "StudentGroupWidget.h"
#include "SetOperationsWidget.h"
#include "AllWidgets.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAbout();
    void showHelp();
    void showWelcome();
    void onTabChanged(int index);

private:
    void createMenus();
    void createStatusBar();
    void setupCentralWidget();
    void setupSplashScreen();
    
    // UI Components
    QTabWidget *m_tabWidget;
    QStatusBar *m_statusBar;
    QLabel *m_statusLabel;
    QProgressBar *m_progressBar;
    
    // Menu actions
    QAction *m_aboutAction;
    QAction *m_helpAction;
    QAction *m_exitAction;
    QAction *m_welcomeAction;
    
    // Module widgets
    CoursePrerequisiteWidget *m_courseWidget;
    StudentGroupWidget *m_studentWidget;
    SetOperationsWidget *m_setWidget;
    RelationPropertiesWidget *m_relationWidget;
    ProofEngineWidget *m_proofWidget;
    InductionEngineWidget *m_inductionWidget;
    TestsWidget *m_testsWidget;
    FunctionsManagerWidget *m_functionsWidget;
    LogicInferenceWidget *m_logicWidget;
    ConsistencyCheckerWidget *m_consistencyWidget;
    EfficiencyBenchmarksWidget *m_efficiencyWidget;
};

#endif // MAINWINDOW_H