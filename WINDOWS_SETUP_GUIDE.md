# Discrete Mathematics GUI - Complete Windows Setup & Running Guide

## Table of Contents
1. [System Requirements](#system-requirements)
2. [Installation Guide](#installation-guide)
3. [Building the Project](#building-the-project)
4. [Running the Application](#running-the-application)
5. [Troubleshooting](#troubleshooting)
6. [Features Guide](#features-guide)
7. [FAQ](#faq)

---

## System Requirements

### Minimum Requirements
- **OS**: Windows 10 (64-bit) or Windows 11
- **RAM**: 4 GB minimum, 8 GB recommended
- **Storage**: 2 GB free space
- **CPU**: Intel Core i3 or AMD equivalent

### Software Dependencies
- **Qt 6.x** (6.5 or later recommended)
- **CMake** (3.16 or later)
- **C++ Compiler**: Visual Studio 2019/2022 or MinGW-w64
- **Git** (for cloning the repository)

---

## Installation Guide

### Option 1: Qt Online Installer (Recommended)

1. **Download Qt Online Installer**
   ```
   https://www.qt.io/download-qt-installer
   ```

2. **Install Qt with Required Components**
   - Launch the installer as Administrator
   - Create Qt account (free for open source)
   - Select Qt 6.5 or later
   - Required components:
     - Qt 6.x Desktop (MSVC 2019 64-bit or MinGW)
     - Qt Creator IDE
     - CMake
     - Ninja build system

3. **Add Qt to System PATH**
   ```cmd
   # Add to System Environment Variables:
   C:\Qt\6.5.0\msvc2019_64\bin
   C:\Qt\Tools\CMake_64\bin
   C:\Qt\Tools\Ninja
   ```

### Option 2: Manual Installation

1. **Install Visual Studio Build Tools**
   ```
   https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022
   ```
   - Select "C++ build tools"
   - Include Windows 10/11 SDK

2. **Install CMake**
   ```
   https://cmake.org/download/
   ```
   - Download Windows x64 Installer
   - Check "Add CMake to system PATH"

3. **Install Qt6**
   - Download Qt6 from official website
   - Install to `C:\Qt\6.x.x\`

### Option 3: Package Manager (Advanced)

**Using vcpkg:**
```cmd
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install qt6[core,widgets] --triplet x64-windows
```

**Using Chocolatey:**
```cmd
choco install cmake
choco install qt6
```

---

## Building the Project

### Step 1: Clone the Repository
```cmd
git clone <repository-url> discrete-math-gui
cd discrete-math-gui
```

### Step 2: Configure Build Environment

**Option A: Using Qt Creator (Easiest)**
1. Open Qt Creator
2. File → Open File or Project
3. Select `CMakeLists.txt`
4. Choose kit (MSVC 2019/2022 64-bit)
5. Configure project settings
6. Click "Build" button

**Option B: Command Line Build**

1. **Open Developer Command Prompt**
   - Search "Developer Command Prompt for VS 2022"
   - Or use regular CMD with Qt environment

2. **Set Environment Variables**
   ```cmd
   set Qt6_DIR=C:\Qt\6.5.0\msvc2019_64\lib\cmake\Qt6
   set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
   ```

3. **Configure with CMake**
   ```cmd
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
   ```

4. **Build the Project**
   ```cmd
   cmake --build . --config Release
   ```

### Step 3: Alternative Build Script

Create `build.bat` in project root:
```batch
@echo off
echo Building Discrete Mathematics GUI...

:: Set Qt path (adjust to your installation)
set Qt6_DIR=C:\Qt\6.5.0\msvc2019_64\lib\cmake\Qt6
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin

:: Create build directory
if not exist build mkdir build
cd build

:: Configure
echo Configuring with CMake...
cmake .. -G "Visual Studio 17 2022" -A x64
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

:: Build
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo Executable location: build\Release\UnidiscEngine.exe
pause
```

---

## Running the Application

### Method 1: From Build Directory
```cmd
cd build\Release
UnidiscEngine.exe
```

### Method 2: Create Desktop Shortcut
1. Navigate to `build\Release\UnidiscEngine.exe`
2. Right-click → "Create shortcut"
3. Move shortcut to Desktop
4. Rename to "Discrete Mathematics GUI"

### Method 3: Create Start Menu Entry
1. Copy `UnidiscEngine.exe` to desired location
2. Create shortcut in Start Menu folder:
   ```
   %APPDATA%\Microsoft\Windows\Start Menu\Programs\
   ```

---

## Troubleshooting

### Common Build Issues

#### 1. "Qt6 not found" Error
**Problem**: CMake cannot locate Qt6 installation
```
CMake Error: Could not find Qt6
```

**Solutions**:
```cmd
# Option A: Set Qt6_DIR explicitly
set Qt6_DIR=C:\Qt\6.5.0\msvc2019_64\lib\cmake\Qt6
cmake .. -DQt6_DIR=%Qt6_DIR%

# Option B: Add Qt to PATH
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
```

#### 2. "MSVC Compiler not found"
**Problem**: No C++ compiler detected
```
No CMAKE_CXX_COMPILER could be found
```

**Solutions**:
- Install Visual Studio Build Tools
- Use Developer Command Prompt
- Or specify compiler explicitly:
```cmd
cmake .. -G "Visual Studio 17 2022" -A x64
```

#### 3. "moc.exe not found" Error
**Problem**: Qt Meta-Object Compiler missing
```
Could not find moc.exe
```

**Solution**:
```cmd
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
```

#### 4. Missing DLL Errors
**Problem**: Runtime DLLs not found
```
The program can't start because Qt6Core.dll is missing
```

**Solutions**:

**Option A: Deploy Qt DLLs**
```cmd
# Navigate to your exe directory
cd build\Release

# Use Qt deployment tool
C:\Qt\6.5.0\msvc2019_64\bin\windeployqt.exe UnidiscEngine.exe
```

**Option B: Add Qt to System PATH**
```cmd
# Add to System Environment Variables:
C:\Qt\6.5.0\msvc2019_64\bin
```

**Option C: Copy DLLs Manually**
Copy these DLLs to your exe directory:
- Qt6Core.dll
- Qt6Gui.dll  
- Qt6Widgets.dll
- platforms\qwindows.dll (in platforms subfolder)

#### 5. Antivirus False Positives
**Problem**: Antivirus blocks the executable

**Solutions**:
- Add exception for the build directory
- Add exception for UnidiscEngine.exe
- Temporarily disable real-time protection during build

### Runtime Issues

#### 1. Application Won't Start
**Diagnostics**:
```cmd
# Check dependencies
dumpbin /dependents UnidiscEngine.exe

# Run with debug output
UnidiscEngine.exe --debug
```

**Solutions**:
- Ensure all Qt DLLs are available
- Run `windeployqt.exe` 
- Check Windows Event Viewer for errors

#### 2. Graphics/Display Issues
**Problem**: Blank window or rendering issues

**Solutions**:
```cmd
# Force software rendering
set QT_OPENGL=software
UnidiscEngine.exe

# Or set specific graphics adapter
set QT_OPENGL=desktop
```

#### 3. Font Rendering Problems
**Problem**: Text appears corrupted or missing

**Solutions**:
```cmd
# Reset font cache
C:\Windows\System32\fontcache.exe

# Use different font rendering
set QT_SCALE_FACTOR=1.0
```

### Performance Issues

#### 1. Slow Startup
**Solutions**:
- Run as Administrator once to cache fonts
- Disable Windows Defender scanning for exe
- Move to SSD if using HDD

#### 2. High Memory Usage
**Solutions**:
- Close other applications
- Increase virtual memory
- Check for memory leaks in Task Manager

---

## Features Guide

### Module Overview
The application contains 11 functional modules:

1. **Course Prerequisites** - Manage course dependencies
2. **Student Groups** - Handle student assignments
3. **Set Operations** - Perform set theory operations
4. **Relations Properties** - Analyze mathematical relations
5. **Proof Engine** - Generate formal proofs
6. **Induction Engine** - Mathematical induction proofs
7. **Unit Tests** - Comprehensive testing framework
8. **Functions Manager** - Function analysis tools
9. **Logic Inference** - Rule-based logical deduction
10. **Consistency Checker** - Data consistency validation
11. **Efficiency Benchmarks** - Algorithm performance analysis

### Basic Usage

1. **Starting the Application**
   - Launch UnidiscEngine.exe
   - The main window opens with tabbed interface

2. **Navigating Modules**
   - Click tabs at the top to switch between modules
   - Each module is independent and self-contained

3. **Exporting Results**
   - Most modules support HTML, CSV, or text export
   - Use "Export" buttons in each module
   - Files save to Documents folder by default

### Advanced Features

#### Dark Theme Interface
- Professional dark theme (#2b2b2b background)
- High contrast white text for readability
- Consistent styling across all modules

#### Interactive Visualizations
- Text-based charts and graphs
- Real-time algorithm performance visualization
- Step-by-step proof generation display

#### Educational Tools
- Detailed explanations for mathematical concepts
- Step-by-step algorithm walkthroughs
- Interactive learning interfaces

---

## FAQ

### Q: Can I run this on Windows 7?
**A**: No, Qt6 requires Windows 10 or later. Consider upgrading your OS or using Qt5 version.

### Q: Do I need Visual Studio IDE?
**A**: No, only the Build Tools are required. Qt Creator is sufficient for development.

### Q: How much disk space does it need?
**A**: About 2 GB total (including Qt runtime and build artifacts).

### Q: Can I redistribute the executable?
**A**: Yes, but you must include Qt DLLs. Use `windeployqt.exe` for proper deployment.

### Q: The application crashes on startup
**A**: 
1. Check if all Qt DLLs are present
2. Run `windeployqt.exe UnidiscEngine.exe`
3. Check Windows Event Viewer for detailed error
4. Try running as Administrator

### Q: How do I update Qt version?
**A**: 
1. Install new Qt version
2. Update `Qt6_DIR` environment variable
3. Clean and rebuild project
```cmd
rmdir /s build
mkdir build
cd build
cmake .. -DQt6_DIR=C:\Qt\6.6.0\msvc2019_64\lib\cmake\Qt6
cmake --build . --config Release
```

### Q: Performance is slow on my system
**A**:
1. Close unnecessary applications
2. Ensure you're running Release build (not Debug)
3. Update graphics drivers
4. Consider using software rendering:
   ```cmd
   set QT_OPENGL=software
   UnidiscEngine.exe
   ```

### Q: Can I customize the dark theme?
**A**: The theme is built into the application. You would need to modify the source code and rebuild to change colors.

---

## Support & Contact

For additional support:
- Check the GitHub Issues page
- Review Qt6 documentation: https://doc.qt.io/qt-6/
- CMake documentation: https://cmake.org/documentation/

---

## Version Information
- **Application Version**: 1.0.0
- **Qt Version**: 6.x (6.5+ recommended)
- **CMake Version**: 3.16+
- **Last Updated**: November 22, 2025

---

*This guide covers the complete setup and troubleshooting for Windows systems. For Linux or macOS, refer to the respective platform guides.*