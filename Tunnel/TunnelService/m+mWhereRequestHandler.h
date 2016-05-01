//--------------------------------------------------------------------------------------------------
//
//  File:       m+mWhereRequestHandler.h
//
//  Project:    m+m
//
//  Contains:   The class declaration for the request handler for a 'where' request.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2015 by H Plus Technologies Ltd. and Simon Fraser University.
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
//  Created:    2015-02-11
//
//--------------------------------------------------------------------------------------------------

#if (! defined(MpMWhereRequestHandler_H_))
# define MpMWhereRequestHandler_H_ /* Header guard */

# include <m+m/m+mBaseRequestHandler.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the request handler for a 'where' request. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace MplusM
{
    namespace Tunnel
    {
        class TunnelService;

        /*! @brief The 'where' request handler for the %Tunnel service.

         There is no input or output for the request. */
        class WhereRequestHandler : public Common::BaseRequestHandler
        {
        public :

        protected :

        private :

            /*! @brief The class that this class is derived from. */
            typedef BaseRequestHandler inherited;

        public :

            /*! @brief The constructor.
             @param service The service that has registered this request. */
            explicit
            WhereRequestHandler(TunnelService & service);

            /*! @brief The destructor. */
            virtual
            ~WhereRequestHandler(void);

        protected :

        private :

            /*! @brief The copy constructor.
             @param other The object to be copied. */
            WhereRequestHandler(const WhereRequestHandler & other);
            
            /*! @brief Fill in a description dictionary for the request.
             @param request The actual request name.
             @param info The dictionary to be filled in. */
            virtual void
            fillInDescription(const YarpString &   request,
                              yarp::os::Property & info);
            
            /*! @brief The assignment operator.
             @param other The object to be copied.
             @returns The updated object. */
            WhereRequestHandler &
            operator =(const WhereRequestHandler & other);
            
            /*! @brief Process a request.
             @param request The actual request name.
             @param restOfInput The arguments to the operation.
             @param senderChannel The name of the channel used to send the input data.
             @param replyMechanism non-@c NULL if a reply is expected and @c NULL otherwise. */
            virtual bool
            processRequest(const YarpString &           request,
                           const yarp::os::Bottle &     restOfInput,
                           const YarpString &           senderChannel,
                           yarp::os::ConnectionWriter * replyMechanism);

        public :

        protected :

        private :

        }; // WhereRequestHandler

    } // Tunnel

} // MplusM

#endif // ! defined(MpMWhereRequestHandler_H_)
