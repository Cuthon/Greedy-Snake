AUX_SOURCE_DIRECTORY(. SRC)

add_executable(Snake ${SRC})

target_link_libraries(Snake -leasyx)