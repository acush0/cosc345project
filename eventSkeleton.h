#include <string>
#pragma once
using namespace std;

class eventSkeleton{
private:
    string paperCode;
    int day;
    int week;

public:
    // Constructor
    eventSkeleton(string paperCode,  int day, int week);

    // Getters
    string getPaperCode();
    int getDay();
    int getWeek();

    // setters
    void setPaperCode(string& paperCode);
    void setDay(int day);
    void setWeek(int week);
};