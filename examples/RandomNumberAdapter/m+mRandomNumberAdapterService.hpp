//--------------------------------------------------------------------------------------------------
//
//  File:       m+mRandomNumberAdapterService.hpp
//
//  Project:    m+m
//
//  Contains:   The class declaration for the Random Number adapter service.
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
//  Created:    2015-05-27
//
//--------------------------------------------------------------------------------------------------

#if (! defined(MpMRandomNumberAdapterService_HPP_))
# define MpMRandomNumberAdapterService_HPP_ /* Header guard */

# include <m+m/m+mBaseAdapterService.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the Random Number adapter service. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The base channel name to use for the service if not provided. */
# define DEFAULT_RANDOMNUMBERADAPTER_SERVICE_NAME_ BUILD_NAME_(MpM_ADAPTER_BASE_NAME_, \
                                                               BUILD_NAME_("examples", \
                                                                           "randomnumber"))

/*! @brief The description of the service. */
# define RANDOMNUMBERADAPTER_SERVICE_DESCRIPTION_ T_("Random Number adapter")

namespace MplusM
{
    namespace Example
    {
        class RandomNumberAdapterData;
        class RandomNumberInputHandler;

        /*! @brief The Random Number adapter service. */
        class RandomNumberAdapterService : public Common::BaseAdapterService
        {
        public :

        protected :

        private :

            /*! @brief The class that this class is derived from. */
            typedef BaseAdapterService inherited;

        public :

            /*! @brief The constructor.
             @param argumentList Descriptions of the arguments to the executable.
             @param launchPath The command-line name used to launch the service.
             @param argc The number of arguments in 'argv'.
             @param argv The arguments passed to the executable used to launch the service.
             @param tag The modifier for the service name and port names.
             @param serviceEndpointName The YARP name to be assigned to the new service.
             @param servicePortNumber The port being used by the service. */
            RandomNumberAdapterService(const Utilities::DescriptorVector & argumentList,
                                       const YarpString &                  launchPath,
                                       const int                           argc,
                                       char * *                            argv,
                                       const YarpString &                  tag,
                                       const YarpString &                  serviceEndpointName,
                                       const YarpString &                  servicePortNumber = "");

            /*! @brief The destructor. */
            virtual
            ~RandomNumberAdapterService(void);

            /*! @brief Turn off the send / receive metrics collecting. */
            virtual void
            disableMetrics(void);

            /*! @brief Turn on the send / receive metrics collecting. */
            virtual void
            enableMetrics(void);

            /*! @brief Set up the input handlers.
             @param sharedData The shared data for the input handlers. */
            void
            setUpInputHandlers(RandomNumberAdapterData & sharedData);

            /*! @brief Start the input / output streams. */
            virtual void
            startStreams(void);

            /*! @brief Stop the input / output streams. */
            virtual void
            stopStreams(void);

        protected :

        private :

            /*! @brief The copy constructor.
             @param other The object to be copied. */
            RandomNumberAdapterService(const RandomNumberAdapterService & other);

            /*! @brief The assignment operator.
             @param other The object to be copied.
             @returns The updated object. */
            RandomNumberAdapterService &
            operator =(const RandomNumberAdapterService & other);

            /*! @brief Set up the descriptions that will be used to construct the input / output
             streams.
             @returns @c true if the descriptions were set up and @c false otherwise. */
            virtual bool
            setUpStreamDescriptions(void);

        public :

        protected :

        private :

            /*! @brief The handler for input data. */
            RandomNumberInputHandler * _inHandler;

        }; // RandomNumberAdapterService

    } // Example

} // MplusM

#endif // ! defined(MpMRandomNumberAdapterService_HPP_)