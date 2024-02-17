# CMakeList.txt : projet CMake pour uchu-p, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

endif()

project ("uchu-p")

set(SRC_FILE "src/main.cpp" "src/lib/window/window_logger.cpp" "src/lib/window/window_graphic.cpp" "src/game/uchu.cpp" "src/lib/ecs/ecs.cpp" "src/game/component/box.cpp" "src/game/component/position.cpp" "src/game/entity/player.cpp" "src/game/system/inputSystem.cpp" "src/game/component/input.cpp" "src/game/component/velocity.cpp" "src/lib/window/window_sound.cpp" "src/game/entity/bullet.cpp" "src/game/system/graphicSystem.cpp" "src/game/system/movementSystem.cpp" "src/game/component/sprite.cpp" "src/game/system/cleanSystem.cpp" "src/game/component/lifetime.cpp")
set(HEADER_FILE "src/lib/logger.h" "src/lib/graphic.h" "src/game/key_binding.h" "src/lib/ecs/ecs.h" "src/game/component/box.h" "src/game/component/position.h" "src/game/entity/player.h" "src/game/component/input.h" "src/game/component/velocity.h" "src/lib/sound.h" "src/game/entity/bullet.h"  "src/game/component/action.h" "src/game/component/player/shoot.h" "src/game/system/system.h" "src/game/system/movementSystem.h" "src/game/component/sprite.h" "src/game/asset.h" "src/game/system/cleanSystem.h" "src/game/component/lifetime.h")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (uchu-p ${SRC_FILE} ${HEADER_FILE} )
target_link_libraries(uchu-p PRIVATE winmm)
target_include_directories(${PROJECT_NAME} PRIVATE
    src/lib
    src/game
  
    # Remember to add the include directories of any other libraries too
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
     target_link_options(uchu-p PRIVATE "/subsystem:windows,5.1")
     #target_compile_options(uchu-p PRIVATE "/D_WIN32_WINNT=0x0501")
endif()

message(STATUS "Modified string: ${CMAKE_CXX_FLAGS}")
message(STATUS "Modified string: ${CMAKE_CXX_FLAGS_RELEASE}")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET uchu-p PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
