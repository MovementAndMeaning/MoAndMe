//--------------------------------------------------------------------------------------
//
//  File:       M+MClientChannel.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for channels for responses from a service to a client.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms,
//              with or without modification, are permitted provided that the following
//              conditions are met:
//                * Redistributions of source code must retain the above copyright
//                  notice, this list of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright
//                  notice, this list of conditions and the following disclaimer in the
//                  documentation and/or other materials provided with the
//                  distribution.
//                * Neither the name of the copyright holders nor the names of its
//                  contributors may be used to endorse or promote products derived
//                  from this software without specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//              "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//              LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//              PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//              OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//              DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//              THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//              (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//              OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Created:    2014-03-18
//
//--------------------------------------------------------------------------------------

#include "M+MClientChannel.h"
#include "M+MBailOut.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wc++11-extensions"
# pragma clang diagnostic ignored "-Wdocumentation"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# pragma clang diagnostic ignored "-Wpadded"
# pragma clang diagnostic ignored "-Wshadow"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif // defined(__APPLE__)
#include <yarp/os/Time.h>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for channels for responses from a service to a client. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

using namespace MplusM::Common;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

ClientChannel::ClientChannel(void) :
        inherited()
{
    OD_LOG_ENTER();//####
    OD_LOG_EXIT_P(this);//####
} // ClientChannel::ClientChannel

ClientChannel::~ClientChannel(void)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_OBJEXIT();//####
} // ClientChannel::~ClientChannel

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

/*! @brief Add an output to the channel, using a backoff strategy with retries.
 @param theChannelToBeAdded The output to be added to the channel.
 @returns @c true if the channel was opened and @c false if it could not be opened. */
bool ClientChannel::addOutputWithRetries(const yarp::os::ConstString & theChannelToBeAdded)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("theChannelToBeAdded = ", theChannelToBeAdded.c_str());//####
    bool   result = false;
    double retryTime = INITIAL_RETRY_INTERVAL;
#if (! defined(MpM_DONT_USE_TIMEOUTS))
    int    retriesLeft = MAX_RETRIES;
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
    
    SetUpCatcher();
    try
    {
#if defined(MpM_DONT_USE_TIMEOUTS)
        do
        {
            OD_LOG("about to add an output");//####
            result = inherited::addOutput(theChannelToBeAdded);
            if (! result)
            {
                OD_LOG("%%retry%%");//####
                yarp::os::Time::delay(retryTime);
                retryTime *= RETRY_MULTIPLIER;
            }
        }
        while (! result);
#else // ! defined(MpM_DONT_USE_TIMEOUTS)
        do
        {
            BailOut bailer(*this);
            
            OD_LOG("about to add an output");//####
            result = inherited::addOutput(theChannelToBeAdded);
            if (! result)
            {
                if (0 < --retriesLeft)
                {
                    OD_LOG("%%retry%%");//####
                    yarp::os::Time::delay(retryTime);
                    retryTime *= RETRY_MULTIPLIER;
                }
            }
        }
        while ((! result) && (0 < retriesLeft));
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    ShutDownCatcher();
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // ClientChannel::addOutputWithRetries

void ClientChannel::close(void)
{
    OD_LOG_OBJENTER();//####
    SetUpCatcher();
    try
    {
#if (! defined(MpM_DONT_USE_TIMEOUTS))
        BailOut bailer(*this);
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
        
        inherited::interrupt();
        OD_LOG("about to close");//####
        inherited::close();
        OD_LOG("close completed.");//####
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    ShutDownCatcher();
    OD_LOG_OBJEXIT();//####
} // ClientChannel::close

bool ClientChannel::openWithRetries(const yarp::os::ConstString & theChannelName)
{
    OD_LOG_OBJENTER();//####
    OD_LOG_S1("theChannelName = ", theChannelName.c_str());//####
    bool   result = false;
    double retryTime = INITIAL_RETRY_INTERVAL;
#if (! defined(MpM_DONT_USE_TIMEOUTS))
    int    retriesLeft = MAX_RETRIES;
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
    
#if (! defined(MpM_CHANNELS_USE_RPC))
# if (defined(OD_ENABLE_LOGGING) && defined(MpM_LOG_INCLUDES_YARP_TRACE))
    inherited::setVerbosity(1);
# else // ! (defined(OD_ENABLE_LOGGING) && defined(MpM_LOG_INCLUDES_YARP_TRACE))
    inherited::setVerbosity(-1);
# endif // ! (defined(OD_ENABLE_LOGGING) && defined(MpM_LOG_INCLUDES_YARP_TRACE))
#endif // ! defined(MpM_CHANNELS_USE_RPC)
    SetUpCatcher();
    try
    {
#if defined(MpM_DONT_USE_TIMEOUTS)
        do
        {
            OD_LOG("about to open");//####
            result = inherited::open(theChannelName);
            if (! result)
            {
                OD_LOG("%%retry%%");//####
                yarp::os::Time::delay(retryTime);
                retryTime *= RETRY_MULTIPLIER;
            }
        }
        while (! result);
#else // ! defined(MpM_DONT_USE_TIMEOUTS)
        do
        {
            BailOut bailer(*this);
            
            OD_LOG("about to open");//####
            result = inherited::open(theChannelName);
            if (! result)
            {
                if (0 < --retriesLeft)
                {
                    OD_LOG("%%retry%%");//####
                    yarp::os::Time::delay(retryTime);
                    retryTime *= RETRY_MULTIPLIER;
                }
            }
        }
        while ((! result) && (0 < retriesLeft));
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    ShutDownCatcher();
    OD_LOG_OBJEXIT_B(result);//####
    return result;
} // ClientChannel::openWithRetries

void ClientChannel::RelinquishChannel(ClientChannel * & theChannel)
{
    OD_LOG_ENTER();//####
    OD_LOG_P1("theChannel = ", theChannel);//####
    SetUpCatcher();
    try
    {
#if (! defined(MpM_DONT_USE_TIMEOUTS))
        BailOut bailer(*theChannel);
#endif // ! defined(MpM_DONT_USE_TIMEOUTS)
        
        delete theChannel;
        theChannel = NULL;
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    ShutDownCatcher();
    OD_LOG_EXIT();//####
} // ClientChannel::RelinquishChannel

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
