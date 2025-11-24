# 🎓 UNIDISC Engine - Installation Guide

## Overview
UNIDISC Engine is a comprehensive GUI application for learning discrete mathematics concepts, built with Qt 6 and C++17. This guide covers installation on both Windows and Kali Linux.

## System Requirements

### Minimum Requirements
- **OS**: Windows 10/11 (64-bit) or Linux (64-bit)
- **RAM**: 4 GB minimum, 8 GB recommended
- **Storage**: 2 GB free space
- **CPU**: Any modern 64-bit processor

### Dependencies
- Qt 6.2 or higher
- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

---

## 🪟 Windows Installation

### Option 1: Using Qt Creator (Recommended)

#### Step 1: Install Qt
1. Download Qt Open Source installer from: `https://www.qt.io/download-qt-installer`
2. Run the installer and select:
   - Qt 6.5 LTS (or latest stable version)
   - Qt Creator IDE
   - MinGW compiler (64-bit)
   - CMake tools

#### Step 2: Build the Project
1. Open Qt Creator
2. Click "File" → "Open File or Project"
3. Navigate to your project folder and select `CMakeLists.txt`
4. Configure the project with Qt 6.x kit
5. Click the green "Run" button to build and execute

### Option 2: Command Line Build

#### Step 1: Install Dependencies
```cmd
# Install Qt via vcpkg (requires Visual Studio)
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install qt6-base qt6-widgets

# Or download Qt binaries directly from qt.io
```

#### Step 2: Build Project
```cmd
cd /path/to/UnidiscEngine
mkdir build
cd build

# Configure with CMake
cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2019_64 ..

# Build
cmake --build . --config Release

# Run
.\bin\UnidiscEngine.exe
```

### Option 3: Pre-built Binaries
1. Download the latest release from the project repository
2. Extract the ZIP file
3. Run `UnidiscEngine.exe`
4. If you get DLL errors, install Qt runtime or copy Qt DLLs to the executable folder

---

## 🐧 Kali Linux Installation

### Option 1: Using Package Manager (Recommended)

#### Step 1: Update System
```bash
sudo apt update && sudo apt upgrade -y
```

#### Step 2: Install Qt Development Tools
```bash
# Install Qt 6 development packages
sudo apt install -y qt6-base-dev qt6-tools-dev cmake build-essential

# Install additional Qt modules
sudo apt install -y qt6-widgets-dev qt6-declarative-dev

# Verify installation
qmake6 --version
cmake --version
```

#### Step 3: Build the Project
```bash
cd /path/to/UnidiscEngine
mkdir build && cd build

# Configure with CMake
cmake -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6 ..

# Build with all CPU cores
make -j$(nproc)

# Run the application
./bin/UnidiscEngine
```

### Option 2: Using qmake
```bash
cd /path/to/UnidiscEngine

# Generate Makefile
qmake6 UnidiscEngine.pro

# Build
make -j$(nproc)

# Run
./UnidiscEngine
```

### Option 3: Manual Qt Installation
```bash
# Download Qt installer
wget https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run

# Make executable and run
chmod +x qt-unified-linux-x64-online.run
./qt-unified-linux-x64-online.run

# Follow GUI installer, then add to PATH
echo 'export PATH=/opt/Qt/6.5.0/gcc_64/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/opt/Qt/6.5.0/gcc_64/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
```

---

## 🚀 Quick Start Guide

### 1. First Launch
When you first run UNIDISC Engine, you'll see:
- A splash screen with loading animation
- Welcome dialog with feature overview
- Main window with 11 interactive modules

### 2. Navigation
- **Tabs**: Click on module tabs to switch between different tools
- **Menu Bar**: Access Help, About, and other utilities
- **Status Bar**: Shows current module and operation status

### 3. Module Overview
1. **Course Prerequisites** - Manage FAST University curriculum and dependencies
2. **Student Groups** - Calculate combinations for group formations
3. **Set Operations** - Perform union, intersection, difference operations
4. **Relations** - Check reflexive, symmetric, transitive properties
5. **Proof Engine** - Generate mathematical proofs
6. **Induction** - Mathematical and strong induction examples
7. **Unit Tests** - Run system functionality tests
8. **Functions** - Analyze function properties
9. **Logic & Inference** - Rule-based reasoning system
10. **Consistency Checker** - Validate system consistency
11. **Efficiency Benchmarks** - Algorithm performance analysis

---

## 🛠️ Development Setup

### For Contributors

#### Clone Repository
```bash
git clone <repository-url>
cd UnidiscEngine
```

#### Development Dependencies
```bash
# Linux
sudo apt install -y qt6-base-dev-tools qt6-declarative-dev-tools

# Additional tools for development
sudo apt install -y qtcreator gdb valgrind
```

#### IDE Setup
- **Qt Creator**: Recommended IDE with built-in Qt support
- **Visual Studio**: Use Qt VS Tools extension
- **CLion**: Configure Qt as external library
- **Code::Blocks**: Setup Qt project manually

---

## ❗ Troubleshooting

### Common Issues

#### Windows
**Error: "Qt6Core.dll not found"**
```cmd
# Solution: Add Qt bin directory to PATH
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
```

**Error: "MSVCR120.dll missing"**
```cmd
# Install Visual C++ Redistributable
# Download from Microsoft website
```

#### Linux
**Error: "qt6-widgets-dev not found"**
```bash
# Enable universe repository (Ubuntu/Debian)
sudo add-apt-repository universe
sudo apt update

# Or install from source
wget https://download.qt.io/archive/qt/6.5/6.5.0/single/qt-everywhere-src-6.5.0.tar.xz
```

**Error: "libQt6Widgets.so.6 not found"**
```bash
# Add Qt lib directory to LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH

# Or update library cache
sudo ldconfig
```

### Performance Issues
- **Slow startup**: Disable splash screen by removing `setupSplashScreen()` call
- **High memory usage**: Reduce module complexity or implement lazy loading
- **UI freezing**: Check for blocking operations in main thread

---

## 📦 Deployment

### Windows Deployment
```cmd
# Use Qt deployment tool
windeployqt.exe --release --qmldir . UnidiscEngine.exe

# Create installer with NSIS or Inno Setup
```

### Linux Deployment
```bash
# Create AppImage
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage --executable UnidiscEngine --appdir AppDir --output appimage

# Or create DEB package
mkdir -p package/DEBIAN package/usr/bin package/usr/share/applications
cp UnidiscEngine package/usr/bin/
# Create control file and build with dpkg-deb
```

---

## 🔧 Configuration

### Environment Variables
```bash
# Qt plugin path (if needed)
export QT_PLUGIN_PATH=/path/to/qt/plugins

# Custom theme
export QT_STYLE_OVERRIDE=Fusion

# Debug Qt
export QT_LOGGING_RULES="*.debug=true"
```

### Application Settings
Settings are stored in:
- **Windows**: `%APPDATA%/FAST University/UNIDISC Engine/`
- **Linux**: `~/.config/FAST University/UNIDISC Engine/`

---

## 📞 Support

### Getting Help
- 📧 Email: support@unidisc-engine.edu
- 🐛 Issues: Report on project repository
- 📚 Documentation: Check `/docs` folder
- 💬 Community: Join our Discord server

### System Information
For support requests, provide:
```bash
# System info
uname -a                    # Linux
systeminfo                 # Windows

# Qt version
qmake6 --version

# Application logs
# Check ~/.local/share/FAST University/UNIDISC Engine/logs/
```

---

## 📝 License

This project is licensed under the MIT License. See `LICENSE` file for details.

---

**Happy Learning with UNIDISC Engine! 🎓✨**