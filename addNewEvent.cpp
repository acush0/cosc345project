
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "addNewEvent.h"
#include "tutorial.h"
#include "lab.h"
#include "assignment.h"
#include "exam.h"
#include "lecture.h"
#include "Calendar.h"
#include "eventSkeleton.h"

using namespace std;

vector<eventSkeleton> events;

// need input validation

//enum lecture, tutorial, lab, assignment, exam


// Constructor to initialize papers
addNewEvent::addNewEvent(vector<paper>& papers) : papers(papers) {}

void addNewEvent::addNewEventMenu() {
    EventType eventType;
    eventType = EventType::LECTURE;
    string paperCode, location;
    int startTime, endTime, day, week, typeChoice;


    cout << "Choose paper code:\n";
    // displays paper codes by getting menu's vector<paper> papers
    int index = 1;
    for(auto& paper : papers){
        cout << index << ". " << paper.getPaperCode() << " - " << paper.getPaperName() << "\n" << endl;
        index++;
    }
    cin >> paperCode;

    cout << "Choose the type of event to add:\n1. Lecture\n2. Tutorial\n3. Lab\n4. Assignment\n5. Exam\n";
    cin >> typeChoice;
    // need to add input validation if they put outside of input range
    switch(typeChoice) {
        case 1:
            eventType = EventType::LECTURE;
            break;
        case 2:
            eventType = EventType::TUTORIAL;
            break;
        case 3:
            eventType = EventType::LAB;
            break;
        case 4:
            eventType = EventType::ASSIGNMENT;
            break;
        case 5:
            eventType = EventType::EXAM;
            break;
        default:
            cout << "bad input";
    }

    

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

    //pseudo
    if(eventType == EventType::TUTORIAL){
        Tutorial newTutorial = Tutorial(paperCode, day, week, startTime, endTime, location);
        events.push_back(newTutorial);
    }
    else if(eventType == EventType::LAB){
        Lab newLab = Lab(paperCode, day, week, startTime, endTime, location);
        events.push_back(newLab);
    }
    else if(eventType == EventType::LECTURE){
        Lecture newLecture = Lecture(paperCode, day, week, startTime, endTime, location);
        events.push_back(newLecture);
    }
    else if(eventType == EventType::ASSIGNMENT){
        Assignment newAssignment = Assignment(paperCode, day, week, startTime, endTime, location);
        events.push_back(newAssignment);
    }
    else if(eventType == EventType::EXAM){
        Exam newExam = Exam(paperCode, day, week, startTime, endTime, location);
        events.push_back(newExam);
    }
    else{
        cout << "Invalid event type.";
    }
    }





