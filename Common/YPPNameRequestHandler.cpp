//--------------------------------------------------------------------------------------
//
//  File:       YPPNameRequestHandler.cpp
//
//  Project:    YarpPlusPlus
//
//  Contains:   The class definition for the request handler for the standard 'name'
//              request.
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

#include "YPPNameRequestHandler.h"
//#define ENABLE_OD_SYSLOG /* */
#include "ODSyslog.h"
#include "YPPBaseService.h"
#include "YPPRequests.h"

using namespace YarpPlusPlus;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The protocol version number for the 'list' request. */
#define NAME_REQUEST_VERSION_NUMBER "1.0"

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

NameRequestHandler::NameRequestHandler(BaseService & service) :
        inherited(YPP_NAME_REQUEST), _service(service)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_EXIT_P(this);//####
} // NameRequestHandler::NameRequestHandler

NameRequestHandler::~NameRequestHandler(void)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_EXIT();//####
} // NameRequestHandler::~NameRequestHandler

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void NameRequestHandler::fillInDescription(yarp::os::Property & info)
{
    OD_SYSLOG_ENTER();//####
    info.put(YPP_REQREP_DICT_REQUEST_KEY, YPP_NAME_REQUEST);
    info.put(YPP_REQREP_DICT_OUTPUT_KEY, YPP_REQREP_STRING);
    info.put(YPP_REQREP_DICT_VERSION_KEY, NAME_REQUEST_VERSION_NUMBER);
    info.put(YPP_REQREP_DICT_DESCRIPTION_KEY, "Return the canonical name of the service");
    yarp::os::Value    keywords;
    yarp::os::Bottle * asList = keywords.asList();
    
    asList->addString(YPP_NAME_REQUEST);
    asList->addString("canonical");
    info.put(YPP_REQREP_DICT_KEYWORDS_KEY, keywords);
    OD_SYSLOG_EXIT();//####
} // NameRequestHandler::fillInDescription

bool NameRequestHandler::operator() (const yarp::os::Bottle &     restOfInput,
                                     yarp::os::ConnectionWriter * replyMechanism)
{
#if (! defined(ENABLE_OD_SYSLOG))
# pragma unused(restOfInput)
#endif // ! defined(ENABLE_OD_SYSLOG)
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_S1("restOfInput = ", restOfInput.toString().c_str());//####
    OD_SYSLOG_P1("replyMechanism = ", replyMechanism);//####
    bool result = true;
    
    if (replyMechanism)
    {
        yarp::os::Bottle reply;
        
        reply.addString(_service.canonicalName());
        OD_SYSLOG_S1("reply <- ", reply.toString().c_str());
        reply.write(*replyMechanism);
    }
    OD_SYSLOG_EXIT_B(result);//####
    return result;
} // NameRequestHandler::operator()

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)