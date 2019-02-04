# Install script for directory: /home/davidrs/Escritorio/assimp-4.1.0/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/davidrs/Escritorio/assimp-4.1.0/lib/libassimp.so.4.1.0"
    "/home/davidrs/Escritorio/assimp-4.1.0/lib/libassimp.so.4"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.4"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/davidrs/Escritorio/assimp-4.1.0/lib/libassimp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/anim.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/ai_assert.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/camera.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/color4.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/color4.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/config.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/defs.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Defines.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/cfileio.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/light.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/material.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/material.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/matrix3x3.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/matrix3x3.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/matrix4x4.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/matrix4x4.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/mesh.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/postprocess.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/quaternion.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/quaternion.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/scene.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/metadata.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/texture.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/types.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/vector2.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/vector2.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/vector3.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/vector3.inl"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/version.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/cimport.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/importerdesc.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Importer.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/DefaultLogger.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/ProgressHandler.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/IOStream.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/IOSystem.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Logger.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/LogStream.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/NullLogger.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/cexport.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Exporter.hpp"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/DefaultIOStream.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/DefaultIOSystem.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/SceneCombiner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Compiler/pushpack1.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Compiler/poppack1.h"
    "/home/davidrs/Escritorio/assimp-4.1.0/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

