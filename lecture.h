#include <string>
#include "eventSkeleton.h"
#pragma once

using namespace std;

class Lecture : public eventSkeleton {
public:
    // Constructor
    Lecture(string paperCode, int day, int week, int startTime, int endTime, string location)
        : eventSkeleton(EventType::LECTURE, paperCode, day, week, startTime, endTime, location) {}


};
