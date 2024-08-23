#include <vector>
#include <iostream>
#include "Calendar.h"
#include "Event.h"
#include "eventSkeleton.h"

using namespace std;

Day::Day(int dayNumber) : dayNumber(dayNumber) {
        // Constructor implementation
    }

bool Day::addEvent(const Event& d) {
    for (const auto& e : events) {
        // Check if event d overlaps with event e
        if ((d.getStartTime() < e.getEndTime() && d.getEndTime() > e.getStartTime()) ||
            (e.getStartTime() < d.getEndTime() && e.getEndTime() > d.getStartTime())
            || d.getStartTime() == e.getStartTime() && d.getEndTime() == e.getEndTime()) {
            std::cout << "Event overlaps with another event" << std::endl;
            return false;
        }
    }
    std::cout << "Event Name: " << d.getEventName() << std::endl;
    std::cout << "Start Time: " << d.getStartTime() << std::endl;
    std::cout << "End Time: " << d.getEndTime() << std::endl;
    std::cout << "Day: " << d.getDay() << std::endl;
    std::cout << "Week: " << d.getWeek() << std::endl;
    std::cout << "-----------------------" << std::endl;
    // If no overlap, add the event
    events.push_back(d);
    return true;
}
//

Week::Week(int weekNumber) : weekNumber(weekNumber) {
    for(int i = 0; i < 7; i++) {
        days.push_back(Day(i));
    }
}

bool Week::addEvent(const Event& e) {
    int day = e.getDay();
    if(days[day].addEvent(e)){
        return true;
    }
    else{
        return false;   
    }
}

Calendar::Calendar() {
    for(int i = 0; i < 52; i++) {
        weeks.push_back(Week(i));
    }
}

void Calendar::display() {
    // Implement display logic
}

bool Calendar::addEvent(const Event& e) {
    string name = e.getEventName();
    int week = e.getWeek();
    int day = e.getDay();
    int startTime = e.getStartTime();
    int endTime = e.getEndTime();
    if(weeks[week].addEvent(e)){
        return true;
    }
    else{
        return false;
    }
}

bool Calendar::removeEvent(const Event& e) {
    // Implement logic to remove event
    return true;
}

bool Calendar::editEvent(const Event& e) {
    // Implement logic to edit event
    return true;
}

// int main() {
//     Calendar calendar;
//     calendar.display();
//     // Additional logic for testing
//     return 0;
// }
bool Calendar::test(){
    Calendar testCalendar;
    Event testEvent("Test Event", 0, 6, 0, 0);
    testCalendar.addEvent(testEvent);
    Event testEvent2("Test Event2", 2,10 , 0, 0);
    if(testCalendar.addEvent(testEvent) == false && testCalendar.addEvent(testEvent2)==false){ // Test that events cannot overlap
        cout << "Calender Test Passed" << endl;
        return true;
    }
    return false;
}