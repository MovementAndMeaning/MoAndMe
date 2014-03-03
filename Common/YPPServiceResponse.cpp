//
//  YPPServiceResponse.cpp
//  YarpPlusPlus
//
//  Created by Norman Jaffe on 2014-02-06.
//  Copyright (c) 2014 OpenDragon. All rights reserved.
//

#include "YPPServiceResponse.h"
//#define ENABLE_OD_SYSLOG /* */
#include "ODSyslog.h"

using namespace YarpPlusPlus;

#pragma mark Private structures and constants

#pragma mark Local functions

#pragma mark Class methods

#pragma mark Constructors and destructors

ServiceResponse::ServiceResponse(const yarp::os::Bottle & values) :
        _values(values)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_LL1("input size = ", values.size());//####
    OD_SYSLOG_EXIT_P(this);//####
} // ServiceResponse::ServiceResponse

ServiceResponse::~ServiceResponse(void)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_EXIT();//####
} // ServiceResponse::~ServiceResponse

ServiceResponse & ServiceResponse::operator=(const yarp::os::Bottle & values)
{
    OD_SYSLOG_ENTER();//####
    OD_SYSLOG_LL1("input size = ", values.size());//####
    _values = values;
    OD_SYSLOG_EXIT_P(this);//####
    return *this;
} // ServiceResponse::operator=

#pragma mark Actions

/*! @brief Return a printable version of the response.
 @returns A printable version of the response. */
yarp::os::ConstString ServiceResponse::asString(void)
const
{
    OD_SYSLOG_ENTER();//####
    yarp::os::ConstString result = _values.toString();
    
    OD_SYSLOG_EXIT_S(result.c_str());//####
    return result;
} // ServiceResponse::asString

yarp::os::Value ServiceResponse::element(const int index)
const
{
    OD_SYSLOG_ENTER();//####
    yarp::os::Value result;
    
    if ((index >= 0) && (index < _values.size()))
    {
        result = _values.get(index);
    }
    OD_SYSLOG_EXIT_S(result.toString().c_str());//####
    return result;
} // ServiceResponse::element

#pragma mark Accessors

#pragma mark Global functions
