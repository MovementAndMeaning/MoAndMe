//--------------------------------------------------------------------------------------------------
//
//  File:       M+MRunningSumControlInputHandler.h
//
//  Project:    M+M
//
//  Contains:   The class declaration for the custom control channel input handler used by the
//              Running Sum adapter.
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
//  Created:    2014-03-24
//
//--------------------------------------------------------------------------------------------------

#if (! defined(MpMRunningSumControlInputHandler_H_))
# define MpMRunningSumControlInputHandler_H_ /* Header guard */

# include <mpm/M+MBaseInputHandler.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the custom control channel input handler used by the Running Sum
 adapter. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace MplusM
{
    namespace Example
    {
        class RunningSumAdapterData;
        
        /*! @brief A handler for partially-structured input data.
         
         The data is expected to be in the form of a sequence of commands. */
        class RunningSumControlInputHandler : public Common::BaseInputHandler
        {
        public :
            
            /*! @brief The constructor.
             @param shared The data shared between the input handlers and the main thread. */
            RunningSumControlInputHandler(RunningSumAdapterData & shared);
            
            /*! @brief The destructor. */
            virtual ~RunningSumControlInputHandler(void);
            
            /*! @brief Process partially-structured input data.
             @param input The partially-structured input data.
             @param senderChannel The name of the channel used to send the input data.
             @param replyMechanism @c NULL if no reply is expected and non-@c NULL otherwise.
             @param numBytes The number of bytes available on the connection.
             @returns @c true if the input was correctly structured and successfully processed. */
            virtual bool handleInput(const yarp::os::Bottle &      input,
                                     const yarp::os::ConstString & senderChannel,
                                     yarp::os::ConnectionWriter *  replyMechanism,
                                     const size_t                  numBytes);
            
        protected :
            
        private :
            
            COPY_AND_ASSIGNMENT_(RunningSumControlInputHandler);
            
        public :
        
        protected :
        
        private :
            
            /*! @brief The class that this class is derived from. */
            typedef BaseInputHandler inherited;
            
            /*! @brief The shared data that describes the connection to the service that we are
             using. */
            RunningSumAdapterData & _shared;
            
        }; // RunningSumControlInputHandler
        
    } // Example
    
} // MplusM

#endif // ! defined(MpMRunningSumControlInputHandler_H_)
