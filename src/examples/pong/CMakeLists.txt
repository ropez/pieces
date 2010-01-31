find_package(OpenThreads REQUIRED)
find_package(OpenSceneGraph 2.0.0 REQUIRED osgViewer)

include_directories(${OPENTHREADS_INCLUDE_DIRS} ${OPENSCENEGRAPH_INCLUDE_DIRS})

set(ponghost_SOURCES
    main_host.cpp
    pong_host.cpp
    ball.cpp
    ball_host_callback.cpp
    player.cpp
    player_host_callback.cpp
    timer.cpp
)

set(pongpeer_SOURCES
    main_peer.cpp
    pong_peer.cpp
    ball.cpp
    ballosg.cpp
    event_handler.cpp
    frame.cpp
    osg_thread.cpp
    player.cpp
    playerosg.cpp
    score_board.cpp
)

add_executable(ponghost ${ponghost_SOURCES})
target_link_libraries(ponghost pieces ${OPENTHREADS_LIBRARIES})

add_executable(pongpeer ${pongpeer_SOURCES})
target_link_libraries(pongpeer pieces ${OPENSCENEGRAPH_LIBRARIES})
