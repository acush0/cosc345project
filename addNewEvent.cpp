
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "addNewEvent.h"
#include "tutorial.h"
#include "lab.h"
#include "lecture.h"
#include "Calendar.h"
#include "eventSkeleton.h"

using namespace std;

vector<eventSkeleton> events;

// need input validation

enum class EventType {
    TUTORIAL,
    LAB,
    LECTURE,
    // ASSIGNMENT,
    // EXAM,
};

// Constructor to initialize papers
addNewEvent::addNewEvent(vector<paper>& papers) : papers(papers) {}

void addNewEvent::addNewEventMenu() {
    string paperCode, eventType, location;
    int startTime, endTime, day, week;
    // any more variables for exams/assignments


    cout << "Choose paper code:\n";
    // displays paper codes by getting menu's vector<paper> papers
    int index = 1;
    for(auto& paper : papers){
        cout << index << ". " << paper.getPaperCode() << " - " << paper.getPaperName() << "\n" << endl;
        index++;
    }
    cin >> paperCode;

    cout << "Choose type: (tutorial, lab, lecture)\n";
    // implement enum
    cin >> eventType;

    //depending on type/enum, ask for properties tied to specific event e.g. lecture has different properties to assignment
    cout << "Enter start time: ";
    cin >> startTime;

    cout << "Enter end time: ";
    cin >> endTime;

    cout << "Enter location: ";
    cin >> location;

    cout << "Enter day: ";
    cin >> day;
    // may need to also ask for range of weeks? - can sort out later
    cout << "Enter week: ";
    cin >> week;

    // create object based on enum then push to events

    //pseudo
    // if eventType == tutorial 
    Tutorial newTutorial = Tutorial(eventType, paperCode, startTime, endTime, location, day, week);
    // else if eventType == lab
    //lab newLab = lab(eventType, paperCode, startTime, endTime, location, day, week);
    // else if eventType == lecture
    //lecture newLecture = lecture(eventType, paperCode, startTime, endTime, location, day, week);

    // just has as default before enum is implemented
    events.push_back(newTutorial);
    }





