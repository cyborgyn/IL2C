cmake_minimum_required (VERSION 3.7)

set(CMAKE_BUILD_TYPE "${CONFIGURATION}")

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -Wall -Werror -Wstrict-prototypes -Wno-unused -fdata-sections -ffunction-sections -Wl,--gc-sections  -march=native")

if("${CONFIGURATION}" STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -flto -fomit-frame-pointer -DNDEBUG -s")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -D_DEBUG -g2")
endif()

set(IL2C_LIBRARY_NAME_BASE "il2c-gcc-linux-${PLATFORM}")
set(IL2C_LIBRARY_NAME "lib${IL2C_LIBRARY_NAME_BASE}-${CONFIGURATION}.a")

set(TARGET_LIBRARY_NAME "${IL2C_LIBRARY_NAME_BASE}-${CONFIGURATION}")

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/../lib)
