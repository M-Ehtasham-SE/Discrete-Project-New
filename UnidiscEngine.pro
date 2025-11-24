QT += core widgets

CONFIG += c++17

TARGET = UnidiscEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/main_gui.cpp \
    src/MainWindow.cpp \
    src/CoursePrerequisiteWidget.cpp \
    src/StudentGroupWidget.cpp \
    src/SetOperationsWidget.cpp \
    src/AllWidgets.cpp \
    src/CoursePrerequisiteManager.cpp \
    src/StudentGroup.cpp \
    src/SetOperationsManager.cpp \
    src/RelationPropertiesChecker.cpp \
    src/ProofEngine.cpp \
    src/InductionEngine.cpp \
    src/Tests.cpp \
    src/FunctionsManager.cpp \
    src/LogicInferenceEngine.cpp \
    src/ConsistencyChecker.cpp \
    src/EfficiencyBenchmarks.cpp

HEADERS += \
    include/MainWindow.h \
    include/CoursePrerequisiteWidget.h \
    include/StudentGroupWidget.h \
    include/SetOperationsWidget.h \
    include/AllWidgets.h \
    include/CoursePrerequisiteManager.h \
    include/StudentGroup.h \
    include/SetOperationsManager.h \
    include/RelationPropertiesChecker.h \
    include/ProofEngine.h \
    include/InductionEngine.h \
    include/Tests.h \
    include/FunctionsManager.h \
    include/LogicInferenceEngine.h \
    include/ConsistencyChecker.h \
    include/EfficiencyBenchmarks.h \
    include/Module.h

# FORMS += \
#     ui/MainWindow.ui

RESOURCES += \
    resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target