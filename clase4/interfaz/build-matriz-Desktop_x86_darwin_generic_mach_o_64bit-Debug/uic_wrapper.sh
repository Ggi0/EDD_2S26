#!/bin/bash
DYLD_FRAMEWORK_PATH=/Users/gio/Desktop/qt/qt-everywhere-src-5.15.2/qtbase/lib${DYLD_FRAMEWORK_PATH:+:$DYLD_FRAMEWORK_PATH}
export DYLD_FRAMEWORK_PATH
QT_PLUGIN_PATH=/Users/gio/Desktop/qt/qt-everywhere-src-5.15.2/qtbase/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec /Users/gio/Desktop/qt/qt-everywhere-src-5.15.2/qtbase/bin/uic "$@"
