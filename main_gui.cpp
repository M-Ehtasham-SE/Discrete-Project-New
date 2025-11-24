#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("UNIDISC Engine");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("FAST University");
    app.setApplicationDisplayName("UNIDISC Engine - Discrete Mathematics Learning Platform");
    
    // Set modern style
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Apply dark theme
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    app.setPalette(darkPalette);
    
    // Custom stylesheet for better appearance
    app.setStyleSheet(
        "QMainWindow {"
        "    background-color: #2b2b2b;"
        "}"
        "QMenuBar {"
        "    background-color: #3c3c3c;"
        "    color: white;"
        "    border: 1px solid #555;"
        "}"
        "QMenuBar::item:selected {"
        "    background-color: #2a82da;"
        "}"
        "QMenu {"
        "    background-color: #3c3c3c;"
        "    color: white;"
        "    border: 1px solid #555;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #2a82da;"
        "}"
        "QTabWidget::pane {"
        "    border: 1px solid #555;"
        "    background-color: #2b2b2b;"
        "}"
        "QTabBar::tab {"
        "    background-color: #3c3c3c;"
        "    color: white;"
        "    padding: 8px 16px;"
        "    margin-right: 2px;"
        "}"
        "QTabBar::tab:selected {"
        "    background-color: #2a82da;"
        "}"
        "QPushButton {"
        "    background-color: #3c3c3c;"
        "    border: 2px solid #555;"
        "    border-radius: 6px;"
        "    padding: 6px 12px;"
        "    color: white;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4a4a4a;"
        "    border-color: #2a82da;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2a82da;"
        "}"
        "QLineEdit, QTextEdit, QSpinBox, QDoubleSpinBox {"
        "    background-color: #191919;"
        "    border: 2px solid #555;"
        "    border-radius: 4px;"
        "    padding: 4px;"
        "    color: white;"
        "}"
        "QLineEdit:focus, QTextEdit:focus {"
        "    border-color: #2a82da;"
        "}"
        "QListWidget, QTreeWidget, QTableWidget {"
        "    background-color: #191919;"
        "    border: 1px solid #555;"
        "    alternate-background-color: #2b2b2b;"
        "}"
        "QScrollBar {"
        "    background-color: #3c3c3c;"
        "    width: 12px;"
        "}"
        "QScrollBar::handle {"
        "    background-color: #555;"
        "    border-radius: 6px;"
        "}"
        "QScrollBar::handle:hover {"
        "    background-color: #666;"
        "}"
    );
    
    MainWindow window;
    window.show();
    
    return app.exec();
}