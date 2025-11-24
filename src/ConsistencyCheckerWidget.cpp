#include "ConsistencyCheckerWidget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QHeaderView>
#include <QSplitter>

ConsistencyCheckerWidget::ConsistencyCheckerWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void ConsistencyCheckerWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Consistency Checker");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    m_mainLayout->addWidget(splitter);

    // Left panel - Input tabs
    m_tabWidget = new QTabWidget();
    m_tabWidget->setMaximumWidth(450);

    // Course Time Conflicts Tab
    m_timeTab = new QWidget();
    QVBoxLayout *timeLayout = new QVBoxLayout(m_timeTab);
    
    QGroupBox *timeGroup = new QGroupBox("Course Schedule");
    QVBoxLayout *timeGroupLayout = new QVBoxLayout(timeGroup);
    
    QGridLayout *timeInputLayout = new QGridLayout();
    timeInputLayout->addWidget(new QLabel("Course Name:"), 0, 0);
    m_courseNameInput = new QLineEdit();
    m_courseNameInput->setPlaceholderText("e.g., Data Structures");
    timeInputLayout->addWidget(m_courseNameInput, 0, 1);
    
    timeInputLayout->addWidget(new QLabel("Time Slot:"), 1, 0);
    m_timeSlotInput = new QLineEdit();
    m_timeSlotInput->setPlaceholderText("e.g., Mon 9-11, Tue 14-16");
    timeInputLayout->addWidget(m_timeSlotInput, 1, 1);
    
    timeGroupLayout->addLayout(timeInputLayout);
    
    QHBoxLayout *timeButtonsLayout = new QHBoxLayout();
    m_addCourseTimeBtn = new QPushButton("Add Course");
    m_addCourseTimeBtn->setStyleSheet("QPushButton { background-color: #28a745; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_removeCourseTimeBtn = new QPushButton("Remove Selected");
    m_clearCourseTimesBtn = new QPushButton("Clear All");
    
    timeButtonsLayout->addWidget(m_addCourseTimeBtn);
    timeButtonsLayout->addWidget(m_removeCourseTimeBtn);
    timeButtonsLayout->addWidget(m_clearCourseTimesBtn);
    timeGroupLayout->addLayout(timeButtonsLayout);
    
    m_courseTimesTable = new QTableWidget(0, 2);
    QStringList timeHeaders;
    timeHeaders << "Course" << "Time Slot";
    m_courseTimesTable->setHorizontalHeaderLabels(timeHeaders);
    m_courseTimesTable->horizontalHeader()->setStretchLastSection(true);
    m_courseTimesTable->setMaximumHeight(150);
    timeGroupLayout->addWidget(m_courseTimesTable);
    
    m_checkTimeConflictsBtn = new QPushButton("Check Time Conflicts");
    m_checkTimeConflictsBtn->setStyleSheet("QPushButton { background-color: #dc3545; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    timeGroupLayout->addWidget(m_checkTimeConflictsBtn);
    
    timeLayout->addWidget(timeGroup);
    timeLayout->addStretch();
    m_tabWidget->addTab(m_timeTab, "Time Conflicts");

    // Prerequisites Tab
    m_prereqTab = new QWidget();
    QVBoxLayout *prereqLayout = new QVBoxLayout(m_prereqTab);
    
    QGroupBox *prereqGroup = new QGroupBox("Prerequisites");
    QVBoxLayout *prereqGroupLayout = new QVBoxLayout(prereqGroup);
    
    QGridLayout *prereqInputLayout = new QGridLayout();
    prereqInputLayout->addWidget(new QLabel("Course:"), 0, 0);
    m_courseInput = new QLineEdit();
    m_courseInput->setPlaceholderText("e.g., Operating Systems");
    prereqInputLayout->addWidget(m_courseInput, 0, 1);
    
    prereqInputLayout->addWidget(new QLabel("Prerequisite:"), 1, 0);
    m_prerequisiteInput = new QLineEdit();
    m_prerequisiteInput->setPlaceholderText("e.g., Data Structures");
    prereqInputLayout->addWidget(m_prerequisiteInput, 1, 1);
    
    prereqGroupLayout->addLayout(prereqInputLayout);
    
    QHBoxLayout *prereqButtonsLayout = new QHBoxLayout();
    m_addPrereqBtn = new QPushButton("Add Prerequisite");
    m_addPrereqBtn->setStyleSheet("QPushButton { background-color: #007bff; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_removePrereqBtn = new QPushButton("Remove Selected");
    m_clearPrereqBtn = new QPushButton("Clear All");
    
    prereqButtonsLayout->addWidget(m_addPrereqBtn);
    prereqButtonsLayout->addWidget(m_removePrereqBtn);
    prereqButtonsLayout->addWidget(m_clearPrereqBtn);
    prereqGroupLayout->addLayout(prereqButtonsLayout);
    
    m_prerequisitesTable = new QTableWidget(0, 2);
    QStringList prereqHeaders;
    prereqHeaders << "Course" << "Prerequisite";
    m_prerequisitesTable->setHorizontalHeaderLabels(prereqHeaders);
    m_prerequisitesTable->horizontalHeader()->setStretchLastSection(true);
    m_prerequisitesTable->setMaximumHeight(150);
    prereqGroupLayout->addWidget(m_prerequisitesTable);
    
    m_checkPrereqBtn = new QPushButton("Check Prerequisite Violations");
    m_checkPrereqBtn->setStyleSheet("QPushButton { background-color: #ffc107; color: black; font-weight: bold; padding: 10px; border-radius: 4px; }");
    prereqGroupLayout->addWidget(m_checkPrereqBtn);
    
    prereqLayout->addWidget(prereqGroup);
    prereqLayout->addStretch();
    m_tabWidget->addTab(m_prereqTab, "Prerequisites");

    // Faculty Assignments Tab
    m_facultyTab = new QWidget();
    QVBoxLayout *facultyLayout = new QVBoxLayout(m_facultyTab);
    
    QGroupBox *facultyGroup = new QGroupBox("Faculty Assignments");
    QVBoxLayout *facultyGroupLayout = new QVBoxLayout(facultyGroup);
    
    QGridLayout *facultyInputLayout = new QGridLayout();
    facultyInputLayout->addWidget(new QLabel("Faculty Name:"), 0, 0);
    m_facultyNameInput = new QLineEdit();
    m_facultyNameInput->setPlaceholderText("e.g., Dr. Smith");
    facultyInputLayout->addWidget(m_facultyNameInput, 0, 1);
    
    facultyInputLayout->addWidget(new QLabel("Course:"), 1, 0);
    m_assignedCourseInput = new QLineEdit();
    m_assignedCourseInput->setPlaceholderText("e.g., Data Structures");
    facultyInputLayout->addWidget(m_assignedCourseInput, 1, 1);
    
    facultyInputLayout->addWidget(new QLabel("Room:"), 2, 0);
    m_roomInput = new QLineEdit();
    m_roomInput->setPlaceholderText("e.g., Room 101");
    facultyInputLayout->addWidget(m_roomInput, 2, 1);
    
    facultyGroupLayout->addLayout(facultyInputLayout);
    
    QHBoxLayout *facultyButtonsLayout = new QHBoxLayout();
    m_addFacultyBtn = new QPushButton("Add Assignment");
    m_addFacultyBtn->setStyleSheet("QPushButton { background-color: #6f42c1; color: white; font-weight: bold; padding: 8px; border-radius: 4px; }");
    m_removeFacultyBtn = new QPushButton("Remove Selected");
    m_clearFacultyBtn = new QPushButton("Clear All");
    
    facultyButtonsLayout->addWidget(m_addFacultyBtn);
    facultyButtonsLayout->addWidget(m_removeFacultyBtn);
    facultyButtonsLayout->addWidget(m_clearFacultyBtn);
    facultyGroupLayout->addLayout(facultyButtonsLayout);
    
    m_facultyTable = new QTableWidget(0, 3);
    QStringList facultyHeaders;
    facultyHeaders << "Faculty" << "Course" << "Room";
    m_facultyTable->setHorizontalHeaderLabels(facultyHeaders);
    m_facultyTable->horizontalHeader()->setStretchLastSection(true);
    m_facultyTable->setMaximumHeight(150);
    facultyGroupLayout->addWidget(m_facultyTable);
    
    m_checkFacultyBtn = new QPushButton("Check Faculty Conflicts");
    m_checkFacultyBtn->setStyleSheet("QPushButton { background-color: #17a2b8; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    facultyGroupLayout->addWidget(m_checkFacultyBtn);
    
    facultyLayout->addWidget(facultyGroup);
    facultyLayout->addStretch();
    m_tabWidget->addTab(m_facultyTab, "Faculty");

    splitter->addWidget(m_tabWidget);

    // Right panel - Results
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    
    QLabel *resultsLabel = new QLabel("Consistency Check Results:");
    resultsLabel->setStyleSheet("font-weight: bold; margin-bottom: 5px;");
    rightLayout->addWidget(resultsLabel);
    
    m_resultsDisplay = new QTextEdit();
    m_resultsDisplay->setReadOnly(true);
    m_resultsDisplay->setStyleSheet("background-color: #2b2b2b; color: #ffffff; border: 1px solid #555; font-family: 'Consolas', monospace; font-size: 13px;");
    rightLayout->addWidget(m_resultsDisplay);
    
    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_runAllBtn = new QPushButton("Run All Checks");
    m_runAllBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; font-weight: bold; padding: 10px; border-radius: 4px; }");
    m_loadExampleBtn = new QPushButton("Load Example");
    m_exportBtn = new QPushButton("Export Results");
    m_clearResultsBtn = new QPushButton("Clear Results");
    
    controlLayout->addWidget(m_runAllBtn);
    controlLayout->addWidget(m_loadExampleBtn);
    controlLayout->addWidget(m_exportBtn);
    controlLayout->addWidget(m_clearResultsBtn);
    rightLayout->addLayout(controlLayout);
    
    splitter->addWidget(rightPanel);
    splitter->setSizes({450, 350});

    // Connect signals
    connect(m_addCourseTimeBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::addCourseTime);
    connect(m_removeCourseTimeBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::removeCourseTime);
    connect(m_clearCourseTimesBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::clearCourseTimes);
    connect(m_checkTimeConflictsBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::checkTimeConflicts);
    
    connect(m_addPrereqBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::addPrerequisite);
    connect(m_removePrereqBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::removePrerequisite);
    connect(m_clearPrereqBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::clearPrerequisites);
    connect(m_checkPrereqBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::checkPrerequisiteViolations);
    
    connect(m_addFacultyBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::addFacultyAssignment);
    connect(m_removeFacultyBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::removeFacultyAssignment);
    connect(m_clearFacultyBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::clearFacultyAssignments);
    connect(m_checkFacultyBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::checkFacultyConflicts);
    
    connect(m_runAllBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::runAllChecks);
    connect(m_loadExampleBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::loadExample);
    connect(m_exportBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::exportResults);
    connect(m_clearResultsBtn, &QPushButton::clicked, this, &ConsistencyCheckerWidget::clearResults);
    
    // Allow Enter key
    connect(m_courseNameInput, &QLineEdit::returnPressed, this, &ConsistencyCheckerWidget::addCourseTime);
    connect(m_timeSlotInput, &QLineEdit::returnPressed, this, &ConsistencyCheckerWidget::addCourseTime);
    connect(m_courseInput, &QLineEdit::returnPressed, this, &ConsistencyCheckerWidget::addPrerequisite);
    connect(m_prerequisiteInput, &QLineEdit::returnPressed, this, &ConsistencyCheckerWidget::addPrerequisite);
    
    // Initial display
    m_resultsDisplay->setHtml("<p style='color: #cccccc; text-align: center; margin-top: 50px;'>Add data in the tabs and run consistency checks to identify conflicts and violations.</p>");
}

void ConsistencyCheckerWidget::addCourseTime()
{
    QString course = m_courseNameInput->text().trimmed();
    QString timeSlot = m_timeSlotInput->text().trimmed();
    
    if (course.isEmpty() || timeSlot.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both course name and time slot.");
        return;
    }
    
    m_courseTimes.append(QPair<QString, QString>(course, timeSlot));
    
    int row = m_courseTimesTable->rowCount();
    m_courseTimesTable->insertRow(row);
    m_courseTimesTable->setItem(row, 0, new QTableWidgetItem(course));
    m_courseTimesTable->setItem(row, 1, new QTableWidgetItem(timeSlot));
    
    m_courseNameInput->clear();
    m_timeSlotInput->clear();
    m_courseNameInput->setFocus();
}

void ConsistencyCheckerWidget::removeCourseTime()
{
    int currentRow = m_courseTimesTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a course to remove.");
        return;
    }
    
    m_courseTimes.removeAt(currentRow);
    m_courseTimesTable->removeRow(currentRow);
}

void ConsistencyCheckerWidget::clearCourseTimes()
{
    m_courseTimes.clear();
    m_courseTimesTable->setRowCount(0);
}

void ConsistencyCheckerWidget::checkTimeConflicts()
{
    if (m_courseTimes.size() < 2) {
        QMessageBox::warning(this, "Warning", "Please add at least 2 courses to check for conflicts.");
        return;
    }
    
    QString results = "<div style='background-color: #2b2b2b; color: #ffffff; padding: 15px;'>";
    results += "<h3 style='color: #FF5722;'>⏰ Course Time Conflict Analysis</h3>";
    results += "<hr style='border-color: #555;'>";
    
    results += "<h4 style='color: #2196F3;'>Course Schedule:</h4>";
    results += "<table style='width: 100%; border-collapse: collapse; color: #cccccc;'>";
    results += "<tr style='background-color: #444; color: #fff;'><th style='padding: 8px; border: 1px solid #666;'>Course</th><th style='padding: 8px; border: 1px solid #666;'>Time Slot</th></tr>";
    
    for (const auto &courseTime : m_courseTimes) {
        results += QString("<tr><td style='padding: 8px; border: 1px solid #666;'>%1</td><td style='padding: 8px; border: 1px solid #666;'>%2</td></tr>")
                   .arg(courseTime.first).arg(courseTime.second);
    }
    results += "</table><br>";
    
    // Check for conflicts
    QStringList conflicts;
    for (int i = 0; i < m_courseTimes.size(); ++i) {
        for (int j = i + 1; j < m_courseTimes.size(); ++j) {
            if (m_courseTimes[i].second == m_courseTimes[j].second) {
                conflicts.append(QString("⚠️ <b>%1</b> and <b>%2</b> both scheduled at <b>%3</b>")
                               .arg(m_courseTimes[i].first)
                               .arg(m_courseTimes[j].first)
                               .arg(m_courseTimes[i].second));
            }
        }
    }
    
    if (conflicts.isEmpty()) {
        results += "<p style='color: #4CAF50; font-size: 16px;'><b>✅ No time conflicts found!</b></p>";
        results += "<p style='color: #8BC34A;'>All courses have unique time slots.</p>";
    } else {
        results += QString("<h4 style='color: #F44336;'>❌ Found %1 Time Conflict(s):</h4>").arg(conflicts.size());
        results += "<ul style='color: #FFCDD2;'>";
        for (const QString &conflict : conflicts) {
            results += QString("<li>%1</li>").arg(conflict);
        }
        results += "</ul>";
    }
    
    results += "</div>";
    m_resultsDisplay->setHtml(results);
}

void ConsistencyCheckerWidget::addPrerequisite()
{
    QString course = m_courseInput->text().trimmed();
    QString prerequisite = m_prerequisiteInput->text().trimmed();
    
    if (course.isEmpty() || prerequisite.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both course and prerequisite.");
        return;
    }
    
    m_prerequisites.append(QPair<QString, QString>(course, prerequisite));
    
    int row = m_prerequisitesTable->rowCount();
    m_prerequisitesTable->insertRow(row);
    m_prerequisitesTable->setItem(row, 0, new QTableWidgetItem(course));
    m_prerequisitesTable->setItem(row, 1, new QTableWidgetItem(prerequisite));
    
    m_courseInput->clear();
    m_prerequisiteInput->clear();
    m_courseInput->setFocus();
}

void ConsistencyCheckerWidget::removePrerequisite()
{
    int currentRow = m_prerequisitesTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a prerequisite to remove.");
        return;
    }
    
    m_prerequisites.removeAt(currentRow);
    m_prerequisitesTable->removeRow(currentRow);
}

void ConsistencyCheckerWidget::clearPrerequisites()
{
    m_prerequisites.clear();
    m_prerequisitesTable->setRowCount(0);
}

void ConsistencyCheckerWidget::checkPrerequisiteViolations()
{
    if (m_prerequisites.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please add some prerequisites to check.");
        return;
    }
    
    QString results = "<div style='background-color: #2b2b2b; color: #ffffff; padding: 15px;'>";
    results += "<h3 style='color: #FF9800;'>📚 Prerequisite Violation Analysis</h3>";
    results += "<hr style='border-color: #555;'>";
    
    results += "<h4 style='color: #2196F3;'>Prerequisite Rules:</h4>";
    results += "<ul style='color: #cccccc;'>";
    for (const auto &prereq : m_prerequisites) {
        results += QString("<li><b>%1</b> requires <b>%2</b></li>").arg(prereq.first).arg(prereq.second);
    }
    results += "</ul>";
    
    // Check for circular dependencies
    QStringList violations;
    
    for (int i = 0; i < m_prerequisites.size(); ++i) {
        for (int j = 0; j < m_prerequisites.size(); ++j) {
            if (i != j) {
                // Check if A requires B and B requires A (circular)
                if (m_prerequisites[i].first == m_prerequisites[j].second &&
                    m_prerequisites[i].second == m_prerequisites[j].first) {
                    QString violation = QString("🔄 Circular dependency: <b>%1</b> ↔ <b>%2</b>")
                                       .arg(m_prerequisites[i].first).arg(m_prerequisites[i].second);
                    if (!violations.contains(violation)) {
                        violations.append(violation);
                    }
                }
            }
        }
    }
    
    // Check for longer chains (A->B->A)
    for (const auto &prereq1 : m_prerequisites) {
        for (const auto &prereq2 : m_prerequisites) {
            if (prereq1.first == prereq2.second && prereq1.second == prereq2.first && prereq1 != prereq2) {
                QString violation = QString("🔄 Chain dependency: <b>%1</b> → <b>%2</b> → <b>%1</b>")
                                   .arg(prereq1.first).arg(prereq1.second);
                if (!violations.contains(violation)) {
                    violations.append(violation);
                }
            }
        }
    }
    
    if (violations.isEmpty()) {
        results += "<p style='color: #4CAF50; font-size: 16px;'><b>✅ No prerequisite violations found!</b></p>";
        results += "<p style='color: #8BC34A;'>All prerequisite rules are consistent.</p>";
    } else {
        results += QString("<h4 style='color: #F44336;'>❌ Found %1 Violation(s):</h4>").arg(violations.size());
        results += "<ul style='color: #FFCDD2;'>";
        for (const QString &violation : violations) {
            results += QString("<li>%1</li>").arg(violation);
        }
        results += "</ul>";
    }
    
    results += "</div>";
    m_resultsDisplay->setHtml(results);
}

void ConsistencyCheckerWidget::addFacultyAssignment()
{
    QString faculty = m_facultyNameInput->text().trimmed();
    QString course = m_assignedCourseInput->text().trimmed();
    QString room = m_roomInput->text().trimmed();
    
    if (faculty.isEmpty() || course.isEmpty() || room.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in all fields.");
        return;
    }
    
    QStringList assignment;
    assignment << faculty << course << room;
    m_facultyAssignments.append(assignment);
    
    int row = m_facultyTable->rowCount();
    m_facultyTable->insertRow(row);
    m_facultyTable->setItem(row, 0, new QTableWidgetItem(faculty));
    m_facultyTable->setItem(row, 1, new QTableWidgetItem(course));
    m_facultyTable->setItem(row, 2, new QTableWidgetItem(room));
    
    m_facultyNameInput->clear();
    m_assignedCourseInput->clear();
    m_roomInput->clear();
    m_facultyNameInput->setFocus();
}

void ConsistencyCheckerWidget::removeFacultyAssignment()
{
    int currentRow = m_facultyTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select an assignment to remove.");
        return;
    }
    
    m_facultyAssignments.removeAt(currentRow);
    m_facultyTable->removeRow(currentRow);
}

void ConsistencyCheckerWidget::clearFacultyAssignments()
{
    m_facultyAssignments.clear();
    m_facultyTable->setRowCount(0);
}

void ConsistencyCheckerWidget::checkFacultyConflicts()
{
    if (m_facultyAssignments.size() < 2) {
        QMessageBox::warning(this, "Warning", "Please add at least 2 faculty assignments to check for conflicts.");
        return;
    }
    
    QString results = "<div style='background-color: #2b2b2b; color: #ffffff; padding: 15px;'>";
    results += "<h3 style='color: #9C27B0;'>👨‍🏫 Faculty Assignment Analysis</h3>";
    results += "<hr style='border-color: #555;'>";
    
    results += "<h4 style='color: #2196F3;'>Faculty Assignments:</h4>";
    results += "<table style='width: 100%; border-collapse: collapse; color: #cccccc;'>";
    results += "<tr style='background-color: #444; color: #fff;'><th style='padding: 8px; border: 1px solid #666;'>Faculty</th><th style='padding: 8px; border: 1px solid #666;'>Course</th><th style='padding: 8px; border: 1px solid #666;'>Room</th></tr>";
    
    for (const auto &assignment : m_facultyAssignments) {
        results += QString("<tr><td style='padding: 8px; border: 1px solid #666;'>%1</td><td style='padding: 8px; border: 1px solid #666;'>%2</td><td style='padding: 8px; border: 1px solid #666;'>%3</td></tr>")
                   .arg(assignment[0]).arg(assignment[1]).arg(assignment[2]);
    }
    results += "</table><br>";
    
    // Check for conflicts
    QStringList conflicts;
    
    // Check room conflicts
    for (int i = 0; i < m_facultyAssignments.size(); ++i) {
        for (int j = i + 1; j < m_facultyAssignments.size(); ++j) {
            if (m_facultyAssignments[i][2] == m_facultyAssignments[j][2]) {
                conflicts.append(QString("🏢 Room conflict: <b>%1</b> and <b>%2</b> both assigned to <b>%3</b>")
                               .arg(m_facultyAssignments[i][0])
                               .arg(m_facultyAssignments[j][0])
                               .arg(m_facultyAssignments[i][2]));
            }
        }
    }
    
    if (conflicts.isEmpty()) {
        results += "<p style='color: #4CAF50; font-size: 16px;'><b>✅ No faculty conflicts found!</b></p>";
        results += "<p style='color: #8BC34A;'>All faculty assignments are consistent.</p>";
    } else {
        results += QString("<h4 style='color: #F44336;'>❌ Found %1 Conflict(s):</h4>").arg(conflicts.size());
        results += "<ul style='color: #FFCDD2;'>";
        for (const QString &conflict : conflicts) {
            results += QString("<li>%1</li>").arg(conflict);
        }
        results += "</ul>";
    }
    
    results += "</div>";
    m_resultsDisplay->setHtml(results);
}

void ConsistencyCheckerWidget::runAllChecks()
{
    QString results = "<div style='background-color: #2b2b2b; color: #ffffff; padding: 15px;'>";
    results += "<h3 style='color: #E91E63;'>🔍 Complete Consistency Analysis</h3>";
    results += "<hr style='border-color: #555;'>";
    
    int totalIssues = 0;
    
    // Time conflicts
    if (!m_courseTimes.isEmpty()) {
        results += "<h4 style='color: #FF5722;'>⏰ Time Conflicts:</h4>";
        QStringList timeConflicts;
        for (int i = 0; i < m_courseTimes.size(); ++i) {
            for (int j = i + 1; j < m_courseTimes.size(); ++j) {
                if (m_courseTimes[i].second == m_courseTimes[j].second) {
                    timeConflicts.append(QString("%1 & %2 (%3)")
                                       .arg(m_courseTimes[i].first)
                                       .arg(m_courseTimes[j].first)
                                       .arg(m_courseTimes[i].second));
                    totalIssues++;
                }
            }
        }
        
        if (timeConflicts.isEmpty()) {
            results += "<p style='color: #4CAF50;'>✅ No time conflicts</p>";
        } else {
            results += "<ul style='color: #FFCDD2;'>";
            for (const QString &conflict : timeConflicts) {
                results += QString("<li>❌ %1</li>").arg(conflict);
            }
            results += "</ul>";
        }
    }
    
    // Prerequisite violations
    if (!m_prerequisites.isEmpty()) {
        results += "<h4 style='color: #FF9800;'>📚 Prerequisite Issues:</h4>";
        QStringList prereqIssues;
        
        for (int i = 0; i < m_prerequisites.size(); ++i) {
            for (int j = 0; j < m_prerequisites.size(); ++j) {
                if (i != j && m_prerequisites[i].first == m_prerequisites[j].second &&
                    m_prerequisites[i].second == m_prerequisites[j].first) {
                    QString issue = QString("Circular: %1 ↔ %2")
                                   .arg(m_prerequisites[i].first).arg(m_prerequisites[i].second);
                    if (!prereqIssues.contains(issue)) {
                        prereqIssues.append(issue);
                        totalIssues++;
                    }
                }
            }
        }
        
        if (prereqIssues.isEmpty()) {
            results += "<p style='color: #4CAF50;'>✅ No prerequisite violations</p>";
        } else {
            results += "<ul style='color: #FFCDD2;'>";
            for (const QString &issue : prereqIssues) {
                results += QString("<li>❌ %1</li>").arg(issue);
            }
            results += "</ul>";
        }
    }
    
    // Faculty conflicts
    if (!m_facultyAssignments.isEmpty()) {
        results += "<h4 style='color: #9C27B0;'>👨‍🏫 Faculty Issues:</h4>";
        QStringList facultyIssues;
        
        for (int i = 0; i < m_facultyAssignments.size(); ++i) {
            for (int j = i + 1; j < m_facultyAssignments.size(); ++j) {
                if (m_facultyAssignments[i][2] == m_facultyAssignments[j][2]) {
                    facultyIssues.append(QString("Room conflict: %1 & %2 in %3")
                                       .arg(m_facultyAssignments[i][0])
                                       .arg(m_facultyAssignments[j][0])
                                       .arg(m_facultyAssignments[i][2]));
                    totalIssues++;
                }
            }
        }
        
        if (facultyIssues.isEmpty()) {
            results += "<p style='color: #4CAF50;'>✅ No faculty conflicts</p>";
        } else {
            results += "<ul style='color: #FFCDD2;'>";
            for (const QString &issue : facultyIssues) {
                results += QString("<li>❌ %1</li>").arg(issue);
            }
            results += "</ul>";
        }
    }
    
    // Summary
    results += "<hr style='border-color: #555;'>";
    if (totalIssues == 0) {
        results += "<h4 style='color: #4CAF50; text-align: center;'>🎉 All Systems Consistent!</h4>";
        results += "<p style='color: #8BC34A; text-align: center;'>No conflicts or violations detected.</p>";
    } else {
        results += QString("<h4 style='color: #F44336; text-align: center;'>⚠️ %1 Issue(s) Found</h4>").arg(totalIssues);
        results += "<p style='color: #FFCDD2; text-align: center;'>Please resolve the conflicts above.</p>";
    }
    
    results += "</div>";
    m_resultsDisplay->setHtml(results);
}

void ConsistencyCheckerWidget::loadExample()
{
    // Clear existing data
    clearCourseTimes();
    clearPrerequisites();
    clearFacultyAssignments();
    
    // Add example course times
    m_courseTimes.append(QPair<QString, QString>("Data Structures", "Mon 9-11"));
    m_courseTimes.append(QPair<QString, QString>("Operating Systems", "Tue 14-16"));
    m_courseTimes.append(QPair<QString, QString>("Database Systems", "Mon 9-11")); // Conflict!
    
    // Update course times table
    for (int i = 0; i < m_courseTimes.size(); ++i) {
        m_courseTimesTable->insertRow(i);
        m_courseTimesTable->setItem(i, 0, new QTableWidgetItem(m_courseTimes[i].first));
        m_courseTimesTable->setItem(i, 1, new QTableWidgetItem(m_courseTimes[i].second));
    }
    
    // Add example prerequisites
    m_prerequisites.append(QPair<QString, QString>("Operating Systems", "Data Structures"));
    m_prerequisites.append(QPair<QString, QString>("Database Systems", "Data Structures"));
    
    // Update prerequisites table
    for (int i = 0; i < m_prerequisites.size(); ++i) {
        m_prerequisitesTable->insertRow(i);
        m_prerequisitesTable->setItem(i, 0, new QTableWidgetItem(m_prerequisites[i].first));
        m_prerequisitesTable->setItem(i, 1, new QTableWidgetItem(m_prerequisites[i].second));
    }
    
    // Add example faculty assignments
    QStringList assignment1;
    assignment1 << "Dr. Smith" << "Data Structures" << "Room 101";
    m_facultyAssignments.append(assignment1);
    
    QStringList assignment2;
    assignment2 << "Dr. Johnson" << "Operating Systems" << "Room 102";
    m_facultyAssignments.append(assignment2);
    
    QStringList assignment3;
    assignment3 << "Dr. Brown" << "Database Systems" << "Room 101"; // Room conflict!
    m_facultyAssignments.append(assignment3);
    
    // Update faculty table
    for (int i = 0; i < m_facultyAssignments.size(); ++i) {
        m_facultyTable->insertRow(i);
        m_facultyTable->setItem(i, 0, new QTableWidgetItem(m_facultyAssignments[i][0]));
        m_facultyTable->setItem(i, 1, new QTableWidgetItem(m_facultyAssignments[i][1]));
        m_facultyTable->setItem(i, 2, new QTableWidgetItem(m_facultyAssignments[i][2]));
    }
    
    QMessageBox::information(this, "Example Loaded", "Loaded example data with some conflicts. Click 'Run All Checks' to see the consistency analysis.");
}

void ConsistencyCheckerWidget::exportResults()
{
    if (m_resultsDisplay->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "No results to export. Please run checks first.");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Export Consistency Results", "consistency_check.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<!DOCTYPE html><html><head><title>Consistency Check Results</title>";
        stream << "<style>body { font-family: Arial, sans-serif; max-width: 1000px; margin: 0 auto; padding: 20px; background-color: #2b2b2b; color: #ffffff; }</style>";
        stream << "</head><body>";
        stream << m_resultsDisplay->toHtml();
        stream << "</body></html>";
        QMessageBox::information(this, "Success", "Results exported successfully!");
    }
}

void ConsistencyCheckerWidget::clearResults()
{
    m_resultsDisplay->clear();
    m_resultsDisplay->setHtml("<p style='color: #cccccc; text-align: center; margin-top: 50px;'>Add data in the tabs and run consistency checks to identify conflicts and violations.</p>");
}