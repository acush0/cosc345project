#include <string>
#include "eventSkeleton.h"
#pragma once

using namespace std;

class Tutorial : public eventSkeleton {
public:

    Tutorial(string paperCode, int day, int week, int startTime, int endTime, string location)
        : eventSkeleton(EventType::TUTORIAL, paperCode, day, week, startTime, endTime, location) {}

};
