/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
// This file is generated by Simplicity Studio.  Please do not edit manually.

// This is a set of generated functions that parse the
// the incomming message, and call appropriate command handler.

#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/serial-interface.h"
#include "stack/include/ember-types.h"
#include "stack/include/error.h"
#else
// Includes needed for ember related functions for the EM250
// #include "stack/include/ember.h"
#endif // EZSP_HOST

#include <stdint.h>

#include "af-structs.h"
#include "call-command-handler.h"
#include "callback.h"
#include "command-id.h"
#include "util.h"

static EmberAfStatus status(bool wasHandled, bool clusterExists, bool mfgSpecific)
{
    if (wasHandled)
    {
        return EMBER_ZCL_STATUS_SUCCESS;
    }
    else if (mfgSpecific)
    {
        return EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND;
    }
    else if (clusterExists)
    {
        return EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND;
    }
    else
    {
        return EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER;
    }
}

// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse(EmberAfClusterCommand * cmd)
{
    EmberAfStatus result = status(false, false, cmd->mfgSpecific);
    if (cmd->direction == (uint8_t) ZCL_DIRECTION_SERVER_TO_CLIENT &&
        emberAfContainsClientWithMfgCode(cmd->apsFrame->destinationEndpoint, cmd->apsFrame->clusterId, cmd->mfgCode))
    {
        switch (cmd->apsFrame->clusterId)
        {
        case ZCL_BASIC_CLUSTER_ID:
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
            result = status(false, true, cmd->mfgSpecific);
            break;
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
        }
    }
    else if (cmd->direction == (uint8_t) ZCL_DIRECTION_CLIENT_TO_SERVER &&
             emberAfContainsServerWithMfgCode(cmd->apsFrame->destinationEndpoint, cmd->apsFrame->clusterId, cmd->mfgCode))
    {
        switch (cmd->apsFrame->clusterId)
        {
        case ZCL_BASIC_CLUSTER_ID:
            result = emberAfBasicClusterServerCommandParse(cmd);
            break;
        case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
            result = status(false, true, cmd->mfgSpecific);
            break;
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
        }
    }
    return result;
}

// Cluster: Basic, server
EmberAfStatus emberAfBasicClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;
    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID: {
            // Command is fixed length: 0
            wasHandled = emberAfBasicClusterResetToFactoryDefaultsCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
