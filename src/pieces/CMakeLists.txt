set(pieces_SOURCES
    debug_stream.cpp
    exception.cpp
    io_exception.cpp
    disconnected_exception.cpp
    timeout_exception.cpp
    invalid_key_exception.cpp
    value_list.cpp
    property_list.cpp
    byte_array.cpp
    data_stream.cpp
    buffer_stream.cpp
    stream_target.cpp
    data_buffer.cpp
    file.cpp
    shared_data.cpp
    event.cpp
    event_loop.cpp
    event_loop_thread.cpp
    event_queue.cpp
    event_handler.cpp
    event_filter.cpp
    network_event_filter.cpp
    timer_event.cpp
    game_event.cpp
    input_event.cpp
    timer_thread.cpp
    timer.cpp
    inet_address.cpp
    socket_address.cpp
    datagram.cpp
    object.cpp
    game_object.cpp
    game_object_db.cpp
    frame_data.cpp
    game_data.cpp
    game_data_sender.cpp
    game_data_receiver_thread.cpp
    game_data_receiver.cpp
    network_event.cpp
    message_received_event.cpp
    disconnected_event.cpp
    connected_event.cpp
    game_data_event.cpp
    message.cpp
    message_queue.cpp
    tcp_receiver_thread.cpp
    tcp_sender_thread.cpp
    tcp_listener_thread.cpp
    tcp_connection.cpp
    tcp_connection_manager.cpp
    application.cpp
    host.cpp
    peer.cpp
    host_thread.cpp
    peer_thread.cpp
)
if (CMAKE_HOST_UNIX)
    enable_language(ASM-ATT)
    set(pieces_SOURCES ${pieces_SOURCES}
        atomic_linux.s
        tcp_socket_linux.cpp
        udp_socket_linux.cpp
    )
elseif (CMAKE_HOST_WIN32)
    set(pieces_SOURCES ${pieces_SOURCES}
        atomic_win32.c
        tcp_socket_win32.cpp
        udp_socket_win32.cpp
    )
endif (CMAKE_HOST_UNIX)

add_library(pieces SHARED ${pieces_SOURCES})
set_target_properties(pieces PROPERTIES VERSION 0.1.1 SOVERSION 0.1)
install(TARGETS pieces LIBRARY DESTINATION lib)
