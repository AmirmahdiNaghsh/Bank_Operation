cmake_minimum_required(VERSION 3.16)
# Fix macOS SDK path warning
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Set valid build types
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")

project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols for Debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# Console version (always works)
set(CONSOLE_SOURCES
    main_working.cpp
    bankingsystem_console.cpp
    Account.cpp
    User.cpp
    Customer.cpp
    Admin.cpp
    SavingsAccount.cpp
    CurrentAccount.cpp
    LoanAccount.cpp
)

# Create console executable
add_executable(banking_console ${CONSOLE_SOURCES})

# Try to find Qt for GUI version
find_package(Qt6 COMPONENTS Core Widgets QUIET)
if(Qt6_FOUND)
    # Enable Qt MOC
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    # Qt version sources
    set(QT_SOURCES
        main_qt.cpp
        bankingsystem.cpp
        loginwindow.cpp
        customerwindow.cpp
        adminwindow.cpp
        transferdialog.cpp
        Account.cpp
        User.cpp
        Customer.cpp
        Admin.cpp
        SavingsAccount.cpp
        CurrentAccount.cpp
        LoanAccount.cpp
    )

    # UI files
    set(UI_FILES
        loginwindow.ui
        customerwindow.ui
    )

    # Create Qt executable
    add_executable(banking_qt ${QT_SOURCES} ${UI_FILES})
    target_link_libraries(banking_qt Qt6::Core Qt6::Widgets)
    
    # Set target properties
    set_target_properties(banking_qt PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
        OUTPUT_NAME "BankingSystemGUI"
    )
    
    # Configure for Debug/Release
    target_compile_definitions(banking_qt PRIVATE
        $<$<CONFIG:Debug>:QT_QML_DEBUG>
    )
    
    message(STATUS "Qt6 found - building both console and Qt versions")
else()
    message(STATUS "Qt6 not found - building console version only")
endif()

# Configure console target
set_target_properties(banking_console PROPERTIES
    OUTPUT_NAME "banking_console"
)
