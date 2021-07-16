add_compile_options(-Wall -Wextra -pedantic -Werror -fsanitize=undefined )
add_executable(helloworldServer hwserver.cpp)
target_link_libraries(helloworldServer zmq ubsan)

add_executable(helloworldClient hwclient.cpp)
target_link_libraries(helloworldClient zmq ubsan)

add_executable(pricepub pricepub.cpp)
target_link_libraries(pricepub zmq ubsan)

add_executable(priceclient priceclient.cpp)
target_link_libraries(priceclient zmq ubsan)

add_executable(taskvent taskvent.cpp)
target_link_libraries(taskvent zmq ubsan)
