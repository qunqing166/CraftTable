cmake_minimum_required(VERSION 3.16)

project(CraftTable VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        logo.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CraftTable
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        TrayView.h TrayView.cpp
        res.qrc
        TaskView.h TaskView.cpp
        TaskViewItem.h TaskViewItem.cpp
        model/TaskInfo.h model/TaskInfo.cpp
        TaskEditDialog.h TaskEditDialog.cpp

        FileManagement.h FileManagement.cpp
        model/ScheduleInfo.h model/ScheduleInfo.cpp
        model/BaseInfo.h model/BaseInfo.cpp
        model/CountdownDayInfo.h model/CountdownDayInfo.cpp
        model/ModelType.h
        utility/Utility.cpp utility/Utility.h
        model/LongTaskInfo.h model/LongTaskInfo.cpp
        UserControl/AbstractDataSelector.cpp UserControl/AbstractDataSelector.h
        UserControl/MonthDaySelector.h UserControl/MonthDaySelector.cpp
        UserControl/NumSelector.h UserControl/NumSelector.cpp
        UserControl/DateTimeEditor.h UserControl/DateTimeEditor.cpp
        model/DailyTask.h model/DailyTask.cpp
        model/TaskBuilder.h model/TaskBuilder.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DayDayUp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CraftTable SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CraftTable
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CraftTable PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CraftTable)
endif()
set_target_properties(CraftTable PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CraftTable
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CraftTable)
endif()
