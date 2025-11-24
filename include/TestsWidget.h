#ifndef TESTSWIDGET_H
#define TESTSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QGroupBox>
#include <QListWidget>

class TestsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestsWidget(QWidget *parent = nullptr);

private slots:
    void runAllTests();
    void runSelectedTest();
    void clearResults();
    void exportResults();

private:
    void setupUI();
    void runTest(const QString &testName);

    // UI Components
    QVBoxLayout *m_mainLayout;
    QListWidget *m_testsList;
    QPushButton *m_runAllBtn;
    QPushButton *m_runSelectedBtn;
    QPushButton *m_clearBtn;
    QPushButton *m_exportBtn;
    QTextEdit *m_resultsDisplay;
    QProgressBar *m_progressBar;
    QLabel *m_statusLabel;
    
    int m_testsRun;
    int m_testsPassed;
    int m_testsFailed;
};

#endif // TESTSWIDGET_H