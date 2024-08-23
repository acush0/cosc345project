#include "eventSkeleton.h"
#include <string>
using namespace std;

// constructor
eventSkeleton::eventSkeleton(string paperCode, int day, int week)
    : paperCode(paperCode), day(day), week(week) {
}

// getter methods
string eventSkeleton::getPaperCode(){
    return paperCode;
}
int eventSkeleton::getDay(){
    return day;
}

int eventSkeleton::getWeek(){
    return week;
}

// setter methods
void eventSkeleton::setPaperCode(string& paperCode){
    this->paperCode = paperCode;
}
void eventSkeleton::setDay(int day){
    this->day = day;
}
void eventSkeleton::setWeek(int week){
    this->week = week;
}
void displayInfo(){

}


