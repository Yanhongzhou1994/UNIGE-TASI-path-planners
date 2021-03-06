cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED OPT_LVL)
    set(OPT_LVL 2)
endif ()
add_definitions(-DOPT_LVL=${OPT_LVL})

if (NO_HEURISTIC MATCHES 1)
    set(HEUR "no_heur")
    add_definitions(-DNO_HEURISTIC)
else(NOT DEFINED NO_HEURISTIC)
    set(HEUR "heur")
endif ()

include_directories(SYSTEM ../../../RobinHoodHashMap/src/include)
include_directories(SYSTEM ../../../TartanLlamaOptional/include)
include_directories(SYSTEM ../../../BoostHeap)
include_directories(../../../ShiftedGridFastMarching)
include_directories(../../../PathExtraction)
include_directories(../../../ProjectToolkit/include)

add_executable(shifted_grid_planner_${OPT_LVL}_${HEUR}
               main.cpp)

target_link_libraries(shifted_grid_planner_${OPT_LVL}_${HEUR} gcov)
target_link_libraries(shifted_grid_planner_${OPT_LVL}_${HEUR} pthread)
target_link_libraries(shifted_grid_planner_${OPT_LVL}_${HEUR} ProjectToolkit)
target_link_libraries(shifted_grid_planner_${OPT_LVL}_${HEUR} robin_hood)

add_custom_command(TARGET shifted_grid_planner_${OPT_LVL}_${HEUR}
                   POST_BUILD
                   COMMAND sudo setcap 'cap_sys_nice=eip' "${CMAKE_CURRENT_BINARY_DIR}/shifted_grid_planner_${OPT_LVL}_${HEUR}")