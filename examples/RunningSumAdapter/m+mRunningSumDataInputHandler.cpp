//--------------------------------------------------------------------------------------------------
//
//  File:       m+mRunningSumDataInputHandler.cpp
//
//  Project:    m+m
//
//  Contains:   The class definition for the custom data channel input handler used by the Running
//              Sum adapter.
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
//  Created:    2014-03-24
//
//--------------------------------------------------------------------------------------------------

#include "m+mRunningSumDataInputHandler.h"

#include "m+mRunningSumAdapterData.h"
#include "m+mRunningSumClient.h"
#include "m+mRunningSumRequests.h"

#include <m+m/m+mBaseChannel.h>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the custom data channel input handler used by the Running Sum
 adapter. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::Example;

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

RunningSumDataInputHandler::RunningSumDataInputHandler(RunningSumAdapterData & shared) :
    inherited(), _shared(shared)
{
    ODL_ENTER(); //####
    ODL_P1("shared = ", &shared); //####
    ODL_EXIT_P(this); //####
} // RunningSumDataInputHandler::RunningSumDataInputHandler

RunningSumDataInputHandler::~RunningSumDataInputHandler(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // RunningSumDataInputHandler::~RunningSumDataInputHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
bool
RunningSumDataInputHandler::handleInput(const yarp::os::Bottle &     input,
                                        const YarpString &           senderChannel,
                                        yarp::os::ConnectionWriter * replyMechanism,
                                        const size_t                 numBytes)
{
#if (! defined(OD_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(senderChannel,replyMechanism)
# endif // MAC_OR_LINUX_
#endif // ! defined(OD_ENABLE_LOGGING_)
    ODL_OBJENTER(); //####
    ODL_S2s("senderChannel = ", senderChannel, "got ", input.toString()); //####
    ODL_P1("replyMechanism = ", replyMechanism); //####
    ODL_L1("numBytes = ", numBytes); //####
    bool result = true;

    try
    {
        int howMany = input.size();

        if (0 < howMany)
        {
            BaseChannel *      theOutput = _shared.getOutput();
            RunningSumClient * theClient = (RunningSumClient *) _shared.getClient();

            if (_shared.isActive() && theClient && theOutput)
            {
                if (1 == howMany)
                {
                    bool            gotValue = false;
                    double          inValue = 0.0;
                    yarp::os::Value argValue(input.get(0));

                    if (argValue.isInt())
                    {
                        inValue = argValue.asInt();
                        gotValue = true;
                    }
                    else if (argValue.isDouble())
                    {
                        inValue = argValue.asDouble();
                        gotValue = true;
                    }
                    if (gotValue)
                    {
                        double outValue;

                        _shared.lock();
                        if (theClient->addToSum(inValue, outValue))
                        {
                            yarp::os::Bottle message;

                            message.addDouble(outValue);
                            if (! theOutput->write(message))
                            {
                                ODL_LOG("(! theOutput->write(message))"); //####
#if defined(MpM_StallOnSendProblem)
                                Stall();
#endif // defined(MpM_StallOnSendProblem)
                            }
                        }
                        else
                        {
                            ODL_LOG("! (theClient->startSum())"); //####
                        }
                        _shared.unlock();
                    }
                }
                else
                {
                    DoubleVector values;

                    for (int ii = 0; ii < howMany; ++ii)
                    {
                        double          inValue;
                        yarp::os::Value aValue(input.get(ii));

                        if (aValue.isInt())
                        {
                            inValue = aValue.asInt();
                            values.push_back(inValue);
                        }
                        else if (aValue.isDouble())
                        {
                            inValue = aValue.asDouble();
                            values.push_back(inValue);
                        }
                    }
                    if (0 < values.size())
                    {
                        double outValue;

                        _shared.lock();
                        if (theClient->addToSum(values, outValue))
                        {
                            yarp::os::Bottle message;

                            message.addDouble(outValue);
                            if (! theOutput->write(message))
                            {
                                ODL_LOG("(! theOutput->write(message))"); //####
#if defined(MpM_StallOnSendProblem)
                                Stall();
#endif // defined(MpM_StallOnSendProblem)
                            }
                        }
                        else
                        {
                            ODL_LOG("! (theClient->startSum())"); //####
                        }
                        _shared.unlock();
                    }
                }
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
} // RunningSumDataInputHandler::handleInput
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
