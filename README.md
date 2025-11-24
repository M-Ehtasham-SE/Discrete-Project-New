# 🎓 UNIDISC Engine - FAST University Discrete Mathematics Platform

<div align="center">

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Qt Version](https://img.shields.io/badge/Qt-6.x-green.svg)](https://www.qt.io/)
[![C++ Version](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)](https://github.com)

*A comprehensive interactive GUI application for learning discrete mathematics concepts*

[Features](#-features) • [Installation](#-installation) • [Screenshots](#-screenshots) • [Usage](#-usage) • [Contributing](#-contributing)

</div>

---

## 📋 Overview

UNIDISC Engine is a modern, interactive educational platform designed specifically for FAST University's discrete mathematics curriculum. Built with Qt 6 and C++17, it provides a rich graphical interface for exploring mathematical concepts, performing calculations, and visualizing results.

### 🎯 Target Audience
- **Students** learning discrete mathematics
- **Educators** teaching discrete math concepts
- **Researchers** exploring mathematical relationships
- **Developers** interested in educational software

---

## ✨ Features

### 🔧 Core Modules

| Module | Description | Key Features |
|--------|-------------|--------------|
| **📚 Course Prerequisites** | Manage curriculum dependencies | Tree view, prerequisite chains, semester planning |
| **👥 Student Groups** | Calculate group combinations | Interactive combinations, permutations, visualizations |
| **🔢 Set Operations** | Perform set theory operations | Union, intersection, Venn diagrams, properties |
| **🔗 Relations** | Analyze relation properties | Reflexive, symmetric, transitive checking |
| **📝 Proof Engine** | Generate mathematical proofs | Step-by-step proofs, verification |
| **🔄 Induction** | Mathematical induction examples | Base case, inductive step, strong induction |
| **✅ Unit Tests** | System functionality testing | Automated testing, result verification |
| **📊 Functions** | Function property analysis | Injective, surjective, bijective classification |
| **🧠 Logic & Inference** | Rule-based reasoning | Forward chaining, knowledge base |
| **⚖️ Consistency Checker** | Validate logical consistency | Conflict detection, resolution |
| **⚡ Efficiency Benchmarks** | Algorithm performance analysis | Time complexity, optimization |

### 🎨 User Interface Features
- **Modern Dark Theme** with customizable styling
- **Tabbed Interface** for easy navigation
- **Interactive Visualizations** and diagrams
- **Real-time Calculations** and updates
- **Export Functionality** for results and reports
- **Comprehensive Help System** with tooltips and guides

### 🔧 Technical Features
- **Cross-platform Compatibility** (Windows, Linux)
- **Responsive Design** that adapts to different screen sizes
- **Memory Efficient** with optimized data structures
- **Extensible Architecture** for adding new modules
- **Error Handling** with user-friendly messages

---

## 🚀 Installation

### Quick Start
```bash
# Clone the repository
git clone <repository-url>
cd UnidiscEngine

# Build and run (Linux)
mkdir build && cd build
cmake .. && make -j$(nproc)
./bin/UnidiscEngine

# Build and run (Windows with Qt Creator)
# Open CMakeLists.txt in Qt Creator and click Run
```

### Detailed Installation
For comprehensive installation instructions, see [INSTALLATION_GUIDE.md](INSTALLATION_GUIDE.md)

### System Requirements
- **OS**: Windows 10+ or Linux (64-bit)
- **Qt**: Version 6.2 or higher
- **RAM**: 4 GB minimum, 8 GB recommended
- **Storage**: 2 GB free space

---

## 📱 Screenshots

### Main Interface
```
┌─────────────────────────────────────────────────────────────┐
│ UNIDISC Engine - FAST University                           │
├─────────────────────────────────────────────────────────────┤
│ File  Help                                                  │
├─────────────────────────────────────────────────────────────┤
│ [Course Prerequisites] [Student Groups] [Set Operations]... │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─ Course Tree ─────┐  ┌─ Details ──────────────────────┐ │
│  │ Semester 1        │  │ Course: Programming Fundamentals │ │
│  │ ├─ Prog. Fund.    │  │ Semester: 1                     │ │
│  │ ├─ Intro to ICT   │  │ Credits: 3                      │ │
│  │ ├─ Calculus       │  │                                 │ │
│  │ Semester 2        │  │ Prerequisites: None             │ │
│  │ ├─ OOP           │  │ (Foundational Course)           │ │
│  │ └─ Discrete...    │  │                                 │ │
│  └───────────────────┘  └─────────────────────────────────┘ │
│                                                             │
├─────────────────────────────────────────────────────────────┤
│ Active Module: Course Prerequisites                   v1.0.0│
└─────────────────────────────────────────────────────────────┘
```

### Set Operations Module
```
┌─────────────────────────────────────────────────────────────┐
│                    Set Operations Manager                   │
├─────────────────────────────────────────────────────────────┤
│ [Set Management] [Operations] [Visualization] [Properties]  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│ Set A = {1, 2, 3, 4, 5}    Set B = {4, 5, 6, 7, 8}       │
│                                                             │
│ ┌─ A ∪ B ─┐ ┌─ A ∩ B ─┐ ┌─ A - B ─┐ ┌─ A ⊕ B ─┐        │
│ │ Union   │ │ Intersect│ │ Diff.   │ │ Sym.Diff │        │
│ └─────────┘ └─────────┘ └─────────┘ └─────────┘        │
│                                                             │
│ Results: A ∪ B = {1, 2, 3, 4, 5, 6, 7, 8}                │
│         A ∩ B = {4, 5}                                     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## 📖 Usage

### Getting Started
1. **Launch Application**: Run the executable or use Qt Creator
2. **Welcome Screen**: Read the welcome dialog for feature overview
3. **Select Module**: Click on any tab to access different functionalities
4. **Interactive Learning**: Use input fields, buttons, and displays to explore concepts

### Module-Specific Usage

#### Course Prerequisites
- **Load Curriculum**: Click "Reload Curriculum" to load FAST University courses
- **Search**: Use the search box to find specific courses
- **View Details**: Click on any course to see prerequisites and details
- **Generate Sequence**: Click "Generate Valid Order" for semester-wise planning

#### Student Groups
- **Input Parameters**: Set total students and group size using spin boxes
- **Calculate**: Use "Calculate Combinations" for C(n,r) or "Calculate Permutations" for P(n,r)
- **Manage Students**: Add/remove students in the Student Management tab
- **Assign Projects**: Automatically create project groups with specified sizes

#### Set Operations
- **Create Sets**: Add elements to Set A and Set B using input fields
- **Perform Operations**: Click operation buttons for union, intersection, etc.
- **Visualize**: Use the Visualization tab for Venn diagrams
- **Check Properties**: Analyze set relationships and mathematical properties

### Tips and Tricks
- **Hover for Help**: Most buttons have tooltips with additional information
- **Keyboard Shortcuts**: Use Ctrl+Q to quit, F1 for help
- **Export Results**: Most modules support exporting results to HTML files
- **Dark Theme**: The application uses a modern dark theme by default

---

## 🏗️ Architecture

### Project Structure
```
UnidiscEngine/
├── src/                    # Source files
│   ├── main_gui.cpp       # Application entry point
│   ├── MainWindow.cpp     # Main window implementation
│   ├── *Widget.cpp        # Module implementations
│   └── *.cpp              # Original logic classes
├── include/               # Header files
│   ├── MainWindow.h       # Main window header
│   ├── *Widget.h          # Module headers
│   └── *.h                # Original headers
├── ui/                    # UI form files (optional)
├── resources/             # Resources (icons, styles)
│   ├── resources.qrc      # Resource collection
│   └── *.png              # Icon files
├── CMakeLists.txt         # CMake build configuration
├── UnidiscEngine.pro      # qmake build configuration
└── docs/                  # Documentation
```

### Design Patterns
- **Model-View Pattern**: Separation of business logic and UI
- **Factory Pattern**: Module creation and management
- **Observer Pattern**: UI updates based on data changes
- **Strategy Pattern**: Different algorithms for mathematical operations

### Dependencies
- **Qt 6.x**: GUI framework, widgets, layouts
- **C++17 Standard Library**: STL containers, algorithms
- **CMake/qmake**: Build system configuration

---

## 🧪 Testing

### Running Tests
```bash
# Build with tests enabled
cmake -DBUILD_TESTS=ON ..
make -j$(nproc)

# Run unit tests
./tests/unit_tests

# Run integration tests  
./tests/integration_tests
```

### Test Coverage
- **Unit Tests**: Individual module functionality
- **Integration Tests**: Module interactions
- **UI Tests**: User interface behavior
- **Performance Tests**: Algorithm efficiency benchmarks

---

## 🤝 Contributing

We welcome contributions from students, educators, and developers!

### How to Contribute
1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Commit** your changes: `git commit -m 'Add amazing feature'`
4. **Push** to the branch: `git push origin feature/amazing-feature`
5. **Open** a Pull Request

### Contribution Guidelines
- Follow the existing code style and conventions
- Add unit tests for new functionality
- Update documentation for API changes
- Use meaningful commit messages
- Test on both Windows and Linux (if possible)

### Areas for Contribution
- **New Modules**: Additional discrete math concepts
- **Visualizations**: Enhanced graphics and diagrams  
- **Performance**: Algorithm optimizations
- **UI/UX**: Interface improvements and accessibility
- **Documentation**: Tutorials, examples, translations
- **Testing**: Additional test cases and coverage

---

## 📚 Educational Content

### Learning Objectives
By using UNIDISC Engine, students will:
- Understand fundamental discrete mathematics concepts
- Practice problem-solving with interactive tools
- Visualize abstract mathematical relationships
- Apply theoretical knowledge to practical scenarios
- Develop computational thinking skills

### Curriculum Alignment
Aligned with **FAST University** discrete mathematics syllabus:
- **Set Theory**: Operations, properties, Venn diagrams
- **Relations**: Properties, equivalence relations, ordering
- **Functions**: Types, composition, inverse functions
- **Logic**: Propositional logic, inference rules, proofs
- **Combinatorics**: Permutations, combinations, principles
- **Graph Theory**: Basic concepts and algorithms
- **Number Theory**: Divisibility, modular arithmetic

---

## 🐛 Known Issues

### Current Limitations
- **Performance**: Large datasets (>1000 elements) may cause UI lag
- **Memory**: Some modules don't implement lazy loading
- **Mobile**: Not optimized for touch interfaces
- **Internationalization**: Currently English-only

### Planned Improvements
- [ ] Performance optimization for large datasets
- [ ] Mobile-responsive design
- [ ] Multi-language support
- [ ] Cloud synchronization
- [ ] Advanced visualization options
- [ ] Plugin architecture for extensibility

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### Third-Party Licenses
- **Qt Framework**: LGPL v3 / GPL v3 / Commercial
- **Icons**: Various open-source licenses (see `resources/CREDITS.md`)

---

## 👥 Team

### Development Team
- **Ehtasham Batalwi - 4** - *Lead Developer* - Original console application
- **GUI Development Team** - *Qt Interface Implementation*

### Acknowledgments
- **FAST University** - Educational requirements and curriculum
- **Qt Community** - Framework and development tools
- **Open Source Contributors** - Icons, themes, and libraries

---

## 📞 Support

### Getting Help
- 📧 **Email**: support@unidisc-engine.edu
- 🐛 **Issues**: [GitHub Issues](repository-url/issues)
- 📚 **Documentation**: Check `/docs` folder
- 💬 **Discussions**: [GitHub Discussions](repository-url/discussions)

### Reporting Bugs
When reporting bugs, please include:
- Operating system and version
- Qt version
- Steps to reproduce the issue
- Expected vs actual behavior
- Screenshots (if applicable)

---

## 🎯 Roadmap

### Version 2.0 (Future)
- [ ] Web-based version using Qt for WebAssembly
- [ ] Advanced graph theory modules
- [ ] Machine learning integration
- [ ] Collaborative features
- [ ] Real-time synchronization
- [ ] Advanced analytics and progress tracking

### Version 1.1 (Next Release)
- [ ] Complete all remaining module implementations
- [ ] Enhanced visualizations
- [ ] Performance optimizations
- [ ] Bug fixes and stability improvements

---

<div align="center">

**Made with ❤️ for the FAST University Community**

[⬆ Back to Top](#-unidisc-engine---fast-university-discrete-mathematics-platform)

</div>