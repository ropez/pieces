find_package(OpenThreads REQUIRED)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

include_directories(${OPENTHREADS_INCLUDE_DIR})

set(qchat_SOURCES
    qchat.cpp
    chatwidget.cpp
    chathost.cpp
    chatpeer.cpp
    startwidget.cpp
)

set(qchat_HEADERS
    startwidget.h
    chatwidget.h
    chatpeer.h
)

QT4_WRAP_CPP(MOC_OUTPUT_FILES ${qchat_HEADERS})

add_executable(qchat ${qchat_SOURCES} ${MOC_OUTPUT_FILES})
target_link_libraries(qchat pieces ${OPENTHREADS_LIBRARY} ${QT_LIBRARIES})
