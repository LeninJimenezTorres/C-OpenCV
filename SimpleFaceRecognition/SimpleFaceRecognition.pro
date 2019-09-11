TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv/build/x64/vc14/lib/ -lopencv_world341
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv/build/x64/vc14/lib/ -lopencv_world341d

INCLUDEPATH += $$PWD/../../../opencv/build/include
DEPENDPATH += $$PWD/../../../opencv/build/include/opencv2


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_calib3d2413 -lopencv_contrib2413 -lopencv_core2413 -lopencv_features2d2413 -lopencv_photo2413 -lopencv_video2413 -lopencv_videostab2413 -lopencv_highgui2413 -lopencv_imgproc2413 -lopencv_flann2413 -lopencv_ml2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_calib3d2413d -lopencv_contrib2413d -lopencv_core2413d -lopencv_features2d2413d -lopencv_photo2413d -lopencv_video2413d -lopencv_videostab2413d -lopencv_highgui2413d -lopencv_imgproc2413d -lopencv_flann2413d -lopencv_ml2413d

INCLUDEPATH += $$PWD/../../../opencv2.4/build/x64/include
DEPENDPATH += $$PWD/../../../opencv2.4/build/x64/include/opencv2


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_nonfree2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_nonfree2413d

INCLUDEPATH += $$PWD/../../../opencv2.4/build/include
DEPENDPATH += $$PWD/../../../opencv2.4/build/include/opencv2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_objdetect2413
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv2.4/build/x64/vc14/lib/ -lopencv_objdetect2413d

INCLUDEPATH += $$PWD/../../../opencv2.4/build/include
DEPENDPATH += $$PWD/../../../opencv2.4/build/include/openvc2
