//--------------------------------------------------------------------------------------
//
//  File:       M+MUtilities.h
//
//  Project:    M+M
//
//  Contains:   The function and variable declarations for utilities for M+M clients and
//              services.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2014 by HPlus Technologies Ltd. and Simon Fraser University.
//
//              All rights reserved. Redistribution and use in source and binary forms,
//              with or without modification, are permitted provided that the following
//              conditions are met:
//                * Redistributions of source code must retain the above copyright
//                  notice, this list of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright
//                  notice, this list of conditions and the following disclaimer in the
//                  documentation and/or other materials provided with the
//                  distribution.
//                * Neither the name of the copyright holders nor the names of its
//                  contributors may be used to endorse or promote products derived
//                  from this software without specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//              "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//              LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//              PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//              OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//              SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//              LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//              DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//              THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//              (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//              OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Created:    2014-05-16
//
//--------------------------------------------------------------------------------------

#if (! defined(MpMUtilities_H_))
/*! @brief Header guard. */
# define MpMUtilities_H_ /* */

# include "M+MCommon.h"

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 
 @brief The function and variable declarations for utilities for M+M clients and services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace MplusM
{
    namespace Utilities
    {
        /*! @brief Which combination of input and output to use. */
        enum InputOutputFlag
        {
            /*! @brief Neither input nor output. */
            kInputAndOutputNone   = 0x0,
            /*! @brief Input. */
            kInputAndOutputInput  = 0x1,
            /*! @brief Output. */
            kInputAndOutputOutput = 0x2,
            /*! @brief Both input and output. */
            kInputAndOutputBoth   = 0x3
        }; // InputOutputFlag
        
        /*! @brief The attributes of a port. */
        struct PortDescriptor
        {
            /*! @brief The registered name of the port. */
            yarp::os::ConstString _portName;
            /*! @brief The IP address for the port. */
            yarp::os::ConstString _portIpAddress;
            /*! @brief The IP port number for the port. */
            yarp::os::ConstString _portPortNumber;
        }; // PortDescriptor
        
        /*! @brief The attributes of a service. */
        struct ServiceDescriptor
        {
            /*! @brief The standard name for the service. */
            yarp::os::ConstString _canonicalName;
            /*! @brief The description of the service. */
            yarp::os::ConstString _description;
            /*! @brief The name of the input channel for the service. */
            yarp::os::ConstString _path;
            /*! @brief The set of secondary channels for the service. */
            Common::StringVector  _channels;
        }; // ServiceDescriptor
        
        /*! @brief A set of port descriptions. */
        typedef std::vector<PortDescriptor> PortVector;
        
        /*! @brief Check if the Registry Service is active.
         @param ports The set of detected ports.
         @returns @c true if the Registry Service port is present and @c false otherwise. */
        bool CheckForRegistryService(const PortVector & ports);
        
        /*! @brief Collect the input and output connections for a port.
         @param portName The port to be inspected.
         @param inputs The collected inputs for the port.
         @param outputs The collected outputs for the port.
         @param which A flag to specify what is to be gathered.
         @param quiet @c true if status output is to be suppressed and @c false otherwise. */
        void GatherPortConnections(const yarp::os::ConstString & portName,
                                   Common::StringVector &        inputs,
                                   Common::StringVector &        outputs,
                                   const InputOutputFlag         which,
                                   const bool                    quiet = false);
        
        /*! @brief Get the set of detected ports.
         @param ports The set of detected ports. */
        void GetDetectedPortList(PortVector & ports);

        /*! @brief Retrieve the details for a service.
         @param serviceChannelName The channel for the service.
         @param descriptor The details for a service.
         @returns @c true if the service returned the desired information and @c false otherwise. */
        bool GetNameAndDescriptionForService(const yarp::os::ConstString & serviceChannelName,
                                             ServiceDescriptor &           descriptor);

        /*! @brief Retrieve the set of known services.
         @param services The set of registered services.
         @param quiet @c true if status output is to be suppressed and @c false otherwise. */
        void GetServiceNames(Common::StringVector & services,
                             const bool             quiet = false);
        
    } // Utilities
    
} // MplusM

#endif // ! defined(MpMUtilities_H_)
