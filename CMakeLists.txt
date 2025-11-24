cmake_minimum_required(VERSION 3.16)

project(UnidiscEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable automatic MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
set(SOURCES
    src/main_gui.cpp
    src/MainWindow.cpp
    src/CoursePrerequisiteWidget.cpp
    src/StudentGroupWidget.cpp
    src/SetOperationsWidget.cpp
    src/RelationPropertiesWidget.cpp
    src/ProofEngineWidget.cpp
    src/InductionEngineWidget.cpp
    src/TestsWidget.cpp
    src/FunctionsManagerWidget.cpp
    src/LogicInferenceWidget.cpp
    src/ConsistencyCheckerWidget.cpp
    src/EfficiencyBenchmarksWidget.cpp
    src/AllWidgets.cpp
    
    # Original logic classes (adapted)
    src/CoursePrerequisiteManager.cpp
    src/StudentGroup.cpp
    src/SetOperationsManager.cpp
    src/RelationPropertiesChecker.cpp
    src/ProofEngine.cpp
    src/InductionEngine.cpp
    src/Tests.cpp
    src/FunctionsManager.cpp
    src/LogicInferenceEngine.cpp
    src/ConsistencyChecker.cpp
    src/EfficiencyBenchmarks.cpp
)

# Header files
set(HEADERS
    include/MainWindow.h
    include/CoursePrerequisiteWidget.h
    include/StudentGroupWidget.h
    include/SetOperationsWidget.h
    include/RelationPropertiesWidget.h
    include/ProofEngineWidget.h
    include/InductionEngineWidget.h
    include/TestsWidget.h
    include/FunctionsManagerWidget.h
    include/LogicInferenceWidget.h
    include/ConsistencyCheckerWidget.h
    include/EfficiencyBenchmarksWidget.h
    include/AllWidgets.h
    
    # Original headers (adapted)
    include/CoursePrerequisiteManager.h
    include/StudentGroup.h
    include/SetOperationsManager.h
    include/RelationPropertiesChecker.h
    include/ProofEngine.h
    include/InductionEngine.h
    include/Tests.h
    include/FunctionsManager.h
    include/LogicInferenceEngine.h
    include/ConsistencyChecker.h
    include/EfficiencyBenchmarks.h
    include/Module.h
)

# UI files (optional - we're using code-based UI)
# set(UI_FILES
#     ui/MainWindow.ui
# )

# Resource files
set(RESOURCES
    resources/resources.qrc
)

# Include directories
include_directories(include)

# Create executable
add_executable(UnidiscEngine ${SOURCES} ${HEADERS} ${RESOURCES})

# Link Qt libraries
target_link_libraries(UnidiscEngine Qt6::Core Qt6::Widgets)

# Set application properties
set_target_properties(UnidiscEngine PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Install target
install(TARGETS UnidiscEngine
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)