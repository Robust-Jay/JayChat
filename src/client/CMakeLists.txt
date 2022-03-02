aux_source_directory(. SRC_LIST)

add_executable(JayChatClient ${SRC_LIST})

target_link_libraries(JayChatClient pthread)