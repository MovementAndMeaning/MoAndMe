#--------------------------------------------------------------------------------------
#
#  File:       RGBLEDService/CMakeLists.txt
#
#  Project:    M+M
#
#  Contains:   The CMAKE definitions for the example RGB service application.
#
#  Written by: Norman Jaffe; Johnty Wang
#
#  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
#
#              All rights reserved. Redistribution and use in source and binary forms,
#              with or without modification, are permitted provided that the following
#              conditions are met:
#                * Redistributions of source code must retain the above copyright
#                  notice, this list of conditions and the following disclaimer.
#                * Redistributions in binary form must reproduce the above copyright
#                  notice, this list of conditions and the following disclaimer in the
#                  documentation and/or other materials provided with the
#                  distribution.
#                * Neither the name of the copyright holders nor the names of its
#                  contributors may be used to endorse or promote products derived
#                  from this software without specific prior written permission.
#
#              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#              "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#              LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
#              PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#              OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#              DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#              THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#              (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#              OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Created:    2014-02-06
#
#--------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)

# Find YARP
find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})

# Add YARP include directories
include_directories(${YARP_INCLUDE_DIRS})

# Find ACE
find_package(ACE REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ACE_MODULE_PATH})

# Add ACE include directories
include_directories(${ACE_INCLUDE_DIRS})


if(APPLE)
	set(CMAKE_OSX_ARCHITECTURES "i386;x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
	set(CMAKE_CXX_FLAGS "-stdlib=libstdc++" CACHE STRING "Fixes linking error for M+M/ACE" FORCE)
endif(APPLE)

# Set up our program
add_executable(mpmRGBLEDService
               main.cpp
			   M+MRGBLEDRequestHandler.cpp
               M+MRGBLEDService.cpp)

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be processed once.
target_link_libraries(mpmRGBLEDService
                      mpmCommon
                      odLogging
                      ${YARP_LIBRARIES})

enable_testing()