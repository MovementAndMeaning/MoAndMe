//--------------------------------------------------------------------------------------------------
//
//  File:       m+mOpenStageInputService.hpp
//
//  Project:    m+m
//
//  Contains:   The class declaration for the Organic Motion OpenStage input service.
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
//  Created:    2015-06-25
//
//--------------------------------------------------------------------------------------------------

#if (! defined(MpMOpenStageInputService_HPP_))
# define MpMOpenStageInputService_HPP_ /* Header guard */

# include <m+m/m+mBaseInputService.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the Organic Motion %OpenStage input service. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The base channel name to use for the service if not provided. */
# define DEFAULT_OPENSTAGEINPUT_SERVICE_NAME_ BUILD_NAME_(MpM_SERVICE_BASE_NAME_, \
                                                          BUILD_NAME_("input", "openstageos"))

/*! @brief The description of the service. */
# define OPENSTAGEINPUT_SERVICE_DESCRIPTION_ T_("OpenStage input service")

namespace MplusM
{
    namespace OpenStage
    {
        class OpenStageInputThread;

        /*! @brief The Organic Motion %OpenStage input service. */
        class OpenStageInputService : public Common::BaseInputService
        {
        public :

        protected :

        private :

            /*! @brief The class that this class is derived from. */
            typedef BaseInputService inherited;

        public :

            /*! @brief The constructor.
             @param[in] argumentList Descriptions of the arguments to the executable.
             @param[in] launchPath The command-line name used to launch the service.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The arguments passed to the executable used to launch the service.
             @param[in] tag The modifier for the service name and port names.
             @param[in] serviceEndpointName The YARP name to be assigned to the new service.
             @param[in] servicePortNumber The port being used by the service. */
            OpenStageInputService(const Utilities::DescriptorVector & argumentList,
                                  const YarpString &                  launchPath,
                                  const int                           argc,
                                  char * *                            argv,
                                  const YarpString &                  tag,
                                  const YarpString &                  serviceEndpointName,
                                  const YarpString &                  servicePortNumber = "");

            /*! @brief The destructor. */
            virtual
            ~OpenStageInputService(void);

            /*! @brief Configure the input/output streams.
             @param[in] details The configuration information for the input/output streams.
             @return @c true if the service was successfully configured and @c false otherwise. */
            virtual bool
            configure(const yarp::os::Bottle & details);

            /*! @brief Get the configuration of the input/output streams.
             @param[out] details The configuration information for the input/output streams.
             @return @c true if the configuration was successfully retrieved and @c false
             otherwise. */
            virtual bool
            getConfiguration(yarp::os::Bottle & details);

            /*! @brief Shut down the output streams.
             @return @c true if the channels were shut down and @c false otherwise. */
            virtual bool
            shutDownOutputStreams(void);

            /*! @brief Start the input / output streams. */
            virtual void
            startStreams(void);

            /*! @brief Stop the input / output streams. */
            virtual void
            stopStreams(void);

        protected :

        private :

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            OpenStageInputService(const OpenStageInputService & other);

            /*! @brief The assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            OpenStageInputService &
            operator =(const OpenStageInputService & other);

            /*! @brief Set up the descriptions that will be used to construct the input / output
             streams.
             @return @c true if the descriptions were set up and @c false otherwise. */
            virtual bool
            setUpStreamDescriptions(void);

        public :

        protected :

        private :

            /*! @brief The name of the Organic Motion %OpenStage device server. */
            YarpString _hostName;

            /*! @brief The port to connect to the Organic Motion %OpenStage device server. */
            int _hostPort;

            /*! @brief The output thread to use. */
            OpenStageInputThread * _eventThread;

        }; // OpenStageInputService

    } // OpenStage

} // MplusM

#endif // ! defined(MpMOpenStageInputService_HPP_)
