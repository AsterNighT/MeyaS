// MeyaS for Meya Socket or Meya·S·Ephemeral, both of which are good names. (Really?)
// Author: AsterNighT https://github.com/AsterNighT
// Github: https://github.com/AsterNighT/MeyaS
// Wish I would not write trash code again in this project.
//
// The only file should be included to use the lib

//TODO: Use macro to differ ascii mode from UTF16 mod except rather than has two version of send and recv
#pragma once
#include "common.h"
#include "Server.h"
#include "Client.h"

namespace MeyaS {
    // Initialize Winsock
    bool initialize(WORD version = MAKEWORD(2, 2));

    // Clean up for winsock
    bool cleanUp();
}
