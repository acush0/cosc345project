#include <iostream>
#include "tutorial.h"

using namespace std;

// constructor
Tutorial::Tutorial(string eventType, string paperCode, int startTime, int endTime, string location, int day, int week)
    : eventSkeleton(paperCode, day, week),eventType(eventType), startTime(startTime), endTime(endTime), location(location) {
}

// getter methods
string Tutorial::getEventType() {
    return eventType;
}

int Tutorial::getStartTime()  {
    return startTime;
}

int Tutorial::getEndTime()  {
    return endTime;
}

string Tutorial::getLocation()  {
    return location;
}

// setter methods
void Tutorial::setEventType(string& eventType) {
    this->eventType = eventType;
}

void Tutorial::setStartTime(int startTime) {
    this->startTime = startTime;
}

void Tutorial::setEndTime(int endTime) {
    this->endTime = endTime;
}

void Tutorial::setLocation( string& location) {
    this->location = location;
}


// display tutorial information
void Tutorial::displayInfo()  {
    cout << "Tutorial for " << getPaperCode() << " at " << location << " on day " << getDay() << " of week " << getWeek() << " from " << startTime << " to " << endTime << endl;
}
