//--------------------------------------------------------------------------------------------------
//
//  File:       RequestCounterClientMain.cpp
//
//  Project:    M+M
//
//  Contains:   The main application for the client of the request counter service.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and/or
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
//  Created:    2014-03-14
//
//--------------------------------------------------------------------------------------------------

#include "M+MChannelStatusReporter.h"
#include "M+MRequestCounterClient.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The main application for the client of the request counter service. */

/*! @dir RequestCounterClient
 @brief The mpmRequestCounterClient application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::RequestCounter;
using std::cin;
using std::cout;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Write out a time value in a human-friendly form.
 @param measurement The time value to write out. */
static void reportTimeInReasonableUnits(const double measurement)
{
    double       newValue;
    const char * tag;
    
    if (measurement < 1e-6)
    {
        // Less than a microsecond
        newValue = (measurement * 1e6);
        tag = " microseconds";
    }
    else if (measurement < 1e-3)
    {
        // Less than a millisecond
        newValue = (measurement * 1e3);
        tag = " milliseconds";
    }
    else if (measurement < 60.0)
    {
        // Less than a minute
        newValue = measurement;
        tag = " seconds";
    }
    else if (measurement < (60.0 * 60.0))
    {
        // Less than an hour
        newValue = (measurement / 60.0);
        tag = " minutes";
    }
    else if (measurement < (24.0 * 60.0 * 60.0))
    {
        // Less than a day
        newValue = (measurement / (60.0 * 60.0));
        tag = " hours";
    }
    else
    {
        // More than a day
        newValue = (measurement / (24.0 * 60.0 * 60.0));
        tag = " days";
    }
    cout << newValue << tag;
} // reportTimeInReasonableUnits

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for communicating with the Request Counter service.
 
 Integers read from standard input will be sent to the service as the number of requests to
 simulate. Entering a zero will exit the program.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the example client.
 @returns @c 0 on a successful test and @c 1 on failure. */
int main(int     argc,
         char ** argv)
{
#if MAC_OR_LINUX_
# pragma unused(argc)
#endif // MAC_OR_LINUX_
    OD_LOG_INIT(*argv, kODLoggingOptionIncludeProcessID | kODLoggingOptionIncludeThreadID | //####
                kODLoggingOptionEnableThreadSupport | kODLoggingOptionWriteToStderr); //####
    OD_LOG_ENTER(); //####
    MplusM::Common::SetUpLogger(*argv);
    try
    {
        if (MplusM::CanReadFromStandardInput())
        {
#if CheckNetworkWorks_
            if (yarp::os::Network::checkNetwork())
#endif // CheckNetworkWorks_
            {
                yarp::os::Network yarp; // This is necessary to establish any connection to the YARP
                                        // infrastructure
                
                MplusM::Common::Initialize(*argv);
                RequestCounterClient * stuff = new RequestCounterClient;
                
                if (stuff)
                {
#if defined(MpM_ReportOnConnections)
                    stuff->setReporter(ChannelStatusReporter::gReporter, true);
#endif // defined(MpM_ReportOnConnections)
                    MplusM::StartRunning();
                    MplusM::Common::SetSignalHandlers(MplusM::SignalRunningStop);
                    for ( ; MplusM::IsRunning(); )
                    {
                        int count;
                        
                        cout << "How many requests? ";
                        cin >> count;
                        if (0 >= count)
                        {
                            break;
                        }
                        
                        if (stuff->findService("name:RequestCounter"))
                        {
                            if (stuff->connectToService())
                            {
                                if (stuff->resetServiceCounters())
                                {
                                    for (int ii = 0; ii < count; ++ii)
                                    {
                                        if (! stuff->pokeService())
                                        {
                                            MplusM::Common::GetLogger().fail("Problem poking the "
                                                                             "service.");
                                            break;
                                        }
                                        
                                    }
                                    long   counter;
                                    double elapsedTime;
                                    
                                    if (stuff->getServiceStatistics(counter, elapsedTime))
                                    {
                                        if (0 < counter)
                                        {
                                            cout << "count = " << counter << ", elapsed time = ";
                                            reportTimeInReasonableUnits(elapsedTime);
                                            cout << ", average time = ";
                                            reportTimeInReasonableUnits(elapsedTime / counter);
                                            cout << "." << endl;
                                        }
                                        else
                                        {
                                            cout << "Service reports zero requests." << endl;
                                        }
                                    }
                                    else
                                    {
                                        OD_LOG("! (stuff->getServiceStatistics(counter, " //####
                                               "elapsedTime))"); //####
                                        MplusM::Common::GetLogger().fail("Problem getting "
                                                                         "statistics from the "
                                                                         "service.");
                                    }
                                }
                                else
                                {
                                    OD_LOG("! (stuff->resetServiceCounters())"); //####
                                    MplusM::Common::GetLogger().fail("Problem resetting the "
                                                                     "service counters.");
                                }
                                if (! stuff->disconnectFromService())
                                {
                                    OD_LOG("(! stuff->disconnectFromService())"); //####
                                    MplusM::Common::GetLogger().fail("Problem disconnecting from "
                                                                     "the service.");
                                }
                            }
                            else
                            {
                                OD_LOG("! (stuff->connectToService())"); //####
                                MplusM::Common::GetLogger().fail("Problem connecting to the "
                                                                 "service.");
                            }
                        }
                        else
                        {
                            OD_LOG("! (stuff->findService(\"name:RequestCounter\"))"); //####
                            MplusM::Common::GetLogger().fail("Problem locating the service.");
                        }
                    }
                    delete stuff;
                }
                else
                {
                    OD_LOG("! (stuff)"); //####
                }
            }
#if CheckNetworkWorks_
            else
            {
                OD_LOG("! (yarp::os::Network::checkNetwork())"); //####
                MplusM::Common::GetLogger().fail("YARP network not running.");
            }
#endif // CheckNetworkWorks_
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
    }
    yarp::os::Network::fini();
    OD_LOG_EXIT_L(0); //####
    return 0;
} // main
