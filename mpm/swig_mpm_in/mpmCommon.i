%module mpm
%{
#include "M+MAdapterChannel.h"
#include "M+MAddressArgumentDescriptor.h"
#include "M+MBailOut.h"
#include "M+MBailOutThread.h"
#include "M+MBaseAdapterData.h"
#include "M+MBaseArgumentDescriptor.h"
#include "M+MBaseChannel.h"
#include "M+MBaseClient.h"
#include "M+MBaseContext.h"
#include "M+MBaseFilterService.h"
#include "M+MBaseInputHandler.h"
#include "M+MBaseInputHandlerCreator.h"
#include "M+MBaseInputOutputService.h"
#include "M+MBaseInputService.h"
#include "M+MBaseMatcher.h"
#include "M+MBaseNameValidator.h"
#include "M+MBaseOutputService.h"
#include "M+MBaseRequestHandler.h"
#include "M+MBaseService.h"
#include "M+MChannelArgumentDescriptor.h"
#include "M+MChannelStatusReporter.h"
#include "M+MClientChannel.h"
#include "M+MCommon.h"
#include "M+MDoubleArgumentDescriptor.h"
#include "M+MEndpoint.h"
#include "M+MException.h"
#include "M+MFilePathArgumentDescriptor.h"
#include "M+MGeneralChannel.h"
#include "M+MIntegerArgumentDescriptor.h"
#include "M+MMatchConstraint.h"
#include "M+MMatchExpression.h"
#include "M+MMatchFieldName.h"
#include "M+MMatchFieldWithValues.h"
#include "M+MMatchValue.h"
#include "M+MMatchValueList.h"
#include "M+MPortArgumentDescriptor.h"
#include "M+MRequestMap.h"
#include "M+MSendReceiveCounters.h"
#include "M+MServiceChannel.h"
#include "M+MServiceInputHandler.h"
#include "M+MServiceInputHandlerCreator.h"
#include "M+MServiceRequest.h"
#include "M+MServiceResponse.h"
#include "M+MStringArgumentDescriptor.h"
#include "M+MUtilities.h"
%}
