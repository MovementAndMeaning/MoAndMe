//--------------------------------------------------------------------------------------------------
//
//  File:       m+mRegistryCheckThread.h
//
//  Project:    m+m
//
//  Contains:   The class declaration for a registry check thread for m+m.
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
//  Created:    2014-06-18
//
//--------------------------------------------------------------------------------------------------

#if (! defined(MpMRegistryCheckThread_H_))
# define MpMRegistryCheckThread_H_ /* Header guard */

# include <m+m/m+mBaseThread.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a registry check thread for m+m. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace MplusM
{
    namespace Registry
    {
        class RegistryService;

        /*! @brief A convenience class to schedule registry checks. */
        class RegistryCheckThread : public Common::BaseThread
        {
        public :

        protected :

        private :

            /*! @brief The class that this class is derived from. */
            typedef BaseThread inherited;

        public :

            /*! @brief The constructor.
             @param service The service that has owns this thread. */
            explicit
            RegistryCheckThread(RegistryService & service);

            /*! @brief The destructor. */
            virtual
            ~RegistryCheckThread(void);

        protected :

        private :

            /*! @brief The copy constructor.
             @param other The object to be copied. */
            RegistryCheckThread(const RegistryCheckThread & other);
            
            /*! @brief The assignment operator.
             @param other The object to be copied.
             @returns The updated object. */
            RegistryCheckThread &
            operator =(const RegistryCheckThread & other);

            /*! @brief The thread main body. */
            virtual void
            run(void);
            
            /*! @brief The thread initialization method.
             @returns @c true if the thread is ready to run. */
            virtual bool
            threadInit(void);
            
            /*! @brief The thread termination method. */
            virtual void
            threadRelease(void);
            
        public :

        protected :

        private :

            /*! @brief The service that owns this thread. */
            RegistryService & _service;

            /*! @brief The time at which the thread will next check the %Registry Service. */
            double _checkTime;

        }; // RegistryCheckThread

    } // Registry

} // MplusM

#endif // ! defined(MpMRegistryCheckThread_H_)
