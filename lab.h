#include <string>
#include "eventSkeleton.h"
#pragma once

using namespace std;

class Lab : public eventSkeleton {
public:

    Lab(string paperCode, int day, int week, int startTime, int endTime, string location)
        : eventSkeleton(EventType::LAB, paperCode, day, week, startTime, endTime, location) {}

};
