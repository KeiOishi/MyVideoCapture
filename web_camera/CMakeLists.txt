include_directories(3party)

SET(SRC
        directshow_videocapture.cpp
        web_camera.cpp)

SET(HDRS
        directshow_videocapture.h
        web_camera.h
        3party/ewclib/ewclib.h
        3party/ewclib/qedit.h)

add_library(web STATIC ${SRC} ${HDRS})

