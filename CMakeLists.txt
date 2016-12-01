project(pseudosequencer)

add_executable(pseudosequencer main.cpp)

install(TARGETS pseudosequencer RUNTIME DESTINATION bin)

add_subdirectory(application)
add_subdirectory(sequencer)
add_subdirectory(control)