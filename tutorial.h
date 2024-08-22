#include <string>
#include "eventSkeleton.h"
#pragma once

using namespace std;

class Tutorial : public eventSkeleton {
private:
    string eventType;
    int startTime;
    int endTime;
    string location;

public:
    // ructor
    Tutorial(string eventType, string paperCode, int startTime, int endTime, string location, int day, int week);

    // getter methods
    string getEventType();
    int getStartTime() ;
    int getEndTime() ;
    string getLocation() ;

    // setter methods
    void setEventType(string& eventType);
    void setStartTime(int startTime);
    void setEndTime(int endTime);
    void setLocation( string& location);

    // display tutorial information
    void displayInfo() ;
};