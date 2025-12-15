cmake_minimum_required(VERSION 3.10)
project(PhysicsEngineCPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(physics_engine_sample
    src/main.cpp
    src/Vector.cpp
    src/GameObject.cpp
    src/CollisionRec.cpp
    src/Drag.cpp
    src/BodyRec.cpp
)

# Optional SFML app (try pkg-config first, then fallback to common library locations)
find_package(PkgConfig QUIET)
set(_sfml_found FALSE)
set(_sfml_libs)
if(PkgConfig_FOUND)
    pkg_check_modules(SFML_PKG QUIET sfml-graphics sfml-window sfml-system sfml-audio)
    if(SFML_PKG_FOUND)
        set(_sfml_found TRUE)
        # pkg-config provides linker flags and include dirs
        set(_sfml_libs ${SFML_PKG_LIBRARIES})
        include_directories(${SFML_PKG_INCLUDE_DIRS})
    endif()
endif()

if(NOT _sfml_found)
    # Check common Homebrew /usr/local prefixes for SFML libraries
    foreach(_prefix /opt/homebrew /usr/local /usr)
        if(EXISTS "${_prefix}/lib/libsfml-graphics.dylib" OR EXISTS "${_prefix}/lib/libsfml-graphics.a")
            set(_sfml_found TRUE)
            set(_sfml_libs_full)
            foreach(_lib graphics window system audio)
                if(EXISTS "${_prefix}/lib/libsfml-${_lib}.dylib")
                    list(APPEND _sfml_libs_full "${_prefix}/lib/libsfml-${_lib}.dylib")
                elseif(EXISTS "${_prefix}/lib/libsfml-${_lib}.a")
                    list(APPEND _sfml_libs_full "${_prefix}/lib/libsfml-${_lib}.a")
                else()
                    # fallback to -lsfml-<lib> name
                    list(APPEND _sfml_libs_full "-lsfml-${_lib}")
                endif()
            endforeach()
            include_directories(${_prefix}/include)
            break()
        endif()
    endforeach()
endif()

if((DEFINED SFML_PKG_FOUND AND SFML_PKG_FOUND) OR _sfml_libs_full)
    message(STATUS "SFML detected (usable) — building SFML app")
    add_executable(physics_engine_sfml
        src/SFMLApp.cpp
    )
    target_include_directories(physics_engine_sfml PRIVATE ${CMAKE_SOURCE_DIR}/include)
    # If pkg-config returned full linker flags, use them
    if(DEFINED SFML_PKG_FOUND AND SFML_PKG_FOUND)
        # Use pkg-config provided linker flags
        set_target_properties(physics_engine_sfml PROPERTIES LINK_FLAGS "${SFML_PKG_LIBRARIES}")
        target_include_directories(physics_engine_sfml PRIVATE ${SFML_PKG_INCLUDE_DIRS})
    else()
        # Ensure we have full library paths; if not, try to resolve via find_library
        if(NOT _sfml_libs_full)
            set(_sfml_libs_full)
            foreach(_lib graphics window system audio)
                find_library(_found_sfml_lib NAMES sfml-${_lib} HINTS /opt/homebrew/lib /usr/local/lib /usr)
                if(_found_sfml_lib)
                    list(APPEND _sfml_libs_full ${_found_sfml_lib})
                endif()
            endforeach()
        endif()

        if(_sfml_libs_full)
            target_link_libraries(physics_engine_sfml PRIVATE ${_sfml_libs_full})
        else()
            message(WARNING "SFML detected but no usable library files were resolved. To build the SFML demo, set SFML_DIR, install SFML dev package, or install pkg-config SFML modules.")
        endif()
    endif()
else()
    message(WARNING "SFML not found. To build the SFML demo, install SFML (e.g. `brew install sfml`) and re-run CMake.")
endif()
