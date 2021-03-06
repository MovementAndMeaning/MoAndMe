#--------------------------------------------------------------------------------------------------
#
#  File:       examples/CMakeLists.txt
#
#  Project:    m+m
#
#  Contains:   The common CMAKE definitions for the m+m examples.
#
#  Written by: Norman Jaffe
#
#  Copyright:  (c) 2014 by H Plus Technologies Ltd. and Simon Fraser University.
#
#              All rights reserved. Redistribution and use in source and binary forms, with or
#              without modification, are permitted provided that the following conditions are met:
#                * Redistributions of source code must retain the above copyright notice, this list
#                  of conditions and the following disclaimer.
#                * Redistributions in binary form must reproduce the above copyright notice, this
#                  list of conditions and the following disclaimer in the documentation and / or
#                  other materials provided with the distribution.
#                * Neither the name of the copyright holders nor the names of its contributors may
#                  be used to endorse or promote products derived from this software without
#                  specific prior written permission.
#
#              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
#              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#              DAMAGE.
#
#  Created:    2014-03-25
#
#--------------------------------------------------------------------------------------------------

set(MpM_EXAMPLES_DIR "${PROJECT_SOURCE_DIR}/examples")

add_subdirectory(AbsorberService)
add_subdirectory(ChordGeneratorService)
add_subdirectory(EchoClient)
add_subdirectory(EchoService)
add_subdirectory(PlaybackFromJSONService)
add_subdirectory(RandomBurstService)
add_subdirectory(RandomNumberAdapter)
add_subdirectory(RandomNumberClient)
add_subdirectory(RandomNumberService)
add_subdirectory(RecordAsJSONService)
add_subdirectory(RecordIntegersService)
add_subdirectory(RunningSumAdapter)
add_subdirectory(RunningSumAltAdapter)
add_subdirectory(RunningSumClient)
add_subdirectory(RunningSumService)
add_subdirectory(TruncateFloatService)

enable_testing()
