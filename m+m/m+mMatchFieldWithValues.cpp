//--------------------------------------------------------------------------------------------------
//
//  File:       m+m/m+mMatchFieldWithValues.cpp
//
//  Project:    m+m
//
//  Contains:   The class definition for a pattern matcher for field/value pairs.
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
//  Created:    2014-03-07
//
//--------------------------------------------------------------------------------------------------

#include "m+mMatchFieldWithValues.hpp"

#include <m+m/m+mBaseNameValidator.hpp>
#include <m+m/m+mMatchFieldName.hpp>
#include <m+m/m+mMatchValue.hpp>
#include <m+m/m+mMatchValueList.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a pattern matcher for field/value pairs. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace MplusM;
using namespace MplusM::Common;
using namespace MplusM::Parser;

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

MatchFieldWithValues *
MatchFieldWithValues::CreateMatcher(const YarpString &  inString,
                                    const size_t        inLength,
                                    const size_t        startPos,
                                    size_t &            endPos,
                                    BaseNameValidator * validator)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    ODL_I2("inLength = ", inLength, "startPos = ", startPos); //####
    MatchFieldWithValues * result = NULL;

    try
    {
        size_t           workPos = startPos;
        MatchFieldName * fieldName = MatchFieldName::CreateMatcher(inString, inLength, startPos,
                                                                   workPos, validator);

        if (fieldName)
        {
            workPos = SkipWhitespace(inString, inLength, workPos);
            if (workPos < inLength)
            {
                size_t nextPos;

                if (MatchValueList::ListInitiatorCharacter() == inString[workPos])
                {
                    MatchValueList * asList = MatchValueList::CreateMatcher(inString, inLength,
                                                                            workPos, nextPos);

                    if (asList)
                    {
                        result = new MatchFieldWithValues(validator, fieldName, asList);
                    }
                    else
                    {
                        ODL_LOG("! (asList)"); //####
                    }
                }
                else
                {
                    MatchValue * asSingle = MatchValue::CreateMatcher(inString, inLength, workPos,
                                                                      nextPos);

                    if (asSingle)
                    {
                        result = new MatchFieldWithValues(validator, fieldName, asSingle);
                    }
                    else
                    {
                        ODL_LOG("! (asSingle)"); //####
                    }
                }
                if (result)
                {
                    endPos = nextPos;
                }
                else
                {
                    delete fieldName;
                }
            }
            else
            {
                ODL_LOG("! (workPos < inLength)"); //####
                delete fieldName;
            }
        }
        else
        {
            ODL_LOG("! (fieldName)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(result); //####
    return result;
} // MatchFieldWithValues::CreateMatcher

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

MatchFieldWithValues::MatchFieldWithValues(BaseNameValidator * validator,
                                           MatchFieldName *    fieldName,
                                           MatchValue *        asSingle) :
    inherited(), _validator(validator), _fieldName(fieldName), _singleValue(asSingle),
    _values(NULL)
{
    ODL_ENTER(); //####
    ODL_P3("validator = ", validator, "fieldName = ", fieldName, "asSingle = ", asSingle); //####
    ODL_EXIT_P(this); //####
} // MatchFieldWithValues::MatchFieldWithValues

MatchFieldWithValues::MatchFieldWithValues(BaseNameValidator * validator,
                                           MatchFieldName *    fieldName,
                                           MatchValueList *    asList) :
    inherited(), _validator(validator), _fieldName(fieldName), _singleValue(NULL),
    _values(asList)
{
    ODL_ENTER(); //####
    ODL_P3("validator = ", validator, "fieldName = ", fieldName, "asList = ", asList); //####
    ODL_EXIT_P(this); //####
} // MatchFieldWithValues::MatchFieldWithValues

MatchFieldWithValues::~MatchFieldWithValues(void)
{
    ODL_OBJENTER(); //####
    delete _fieldName;
    delete _singleValue;
    delete _values;
    ODL_OBJEXIT(); //####
} // MatchFieldWithValues::~MatchFieldWithValues

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

YarpString
MatchFieldWithValues::asSQLString(void)
const
{
    ODL_OBJENTER(); //####
    YarpString converted;

    try
    {
        bool         negated = _fieldName->isNegated();
        YarpString   field(_fieldName->asString());
        const char * prefixString = NULL;
        const char * suffixString = NULL;
        const char * trueName;

        if (_validator)
        {
            trueName = _validator->getPrefixAndSuffix(field.c_str(), prefixString, suffixString);
        }
        else
        {
            trueName = field.c_str();
        }
        ODL_S1("trueName <- ", trueName); //####
        if (_singleValue)
        {
            if (prefixString)
            {
                converted += prefixString;
            }
            converted += trueName;
            if (_singleValue->hasWildcardCharacters())
            {
                converted += (negated ? " NOT LIKE " : " LIKE ");
            }
            else
            {
                converted += (negated ? " != " : " = ");
            }
            converted += _singleValue->asSQLString();
            if (suffixString)
            {
                converted += suffixString;
            }
        }
        else if (_values)
        {
            if (prefixString)
            {
                converted += prefixString;
            }
            converted += _values->asSQLString(trueName, negated);
            if (suffixString)
            {
                converted += suffixString;
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_OBJEXIT_S(converted.c_str()); //####
    return converted;
} // MatchFieldWithValues::asSQLString

YarpString
MatchFieldWithValues::asString(void)
const
{
    YarpString result;

    try
    {
        result += _fieldName->asString();
        result += (_fieldName->isNegated() ? "! " : ": ");
        if (_singleValue)
        {
            result += _singleValue->asString();
        }
        else if (_values)
        {
            result += _values->asString();
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    return result;
} // MatchFieldWithValues::asString

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
