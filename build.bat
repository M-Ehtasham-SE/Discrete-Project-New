@echo off
REM UNIDISC Engine Build Script for Windows
REM Requires Qt 6.x and CMake or Visual Studio

setlocal enabledelayedexpansion

REM Configuration
set PROJECT_NAME=UnidiscEngine
set BUILD_DIR=build
set QT_DIR=C:\Qt\6.5.0\msvc2019_64

REM Colors (Windows doesn't support ANSI colors in cmd by default)
echo.
echo ================================
echo  UNIDISC Engine Build Script
echo ================================
echo.

REM Check if we're in the right directory
if not exist "CMakeLists.txt" (
    echo ERROR: CMakeLists.txt not found!
    echo Please run this script from the project root directory.
    pause
    exit /b 1
)

REM Check for Qt installation
echo Checking for Qt installation...
if exist "%QT_DIR%\bin\qmake.exe" (
    echo Found Qt at: %QT_DIR%
) else (
    echo WARNING: Qt not found at %QT_DIR%
    echo Please update QT_DIR in this script or install Qt
    echo.
    echo You can download Qt from: https://www.qt.io/download
    pause
    exit /b 1
)

REM Check for CMake
echo Checking for CMake...
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: CMake not found!
    echo Please install CMake from: https://cmake.org/download/
    pause
    exit /b 1
)

REM Check for Visual Studio or MinGW
echo Checking for compiler...
cl >nul 2>&1
if %errorlevel% equ 0 (
    echo Found Visual Studio C++ compiler
    set GENERATOR=Visual Studio 16 2019
    set CMAKE_ARGS=-G "%GENERATOR%" -A x64
) else (
    gcc --version >nul 2>&1
    if %errorlevel% equ 0 (
        echo Found MinGW GCC compiler
        set GENERATOR=MinGW Makefiles
        set CMAKE_ARGS=-G "%GENERATOR%"
    ) else (
        echo ERROR: No suitable compiler found!
        echo Please install Visual Studio or MinGW
        pause
        exit /b 1
    )
)

REM Clean build directory
if exist "%BUILD_DIR%" (
    echo Cleaning existing build directory...
    rmdir /s /q "%BUILD_DIR%"
)

REM Create build directory
echo Creating build directory...
mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Configure with CMake
echo Configuring project...
cmake %CMAKE_ARGS% -DCMAKE_PREFIX_PATH="%QT_DIR%" -DCMAKE_BUILD_TYPE=Release ..

if %errorlevel% neq 0 (
    echo ERROR: Failed to configure project!
    pause
    exit /b 1
)

REM Build project
echo Building project...
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo ERROR: Build failed!
    pause
    exit /b 1
)

REM Find and run executable
echo Build completed successfully!
echo Looking for executable...

if exist "bin\Release\UnidiscEngine.exe" (
    set EXECUTABLE=bin\Release\UnidiscEngine.exe
) else if exist "Release\UnidiscEngine.exe" (
    set EXECUTABLE=Release\UnidiscEngine.exe
) else if exist "UnidiscEngine.exe" (
    set EXECUTABLE=UnidiscEngine.exe
) else (
    echo WARNING: Executable not found!
    echo Available files:
    dir /b
    pause
    exit /b 0
)

echo Found executable: !EXECUTABLE!
echo Starting UNIDISC Engine...

REM Add Qt DLLs to PATH
set PATH=%QT_DIR%\bin;%PATH%

REM Run the application
start "" "!EXECUTABLE!"

echo.
echo Build script completed successfully!
echo UNIDISC Engine should now be running.
echo.
pause