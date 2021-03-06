//--------------------------------------------------------------------------------------------------
//
//  File:       m+m/m+mBaseInputHandler.cpp
//
//  Project:    m+m
//
//  Contains:   The class definition for the interface between m+m input handlers and YARP.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by H Plus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and / or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2014-02-11
//
//--------------------------------------------------------------------------------------------------

#include "m+mBaseInputHandler.hpp"

#include <m+m/m+mBaseChannel.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the interface between m+m input handlers and YARP. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

BaseInputHandler::BaseInputHandler(void) :
    inherited(), _channel(NULL), _canProcessInput(true), _metricsEnabled(false)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // BaseInputHandler::BaseInputHandler

BaseInputHandler::~BaseInputHandler(void)
{
    ODL_OBJENTER(); //####
    stopProcessing();
    ODL_OBJEXIT(); //####
} // BaseInputHandler::~BaseInputHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
BaseInputHandler::disableMetrics(void)
{
    ODL_OBJENTER(); //####
    _metricsEnabled = false;
    ODL_OBJEXIT(); //####
} // BaseInputHandler::disableMetrics

void
BaseInputHandler::enableMetrics(void)
{
    ODL_OBJENTER(); //####
    _metricsEnabled = true;
    ODL_OBJEXIT(); //####
} // BaseInputHandler::enableMetrics

bool
BaseInputHandler::read(yarp::os::ConnectionReader & connection)
{
    ODL_OBJENTER(); //####
    ODL_P1("connection = ", &connection); //####
    bool result = true;

    try
    {
        if (_canProcessInput)
        {
#if defined(MpM_ReportContactDetails)
            DumpContactToLog("input read", connection.getRemoteContact()); //####
#endif // defined(MpM_ReportContactDetails)
            yarp::os::Bottle aBottle;
            size_t           numBytes = connection.getSize();

            if (_metricsEnabled && _channel && _channel->metricsAreEnabled())
            {
                _channel->updateReceiveCounters(numBytes);
            }
            if (aBottle.read(connection))
            {
                result = handleInput(aBottle, connection.getRemoteContact().getName(),
                                     connection.getWriter(), numBytes);
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // BaseInputHandler::read

void
BaseInputHandler::setChannel(BaseChannel * theChannel)
{
    ODL_OBJENTER(); //####
    ODL_P1("theChannel = ", theChannel); //####
    _channel = theChannel;
    ODL_OBJEXIT(); //####
} // BaseInputHandler::setChannel

void
BaseInputHandler::stopProcessing(void)
{
    ODL_OBJENTER(); //####
    _canProcessInput = false;
    ODL_OBJEXIT(); //####
} // BaseInputHandler::stopProcessing

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
