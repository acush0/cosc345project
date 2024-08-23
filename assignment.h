#include <string>
#include "eventSkeleton.h"
#pragma once

using namespace std;

class Assignment : public eventSkeleton {
public:

    Assignment(string paperCode, int day, int week, int startTime, int endTime, string location)
        : eventSkeleton(EventType::ASSIGNMENT, paperCode, day, week, startTime, endTime, location) {}

};
