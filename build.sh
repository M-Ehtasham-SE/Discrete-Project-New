#!/bin/bash

# UNIDISC Engine Build Script
# Supports both Linux and Windows (via Git Bash/WSL)

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PROJECT_NAME="UnidiscEngine"
BUILD_DIR="build"
INSTALL_DIR="install"
QT_MIN_VERSION="6.2"

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to detect OS
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "linux"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macos"
    elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
        echo "windows"
    else
        echo "unknown"
    fi
}

# Function to find Qt installation
find_qt() {
    local qt_dirs=(
        "/usr/lib/x86_64-linux-gnu/cmake/Qt6"
        "/usr/lib/cmake/Qt6"
        "/opt/Qt/*/gcc_64/lib/cmake/Qt6"
        "/opt/Qt/*/msvc*/lib/cmake/Qt6"
        "C:/Qt/*/msvc*/lib/cmake/Qt6"
        "C:/Qt/*/mingw*/lib/cmake/Qt6"
    )
    
    for dir in "${qt_dirs[@]}"; do
        if [[ -d "$dir" ]]; then
            echo "$dir"
            return 0
        fi
    done
    
    # Try to find Qt using qmake
    if command_exists qmake6; then
        local qt_path=$(qmake6 -query QT_INSTALL_LIBS)
        if [[ -d "$qt_path/cmake/Qt6" ]]; then
            echo "$qt_path/cmake/Qt6"
            return 0
        fi
    fi
    
    if command_exists qmake; then
        local qt_path=$(qmake -query QT_INSTALL_LIBS)
        if [[ -d "$qt_path/cmake/Qt6" ]]; then
            echo "$qt_path/cmake/Qt6"
            return 0
        fi
    fi
    
    return 1
}

# Function to check dependencies
check_dependencies() {
    print_status "Checking dependencies..."
    
    local missing_deps=()
    
    # Check CMake
    if ! command_exists cmake; then
        missing_deps+=("cmake")
    else
        local cmake_version=$(cmake --version | head -n1 | cut -d' ' -f3)
        print_status "Found CMake version: $cmake_version"
    fi
    
    # Check C++ compiler
    if ! command_exists g++ && ! command_exists clang++ && ! command_exists cl; then
        missing_deps+=("g++ or clang++ or MSVC")
    fi
    
    # Check Qt
    local qt_path=$(find_qt)
    if [[ -z "$qt_path" ]]; then
        missing_deps+=("Qt 6.2+")
    else
        print_status "Found Qt at: $qt_path"
    fi
    
    if [[ ${#missing_deps[@]} -gt 0 ]]; then
        print_error "Missing dependencies: ${missing_deps[*]}"
        print_status "Please install the missing dependencies and try again."
        exit 1
    fi
    
    print_success "All dependencies found!"
}

# Function to create build directory
prepare_build() {
    print_status "Preparing build environment..."
    
    # Remove old build directory if it exists
    if [[ -d "$BUILD_DIR" ]]; then
        print_warning "Removing existing build directory..."
        rm -rf "$BUILD_DIR"
    fi
    
    # Create new build directory
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    print_success "Build directory prepared!"
}

# Function to configure project
configure_project() {
    print_status "Configuring project with CMake..."
    
    local cmake_args=()
    local qt_path=$(find_qt)
    
    # Add Qt path if found
    if [[ -n "$qt_path" ]]; then
        cmake_args+=("-DCMAKE_PREFIX_PATH=$qt_path")
    fi
    
    # Set build type
    cmake_args+=("-DCMAKE_BUILD_TYPE=Release")
    
    # Platform-specific arguments
    local os=$(detect_os)
    case $os in
        "windows")
            cmake_args+=("-G" "MinGW Makefiles")
            ;;
        "linux"|"macos")
            cmake_args+=("-G" "Unix Makefiles")
            ;;
    esac
    
    # Run CMake configuration
    cmake "${cmake_args[@]}" ..
    
    if [[ $? -eq 0 ]]; then
        print_success "Project configured successfully!"
    else
        print_error "Failed to configure project!"
        exit 1
    fi
}

# Function to build project
build_project() {
    print_status "Building project..."
    
    # Detect number of CPU cores for parallel build
    local nproc_cmd=""
    if command_exists nproc; then
        nproc_cmd=$(nproc)
    elif command_exists sysctl; then
        nproc_cmd=$(sysctl -n hw.ncpu)
    else
        nproc_cmd=4  # Default fallback
    fi
    
    print_status "Building with $nproc_cmd parallel jobs..."
    
    # Build the project
    cmake --build . --config Release --parallel $nproc_cmd
    
    if [[ $? -eq 0 ]]; then
        print_success "Project built successfully!"
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Function to run the application
run_application() {
    print_status "Looking for executable..."
    
    local executable=""
    local os=$(detect_os)
    
    # Find executable based on OS
    case $os in
        "windows")
            if [[ -f "bin/UnidiscEngine.exe" ]]; then
                executable="bin/UnidiscEngine.exe"
            elif [[ -f "UnidiscEngine.exe" ]]; then
                executable="UnidiscEngine.exe"
            fi
            ;;
        *)
            if [[ -f "bin/UnidiscEngine" ]]; then
                executable="bin/UnidiscEngine"
            elif [[ -f "UnidiscEngine" ]]; then
                executable="UnidiscEngine"
            fi
            ;;
    esac
    
    if [[ -n "$executable" ]]; then
        print_success "Found executable: $executable"
        print_status "Starting UNIDISC Engine..."
        ./$executable
    else
        print_error "Executable not found!"
        print_status "Available files in build directory:"
        ls -la
        exit 1
    fi
}

# Function to install (optional)
install_project() {
    print_status "Installing project..."
    
    # Create install directory
    mkdir -p "../$INSTALL_DIR"
    
    # Install using CMake
    cmake --install . --prefix "../$INSTALL_DIR"
    
    if [[ $? -eq 0 ]]; then
        print_success "Project installed to $INSTALL_DIR/"
    else
        print_warning "Installation failed, but build was successful"
    fi
}

# Function to show help
show_help() {
    echo "UNIDISC Engine Build Script"
    echo ""
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  --help, -h          Show this help message"
    echo "  --clean, -c         Clean build directory before building"
    echo "  --install, -i       Install after building"
    echo "  --run, -r           Run the application after building"
    echo "  --debug, -d         Build in debug mode"
    echo "  --verbose, -v       Verbose output"
    echo ""
    echo "Default behavior: configure, build, and run"
}

# Main function
main() {
    local clean_build=false
    local install_after=false
    local run_after=true
    local build_type="Release"
    local verbose=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            --help|-h)
                show_help
                exit 0
                ;;
            --clean|-c)
                clean_build=true
                shift
                ;;
            --install|-i)
                install_after=true
                shift
                ;;
            --run|-r)
                run_after=true
                shift
                ;;
            --debug|-d)
                build_type="Debug"
                shift
                ;;
            --verbose|-v)
                verbose=true
                set -x
                shift
                ;;
            *)
                print_error "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
    
    # Print banner
    echo ""
    echo "🎓 UNIDISC Engine Build Script"
    echo "=============================="
    echo ""
    
    # Check if we're in the right directory
    if [[ ! -f "CMakeLists.txt" ]]; then
        print_error "CMakeLists.txt not found! Please run this script from the project root directory."
        exit 1
    fi
    
    # Detect OS
    local os=$(detect_os)
    print_status "Detected OS: $os"
    
    # Run build process
    check_dependencies
    prepare_build
    configure_project
    build_project
    
    # Optional steps
    if [[ "$install_after" == true ]]; then
        install_project
    fi
    
    if [[ "$run_after" == true ]]; then
        run_application
    fi
    
    print_success "Build script completed successfully!"
    echo ""
    echo "🚀 UNIDISC Engine is ready to use!"
    echo ""
}

# Run main function with all arguments
main "$@"