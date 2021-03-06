//--------------------------------------------------------------------------------------------------
//
//  File:       m+mRequestCounterContext.hpp
//
//  Project:    m+m
//
//  Contains:   The class declaration for a context used with the Request Counter service.
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
//  Created:    2014-04-04
//
//--------------------------------------------------------------------------------------------------

# if (! defined(MpMRequestCounterContext_HPP_))
# define MpMRequestCounterContext_HPP_ /* Header guard */

# include <m+m/m+mBaseContext.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a context used with the Request Counter service. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace MplusM
{
    namespace RequestCounter
    {
        /*! @brief A convenience class to provide context objects for the Request Counter
         service. */
        class RequestCounterContext : public Common::BaseContext
        {
        public :

        protected :

        private :

            /*! @brief The class that this class is derived from. */
            typedef BaseContext inherited;

        public :

            /*! @brief The constructor. */
            RequestCounterContext(void);

            /*! @brief The destructor. */
            virtual
            ~RequestCounterContext(void);

            /*! @brief An accessor for the number of requests since the most recent reset. */
            inline long &
            counter(void)
            {
                return _counter;
            } // counter

            /*! @brief An accessor for the time of the most recent reset. */
            inline double &
            lastReset(void)
            {
                return _lastReset;
            } // lastReset

        protected :

        private :

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            RequestCounterContext(const RequestCounterContext & other);

            /*! @brief The assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            RequestCounterContext &
            operator =(const RequestCounterContext & other);

        public :

        protected :

        private :

            /*! @brief The number of requests since the most recent reset. */
            long _counter;

            /*! @brief The time of the last reset. */
            double _lastReset;

        }; // RequestCounterContext

    } // RequestCounter

} // MplusM

# endif // ! defined(MpMRequestCounterContext_HPP_)
