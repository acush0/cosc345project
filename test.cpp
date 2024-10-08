#include <iostream>
#include <vector>
#include <string>
#include "Calendar.h"
#include "paper.h"
#include "addPaper.h"
#include "eventSkeleton.h"
#include "addNewEvent.h"
#include "eventSkeleton.h"
#include "validation.h"
#include "CalendarFile.h"
#include <iostream>
#include "flashcard.h"
#include <fstream>
#include <sstream>
#include "MenuItem.h"
#include "StudySession.h"

bool testGetValidInteger()
{
    validation v;
    std::string prompt = "Enter a number between 1 and 100: ";
    int result = v.getValidInteger(1, 40, prompt);
    std::cout << "getValidInteger result: " << result << std::endl;
    return (result >= 1 && result <= 100);
}
bool testGetValidStringHelper()
{
    validation v;
    std::string prompt = "Enter a string ";
    std::string result = v.getValidString(prompt);
    std::cout << "getValidString result: " << result << std::endl;
    return (result.length() > 0);
}

bool testGetValidString()
{
    std::ifstream in("input1.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
    std::cin.rdbuf(in.rdbuf());                // redirect std::cin to input.tx
    bool getValidStringTest = testGetValidStringHelper();
    std::cout << "testGetValidString test " << (getValidStringTest ? "passed" : "failed") << std::endl;
    // Restore cin to its original buf
    std::cin.rdbuf(cinbuf);
    return getValidStringTest;
}

// bool testTimeValidation()
// {
//     std::ifstream in("input4.txt");
//     std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
//     std::cin.rdbuf(in.rdbuf());                // redirect std::cin to input4.txt

//     validation v;
//     std::string prompt = "Enter a time: ";
//     int minTime = 0;
//     int result;
//     bool testPassed = false;

//     // We'll loop until we get 1030 or reach end of file
//     while (!in.eof()) {
//         result = v.timeValidation(prompt, minTime);
//         std::cout << "timeValidation result: " << result << std::endl;
        
//         if (result == 1030) {
//             testPassed = true;
//             break;
//         }
//     }

//     // Restore cin to its original buf
//     std::cin.rdbuf(cinbuf);

//     std::cout << "testTimeValidation test " << (testPassed ? "passed" : "failed") << std::endl;
//     return testPassed;
// }

bool testAddEventHelper(){
    Calendar *calendar = new Calendar();
    addPaper newPaper(calendar->getPapers());
    newPaper.addPaperMenu();
    addNewEvent newEvent(calendar->getPapers(), calendar);
    newEvent.addNewEventMenu();
    if(calendar->getPapers().empty()){
        return false;
    }else{
        return true;
    }

}

bool testAddEvent(){
    std::ifstream in("input3.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
    std::cin.rdbuf(in.rdbuf());     
    bool getValidStringTest = true;
    Calendar *calendar = new Calendar();
    addPaper newPaper(calendar->getPapers());
    newPaper.addPaperMenu();
    for(int i=0; i<3; i++){// Loops through testing each event type
        addNewEvent newEvent(calendar->getPapers(), calendar);
        newEvent.addNewEventMenu();
    }           
    std::cout << "testAddEvent test " << (getValidStringTest ? "passed" : "failed") << std::endl;
    // Restore cin to its original buf
    std::cin.rdbuf(cinbuf);
    return getValidStringTest;
}


int main()
{

    bool allTestsPassed = true;
    // Test getValidInteger with input redirection
    std::ifstream in("input.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); // save old buf
    std::cin.rdbuf(in.rdbuf());                // redirect std::cin to input.txt

    bool getValidIntegerPassed = testGetValidInteger();
    allTestsPassed &= getValidIntegerPassed;
    std::cout << "getValidInteger test " << (getValidIntegerPassed ? "passed" : "failed") << std::endl;

    // Restore cin to its original buf
    std::cin.rdbuf(cinbuf);

    // Existing tests
    Calendar calendar;
    eventSkeleton testEvent = eventSkeleton(EventType::LECTURE, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");
    eventSkeleton testEventAssignment = eventSkeleton(EventType::ASSIGNMENT, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");
    eventSkeleton testEventTutorial = eventSkeleton(EventType::TUTORIAL, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");
    eventSkeleton testEventLab = eventSkeleton(EventType::LAB, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");   
    eventSkeleton testEventExam = eventSkeleton(EventType::EXAM, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");

    paper testPaper = paper("name", "code", 1);
    flashcard testFlashcard = flashcard("question", "answer");

    bool flashcardTestPassed = testFlashcard.test();

    bool calendarTestPassed = calendar.test();
    bool eventTestPassed = testEvent.test();
    bool eventAssignmentTestPassed = testEventAssignment.test();
    bool eventTutorialTestPassed = testEventTutorial.test();
    bool eventLabTestPassed = testEventLab.test();
    bool eventExamTestPassed = testEventExam.test();

    //bool timeValidationTestPassed = testTimeValidation();
    bool paperTestPassed = testPaper.test();
    bool calendarFileTestPassed = CalendarFile::test();
    bool menuItemTestPassed = MenuItem::test();
    bool studySessionTestPassed = StudySession::studyTest();

    allTestsPassed &= calendarTestPassed && eventTestPassed && eventAssignmentTestPassed && eventTutorialTestPassed && eventLabTestPassed && eventExamTestPassed && paperTestPassed && calendarFileTestPassed && menuItemTestPassed && studySessionTestPassed && flashcardTestPassed;
    allTestsPassed &= testGetValidString();
    allTestsPassed &= testAddEvent();
    //bool timeValidationPassed = testTimeValidation();
    //allTestsPassed &= timeValidationPassed;

    if (allTestsPassed)
    {
        std::cout << "Allthe  tests passed" << std::endl;
    }
    else
    {
        std::cout << "Somethe tests failed" << std::endl;
        return 1;
    }

    return 0;

    // Calendar calendar;
    // eventSkeleton testEvent = eventSkeleton(EventType::LECTURE, "COSC345", 1, 1, 930, 1000, "Mellor 3.1");
    // validation v = validation();
    // paper testPaper = paper("name", "code",1);
    // //Because it returns either we create a bool called passed then return based on it at end  or we can just do it like this
    // if(calendar.test()&&testEvent.test()&&testPaper.test()){
    //     std::cout << "Testing Passed" << std::endl;
    // }else{
    //     std::cout << "Testing Failed" << std::endl;
    //     return 1;
    // }
}