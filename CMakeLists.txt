cmake_minimum_required(VERSION 3.0.0)
project(LEDEffects VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(led_effects main.c lights.c bouncing_balls.c light_effects.c)

target_link_libraries(led_effects pthread ws2811 m) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
