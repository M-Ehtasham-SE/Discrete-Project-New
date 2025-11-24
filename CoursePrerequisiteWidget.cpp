#include "CoursePrerequisiteWidget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>

CoursePrerequisiteWidget::CoursePrerequisiteWidget(QWidget *parent)
    : QWidget(parent)
    , m_manager(new CoursePrerequisiteManager())
{
    setupUI();
    loadCurriculum(); // Auto-load FAST curriculum
}

void CoursePrerequisiteWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Course Prerequisites Manager");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2a82da; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);
    
    // Create tab widget
    m_tabWidget = new QTabWidget();
    
    // Tab 1: Course Overview
    QWidget *overviewTab = new QWidget();
    QHBoxLayout *overviewLayout = new QHBoxLayout(overviewTab);
    
    // Left side - Course list and controls
    QVBoxLayout *leftLayout = new QVBoxLayout();
    
    // Search and filter controls
    QHBoxLayout *searchLayout = new QHBoxLayout();
    m_searchBox = new QLineEdit();
    m_searchBox->setPlaceholderText("Search courses...");
    QPushButton *searchButton = new QPushButton("Search");
    connect(searchButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::searchCourses);
    connect(m_searchBox, &QLineEdit::returnPressed, this, &CoursePrerequisiteWidget::searchCourses);
    
    m_semesterFilter = new QComboBox();
    m_semesterFilter->addItems({"All Semesters", "Semester 1", "Semester 2", "Semester 3", 
                               "Semester 4", "Semester 5", "Semester 6", "Semester 7", "Semester 8"});
    
    searchLayout->addWidget(new QLabel("Search:"));
    searchLayout->addWidget(m_searchBox);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(new QLabel("Filter:"));
    searchLayout->addWidget(m_semesterFilter);
    leftLayout->addLayout(searchLayout);
    
    // Course tree
    m_courseTree = new QTreeWidget();
    m_courseTree->setHeaderLabels({"Course", "Semester", "Credits"});
    m_courseTree->setAlternatingRowColors(true);
    m_courseTree->setSortingEnabled(true);
    connect(m_courseTree, &QTreeWidget::itemClicked, this, &CoursePrerequisiteWidget::onCourseSelected);
    leftLayout->addWidget(m_courseTree);
    
    // Control buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_loadButton = new QPushButton("Reload Curriculum");
    m_addCourseButton = new QPushButton("Add Course");
    m_addPrereqButton = new QPushButton("Add Prerequisite");
    QPushButton *exportButton = new QPushButton("Export Data");
    
    connect(m_loadButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::loadCurriculum);
    connect(m_addCourseButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::addNewCourse);
    connect(m_addPrereqButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::addNewPrerequisite);
    
    buttonLayout->addWidget(m_loadButton);
    buttonLayout->addWidget(m_addCourseButton);
    buttonLayout->addWidget(m_addPrereqButton);
    buttonLayout->addWidget(exportButton);
    leftLayout->addLayout(buttonLayout);
    
    overviewLayout->addLayout(leftLayout, 2);
    
    // Right side - Details display
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(new QLabel("Course Details:"));
    m_detailsDisplay = new QTextEdit();
    m_detailsDisplay->setReadOnly(true);
    m_detailsDisplay->setMaximumHeight(200);
    rightLayout->addWidget(m_detailsDisplay);
    
    rightLayout->addWidget(new QLabel("Prerequisites Chain:"));
    m_prereqDetails = new QTextEdit();
    m_prereqDetails->setReadOnly(true);
    rightLayout->addWidget(m_prereqDetails);
    
    overviewLayout->addLayout(rightLayout, 1);
    
    m_tabWidget->addTab(overviewTab, "Course Overview");
    
    // Tab 2: Prerequisites Analysis
    QWidget *prereqTab = new QWidget();
    QVBoxLayout *prereqLayout = new QVBoxLayout(prereqTab);
    
    QHBoxLayout *prereqControls = new QHBoxLayout();
    m_courseSearch = new QLineEdit();
    m_courseSearch->setPlaceholderText("Enter course name to check prerequisites...");
    m_checkButton = new QPushButton("Check Prerequisites");
    connect(m_checkButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::checkPrerequisites);
    
    prereqControls->addWidget(new QLabel("Course:"));
    prereqControls->addWidget(m_courseSearch);
    prereqControls->addWidget(m_checkButton);
    prereqLayout->addLayout(prereqControls);
    
    m_prereqTree = new QTreeWidget();
    m_prereqTree->setHeaderLabels({"Prerequisite Chain", "Level", "Status"});
    prereqLayout->addWidget(m_prereqTree);
    
    m_tabWidget->addTab(prereqTab, "Prerequisites Analysis");
    
    // Tab 3: Curriculum Visualization
    QWidget *visualTab = new QWidget();
    QVBoxLayout *visualLayout = new QVBoxLayout(visualTab);
    
    QHBoxLayout *visualControls = new QHBoxLayout();
    m_generateButton = new QPushButton("Generate Valid Order");
    m_showSemesterButton = new QPushButton("Show Semester View");
    m_showGraphButton = new QPushButton("Show Dependency Graph");
    
    connect(m_generateButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::generateValidOrder);
    connect(m_showSemesterButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::showSemesterView);
    connect(m_showGraphButton, &QPushButton::clicked, this, &CoursePrerequisiteWidget::showDependencyGraph);
    
    visualControls->addWidget(m_generateButton);
    visualControls->addWidget(m_showSemesterButton);
    visualControls->addWidget(m_showGraphButton);
    visualControls->addStretch();
    visualLayout->addLayout(visualControls);
    
    m_visualDisplay = new QTextEdit();
    m_visualDisplay->setReadOnly(true);
    m_visualDisplay->setFont(QFont("Consolas", 10));
    visualLayout->addWidget(m_visualDisplay);
    
    m_progressBar = new QProgressBar();
    m_progressBar->setVisible(false);
    visualLayout->addWidget(m_progressBar);
    
    m_tabWidget->addTab(visualTab, "Curriculum Visualization");
    
    m_mainLayout->addWidget(m_tabWidget);
}

void CoursePrerequisiteWidget::loadCurriculum()
{
    m_loadButton->setEnabled(false);
    m_loadButton->setText("Loading...");
    QApplication::processEvents();
    
    // Load FAST curriculum
    m_manager->loadFASTCurriculum();
    
    // Populate data structures
    m_allCourses.clear();
    m_prerequisites.clear();
    m_semesterMap.clear();
    
    // Extract course data from manager
    for (int i = 0; i < m_manager->courseCount; ++i) {
        QString course = QString::fromUtf8(m_manager->courses[i]);
        m_allCourses.append(course);
        
        // Assign semesters (simplified mapping)
        if (course.contains("Programming Fundamentals") || course.contains("Introduction to ICT") || 
            course.contains("Calculus") || course.contains("Applied Physics") || course.contains("Islamic Studies")) {
            m_semesterMap[course] = 1;
        } else if (course.contains("Object Oriented") || course.contains("Discrete Structures") || 
                   course.contains("Digital Logic") || course.contains("Communication") || course.contains("Pakistan Studies")) {
            m_semesterMap[course] = 2;
        } else if (course.contains("Data Structures") || course.contains("Database Systems") || 
                   course.contains("Linear Algebra") || course.contains("Differential")) {
            m_semesterMap[course] = 3;
        } else if (course.contains("Operating Systems") || course.contains("Computer Organization") || 
                   course.contains("Design and Analysis") || course.contains("Theory of Automata")) {
            m_semesterMap[course] = 4;
        } else if (course.contains("Computer Networks") || course.contains("Artificial Intelligence") || 
                   course.contains("Software Engineering")) {
            m_semesterMap[course] = 5;
        } else if (course.contains("Information Security") || course.contains("Human Computer") || 
                   course.contains("Compiler") || course.contains("Advanced Database")) {
            m_semesterMap[course] = 6;
        } else if (course.contains("Final Year Project I") || course.contains("Machine Learning") || 
                   course.contains("Computer Graphics")) {
            m_semesterMap[course] = 7;
        } else {
            m_semesterMap[course] = 8;
        }
    }
    
    // Extract prerequisites
    for (int i = 0; i < m_manager->prereqCount; ++i) {
        QString course = QString::fromUtf8(m_manager->prereqOf[i]);
        QString prereq = QString::fromUtf8(m_manager->prereqCourse[i]);
        m_prerequisites[course].append(prereq);
    }
    
    populateTree();
    updateCourseList();
    
    m_loadButton->setEnabled(true);
    m_loadButton->setText("Reload Curriculum");
    
    m_detailsDisplay->setText(QString("✅ Loaded %1 courses and %2 prerequisites from FAST University curriculum")
                             .arg(m_allCourses.size()).arg(m_manager->prereqCount));
}

void CoursePrerequisiteWidget::populateTree()
{
    m_courseTree->clear();
    
    for (int semester = 1; semester <= 8; ++semester) {
        QTreeWidgetItem *semesterItem = new QTreeWidgetItem(m_courseTree);
        semesterItem->setText(0, QString("Semester %1").arg(semester));
        semesterItem->setText(1, "");
        semesterItem->setText(2, "");
        semesterItem->setExpanded(true);
        
        // Add courses for this semester
        for (const QString &course : m_allCourses) {
            if (m_semesterMap.value(course, 8) == semester) {
                QTreeWidgetItem *courseItem = new QTreeWidgetItem(semesterItem);
                courseItem->setText(0, course);
                courseItem->setText(1, QString::number(semester));
                courseItem->setText(2, "3"); // Default credits
                
                // Color code based on prerequisites
                if (m_prerequisites.contains(course) && !m_prerequisites[course].isEmpty()) {
                    courseItem->setForeground(0, QColor(255, 165, 0)); // Orange for courses with prerequisites
                } else {
                    courseItem->setForeground(0, QColor(144, 238, 144)); // Light green for foundational courses
                }
            }
        }
    }
}

void CoursePrerequisiteWidget::updateCourseList()
{
    // This could be used for a separate list widget if needed
}

void CoursePrerequisiteWidget::onCourseSelected()
{
    QTreeWidgetItem *current = m_courseTree->currentItem();
    if (!current || current->parent() == nullptr) return; // Skip semester headers
    
    QString selectedCourse = current->text(0);
    
    // Update details display
    QString details = QString("<h3>%1</h3>").arg(selectedCourse);
    details += QString("<b>Semester:</b> %1<br>").arg(current->text(1));
    details += QString("<b>Credits:</b> %1<br><br>").arg(current->text(2));
    
    if (m_prerequisites.contains(selectedCourse)) {
        details += "<b>Prerequisites:</b><br>";
        for (const QString &prereq : m_prerequisites[selectedCourse]) {
            details += QString("• %1<br>").arg(prereq);
        }
    } else {
        details += "<b>Prerequisites:</b> None (Foundational Course)<br>";
    }
    
    m_detailsDisplay->setHtml(details);
    
    // Show prerequisite chain
    showPrerequisiteChain(selectedCourse);
}

void CoursePrerequisiteWidget::showPrerequisiteChain(const QString &course)
{
    QString chain = QString("<h3>Prerequisite Chain for: %1</h3>").arg(course);
    
    QStringList visited;
    QStringList currentLevel = {course};
    int level = 0;
    
    while (!currentLevel.isEmpty() && level < 10) { // Prevent infinite loops
        chain += QString("<h4>Level %1:</h4>").arg(level);
        QStringList nextLevel;
        
        for (const QString &c : currentLevel) {
            if (visited.contains(c)) continue;
            visited.append(c);
            
            chain += QString("• %1<br>").arg(c);
            
            if (m_prerequisites.contains(c)) {
                for (const QString &prereq : m_prerequisites[c]) {
                    if (!visited.contains(prereq)) {
                        nextLevel.append(prereq);
                    }
                }
            }
        }
        
        currentLevel = nextLevel;
        level++;
        chain += "<br>";
    }
    
    m_prereqDetails->setHtml(chain);
}

void CoursePrerequisiteWidget::searchCourses()
{
    QString searchTerm = m_searchBox->text().toLower();
    if (searchTerm.isEmpty()) {
        populateTree();
        return;
    }
    
    // Hide all items first
    for (int i = 0; i < m_courseTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem *semesterItem = m_courseTree->topLevelItem(i);
        for (int j = 0; j < semesterItem->childCount(); ++j) {
            QTreeWidgetItem *courseItem = semesterItem->child(j);
            bool matches = courseItem->text(0).toLower().contains(searchTerm);
            courseItem->setHidden(!matches);
        }
    }
}

void CoursePrerequisiteWidget::checkPrerequisites()
{
    QString courseName = m_courseSearch->text().trimmed();
    if (courseName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a course name.");
        return;
    }
    
    m_prereqTree->clear();
    
    // Find matching courses (case-insensitive partial match)
    QStringList matches;
    for (const QString &course : m_allCourses) {
        if (course.toLower().contains(courseName.toLower())) {
            matches.append(course);
        }
    }
    
    if (matches.isEmpty()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(m_prereqTree);
        item->setText(0, "Course not found");
        item->setText(1, "N/A");
        item->setText(2, "❌");
        return;
    }
    
    for (const QString &match : matches) {
        QTreeWidgetItem *courseItem = new QTreeWidgetItem(m_prereqTree);
        courseItem->setText(0, match);
        courseItem->setText(1, "0");
        courseItem->setText(2, "🎯");
        courseItem->setExpanded(true);
        
        // Add prerequisites recursively
        addPrerequisitesToTree(courseItem, match, 1);
    }
}

void CoursePrerequisiteWidget::addPrerequisitesToTree(QTreeWidgetItem *parent, const QString &course, int level)
{
    if (level > 5) return; // Prevent deep recursion
    
    if (m_prerequisites.contains(course)) {
        for (const QString &prereq : m_prerequisites[course]) {
            QTreeWidgetItem *prereqItem = new QTreeWidgetItem(parent);
            prereqItem->setText(0, prereq);
            prereqItem->setText(1, QString::number(level));
            prereqItem->setText(2, "✅");
            
            // Recursively add prerequisites of this prerequisite
            addPrerequisitesToTree(prereqItem, prereq, level + 1);
        }
    }
}

void CoursePrerequisiteWidget::generateValidOrder()
{
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 8);
    
    QString output = "<h2>📚 FAST University - Valid Course Sequence</h2>";
    output += "<p><i>Generated based on prerequisite dependencies</i></p><br>";
    
    for (int semester = 1; semester <= 8; ++semester) {
        m_progressBar->setValue(semester);
        QApplication::processEvents();
        
        output += QString("<h3>🎓 Semester %1</h3>").arg(semester);
        output += "<ul>";
        
        QStringList semesterCourses;
        for (const QString &course : m_allCourses) {
            if (m_semesterMap.value(course, 8) == semester) {
                semesterCourses.append(course);
            }
        }
        
        // Sort courses within semester
        semesterCourses.sort();
        
        for (const QString &course : semesterCourses) {
            QString status = "✅";
            if (m_prerequisites.contains(course) && !m_prerequisites[course].isEmpty()) {
                status = "⚠️"; // Has prerequisites
            }
            output += QString("<li>%1 %2</li>").arg(status, course);
        }
        
        output += "</ul><br>";
    }
    
    output += "<p><b>Legend:</b></p>";
    output += "<ul>";
    output += "<li>✅ - Foundational course (no prerequisites)</li>";
    output += "<li>⚠️ - Has prerequisites (ensure previous courses completed)</li>";
    output += "</ul>";
    
    m_visualDisplay->setHtml(output);
    m_progressBar->setVisible(false);
}

void CoursePrerequisiteWidget::showSemesterView()
{
    generateValidOrder(); // Reuse the same functionality
}

void CoursePrerequisiteWidget::showDependencyGraph()
{
    QString graph = "<h2>📊 Course Dependency Graph</h2>";
    graph += "<p><i>Prerequisite relationships visualization</i></p><br>";
    
    graph += "<div style='font-family: monospace; background-color: #1e1e1e; padding: 10px; border-radius: 5px;'>";
    
    for (const QString &course : m_allCourses) {
        if (m_prerequisites.contains(course) && !m_prerequisites[course].isEmpty()) {
            graph += QString("<b style='color: #4fc3f7;'>%1</b><br>").arg(course);
            
            for (const QString &prereq : m_prerequisites[course]) {
                graph += QString("    ↳ <span style='color: #81c784;'>%1</span><br>").arg(prereq);
            }
            graph += "<br>";
        }
    }
    
    graph += "</div>";
    
    m_visualDisplay->setHtml(graph);
}

void CoursePrerequisiteWidget::addNewCourse()
{
    bool ok;
    QString courseName = QInputDialog::getText(this, "Add New Course", 
                                              "Course name:", QLineEdit::Normal, "", &ok);
    if (ok && !courseName.isEmpty()) {
        if (!m_allCourses.contains(courseName)) {
            m_allCourses.append(courseName);
            m_semesterMap[courseName] = 8; // Default to semester 8
            populateTree();
            m_detailsDisplay->setText(QString("✅ Added course: %1").arg(courseName));
        } else {
            QMessageBox::information(this, "Information", "Course already exists.");
        }
    }
}

void CoursePrerequisiteWidget::addNewPrerequisite()
{
    QStringList courses = m_allCourses;
    courses.sort();
    
    bool ok;
    QString course = QInputDialog::getItem(this, "Add Prerequisite", 
                                          "Select course:", courses, 0, false, &ok);
    if (!ok) return;
    
    QString prereq = QInputDialog::getItem(this, "Add Prerequisite", 
                                          "Select prerequisite:", courses, 0, false, &ok);
    if (ok && course != prereq) {
        if (!m_prerequisites[course].contains(prereq)) {
            m_prerequisites[course].append(prereq);
            m_detailsDisplay->setText(QString("✅ Added prerequisite: %1 → %2").arg(prereq, course));
            
            // Update the current selection if it matches
            if (m_courseTree->currentItem() && m_courseTree->currentItem()->text(0) == course) {
                onCourseSelected();
            }
        } else {
            QMessageBox::information(this, "Information", "Prerequisite relationship already exists.");
        }
    }
}

void CoursePrerequisiteWidget::displayAllCourses()
{
    m_detailsDisplay->clear();
    m_detailsDisplay->append("<h3>All Available Courses</h3>");
    
    for (const auto& course : m_allCourses) {
        m_detailsDisplay->append(QString("• %1").arg(course));
    }
    
    m_detailsDisplay->append(QString("<br><b>Total Courses: %1</b>").arg(m_allCourses.size()));
}

void CoursePrerequisiteWidget::displayPrerequisites()
{
    QTreeWidgetItem *current = m_courseTree->currentItem();
    if (!current) {
        m_detailsDisplay->setText("Please select a course to view its prerequisites.");
        return;
    }
    
    QString course = current->text(0);
    showPrerequisiteChain(course);
}