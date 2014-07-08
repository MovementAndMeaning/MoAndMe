//--------------------------------------------------------------------------------------------------
//
//  File:       M+MMatchRequestHandler.cpp
//
//  Project:    M+M
//
//  Contains:   The class definition for the request handler for the 'match' request.
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
//  Created:    2014-03-10
//
//--------------------------------------------------------------------------------------------------

#include "M+MMatchRequestHandler.h"
#include "M+MBaseNameValidator.h"
#include "M+MEndpoint.h"
#include "M+MMatchExpression.h"
#include "M+MRegistryService.h"
#include "M+MRequests.h"

//#include "ODEnableLogging.h"
#include "ODLogging.h"

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 
 @brief The class definition for the request handler for the 'match' request. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::Parser;
using namespace MplusM::Registry;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The protocol version number for the 'match' request. */
#define MATCH_REQUEST_VERSION_NUMBER "1.0"

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and destructors
#endif // defined(__APPLE__)

MatchRequestHandler::MatchRequestHandler(RegistryService &           service,
                                         Parser::BaseNameValidator * validator) :
    inherited(MpM_MATCH_REQUEST), _service(service), _validator(validator)
{
    OD_LOG_ENTER(); //####
    OD_LOG_P2("service = ", &service, "validator = ", validator); //####
    OD_LOG_EXIT_P(this); //####
} // MatchRequestHandler::MatchRequestHandler

MatchRequestHandler::~MatchRequestHandler(void)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_OBJEXIT(); //####
} // MatchRequestHandler::~MatchRequestHandler

#if defined(__APPLE__)
# pragma mark Actions
#endif // defined(__APPLE__)

void MatchRequestHandler::fillInAliases(Common::StringVector & alternateNames)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("alternateNames = ", &alternateNames); //####
    alternateNames.push_back("find");
    OD_LOG_OBJEXIT(); //####
} // MatchRequestHandler::fillInAliases

void MatchRequestHandler::fillInDescription(const yarp::os::ConstString & request,
                                            yarp::os::Property &          info)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_S1s("request = ", request); //####
    OD_LOG_P1("info = ", &info); //####
    try
    {
        info.put(MpM_REQREP_DICT_REQUEST_KEY, request);
        info.put(MpM_REQREP_DICT_INPUT_KEY, MpM_REQREP_INT MpM_REQREP_STRING);
        info.put(MpM_REQREP_DICT_OUTPUT_KEY, MpM_REQREP_LIST_START MpM_REQREP_STRING
                 MpM_REQREP_0_OR_MORE MpM_REQREP_LIST_END);
        info.put(MpM_REQREP_DICT_VERSION_KEY, MATCH_REQUEST_VERSION_NUMBER);
        info.put(MpM_REQREP_DICT_DETAILS_KEY, "Find a matching service\n"
                 "Input: an integer (1=return names, 0=return ports) and an expression describing "
                 "the service to be found\n"
                 "Output: OK and a list of matching service names/ports or FAILED, with a "
                 "description of the problem encountered");
        yarp::os::Value    keywords;
        yarp::os::Bottle * asList = keywords.asList();
        
        asList->addString(request);
        asList->addString("find");
        info.put(MpM_REQREP_DICT_KEYWORDS_KEY, keywords);
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT(); //####
} // MatchRequestHandler::fillInDescription

bool MatchRequestHandler::processRequest(const yarp::os::ConstString & request,
                                         const yarp::os::Bottle &      restOfInput,
                                         const yarp::os::ConstString & senderChannel,
                                         yarp::os::ConnectionWriter *  replyMechanism)
{
#if (! defined(OD_ENABLE_LOGGING))
# if MAC_OR_LINUX_
#  pragma unused(request,senderChannel)
# endif // MAC_OR_LINUX_
#endif // ! defined(OD_ENABLE_LOGGING)
    OD_LOG_OBJENTER(); //####
    OD_LOG_S3s("request = ", request, "restOfInput = ", restOfInput.toString(), //####
               "senderChannel = ", senderChannel); //####
    OD_LOG_P1("replyMechanism = ", replyMechanism); //####
    bool result = true;
    
    try
    {
        if (replyMechanism)
        {
            OD_LOG("(replyMechanism)"); //####
            yarp::os::Bottle reply;
            
            // We are expecting an integer and a string as the parameter
            if (2 == restOfInput.size())
            {
                yarp::os::Value condition(restOfInput.get(0));
                yarp::os::Value argument(restOfInput.get(1));
                
                if (condition.isInt() && argument.isString())
                {
                    int                   conditionAsInt = condition.asInt();
                    yarp::os::ConstString argAsString(argument.toString());
                    
                    OD_LOG_S1s("argAsString <- ", argAsString); //####
                    size_t                    endPos;
                    Parser::MatchExpression * matcher =
                                                Parser::MatchExpression::CreateMatcher(argAsString,
                                                                               argAsString.length(),
                                                                                       0, endPos,
                                                                                       _validator);

                    if (matcher)
                    {
                        OD_LOG("(matcher)"); //####
                        // Hand off the processing to the registry service. First, put the 'OK'
                        // response in the output buffer, as we have successfully parsed the
                        // request.
                        reply.addString(MpM_OK_RESPONSE);
                        if (! _service.processMatchRequest(matcher, 0 != conditionAsInt, reply))
                        {
                            OD_LOG("(! _service.processMatchRequest(matcher, " //####
                                   "0 != conditionAsInt, reply))"); //####
                            reply.clear();
                            reply.addString(MpM_FAILED_RESPONSE);
                            reply.addString("Invalid criteria");
                        }
                        delete matcher;
                    }
                    else
                    {
                        OD_LOG("! (matcher)"); //####
                        reply.addString(MpM_FAILED_RESPONSE);
                        reply.addString("Invalid criteria");
                    }
                }
                else
                {
                    OD_LOG("! (argument.isString())"); //####
                    reply.addString(MpM_FAILED_RESPONSE);
                    reply.addString("Invalid criteria");
                }
            }
            else
            {
                OD_LOG("! (1 == restOfInput.size())"); //####
                reply.addString(MpM_FAILED_RESPONSE);
                reply.addString("Missing criteria or extra arguments to request");
            }
            OD_LOG_S1s("reply <- ", reply.toString()); //####
            if (! reply.write(*replyMechanism))
            {
                OD_LOG("(! reply.write(*replyMechanism))"); //####
#if defined(MpM_StallOnSendProblem)
                Common::Stall();
#endif // defined(MpM_StallOnSendProblem)
            }
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // MatchRequestHandler::processRequest

#if defined(__APPLE__)
# pragma mark Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
