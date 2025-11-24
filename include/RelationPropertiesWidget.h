#ifndef RELATIONPROPERTIESWIDGET_H
#define RELATIONPROPERTIESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QSplitter>
#include <QFrame>

class RelationPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RelationPropertiesWidget(QWidget *parent = nullptr);

private slots:
    void addSetElement();
    void removeSetElement();
    void clearSet();
    void addRelationPair();
    void removeRelationPair();
    void clearRelations();
    void checkAllProperties();
    void exportResults();
    void generateExample();

private:
    void setupUI();
    void updatePropertiesDisplay();
    void updateRelationDisplay();
    bool isReflexive();
    bool isSymmetric();
    bool isTransitive();
    bool isAntiSymmetric();
    QString getRelationType();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QSplitter *m_mainSplitter;

    // Set input section
    QGroupBox *m_setGroup;
    QLineEdit *m_setElementInput;
    QPushButton *m_addSetBtn;
    QPushButton *m_removeSetBtn;
    QPushButton *m_clearSetBtn;
    QListWidget *m_setList;

    // Relations input section
    QGroupBox *m_relationsGroup;
    QLineEdit *m_relationFromInput;
    QLineEdit *m_relationToInput;
    QPushButton *m_addRelationBtn;
    QPushButton *m_removeRelationBtn;
    QPushButton *m_clearRelationsBtn;
    QTableWidget *m_relationsTable;

    // Analysis section
    QGroupBox *m_analysisGroup;
    QPushButton *m_checkAllBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_exampleBtn;
    QTextEdit *m_resultsDisplay;

    // Properties checkboxes for display
    QCheckBox *m_reflexiveCheck;
    QCheckBox *m_symmetricCheck;
    QCheckBox *m_transitiveCheck;
    QCheckBox *m_antisymmetricCheck;

    // Data storage
    QStringList m_setElements;
    QList<QPair<QString, QString>> m_relations;
};

#endif // RELATIONPROPERTIESWIDGET_H