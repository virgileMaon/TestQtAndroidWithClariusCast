QT += quick statemachine

SOURCES += \
        castbridge.cpp \
        castbridgeandroid.cpp \
        castbridgefake.cpp \
        main.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android: {

    ANDROID_ABIS = arm64-v8a
    ANDROID_MIN_SDK_VERSION=24
    ANDROID_TARGET_SDK_VERSION=31
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    QT += core-private
}

HEADERS += \
    Thread.h \
    castbridge.h \
    castbridgeandroid.h \
    castbridgefake.h
