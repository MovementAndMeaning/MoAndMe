//
//  RegistryService/main.cpp
//  YarpPlusPlus
//
//  Created by Norman Jaffe on 2014-02-06.
//  Copyright (c) 2014 OpenDragon. All rights reserved.
//

#define ENABLE_OD_SYSLOG /* */
#include "ODSyslog.h"
#include "YPPRegistryService.h"
#include "YPPRequests.h"
#include <yarp/os/all.h>
#include <yarp/conf/version.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace YarpPlusPlus;
using std::cout;
using std::cerr;
using std::endl;

#pragma mark Private structures and constants

/*! @brief Run loop control; @c true if the service is to keep going and @c false otherwise. */
static bool lKeepRunning;

#pragma mark Local functions

/*! @brief The signal handler to catch requests to stop the service.
 @param signal The signal being handled. */
static void stopRunning(int signal)
{
#pragma unused(signal)
    lKeepRunning = false;
} // stopRunning

#pragma mark Global functions

/*! @brief The entry point for creating the Service Registry service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the Service Registry service.
 @returns @c 0 on a successful test and @c 1 on failure. */
int main(int      argc,
         char * * argv)
{
    OD_SYSLOG_INIT(*argv, kODSyslogOptionIncludeProcessID | kODSyslogOptionIncludeThreadID |//####
                   kODSyslogOptionEnableThreadSupport);//####
    OD_SYSLOG_ENTER();//####
    yarp::os::Network yarp; // This is necessary to establish any connection to the YARP infrastructure
    RegistryService * stuff = NULL;
    
    cout << "YARP++ Version " << YPP_VERSION << ", YARP Version " << YARP_VERSION_STRING << endl;
    if (argc >= 1)
    {
        switch (argc)
        {
                // Argument order for tests = endpoint name [, IP address / name [, port]]
            case 1:
                stuff = new RegistryService();
                break;
                
            case 2:
                stuff = new RegistryService(argv[1]);
                break;
                
            case 3:
                stuff = new RegistryService(argv[1], argv[2]);
                break;
                
            default:
                break;
                
        }
    }
    if (stuff)
    {
        if (stuff->start())
        {
            // Note that the Registry Service is self-registering... so we don't need to call registerLocalService().
            lKeepRunning = true;
            signal(SIGHUP, stopRunning);
            signal(SIGINT, stopRunning);
            signal(SIGINT, stopRunning);
            signal(SIGUSR1, stopRunning);
            for ( ; lKeepRunning; )
            {
                sleep(1);
            }
            stuff->stop();
        }
        delete stuff;
    }
    OD_SYSLOG_EXIT_L(0);//####
    return 0;
} // main
