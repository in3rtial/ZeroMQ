add_executable(helloworldServer hwserver.cpp)
target_link_libraries(helloworldServer zmq)

add_executable(helloworldClient hwclient.cpp)
target_link_libraries(helloworldClient zmq)
