//
//  YPPBaseService.cpp
//  YarpPlusPlus
//
//  Created by Norman Jaffe on 2014-02-06.
//  Copyright (c) 2014 OpenDragon. All rights reserved.
//

#include "YPPBaseService.h"
#define ENABLE_OD_SYSLOG /* */
#include "ODSyslog.h"
#include "YPPException.h"
#include "YPPBaseServiceInputHandler.h"
#include "YPPBaseServiceInputHandlerCreator.h"
#include "YPPRequests.h"
#include <yarp/os/Property.h>
#include <string>

#pragma mark Private structures and constants

#pragma mark Local functions

static bool standardListHandler(YarpPlusPlus::BaseService *   service,
                                const yarp::os::ConstString & request,
                                const yarp::os::Bottle &      restOfInput,
                                yarp::os::ConnectionWriter *  replyMechanism)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_P1("service = ", service);//####
    OD_SYSLOG_S2("request = ", request.c_str(), "restOfInput = ", restOfInput.toString().c_str());//####
    bool result = true;
    
    if (replyMechanism)
    {
        yarp::os::Bottle reply;
        
        service->fillInListReply(reply);
        reply.write(*replyMechanism);
    }
    OD_SYSLOG_EXIT_B(result);//####
    return result;
} // standardListHandler

#pragma mark Class methods

#pragma mark Constructors and destructors

YarpPlusPlus::BaseService::BaseService(const bool                    useMultipleHandlers,
                                       const yarp::os::ConstString & serviceEndpointName,
                                       const yarp::os::ConstString & serviceHostName,
                                       const yarp::os::ConstString & servicePortNumber) :
        _endpoint(NULL), _handler(NULL), _handlerCreator(NULL), _requestHandlers(), _defaultHandler(NULL),
        _started(false), _useMultipleHandlers(useMultipleHandlers)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_S3("serviceEndpointName = ", serviceEndpointName.c_str(), "serviceHostName = ",//####
                 serviceHostName.c_str(), "servicePortNumber = ", servicePortNumber.c_str());//####
    _endpoint = new Endpoint(serviceEndpointName, serviceHostName, servicePortNumber);
    setUpStandardHandlers();
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::BaseService

YarpPlusPlus::BaseService::BaseService(const bool useMultipleHandlers,
                                       const int  argc,
                                       char **    argv) :
        _endpoint(NULL), _handler(NULL), _handlerCreator(NULL), _requestHandlers(), _defaultHandler(NULL),
        _started(false), _useMultipleHandlers(useMultipleHandlers)
{
    OD_SYSLOG_ENTER();//####
    switch (argc)
    {
            // Argument order for tests = endpoint name [, IP address / name [, port [, carrier]]]
        case 1:
            _endpoint = new YarpPlusPlus::Endpoint(*argv);
            break;
            
        case 2:
            _endpoint = new YarpPlusPlus::Endpoint(*argv, argv[1]);
            break;
            
        case 3:
            _endpoint = new YarpPlusPlus::Endpoint(*argv, argv[1], argv[2]);
            break;
            
        default:
            OD_SYSLOG_EXIT_THROW_S("Invalid parameters for service endpoint");//####
            throw new YarpPlusPlus::Exception("Invalid parameters for service endpoint");
            
    }
    setUpStandardHandlers();
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::BaseService

YarpPlusPlus::BaseService::~BaseService(void)
{
    OD_SYSLOG_ENTER();//####
    delete _endpoint;
    delete _handler;
    delete _handlerCreator;
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::~BaseService

#pragma mark Actions

void YarpPlusPlus::BaseService::fillInListReply(yarp::os::Bottle & reply)
{
    OD_SYSLOG_ENTER();//####
    yarp::os::Property & aDict = reply.addDict();
    
    aDict.put(YPP_REQREP_DICT_NAME_KEY, YPP_LIST_REQUEST);
    aDict.put(YPP_REQREP_DICT_OUTPUT_KEY, YPP_REQREP_LIST_START YPP_REQREP_DICT_START YPP_REQREP_DICT_END
              YPP_REQREP_1_OR_MORE YPP_REQREP_LIST_END);
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::fillInListReply

YarpPlusPlus::BaseService::HandlerFunction YarpPlusPlus::BaseService::lookupRequestHandler(const yarp::os::ConstString & request)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_S1("request = ", request.c_str());//####
    HandlerMap::const_iterator match(_requestHandlers.find(std::string(request)));
    HandlerFunction            result;
    
    if (_requestHandlers.end() == match)
    {
        OD_SYSLOG("(_requestHandlers.end() == match)");//####
        result = _defaultHandler;
    }
    else
    {
        OD_SYSLOG("! (_requestHandlers.end() == match)");//####
        result = match->second;
    }
    OD_SYSLOG_EXIT();//####
    return result;
} // YarpPlusPlus::BaseService::lookupRequestHandler

bool YarpPlusPlus::BaseService::processRequest(const yarp::os::ConstString & request,
                                               const yarp::os::Bottle &      restOfInput,
                                               yarp::os::ConnectionWriter *  replyMechanism)
{
    OD_SYSLOG_ENTER();//####
    bool            result;
    HandlerFunction handler = lookupRequestHandler(request);
    
    if (handler)
    {
        OD_SYSLOG("(handler)");//####
        result = handler(this, request, restOfInput, replyMechanism);
    }
    else
    {
        OD_SYSLOG("! (handler)");//####
        if (replyMechanism)
        {
            yarp::os::Bottle errorMessage("unrecognized request");
            
            errorMessage.write(*replyMechanism);
        }
        result = false;
    }
    OD_SYSLOG_EXIT_B(result);//####
    return result;
} // YarpPlusPlus::BaseService::processRequest

void YarpPlusPlus::BaseService::registerRequestHandler(const yarp::os::ConstString & request,
                                                       HandlerFunction               handler)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_S1("request = ", request.c_str());//####
    _requestHandlers.insert(HandlerMapValue(std::string(request), handler));
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::registerRequestHandler

void YarpPlusPlus::BaseService::setDefaultRequestHandler(HandlerFunction handler)
{
    OD_SYSLOG_ENTER();//####
    _defaultHandler = handler;
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::setDefaultRequestHandler

void YarpPlusPlus::BaseService::setUpStandardHandlers(void)
{
    OD_SYSLOG_ENTER();//####
    registerRequestHandler(YPP_LIST_REQUEST, standardListHandler);
    OD_SYSLOG_EXIT();//####
} // YarpPlusPlus::BaseService::setUpStandardHandlers

bool YarpPlusPlus::BaseService::start(void)
{
    OD_SYSLOG_ENTER();//####
    if (! _started)
    {
        if (_useMultipleHandlers)
        {
            _handlerCreator = new BaseServiceInputHandlerCreator(*this);
            if (_handlerCreator)
            {
                YarpPlusPlus::Endpoint & ourEndpoint = getEndpoint();
                
                if (ourEndpoint.setInputHandlerCreator(*_handlerCreator) && ourEndpoint.open())
                {
                    _started = true;
                }
                else
                {
                    delete _handlerCreator;
                    _handlerCreator = NULL;
                }
            }
        }
        else
        {
            _handler = new BaseServiceInputHandler(*this);
            if (_handler)
            {
                YarpPlusPlus::Endpoint & ourEndpoint = getEndpoint();
                
                if (ourEndpoint.setInputHandler(*_handler) && ourEndpoint.open())
                {
                    _started = true;
                }
                else
                {
                    delete _handler;
                    _handler = NULL;
                }
            }
        }
    }
    OD_SYSLOG_EXIT_B(_started);//####
    return _started;
} // YarpPlusPlus::BaseService::start

bool YarpPlusPlus::BaseService::stop(void)
{
    OD_SYSLOG_ENTER();//####
    _started = false;
    OD_SYSLOG_EXIT_B(! _started);//####
    return (! _started);
} // YarpPlusPlus::BaseService::stop

#pragma mark Accessors

#pragma mark Global functions
