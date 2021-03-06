if(BUILD_SHARED_LIBS)
    add_definitions(-DAXR_IMPORTS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../3rdparty/qtmacextras/src ${CMAKE_BINARY_DIR})

set(browser_SOURCES
    Info.plist
    AboutDialog.cpp
    AboutDialog.h
    AboutDialog.ui
    LogWindow.cpp
    LogWindow.h
    LogWindow.ui
    main.cpp
    PreferencesDialog.cpp
    PreferencesDialog.h
    PreferencesDialog.ui
    BrowserApplication.cpp
    BrowserApplication.h
    BrowserSettings.cpp
    BrowserSettings.h
    BrowserTab.cpp
    BrowserTab.h
    BrowserWindow.cpp
    BrowserWindow.h
    BrowserWindow.ui
    Resources.qrc
    resources.rc

    # These need to be included so they can be copied to the bundle
    ${axr_icon_SOURCES}
    ${hss_SOURCES}
)

source_group("Resources\\HSS Framework" FILES ${hss_SOURCES})

qt_transform_sources(browser_SOURCES "${browser_SOURCES}")

add_executable(${TARGET_NAME_APP_BROWSER} WIN32 MACOSX_BUNDLE ${browser_SOURCES})
target_link_libraries(${TARGET_NAME_APP_BROWSER} ${TARGET_NAME_LIB_CORE} ${QT_QTMACEXTRAS_LIBRARY} "${TARGET_NAME_LIB_QT}" ${QT_QTMAIN_LIBRARY} ${COCOA_LIBRARY})

set(MACOSX_BUNDLE_ICON_FILE prototype.icns)

set_source_files_properties(${axr_icon_SOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

if(UNIX)
    set(AXR_SHARE_PREFIX share/axr/)
endif()

if(APPLE)
    set_source_files_properties(${hss_SOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/framework)
else()
    install(FILES ${hss_SOURCES} DESTINATION ${AXR_SHARE_PREFIX}resources/framework COMPONENT browser)
endif()

if(APPLE AND AXR_BUILD_FRAMEWORKS)
    set(TARGET_NAME_APP_BROWSER_OUTPUT_NAME "AXR Browser")
else()
    set(TARGET_NAME_APP_BROWSER_OUTPUT_NAME axrbrowser)
endif()

set_target_properties(${TARGET_NAME_APP_BROWSER} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    OUTPUT_NAME "${TARGET_NAME_APP_BROWSER_OUTPUT_NAME}"
)

install(TARGETS ${TARGET_NAME_APP_BROWSER}
    BUNDLE DESTINATION . COMPONENT browser
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_REL} COMPONENT browser
)

if(WIN32 OR APPLE)
    install_qt4_executable("${TARGET_NAME_APP_BROWSER_OUTPUT_NAME}${CMAKE_USER_EXECUTABLE_SUFFIX}" "qtaccessiblewidgets;qcncodecs;qjpcodecs;qkrcodecs;qtwcodecs;qsvgicon;qgif;qico;qjpeg;qmng;qsvg;qtiff" "" "${ALL_LIBRARY_DIRS}" "" "" browser)
    empty_lproj(${TARGET_NAME_APP_BROWSER_OUTPUT_NAME} browser)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/axrbrowser.desktop" "${CMAKE_BINARY_DIR}/axrbrowser.desktop")

# This is supposed to go in /usr/share/applications but we hardcode a /usr prefix for deb/rpm so it's OK
# It will otherwise break packaging for the ARCHIVE generator
install(FILES "${CMAKE_BINARY_DIR}/axrbrowser.desktop" DESTINATION share/applications COMPONENT freedesktop)
