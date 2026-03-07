// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type.
// ============================================================
#include <map>
// #include <Arduino.h>
// #include "states.h"
// #include "network.h"
// #include "config.h"
// #include "fsm.h"
// #include "actuators.h"
using std::map;

map<int, int> GCSCommandMap = { {}, {}, {}, {}, {}, {}, {}, {}  };

// 0x