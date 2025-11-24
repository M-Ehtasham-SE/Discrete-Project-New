#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tabWidget(nullptr)
    , m_statusBar(nullptr)
    , m_statusLabel(nullptr)
    , m_progressBar(nullptr)
{
    setWindowTitle("UNIDISC Engine - FAST University Discrete Mathematics Platform");
    setWindowIcon(QIcon(":/icons/app_icon.png"));
    resize(1200, 800);
    setMinimumSize(800, 600);
    
    setupSplashScreen();
    createMenus();
    createStatusBar();
    setupCentralWidget();
    
    // Show welcome message
    QTimer::singleShot(100, this, &MainWindow::showWelcome);
}

MainWindow::~MainWindow()
{
    // Qt handles cleanup automatically
}

void MainWindow::setupSplashScreen()
{
    QPixmap pixmap(400, 300);
    pixmap.fill(QColor(42, 130, 218));
    
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage("Loading UNIDISC Engine...", Qt::AlignBottom | Qt::AlignCenter, Qt::white);
    
    QTimer::singleShot(2000, splash, &QSplashScreen::close);
}

void MainWindow::createMenus()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    m_welcomeAction = new QAction("&Welcome", this);
    m_welcomeAction->setShortcut(QKeySequence::New);
    m_welcomeAction->setStatusTip("Show welcome screen");
    connect(m_welcomeAction, &QAction::triggered, this, &MainWindow::showWelcome);
    fileMenu->addAction(m_welcomeAction);
    
    fileMenu->addSeparator();
    
    m_exitAction = new QAction("E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(m_exitAction);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    
    m_helpAction = new QAction("&Help", this);
    m_helpAction->setShortcut(QKeySequence::HelpContents);
    m_helpAction->setStatusTip("Show help information");
    connect(m_helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    helpMenu->addAction(m_helpAction);
    
    helpMenu->addSeparator();
    
    m_aboutAction = new QAction("&About", this);
    m_aboutAction->setStatusTip("Show information about this application");
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::createStatusBar()
{
    m_statusBar = statusBar();
    
    m_statusLabel = new QLabel("Ready");
    m_statusLabel->setStyleSheet("color: #2a82da; font-weight: bold;");
    m_statusBar->addWidget(m_statusLabel);
    
    m_progressBar = new QProgressBar();
    m_progressBar->setVisible(false);
    m_statusBar->addPermanentWidget(m_progressBar);
    
    // Version info
    QLabel *versionLabel = new QLabel("v1.0.0");
    versionLabel->setStyleSheet("color: #888;");
    m_statusBar->addPermanentWidget(versionLabel);
}

void MainWindow::setupCentralWidget()
{
    m_tabWidget = new QTabWidget();
    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->setTabsClosable(false);
    m_tabWidget->setMovable(true);
    
    // Create all module widgets
    m_courseWidget = new CoursePrerequisiteWidget();
    m_studentWidget = new StudentGroupWidget();
    m_setWidget = new SetOperationsWidget();
    m_relationWidget = new RelationPropertiesWidget();
    m_proofWidget = new ProofEngineWidget();
    m_inductionWidget = new InductionEngineWidget();
    m_testsWidget = new TestsWidget();
    m_functionsWidget = new FunctionsManagerWidget();
    m_logicWidget = new LogicInferenceWidget();
    m_consistencyWidget = new ConsistencyCheckerWidget();
    m_efficiencyWidget = new EfficiencyBenchmarksWidget();
    
    // Add tabs with icons and descriptions
    m_tabWidget->addTab(m_courseWidget, QIcon(":/icons/course.png"), "Course Prerequisites");
    m_tabWidget->addTab(m_studentWidget, QIcon(":/icons/students.png"), "Student Groups");
    m_tabWidget->addTab(m_setWidget, QIcon(":/icons/sets.png"), "Set Operations");
    m_tabWidget->addTab(m_relationWidget, QIcon(":/icons/relations.png"), "Relations");
    m_tabWidget->addTab(m_proofWidget, QIcon(":/icons/proof.png"), "Proof Engine");
    m_tabWidget->addTab(m_inductionWidget, QIcon(":/icons/induction.png"), "Induction");
    m_tabWidget->addTab(m_testsWidget, QIcon(":/icons/tests.png"), "Unit Tests");
    m_tabWidget->addTab(m_functionsWidget, QIcon(":/icons/functions.png"), "Functions");
    m_tabWidget->addTab(m_logicWidget, QIcon(":/icons/logic.png"), "Logic & Inference");
    m_tabWidget->addTab(m_consistencyWidget, QIcon(":/icons/consistency.png"), "Consistency Checker");
    m_tabWidget->addTab(m_efficiencyWidget, QIcon(":/icons/efficiency.png"), "Efficiency Benchmarks");
    
    // Connect tab change signal
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    
    setCentralWidget(m_tabWidget);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "About UNIDISC Engine",
        "<h2>UNIDISC Engine v1.0.0</h2>"
        "<p><b>FAST University Discrete Mathematics Learning Platform</b></p>"
        "<p>A comprehensive educational tool for learning discrete mathematics concepts including:</p>"
        "<ul>"
        "<li>Course Prerequisites Management</li>"
        "<li>Student Group Combinations</li>"
        "<li>Set Operations & Theory</li>"
        "<li>Relation Properties</li>"
        "<li>Mathematical Proofs</li>"
        "<li>Induction & Strong Induction</li>"
        "<li>Functions & Mappings</li>"
        "<li>Logic & Inference</li>"
        "<li>Consistency Checking</li>"
        "<li>Algorithmic Efficiency</li>"
        "</ul>"
        "<p><b>Developed by:</b> Ehtasham Batalwi - 4</p>"
        "<p><b>Institution:</b> FAST University</p>"
        "<p><b>Built with:</b> Qt 6.x and C++17</p>"
    );
}

void MainWindow::showHelp()
{
    QMessageBox::information(this, "Help - UNIDISC Engine",
        "<h3>How to Use UNIDISC Engine</h3>"
        "<p><b>Navigation:</b></p>"
        "<ul>"
        "<li>Use tabs to switch between different modules</li>"
        "<li>Each module has its own interface and functionality</li>"
        "<li>Status bar shows current activity and progress</li>"
        "</ul>"
        "<p><b>Modules Overview:</b></p>"
        "<ol>"
        "<li><b>Course Prerequisites:</b> Manage course dependencies and generate valid sequences</li>"
        "<li><b>Student Groups:</b> Calculate combinations for group formations</li>"
        "<li><b>Set Operations:</b> Perform union, intersection, difference operations</li>"
        "<li><b>Relations:</b> Check reflexive, symmetric, transitive properties</li>"
        "<li><b>Proof Engine:</b> Generate mathematical proofs and verifications</li>"
        "<li><b>Induction:</b> Mathematical and strong induction examples</li>"
        "<li><b>Unit Tests:</b> Run system functionality tests</li>"
        "<li><b>Functions:</b> Analyze function properties (injective, surjective, bijective)</li>"
        "<li><b>Logic & Inference:</b> Rule-based reasoning system</li>"
        "<li><b>Consistency Checker:</b> Validate system consistency</li>"
        "<li><b>Efficiency Benchmarks:</b> Algorithm performance analysis</li>"
        "</ol>"
        "<p><b>Tips:</b></p>"
        "<ul>"
        "<li>Hover over buttons for tooltips</li>"
        "<li>Use Ctrl+Q to quit the application</li>"
        "<li>Check status bar for operation feedback</li>"
        "</ul>"
    );
}

void MainWindow::showWelcome()
{
    QMessageBox welcome(this);
    welcome.setWindowTitle("Welcome to UNIDISC Engine");
    welcome.setIconPixmap(QPixmap(":/icons/app_icon.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    welcome.setText(
        "<h2>🎓 Welcome to UNIDISC Engine!</h2>"
        "<p><b>FAST University Discrete Mathematics Learning Platform</b></p>"
    );
    welcome.setInformativeText(
        "<p>This comprehensive educational tool provides interactive modules for learning discrete mathematics concepts.</p>"
        "<p><b>✨ Features:</b></p>"
        "<ul>"
        "<li>🎯 Interactive GUI for all discrete math concepts</li>"
        "<li>📚 Complete FAST University curriculum integration</li>"
        "<li>🔍 Real-time calculations and visualizations</li>"
        "<li>✅ Built-in testing and verification tools</li>"
        "<li>🚀 Modern, user-friendly interface</li>"
        "</ul>"
        "<p><b>Getting Started:</b> Select any tab above to begin exploring!</p>"
    );
    welcome.setStandardButtons(QMessageBox::Ok);
    welcome.setDefaultButton(QMessageBox::Ok);
    
    welcome.exec();
}

void MainWindow::onTabChanged(int index)
{
    if (index >= 0 && index < m_tabWidget->count()) {
        QString tabName = m_tabWidget->tabText(index);
        m_statusLabel->setText(QString("Active Module: %1").arg(tabName));
        
        // Optional: trigger any module-specific initialization
        QWidget *currentWidget = m_tabWidget->currentWidget();
        if (currentWidget) {
            // Could emit signals or call specific methods here
        }
    }
}