# CMakeList.txt : projet CMake pour uchu-p, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("uchu-p")

set(SRC_FILE "src/main.cpp" "src/lib/window/window_logger.cpp" "src/lib/window/window_graphic.cpp")
set(HEADER_FILE "src/lib/logger.h" "src/lib/graphic.h")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (uchu-p ${SRC_FILE} ${HEADER_FILE})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/lib
  
    # Remember to add the include directories of any other libraries too
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET uchu-p PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
