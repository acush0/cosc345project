#include "eventSkeleton.h"
#include <string>
#include <iostream>
using namespace std;

// constructor
eventSkeleton::eventSkeleton(EventType eventType, string paperCode, int day, int week, int startTime, int endTime, string location)
    : paperCode(paperCode), location(location),day(day), week(week), startTime(startTime), endTime(endTime), eventType(eventType){
}

// getter methods
EventType eventSkeleton::getEventType(){
    return eventType;
}
string eventSkeleton::getPaperCode(){
    return paperCode;
}
int eventSkeleton::getDay(){
    return day;
}

int eventSkeleton::getWeek(){
    return week;
}
int eventSkeleton::getStartTime(){
    return startTime;
}
int eventSkeleton::getEndTime(){
    return endTime;
}
string eventSkeleton::getLocation(){
    return location;
}


// setter methods
void eventSkeleton::setEventType(EventType eventType){
    this->eventType = eventType;
}
void eventSkeleton::setPaperCode(string& paperCode){
    this->paperCode = paperCode;
}
void eventSkeleton::setDay(int day){
    this->day = day;
}
void eventSkeleton::setWeek(int week){
    this->week = week;
}
void eventSkeleton::setStartTime(int startTime){
    this->startTime = startTime;
}
void eventSkeleton::setEndTime(int endTime){
    this->endTime = endTime;
}
void eventSkeleton::setLocation(string& location){
    this->location = location;
}

void eventSkeleton::displayInfo(){
    cout << static_cast<int>(getEventType()) << " for " << getPaperCode() << " at " << getLocation() 
              << " on day " << getDay() << " of week " << getWeek() 
              << " from " << getStartTime() << " to " << getEndTime() << endl;
}


