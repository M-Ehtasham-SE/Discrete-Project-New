#include "StudentGroupWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QtMath>
#include <random>
#include <chrono>

StudentGroupWidget::StudentGroupWidget(QWidget *parent)
    : QWidget(parent)
    , m_manager(new StudentGroup())
{
    // Initialize projects list
    m_projects << "Database Project" << "AI Research" << "Web Application" 
               << "Mobile App" << "Game Development" << "Blockchain Project"
               << "Machine Learning" << "Computer Vision" << "IoT System" << "Cybersecurity Project";
    
    setupUI();
}

void StudentGroupWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Student Group Combination Manager");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Create tab widget
    m_tabWidget = new QTabWidget();
    
    // Tab 1: Combinations Calculator
    QWidget *combinationsTab = new QWidget();
    QVBoxLayout *combLayout = new QVBoxLayout(combinationsTab);
    
    // Input section
    QGroupBox *inputGroup = new QGroupBox("Input Parameters");
    QGridLayout *inputGrid = new QGridLayout(inputGroup);
    
    inputGrid->addWidget(new QLabel("Total Students (n):"), 0, 0);
    m_totalStudentsSpinBox = new QSpinBox();
    m_totalStudentsSpinBox->setRange(1, 100);
    m_totalStudentsSpinBox->setValue(20);
    m_totalStudentsSpinBox->setToolTip("Total number of students available");
    connect(m_totalStudentsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &StudentGroupWidget::onStudentCountChanged);
    inputGrid->addWidget(m_totalStudentsSpinBox, 0, 1);
    
    inputGrid->addWidget(new QLabel("Group Size (r):"), 1, 0);
    m_groupSizeSpinBox = new QSpinBox();
    m_groupSizeSpinBox->setRange(1, 20);
    m_groupSizeSpinBox->setValue(4);
    m_groupSizeSpinBox->setToolTip("Number of students per group");
    connect(m_groupSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &StudentGroupWidget::onGroupSizeChanged);
    inputGrid->addWidget(m_groupSizeSpinBox, 1, 1);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_calculateButton = new QPushButton("Calculate Combinations");
    m_calculateButton->setToolTip("Calculate C(n,r) = n! / (r!(n-r)!)");
    connect(m_calculateButton, &QPushButton::clicked, this, &StudentGroupWidget::calculateCombinations);
    
    QPushButton *permutationButton = new QPushButton("Calculate Permutations");
    permutationButton->setToolTip("Calculate P(n,r) = n! / (n-r)!");
    connect(permutationButton, &QPushButton::clicked, this, &StudentGroupWidget::calculatePermutations);
    
    m_showFormulaButton = new QPushButton("Show Formula");
    connect(m_showFormulaButton, &QPushButton::clicked, this, &StudentGroupWidget::showCombinationFormula);
    
    buttonLayout->addWidget(m_calculateButton);
    buttonLayout->addWidget(permutationButton);
    buttonLayout->addWidget(m_showFormulaButton);
    buttonLayout->addStretch();
    
    combLayout->addWidget(inputGroup);
    combLayout->addLayout(buttonLayout);
    
    // Formula display
    m_formulaLabel = new QLabel();
    m_formulaLabel->setStyleSheet("font-family: 'Times New Roman'; font-size: 14px; color: #4fc3f7; background-color: #2b2b2b; padding: 10px; border-radius: 5px;");
    m_formulaLabel->setAlignment(Qt::AlignCenter);
    combLayout->addWidget(m_formulaLabel);
    
    // Result display
    m_resultLabel = new QLabel();
    m_resultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #81c784; background-color: #1e1e1e; padding: 15px; border-radius: 8px;");
    m_resultLabel->setAlignment(Qt::AlignCenter);
    combLayout->addWidget(m_resultLabel);
    
    // Detailed results
    m_resultDisplay = new QTextEdit();
    m_resultDisplay->setReadOnly(true);
    m_resultDisplay->setMaximumHeight(200);
    combLayout->addWidget(m_resultDisplay);
    
    m_tabWidget->addTab(combinationsTab, "Combinations Calculator");
    
    // Tab 2: Student Management
    QWidget *studentsTab = new QWidget();
    QHBoxLayout *studentsLayout = new QHBoxLayout(studentsTab);
    
    // Left side - Student list
    QVBoxLayout *leftSide = new QVBoxLayout();
    leftSide->addWidget(new QLabel("Student List:"));
    
    m_studentsList = new QListWidget();
    m_studentsList->setAlternatingRowColors(true);
    leftSide->addWidget(m_studentsList);
    
    m_studentCountLabel = new QLabel("Total Students: 0");
    m_studentCountLabel->setStyleSheet("font-weight: bold; color: #4fc3f7;");
    leftSide->addWidget(m_studentCountLabel);
    
    studentsLayout->addLayout(leftSide, 2);
    
    // Right side - Controls
    QVBoxLayout *rightSide = new QVBoxLayout();
    
    QGroupBox *controlGroup = new QGroupBox("Student Management");
    QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);
    
    m_studentNameEdit = new QLineEdit();
    m_studentNameEdit->setPlaceholderText("Enter student name...");
    connect(m_studentNameEdit, &QLineEdit::returnPressed, this, &StudentGroupWidget::addStudent);
    controlLayout->addWidget(m_studentNameEdit);
    
    m_addStudentButton = new QPushButton("Add Student");
    connect(m_addStudentButton, &QPushButton::clicked, this, &StudentGroupWidget::addStudent);
    controlLayout->addWidget(m_addStudentButton);
    
    m_removeStudentButton = new QPushButton("Remove Selected");
    connect(m_removeStudentButton, &QPushButton::clicked, this, &StudentGroupWidget::removeStudent);
    controlLayout->addWidget(m_removeStudentButton);
    
    m_clearStudentsButton = new QPushButton("Clear All");
    connect(m_clearStudentsButton, &QPushButton::clicked, this, &StudentGroupWidget::clearStudents);
    controlLayout->addWidget(m_clearStudentsButton);
    
    controlLayout->addStretch();
    rightSide->addWidget(controlGroup);
    
    studentsLayout->addLayout(rightSide, 1);
    
    m_tabWidget->addTab(studentsTab, "Student Management");
    
    // Tab 3: Project Assignment
    QWidget *projectTab = new QWidget();
    QVBoxLayout *projectLayout = new QVBoxLayout(projectTab);
    
    // Assignment controls
    QGroupBox *assignGroup = new QGroupBox("Project Assignment Parameters");
    QGridLayout *assignGrid = new QGridLayout(assignGroup);
    
    assignGrid->addWidget(new QLabel("Project:"), 0, 0);
    m_projectComboBox = new QComboBox();
    m_projectComboBox->addItems(m_projects);
    assignGrid->addWidget(m_projectComboBox, 0, 1);
    
    assignGrid->addWidget(new QLabel("Members per Group:"), 1, 0);
    m_membersPerGroupSpinBox = new QSpinBox();
    m_membersPerGroupSpinBox->setRange(2, 10);
    m_membersPerGroupSpinBox->setValue(4);
    assignGrid->addWidget(m_membersPerGroupSpinBox, 1, 1);
    
    m_assignButton = new QPushButton("Assign Groups");
    connect(m_assignButton, &QPushButton::clicked, this, &StudentGroupWidget::assignProjectGroups);
    assignGrid->addWidget(m_assignButton, 2, 0, 1, 2);
    
    projectLayout->addWidget(assignGroup);
    
    // Assignment results table
    m_assignmentTable = new QTableWidget();
    m_assignmentTable->setColumnCount(3);
    m_assignmentTable->setHorizontalHeaderLabels({"Group", "Members", "Project"});
    m_assignmentTable->horizontalHeader()->setStretchLastSection(true);
    projectLayout->addWidget(m_assignmentTable);
    
    // Assignment details
    m_assignmentDetails = new QTextEdit();
    m_assignmentDetails->setReadOnly(true);
    m_assignmentDetails->setMaximumHeight(150);
    projectLayout->addWidget(m_assignmentDetails);
    
    m_tabWidget->addTab(projectTab, "Project Assignment");
    
    // Tab 4: Event Planning
    QWidget *eventTab = new QWidget();
    QVBoxLayout *eventLayout = new QVBoxLayout(eventTab);
    
    QGroupBox *eventGroup = new QGroupBox("Event Planning with Combinations");
    QGridLayout *eventGrid = new QGridLayout(eventGroup);
    
    eventGrid->addWidget(new QLabel("Total Attendees:"), 0, 0);
    m_eventAttendeesSpinBox = new QSpinBox();
    m_eventAttendeesSpinBox->setRange(5, 200);
    m_eventAttendeesSpinBox->setValue(30);
    eventGrid->addWidget(m_eventAttendeesSpinBox, 0, 1);
    
    eventGrid->addWidget(new QLabel("Committee Size:"), 1, 0);
    m_committeeStzeSpinBox = new QSpinBox();
    m_committeeStzeSpinBox->setRange(3, 15);
    m_committeeStzeSpinBox->setValue(5);
    eventGrid->addWidget(m_committeeStzeSpinBox, 1, 1);
    
    m_planEventButton = new QPushButton("Plan Event");
    connect(m_planEventButton, &QPushButton::clicked, this, &StudentGroupWidget::planEvent);
    eventGrid->addWidget(m_planEventButton, 2, 0, 1, 2);
    
    eventLayout->addWidget(eventGroup);
    
    m_eventResults = new QTextEdit();
    m_eventResults->setReadOnly(true);
    eventLayout->addWidget(m_eventResults);
    
    m_tabWidget->addTab(eventTab, "Event Planning");
    
    // Tab 5: Interactive Visualization
    QWidget *visualTab = new QWidget();
    QVBoxLayout *visualLayout = new QVBoxLayout(visualTab);
    
    QGroupBox *sliderGroup = new QGroupBox("Interactive Combination Explorer");
    QGridLayout *sliderGrid = new QGridLayout(sliderGroup);
    
    sliderGrid->addWidget(new QLabel("n (Total):"), 0, 0);
    m_nSlider = new QSlider(Qt::Horizontal);
    m_nSlider->setRange(1, 50);
    m_nSlider->setValue(10);
    m_nLabel = new QLabel("10");
    connect(m_nSlider, &QSlider::valueChanged, [this](int value) {
        m_nLabel->setText(QString::number(value));
        updateCombinationDisplay();
    });
    sliderGrid->addWidget(m_nSlider, 0, 1);
    sliderGrid->addWidget(m_nLabel, 0, 2);
    
    sliderGrid->addWidget(new QLabel("r (Choose):"), 1, 0);
    m_rSlider = new QSlider(Qt::Horizontal);
    m_rSlider->setRange(1, 10);
    m_rSlider->setValue(3);
    m_rLabel = new QLabel("3");
    connect(m_rSlider, &QSlider::valueChanged, [this](int value) {
        m_rLabel->setText(QString::number(value));
        updateCombinationDisplay();
    });
    sliderGrid->addWidget(m_rSlider, 1, 1);
    sliderGrid->addWidget(m_rLabel, 1, 2);
    
    visualLayout->addWidget(sliderGroup);
    
    m_visualizationDisplay = new QTextEdit();
    m_visualizationDisplay->setReadOnly(true);
    visualLayout->addWidget(m_visualizationDisplay);
    
    // Export button
    m_exportButton = new QPushButton("Export Results");
    connect(m_exportButton, &QPushButton::clicked, this, &StudentGroupWidget::exportResults);
    visualLayout->addWidget(m_exportButton);
    
    m_tabWidget->addTab(visualTab, "Interactive Explorer");
    
    m_mainLayout->addWidget(m_tabWidget);
    
    // Initialize displays
    updateCombinationDisplay();
    onStudentCountChanged();
}

void StudentGroupWidget::calculateCombinations()
{
    int n = m_totalStudentsSpinBox->value();
    int r = m_groupSizeSpinBox->value();
    
    if (r > n) {
        QMessageBox::warning(this, "Invalid Input", "Group size cannot be larger than total students!");
        return;
    }
    
    long long result = combination(n, r);
    showCalculationSteps(result, n, r, "Combination");
    
    QString resultText = QString("C(%1, %2) = %3").arg(n).arg(r).arg(result);
    m_resultLabel->setText(resultText);
}

void StudentGroupWidget::calculatePermutations()
{
    int n = m_totalStudentsSpinBox->value();
    int r = m_groupSizeSpinBox->value();
    
    if (r > n) {
        QMessageBox::warning(this, "Invalid Input", "Group size cannot be larger than total students!");
        return;
    }
    
    long long result = permutation(n, r);
    showCalculationSteps(result, n, r, "Permutation");
    
    QString resultText = QString("P(%1, %2) = %3").arg(n).arg(r).arg(result);
    m_resultLabel->setText(resultText);
}

void StudentGroupWidget::showCalculationSteps(long long result, int n, int r, const QString &type)
{
    QString steps = QString("<h3>%1 Calculation Steps</h3>").arg(type);
    
    if (type == "Combination") {
        steps += QString("<p><b>Formula:</b> C(n,r) = n! / (r!(n-r)!)</p>");
        steps += QString("<p><b>Given:</b> n = %1, r = %2</p>").arg(n).arg(r);
        steps += QString("<p><b>Calculation:</b></p>");
        steps += QString("<p>C(%1,%2) = %1! / (%2!×%3!)</p>").arg(n).arg(r).arg(n-r);
        steps += QString("<p>= %1 / (%2 × %3)</p>").arg(factorial(n)).arg(factorial(r)).arg(factorial(n-r));
        steps += QString("<p>= %1 / %2</p>").arg(factorial(n)).arg(factorial(r) * factorial(n-r));
    } else {
        steps += QString("<p><b>Formula:</b> P(n,r) = n! / (n-r)!</p>");
        steps += QString("<p><b>Given:</b> n = %1, r = %2</p>").arg(n).arg(r);
        steps += QString("<p><b>Calculation:</b></p>");
        steps += QString("<p>P(%1,%2) = %1! / %3!</p>").arg(n).arg(r).arg(n-r);
        steps += QString("<p>= %1 / %2</p>").arg(factorial(n)).arg(factorial(n-r));
    }
    
    steps += QString("<p><b>Result:</b> %1</p>").arg(result);
    
    if (type == "Combination") {
        steps += "<p><b>Interpretation:</b> There are " + QString::number(result) + 
                " different ways to choose " + QString::number(r) + 
                " students from " + QString::number(n) + " students (order doesn't matter).</p>";
    } else {
        steps += "<p><b>Interpretation:</b> There are " + QString::number(result) + 
                " different ways to arrange " + QString::number(r) + 
                " students from " + QString::number(n) + " students (order matters).</p>";
    }
    
    m_resultDisplay->setHtml(steps);
}

long long StudentGroupWidget::factorial(int n)
{
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long long StudentGroupWidget::combination(int n, int r)
{
    if (r > n || r < 0) return 0;
    if (r == 0 || r == n) return 1;
    
    // Use the more efficient calculation to avoid overflow
    long long result = 1;
    for (int i = 1; i <= r; ++i) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

long long StudentGroupWidget::permutation(int n, int r)
{
    if (r > n || r < 0) return 0;
    if (r == 0) return 1;
    
    long long result = 1;
    for (int i = n; i > n - r; --i) {
        result *= i;
    }
    return result;
}

void StudentGroupWidget::assignProjectGroups()
{
    if (m_students.isEmpty()) {
        QMessageBox::information(this, "No Students", 
            "Please add students in the Student Management tab first.");
        return;
    }
    
    int groupSize = m_membersPerGroupSpinBox->value();
    QString project = m_projectComboBox->currentText();
    
    if (m_students.size() < groupSize) {
        QMessageBox::warning(this, "Insufficient Students", 
            QString("Need at least %1 students to form a group.").arg(groupSize));
        return;
    }
    
    // Clear previous assignments
    m_assignmentTable->setRowCount(0);
    m_groupAssignments.clear();
    
    // Calculate number of complete groups
    int numGroups = m_students.size() / groupSize;
    int remainder = m_students.size() % groupSize;
    
    // Create groups
    QStringList availableStudents = m_students;
    
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < numGroups; ++i) {
        QStringList groupMembers;
        QString groupName = QString("Group %1").arg(i + 1);
        
        // Randomly assign students to groups
        for (int j = 0; j < groupSize; ++j) {
            if (!availableStudents.isEmpty()) {
                std::uniform_int_distribution<> dis(0, availableStudents.size() - 1);
                int randomIndex = dis(gen);
                groupMembers.append(availableStudents.takeAt(randomIndex));
            }
        }
        
        m_groupAssignments[groupName] = groupMembers;
        
        // Add to table
        int row = m_assignmentTable->rowCount();
        m_assignmentTable->insertRow(row);
        m_assignmentTable->setItem(row, 0, new QTableWidgetItem(groupName));
        m_assignmentTable->setItem(row, 1, new QTableWidgetItem(groupMembers.join(", ")));
        m_assignmentTable->setItem(row, 2, new QTableWidgetItem(project));
    }
    
    // Handle remaining students
    QString details = QString("<h3>Group Assignment Results</h3>");
    details += QString("<p><b>Project:</b> %1</p>").arg(project);
    details += QString("<p><b>Group Size:</b> %1 members</p>").arg(groupSize);
    details += QString("<p><b>Total Students:</b> %1</p>").arg(m_students.size());
    details += QString("<p><b>Groups Formed:</b> %1</p>").arg(numGroups);
    
    if (remainder > 0) {
        details += QString("<p><b>Remaining Students:</b> %1 (%2)</p>")
                   .arg(remainder).arg(availableStudents.join(", "));
        details += "<p><i>Suggestion: These students can be distributed among existing groups or form a smaller group.</i></p>";
    }
    
    // Calculate possible combinations
    long long possibleCombinations = combination(m_students.size(), groupSize);
    details += QString("<p><b>Total Possible Group Combinations:</b> %1</p>").arg(possibleCombinations);
    
    m_assignmentDetails->setHtml(details);
}

void StudentGroupWidget::planEvent()
{
    int totalAttendees = m_eventAttendeesSpinBox->value();
    int committeeSize = m_committeeStzeSpinBox->value();
    
    if (committeeSize > totalAttendees) {
        QMessageBox::warning(this, "Invalid Input", "Committee size cannot be larger than total attendees!");
        return;
    }
    
    long long committeeCombinations = combination(totalAttendees, committeeSize);
    
    QString eventPlan = "<h2>🎪 Event Planning Analysis</h2>";
    eventPlan += QString("<p><b>Total Attendees:</b> %1</p>").arg(totalAttendees);
    eventPlan += QString("<p><b>Committee Size:</b> %1</p>").arg(committeeSize);
    eventPlan += QString("<p><b>Possible Committee Combinations:</b> %1</p>").arg(committeeCombinations);
    
    eventPlan += "<h3>📊 Event Planning Scenarios:</h3>";
    eventPlan += "<ul>";
    eventPlan += QString("<li><b>Organizing Committee:</b> %1 ways to select %2 organizers</li>")
                 .arg(committeeCombinations).arg(committeeSize);
    
    // Additional scenarios
    if (totalAttendees >= 8) {
        long long teamCombinations = combination(totalAttendees, 4);
        eventPlan += QString("<li><b>Competition Teams (4 members):</b> %1 possible teams</li>")
                     .arg(teamCombinations);
    }
    
    if (totalAttendees >= 6) {
        long long judgeCombinations = combination(totalAttendees, 3);
        eventPlan += QString("<li><b>Judging Panel (3 judges):</b> %1 possible panels</li>")
                     .arg(judgeCombinations);
    }
    
    eventPlan += "</ul>";
    
    eventPlan += "<h3>🎯 Recommendations:</h3>";
    eventPlan += "<ul>";
    if (committeeCombinations > 1000) {
        eventPlan += "<li>High number of combinations - use additional criteria for selection</li>";
    }
    if (committeeSize < totalAttendees * 0.1) {
        eventPlan += "<li>Committee size is small relative to attendees - consider increasing for better representation</li>";
    }
    if (committeeSize > totalAttendees * 0.3) {
        eventPlan += "<li>Committee size is large - consider reducing for more efficient decision making</li>";
    }
    eventPlan += "<li>Consider role-specific requirements when making final selection</li>";
    eventPlan += "</ul>";
    
    m_eventResults->setHtml(eventPlan);
}

void StudentGroupWidget::addStudent()
{
    QString name = m_studentNameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Empty Name", "Please enter a student name.");
        return;
    }
    
    if (m_students.contains(name)) {
        QMessageBox::information(this, "Duplicate", "Student already exists in the list.");
        return;
    }
    
    m_students.append(name);
    m_studentsList->addItem(name);
    m_studentNameEdit->clear();
    m_studentCountLabel->setText(QString("Total Students: %1").arg(m_students.size()));
    
    // Update the total students spinbox
    m_totalStudentsSpinBox->setValue(m_students.size());
}

void StudentGroupWidget::removeStudent()
{
    int currentRow = m_studentsList->currentRow();
    if (currentRow < 0) {
        QMessageBox::information(this, "No Selection", "Please select a student to remove.");
        return;
    }
    
    QString studentName = m_studentsList->item(currentRow)->text();
    m_students.removeAt(currentRow);
    delete m_studentsList->takeItem(currentRow);
    m_studentCountLabel->setText(QString("Total Students: %1").arg(m_students.size()));
    
    // Update the total students spinbox
    m_totalStudentsSpinBox->setValue(m_students.size());
}

void StudentGroupWidget::clearStudents()
{
    if (m_students.isEmpty()) return;
    
    int ret = QMessageBox::question(this, "Clear All Students", 
                                   "Are you sure you want to remove all students?",
                                   QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        m_students.clear();
        m_studentsList->clear();
        m_studentCountLabel->setText("Total Students: 0");
        m_totalStudentsSpinBox->setValue(1);
    }
}

void StudentGroupWidget::exportResults()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Results", 
                                                   "student_groups.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "<html><head><title>Student Group Analysis Results</title></head><body>";
        stream << "<h1>Student Group Combination Analysis</h1>";
        stream << "<h2>Parameters:</h2>";
        stream << QString("<p>Total Students: %1</p>").arg(m_totalStudentsSpinBox->value());
        stream << QString("<p>Group Size: %1</p>").arg(m_groupSizeSpinBox->value());
        
        if (!m_students.isEmpty()) {
            stream << "<h2>Student List:</h2><ul>";
            for (const QString &student : m_students) {
                stream << "<li>" << student << "</li>";
            }
            stream << "</ul>";
        }
        
        stream << "<h2>Calculation Results:</h2>";
        stream << m_resultDisplay->toHtml();
        stream << "</body></html>";
        
        QMessageBox::information(this, "Export Complete", "Results exported successfully!");
    }
}

void StudentGroupWidget::showCombinationFormula()
{
    QString formula = "<h2>📐 Combination and Permutation Formulas</h2>";
    formula += "<h3>Combinations (Order doesn't matter):</h3>";
    formula += "<p style='font-size: 16px; text-align: center;'>";
    formula += "<b>C(n,r) = n! / (r!(n-r)!)</b>";
    formula += "</p>";
    formula += "<p>Where:</p>";
    formula += "<ul>";
    formula += "<li><b>n</b> = total number of items</li>";
    formula += "<li><b>r</b> = number of items to choose</li>";
    formula += "<li><b>!</b> = factorial (n! = n × (n-1) × (n-2) × ... × 1)</li>";
    formula += "</ul>";
    
    formula += "<h3>Permutations (Order matters):</h3>";
    formula += "<p style='font-size: 16px; text-align: center;'>";
    formula += "<b>P(n,r) = n! / (n-r)!</b>";
    formula += "</p>";
    
    formula += "<h3>Examples:</h3>";
    formula += "<ul>";
    formula += "<li><b>C(5,3)</b> = 5!/(3!×2!) = 120/(6×2) = 10 ways</li>";
    formula += "<li><b>P(5,3)</b> = 5!/2! = 120/2 = 60 ways</li>";
    formula += "</ul>";
    
    formula += "<h3>When to use which:</h3>";
    formula += "<ul>";
    formula += "<li><b>Combinations:</b> Selecting team members, choosing committee</li>";
    formula += "<li><b>Permutations:</b> Arranging people in line, assigning positions</li>";
    formula += "</ul>";
    
    m_formulaLabel->setText(formula);
}

void StudentGroupWidget::onStudentCountChanged()
{
    int n = m_totalStudentsSpinBox->value();
    int r = m_groupSizeSpinBox->value();
    
    if (r > n) {
        m_groupSizeSpinBox->setValue(n);
    }
    m_groupSizeSpinBox->setMaximum(n);
    
    updateCombinationDisplay();
}

void StudentGroupWidget::onGroupSizeChanged()
{
    updateCombinationDisplay();
}

void StudentGroupWidget::updateCombinationDisplay()
{
    int n = qMax(m_nSlider->value(), m_totalStudentsSpinBox->value());
    int r = qMin(m_rSlider->value(), n);
    
    if (r > n) {
        m_rSlider->setValue(n);
        r = n;
    }
    m_rSlider->setMaximum(n);
    
    long long comb = combination(n, r);
    long long perm = permutation(n, r);
    
    QString display = QString("<h3>📊 Live Combination Calculator</h3>");
    display += QString("<p><b>Parameters:</b> n = %1, r = %2</p>").arg(n).arg(r);
    display += QString("<p><b>Combinations C(%1,%2) = %3</b></p>").arg(n).arg(r).arg(comb);
    display += QString("<p><b>Permutations P(%1,%2) = %4</b></p>").arg(n).arg(r).arg(perm);
    display += QString("<p><b>Ratio (P/C) = %1</b></p>").arg(r > 0 ? factorial(r) : 1);
    
    // Visual representation for small numbers
    if (n <= 10 && r <= 5) {
        display += "<h4>📈 Visualization:</h4>";
        display += QString("<p>Imagine choosing %1 items from %2 total items:</p>").arg(r).arg(n);
        
        QString items;
        for (int i = 1; i <= n; ++i) {
            if (i <= r) {
                items += QString("🔵 ");
            } else {
                items += QString("⚪ ");
            }
        }
        display += QString("<p>%1</p>").arg(items);
        display += QString("<p>Blue circles represent chosen items (%1/%2)</p>").arg(r).arg(n);
    }
    
    m_visualizationDisplay->setHtml(display);
}