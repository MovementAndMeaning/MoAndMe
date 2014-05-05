//--------------------------------------------------------------------------------------
//
//  File:       M+MRegistryTest.cpp
//
//  Project:    M+M
//
//  Contains:   The test driver for the unit tests of the Service Registry ervice.
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
//  Created:    2014-03-14
//
//--------------------------------------------------------------------------------------

#include "M+MBaseClient.h"
#include "M+MBaseRequestHandler.h"
#include "M+MEndpoint.h"
#include "M+MRegistryService.h"
#include "M+MRequests.h"
#include "M+MServiceRequest.h"
#include "RegistryTests/M+MTest14Service.h"
#include "RegistryTests/M+MTest15Service.h"
#include "RegistryTests/M+MTest16Service.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#include <cstdlib>
#include <cstring>
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
#include <yarp/os/all.h>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The test driver for the unit tests of the Service Registry service. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::Test;
using std::cout;
using std::cerr;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief Set to @c true to use an in-memory database and @c false to use a disk-based database. */
#define TEST_INMEMORY true

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int doTestCreateRegisterService(const char * launchPath,
                                       const int    argc,
                                       char * *     argv) // create 'register' service
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("launchPath = ", launchPath);//####
    int result = 1;
    
    try
    {
        MplusM::Registry::RegistryService * registry = NULL;
        
        if (0 <= argc)
        {
            switch (argc)
            {
                    // Argument order for tests = [IP address / name [, port]]
                case 0:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY);
                    break;
                    
                case 1:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv);
                    break;
                    
                case 2:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv, argv[1]);
                    break;
                    
                default:
                    break;
                    
            }
        }
        if (registry)
        {
            if (registry->start())
            {
                result = (registry->isActive() ? 0 : 1);
                registry->stop();
            }
            else
            {
                OD_LOG("! (registry->start())");//####
            }
            delete registry;
        }
        else
        {
            OD_LOG("! (registry)");//####
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    OD_LOG_EXIT_L(result);//####
    return result;
} // doTestCreateRegisterService

/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int doTestRequestRegisterService(const char * launchPath,
                                        const int    argc,
                                        char * *     argv) // send 'register' request
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("launchPath = ", launchPath);//####
    int result = false;
    
    try
    {
        const char *                        secondServiceChannel;
        MplusM::Registry::RegistryService * registry = NULL;
        
        if (0 <= argc)
        {
            switch (argc)
            {
                    // Argument order for tests = [IP address / name [, port]]
                case 0:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestregisterservice_1");
                    break;
                    
                case 1:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestregisterservice_2");
                    break;
                    
                case 2:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv, argv[1]);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestregisterservice_3");
                    break;
                    
                default:
                    break;
                    
            }
        }
        if (registry)
        {
            if (registry->start())
            {
                if (registry->isActive())
                {
                    // Now we start up another service (Test14Service) and register it
                    Test14Service * stuff = new Test14Service(1, const_cast<char **>(&secondServiceChannel));
                    
                    if (stuff)
                    {
                        if (stuff->start())
                        {
                            yarp::os::ConstString channelName(stuff->getEndpoint().getName());
                            
                            if (MplusM::Common::RegisterLocalService(channelName))
                            {
                                result = 0;
                            }
                            else
                            {
                                OD_LOG("! (MplusM::Common::RegisterLocalService(channelName))");//####
                            }
                            stuff->stop();
                        }
                        else
                        {
                            OD_LOG("! (stuff->start())");//####
                        }
                        delete stuff;
                    }
                    else
                    {
                        OD_LOG("! (stuff)");//####
                    }
                }
                else
                {
                    OD_LOG("! (registry->isActive())");//####
                }
                registry->stop();
            }
            else
            {
                OD_LOG("! (registry->start())");//####
            }
            delete registry;
        }
        else
        {
            OD_LOG("! (registry)");//####
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    OD_LOG_EXIT_L(result);//####
    return result;
} // doTestRequestRegisterService

/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int doTestRequestUnregisterService(const char * launchPath,
                                          const int    argc,
                                          char * *     argv) // send 'register' request
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("launchPath = ", launchPath);//####
    int result = 1;

    try
    {
        const char *                        secondServiceChannel;
        MplusM::Registry::RegistryService * registry = NULL;
        
        if (0 <= argc)
        {
            switch (argc)
            {
                    // Argument order for tests = [IP address / name [, port]]
                case 0:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestunregisterservice_1");
                    break;
                    
                case 1:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestunregisterservice_2");
                    break;
                    
                case 2:
                    registry = new MplusM::Registry::RegistryService(launchPath, TEST_INMEMORY, *argv, argv[1]);
                    secondServiceChannel = T_(DEFAULT_SERVICE_NAME_BASE "test/requestunregisterservice_3");
                    break;
                    
                default:
                    break;
                    
            }
        }
        if (registry)
        {
            if (registry->start())
            {
                if (registry->isActive())
                {
                    // Now we start up another service (Test15Service) and register it
                    Test15Service * stuff = new Test15Service(1, const_cast<char **>(&secondServiceChannel));
                    
                    if (stuff)
                    {
                        if (stuff->start())
                        {
                            yarp::os::ConstString channelName(stuff->getEndpoint().getName());
                            
                            if (MplusM::Common::RegisterLocalService(channelName))
                            {
                                if (MplusM::Common::UnregisterLocalService(channelName))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    OD_LOG("! (MplusM::Common::UnregisterLocalService(channelName))");//####
                                }
                            }
                            else
                            {
                                OD_LOG("! (MplusM::Common::RegisterLocalService(channelName))");//####
                            }
                            stuff->stop();
                        }
                        else
                        {
                            OD_LOG("! (stuff->start())");//####
                        }
                        delete stuff;
                    }
                    else
                    {
                        OD_LOG("! (stuff)");//####
                    }
                }
                else
                {
                    OD_LOG("! (registry->isActive())");//####
                }
                registry->stop();
            }
            else
            {
                OD_LOG("! (registry->start())");//####
            }
            delete registry;
        }
        else
        {
            OD_LOG("! (registry)");//####
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    OD_LOG_EXIT_L(result);//####
    return result;
} // doTestRequestUnregisterService

/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int doTestRequestSearchService(const char * launchPath,
                                      const int    argc,
                                      char * *     argv) // send 'match' request
{
    OD_LOG_ENTER();//####
    OD_LOG_S1("launchPath = ", launchPath);//####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *                        secondServiceChannel = DEFAULT_SERVICE_NAME_BASE
                                                                        "test/requestsearchservice";
            MplusM::Registry::RegistryService * registry = new MplusM::Registry::RegistryService(launchPath,
                                                                                                 TEST_INMEMORY);
            
            if (registry)
            {
                if (registry->start())
                {
                    if (registry->isActive())
                    {
                        // Now we start up another service (Test16Service) and register it
                        Test16Service * stuff = new Test16Service(1, const_cast<char **>(&secondServiceChannel));
                        
                        if (stuff)
                        {
                            if (stuff->start())
                            {
                                yarp::os::ConstString channelName(stuff->getEndpoint().getName());
                                
                                if (MplusM::Common::RegisterLocalService(channelName))
                                {
                                    // Search for the service that we just registered.
                                    MplusM::Common::Package matches(MplusM::Common::FindMatchingServices(*argv));
                                    MplusM::Common::Package expected(argv[1]);
                                    
                                    OD_LOG_S3("criteria <- ", *argv, "expected <- ", expected.toString().c_str(),//####
                                              "matches <- ", matches.toString().c_str());//####
                                    if ((expected.size() == matches.size()) &&
                                        (MpM_EXPECTED_MATCH_RESPONSE_SIZE == matches.size()))
                                    {
                                        bool            wasASuccess = false;
                                        yarp::os::Value matchesFirst(matches.get(0));
                                        yarp::os::Value expectedFirst(expected.get(0));
                                        
                                        if (expectedFirst.isString())
                                        {
                                            yarp::os::ConstString matchesFirstAsString(matchesFirst.toString());
                                            yarp::os::ConstString expectedFirstAsString(expectedFirst.toString());
                                            
                                            if (matchesFirstAsString == expectedFirstAsString)
                                            {
                                                result = 0;
                                                if (! strcmp(MpM_OK_RESPONSE, matchesFirstAsString.c_str()))
                                                {
                                                    wasASuccess = true;
                                                }
                                            }
                                            else
                                            {
                                                OD_LOG("! (matchesFirstAsString == expectedFirstAsString)");//####
                                            }
                                        }
                                        else
                                        {
                                            OD_LOG("! (expectedFirst.isString())");//####
                                        }
                                        if ((! result) && wasASuccess)
                                        {
                                            yarp::os::Value matchesSecond(matches.get(1));
                                            yarp::os::Value expectedSecond(expected.get(1));
                                            
                                            if (expectedSecond.isList())
                                            {
                                                MplusM::Common::Package * matchesSecondAsList = matchesSecond.asList();
                                                MplusM::Common::Package * expectedSecondAsList =
                                                                                                expectedSecond.asList();
                                                int                       matchesSecondCount =
                                                                                            matchesSecondAsList->size();
                                                int                       expectedSecondCount =
                                                                                        expectedSecondAsList->size();
                                                
                                                OD_LOG_LL2("matchesSecondCount <- ", matchesSecondCount,//####
                                                           "expectedSecondCount <- ", expectedSecondCount);//####
                                                if (matchesSecondCount == expectedSecondCount)
                                                {
                                                    // Since the lists are the same length, we can just look for the
                                                    // expected values in the matched values.
                                                    for (int ii = 0; ii < expectedSecondCount; ++ii)
                                                    {
                                                        bool                  didFind = false;
                                                        yarp::os::Value       expectedSecondValue =
                                                                                        expectedSecondAsList->get(ii);
                                                        yarp::os::ConstString expectedString =
                                                                                        expectedSecondValue.toString();
                                                        
                                                        for (int jj = 0; jj < expectedSecondCount; ++jj)
                                                        {
                                                            yarp::os::Value       matchesSecondValue =
                                                                                        matchesSecondAsList->get(jj);
                                                            yarp::os::ConstString matchesString =
                                                                                        matchesSecondValue.toString();
                                                            
                                                            if (expectedString == matchesString)
                                                            {
                                                                didFind = true;
                                                                break;
                                                            }
                                                            
                                                        }
                                                        if (! didFind)
                                                        {
                                                            OD_LOG("(! didFind)");//####
                                                            result = 1;
                                                            break;
                                                        }
                                                        
                                                    }
                                                }
                                                else
                                                {
                                                    OD_LOG("! (matchesSecondCount == expectedSecondCount)");//####
                                                    result = 1;
                                                }
                                            }
                                            else
                                            {
                                                OD_LOG("! (expectedSecond.isList())");//####
                                                result = 1;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        OD_LOG("! ((expected.size() == matches.size()) && "//####
                                                  "(MpM_EXPECTED_MATCH_RESPONSE_SIZE == matches.size()))");//####
                                    }
                                    if (! MplusM::Common::UnregisterLocalService(channelName))
                                    {
                                        OD_LOG("(! MplusM::Common::UnregisterLocalService(channelName))");//####
                                    }
                                }
                                else
                                {
                                    OD_LOG("! (MplusM::Common::RegisterLocalService(channelName))");//####
                                }
                                stuff->stop();
                            }
                            else
                            {
                                OD_LOG("! (stuff->start())");//####
                            }
                            delete stuff;
                        }
                        else
                        {
                            OD_LOG("! (stuff)");//####
                        }
                    }
                    else
                    {
                        OD_LOG("! (registry->isActive())");//####
                    }
                    registry->stop();
                }
                else
                {
                    OD_LOG("! (registry->start())");//####
                }
                delete registry;
            }
            else
            {
                OD_LOG("! (registry)");//####
            }
        }
        else
        {
            OD_LOG("! (1 < argc)");//####
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
        throw;
    }
    OD_LOG_EXIT_L(result);//####
    return result;
} // doTestRequestSearchService

/*! @brief The signal handler to catch requests to stop the service.
 @param signal The signal being handled. */
static void catchSignal(int signal)
{
    OD_LOG_ENTER();//####
    OD_LOG_LL1("signal = ", signal);//####
    cerr << "Exiting due to signal " << signal << " = " << MplusM::NameOfSignal(signal) << endl;
    OD_LOG_EXIT_EXIT(1);//####
    yarp::os::exit(1);
} // catchSignal

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the Registry Service classes.
 
 The first argument is the test number, the second argument is the name of the channel to be used with the test, the
 optional third argument is the machine to connect to and the optional fourth argument is the port number to be used.
 Output depends on the test being run.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int main(int      argc,
         char * * argv)
{
    OD_LOG_INIT(*argv, kODLoggingOptionIncludeProcessID | kODLoggingOptionIncludeThreadID |//####
                kODLoggingOptionEnableThreadSupport | kODLoggingOptionWriteToStderr);//####
    OD_LOG_ENTER();//####
    int result = 1;
    
    try
    {
        if (yarp::os::Network::checkNetwork())
        {
            yarp::os::Network yarp; // This is necessary to establish any connection to the YARP infrastructure
            
            MplusM::Common::Initialize(*argv);
            if (0 < --argc)
            {
                int selector = atoi(argv[1]);
                
                MplusM::Common::SetSignalHandlers(catchSignal);
                OD_LOG_LL1("selector <- ", selector);//####
                switch (selector)
                {
                    case 13:
                        result = doTestCreateRegisterService(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 14:
                        result = doTestRequestRegisterService(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 15:
                        result = doTestRequestUnregisterService(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 16:
                        result = doTestRequestSearchService(*argv, argc - 1, argv + 2);
                        break;
                        
                    default:
                        break;
                        
                }
                if (result)
                {
                    OD_LOG_LL1("%%%%%%% unit test failure = ", result);//####
                }
            }
            else
            {
                OD_LOG("! (0 < --argc)");//####
            }
        }
        else
        {
            OD_LOG("! (yarp::os::Network::checkNetwork())");//####
            cerr << "YARP network not running." << endl;
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught");//####
    }
    yarp::os::Network::fini();
    OD_LOG_EXIT_L(result);//####
    return result;
} // main
