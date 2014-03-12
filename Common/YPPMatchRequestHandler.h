//
//  YPPMatchRequestHandler.h
//  YarpPlusPlus
//
//  Created by Norman Jaffe on 2014-03-10.
//  Copyright (c) 2014 OpenDragon. All rights reserved.
//

#if (! defined(YPPMATCHREQUESTHANDLER_H_))
# define YPPMATCHREQUESTHANDLER_H_ /* */

# include "YPPRequestHandler.h"
# include "YPPBaseMatcher.h"
# include "YPPServiceResponse.h"

namespace YarpPlusPlus
{
    using namespace YarpPlusPlusParser;
    
    class RegistryService;
    
    /*! @brief The standard 'match' request handler.
     
     The input is in the form of a pattern to be matched and the output is either 'OK', followed by a list of matching
     service ports, which indicates success, or 'FAILED' followed with a description of the reason for failure.
     Note that it is possible to have a successful request with no matching service ports.
     
     The matching pattern consists of a sequence of AND clauses, separated with commas.
     
     If a service matches any of the AND clauses, it will appear in the output of the pattern. Each AND clause is a
     sequence of field/value pairs, separated by ampersands.
     
     If a service matches all of the field/value pairs in the AND clause, it will be in the output of the AND clause.
     Field/value pairs consist of a field name followed by either a single value or a list of values, separated by
     either white space or a colon character. If a list of values is used, it must be surrounded by round brackets and,
     in this case, the white space or colon character between the field name and the list of values are optional.
     
     If the value in the pair is a single value, a service is in the output of the field/value pair if the
     corresponding field in the service matches the specified value. If value in the pair is a list, as service is in
     the output of the field/value pair if the corresponding field in the service matches at least one of the values in
     the list.
     
     A value consists of a sequence of non-blank, printable characters, or a sequence of printable characters surrounded
     by matching quote characters - either single quote or double quote. Note that a single quote character may appear
     within double quotes and vice versa. Three special characters are also used - an asterisk indicates a match for
     one or more characters, a question mark indicates a match for any character and a backslash is used to change the
     meaning of the next character in the value. The backslash provides an 'escape' mechanism so that quote characters,
     asterisks, question marks and backslashes may appear within the value as literal characters rather than being
     interpreted as special characters.
     
     Note that matching is case-sensitive. */
    class MatchRequestHandler : public RequestHandler
    {
    public:
        
        /*! @brief The constructor.
         @param service The service that has registered this request.
         @param validator The field validator to use. */
        MatchRequestHandler(RegistryService &  service,
                            FieldNameValidator validator = NULL);
        
        /*! @brief The destructor. */
        virtual ~MatchRequestHandler(void);
        
        /*! @brief Fill in a description dictionary for the request.
         @param info The dictionary to be filled in. */
        virtual void fillInDescription(yarp::os::Property & info);
        
        /*! @brief Process a request.
         @param restOfInput The arguments to the operation.
         @param replyMechanism non-@c NULL if a reply is expected and @c NULL otherwise. */
        virtual bool operator() (const yarp::os::Bottle &     restOfInput,
                                 yarp::os::ConnectionWriter * replyMechanism);
        
    protected:
        
    private:
        
        /*! @brief The class that this class is derived from. */
        typedef RequestHandler inherited;
        
        /*! @brief Copy constructor.
         
         Note - not implemented and private, to prevent unexpected copying.
         @param other Another object to construct from. */
        MatchRequestHandler(const MatchRequestHandler & other);
        
        /*! @brief Assignment operator.
         
         Note - not implemented and private, to prevent unexpected copying.
         @param other Another object to construct from. */
        MatchRequestHandler & operator=(const MatchRequestHandler & other);
        
        /*! @brief The service that will handle the registration operation. */
        RegistryService &  _service;
        
        /*! @brief The field name validator to be used. */
        FieldNameValidator _validator;
        
    }; // MatchRequestHandler
    
} // YarpPlusPlus

#endif // ! defined(YPPMATCHREQUESTHANDLER_H_)
