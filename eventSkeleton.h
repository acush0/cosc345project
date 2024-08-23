#include <string>
#pragma once
using namespace std;

enum class EventType {
    LECTURE,
    TUTORIAL,
    LAB,
    ASSIGNMENT,
    EXAM,
};

class eventSkeleton{
private:
    string paperCode, location;
    int day, week, startTime, endTime;
    EventType eventType;

public:

    // Constructor
    eventSkeleton(EventType eventType, string paperCode,  int day, int week, int startTime, int endTime, string location);

    // Getters
    EventType getEventType();
    string getPaperCode();
    int getDay();
    int getWeek();
    int getStartTime();
    int getEndTime();
    string getLocation();

    // setters
    void setEventType(EventType eventType);
    void setPaperCode(string& paperCode);
    void setDay(int day);
    void setWeek(int week);
    void setStartTime(int startTime);
    void setEndTime(int endTime);
    void setLocation(string& location);
    
    void displayInfo();
};