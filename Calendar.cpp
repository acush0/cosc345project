#include <vector>
#include <iostream>
#include "Calendar.h"
#include "eventSkeleton.h"
#include "lecture.h"
#include "lab.h"
#include "assignment.h"
#include "exam.h"
#include "tutorial.h"
#include <iomanip>
#include <sstream>
#include "paper.h"
#include <map>
#include "addNewEvent.h"
#include <algorithm>

using namespace std;

Day::Day(int dayNumber) : dayNumber(dayNumber)
{
}

bool Day::addEvent(eventSkeleton &d)
{
    if (d.getEventType() == EventType::ASSIGNMENT)
    {
        assignments.push_back(static_cast<Assignment &>(d));
        return true;
    }
    else if (d.getEventType() == EventType::EXAM)
    {
        exams.push_back(static_cast<Exam &>(d));
        return true;
    }
    else
    {

        return addEventToCalendar(d);
    }
}

bool Day::addEventToCalendar(eventSkeleton &d)
{
    for (auto &e : events)
    {
        // Check if event d overlaps with event e
        if ((d.getStartTime() < e.getEndTime() && d.getEndTime() > e.getStartTime()) ||
            (e.getStartTime() < d.getEndTime() && e.getEndTime() > d.getStartTime()) || (d.getStartTime() == e.getStartTime() && d.getEndTime() == e.getEndTime()))
        {
            std::cout << Calendar::getColour("red", false) + "Event overlaps with another event" << std::endl;
            std::cout << "Other event details:\n";
            e.displayInfo();
            std::cout << Calendar::getColour("reset", false);
            return false;
        }
    }
    // std::cout << "Start Time: " << d.getStartTime() << std::endl;
    // std::cout << "End Time: " << d.getEndTime() << std::endl;
    // std::cout << "Day: " << d.getDay() << std::endl;
    // std::cout << "Week: " << d.getWeek() << std::endl;
    // std::cout << "-----------------------" << std::endl;
    // If no overlap, add the event
    events.push_back(d);
    return true;
}

Week::Week(int weekNumber) : weekNumber(weekNumber)
{
    for (int i = 0; i < 7; i++)
    {
        days.push_back(Day(i));
    }
}

bool Week::addEvent(eventSkeleton &e)
{
    int day = e.getDay() - 1;
    if (days[day].addEvent(e))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Calendar::Calendar()
{
    for (int i = 0; i < 52; i++)
    {
        weeks.push_back(Week(i));
    }
}
int incrementTime(int time)
{
    int hour = time / 100;
    int minute = time % 100;

    // Increment the hour
    hour += 1;

    // Handle overflow if the hour goes beyond 23 (24-hour format)
    if (hour == 24)
    {
        hour = 0;
    }

    // Return the new time in HHMM format
    return (hour * 100) + minute;
}

void Calendar::display()
{

    std::cout << "\n" + getColour("red", true) + ""
                                                 "  ____      _                _            \n"
                                                 " / ___|__ _| | ___ _ __   __| | __ _ _ __ \n"
                                                 "| |   / _` | |/ _ \\ '_ \\ / _` |/ _` | '__|\n"
                                                 "| |__| (_| | |  __/ | | | (_| | (_| | |   \n"
                                                 " \\____\\__,_|_|\\___|_| |_|\\__,_|\\__,_|_|   \n"
                                                 "                                         \n"
                                                 "" +
                     getColour("reset", true) + ""
                                                "=======================================================================================================================================================================================================";
    ;

    for (int i = 1; i < 53; i++)
    {
        displayWeek(i);
    }
}

std::string getWhiteSpace(int n)
{
    std::string result = "";
    while (n > 0)
    {
        result += " ";
        n--;
    }
    return result;
}
std::string getDash(int n)
{
    std::string result = "";
    while (n > 0)
    {
        result += "-";
        n--;
    }
    return result;
}

void Calendar::displayWeeksSem(int week, int relativeWeek)
{
    week = week - 1;
    std::cout << getColour("red", false) + "\nWeek " + std::to_string(relativeWeek) << +"" + getColour("reset", false) + ":" << std::endl;
    for (int i = 1; i < 8; i++)
    {
        std::cout << displayDay(i, week);
    }
}

void Calendar::displayWeek(int week)
{
    week = week - 1;
    std::cout << getColour("red", false) + "\nWeek " << week + 1 << +"" + getColour("reset", false) + ":" << std::endl;
    for (int i = 1; i < 8; i++)
    {
        std::cout << displayDay(i, week);
    }
}

std::string getDOW(int day)
{
    std::map<int, std::string> days;

    days[0] = "Monday:";
    days[1] = "Tuesday:";
    days[2] = "Wednesday:";
    days[3] = "Thursday:";
    days[4] = "Friday:";
    days[5] = "Saturday:";
    days[6] = "Sunday:";
    return days[day];
}

std::string formatTime(int time)
{
    int hours = time / 100;
    int minutes = time % 100;
    return std::to_string(hours) + ":" + (minutes < 10 ? "0" : "") + std::to_string(minutes);
}

std::string Calendar::displayDay(int day, int week)
{
    day = day - 1;
    std::string result = getWhiteSpace(4) + getDOW(day) + getWhiteSpace(4) + "\n";
    vector<eventSkeleton> eventsDay = weeks[week].days[day].events;
    vector<Assignment> assignmentsDay = weeks[week].days[day].assignments;
    vector<Exam> examsDay = weeks[week].days[day].exams;
    std::sort(eventsDay.begin(), eventsDay.end(),
              [](eventSkeleton &a, eventSkeleton &b)
              {
                  return a.getStartTime() < b.getStartTime();
              });
    if (eventsDay.size() == 0)
    {
        result += getWhiteSpace(8) + "No events scheduled\n";
    }
    else
    {
        for (auto &e : eventsDay)
        {
            std::string eventName = e.getPaperCode();
            if (eventName.length() > 10)
            {
                eventName.replace(10, string::npos, "...");
            }
            result += getWhiteSpace(8) + e.getPaperCode() + getWhiteSpace(2) + formatTime(e.getStartTime()) + " - " + formatTime(e.getEndTime()) + " @ " + e.getLocation() + "\n";
        }
        if (assignmentsDay.size() > 0 || examsDay.size() > 0)
        {
            result += getWhiteSpace(8) + getDash(8) + "\n";
        }
        if (assignmentsDay.size() > 0)
        {
            result += getWhiteSpace(8) + getColour("yellow", false) + "Assignments:\n" + getColour("reset", false);
            for (auto &a : assignmentsDay)
            {
                result += getWhiteSpace(12) + a.getPaperCode() + " - " + "Due" + getWhiteSpace(2) + formatTime(a.getStartTime()) + "\n";
            }
        }
        if (examsDay.size() > 0)
        {
            result += getWhiteSpace(8) + getColour("yellow", false) + "Exams:\n" + getColour("reset", false);
            for (auto &a : examsDay)
            {
                result += getWhiteSpace(12) + a.getPaperCode() + getWhiteSpace(2) + formatTime(a.getStartTime()) + " - " + formatTime(a.getEndTime()) + " @ " + a.getLocation() + "\n";
            }
        }
    }
    return result;
}

std::string Calendar::getColour(std::string colour, bool background)
{
    // Create a map to store color codes
    std::map<std::string, std::string> colors;

    // Insert foreground color codes into the map
    colors["reset"] = "\033[0m";
    colors["black"] = "\033[30m";
    colors["red"] = "\033[31m";
    colors["green"] = "\033[32m";
    colors["yellow"] = "\033[33m";
    colors["blue"] = "\033[34m";
    colors["magenta"] = "\033[35m";
    colors["cyan"] = "\033[36m";
    colors["white"] = "\033[37m";

    if (background)
    {
        colors["black"] = "\033[40m";
        colors["red"] = "\033[41m";
        colors["green"] = "\033[42m";
        colors["yellow"] = "\033[43m";
        colors["blue"] = "\033[44m";
        colors["magenta"] = "\033[45m";
        colors["cyan"] = "\033[46m";
        colors["white"] = "\033[47m";
    }

    if (colors.find(colour) != colors.end())
    {
        return colors[colour];
    }
    else
    {
        // If the color is not found, return reset code
        return colors["reset"];
    }
}

void Calendar::displaySemester(int semester)
{
    int startWeek = (semester - 1) * 16 + 1;
    int endWeek = startWeek + 16 + 1;
    int relativeWeek = 1;
    for (int i = startWeek; i < endWeek; i++)
    {
        displayWeeksSem(i, relativeWeek);
        relativeWeek++;
    }
}

bool Calendar::addEvent(eventSkeleton &e)
{
    int week = e.getWeek() - 1;
    if (weeks[week].addEvent(e))
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<paper> &Calendar::getPapers()
{
    return papers;
}

void Calendar::serialize(std::ofstream &outputFile) const
{
    // Serialize papers
    outputFile << papers.size() << std::endl; // Save the number of papers
    for (const auto &p : papers)
    {
        p.serialize(outputFile); // Call serialize function for each paper
    }

    // Serialize weeks
    outputFile << weeks.size() << std::endl; // Save the number of weeks (always 52)
    for (const auto &week : weeks)
    {
        outputFile << week.weekNumber << std::endl;  // Serialize week number
        outputFile << week.days.size() << std::endl; // Serialize number of days in the week
        for (const auto &day : week.days)
        {
            outputFile << day.dayNumber << std::endl; // Serialize day number

            // Serialize events, assignments, and exams
            outputFile << day.events.size() << std::endl;
            for (const auto &event : day.events)
            {
                event.serialize(outputFile); // Serialize each event
            }

            outputFile << day.assignments.size() << std::endl;
            for (const auto &assignment : day.assignments)
            {
                assignment.serialize(outputFile); // Serialize each assignment
            }

            outputFile << day.exams.size() << std::endl;
            for (const auto &exam : day.exams)
            {
                exam.serialize(outputFile); // Serialize each exam
            }
        }
    }
}

void Calendar::deserialize(std::ifstream &inputFile)
{
    this->papers.clear(); // Clear all papers
    this->weeks.clear();  // Clear all weeks

    for (int i = 0; i < 52; i++)
    {
        weeks.push_back(Week(i));
    }

    // Deserialize the papers
    size_t numPapers;

    inputFile >> numPapers;
    inputFile.ignore(); // Ignore the newline symbol

    for (size_t i = 0; i < numPapers; ++i)
    {
        paper p("default_paper", "default_code", 18);
        p.deserialize(inputFile);
        this->papers.push_back(p);
    }

    // Deserialize the weeks (is always 52 but this keeps it consistent)
    size_t numWeeks;

    inputFile >> numWeeks;
    inputFile.ignore(); // Ignrore the newline

    for (size_t i = 0; i < numWeeks; ++i)
    {
        int weekNumber;
        inputFile >> weekNumber; // Grab the week number
        inputFile.ignore();

        Week week(weekNumber); // Create a Week object with the weekNumber

        // Deserialize the days of the week
        size_t numDays; // Always 7!
        inputFile >> numDays;
        inputFile.ignore();

        for (size_t j = 0; j < numDays; ++j)
        {
            int dayNumber;
            inputFile >> dayNumber;
            inputFile.ignore();

            Day dayObject(dayNumber);

            // Deserialize the events
            size_t numEvents; // Number of events in the day
            inputFile >> numEvents;
            inputFile.ignore();

            for (size_t k = 0; k < numEvents; ++k)
            {
                int eventTypeInteger;
                std::string paperCode, location;
                int day, week, startTime, endTime;

                inputFile >> eventTypeInteger;
                inputFile.ignore();

                std::getline(inputFile, paperCode);
                inputFile >> day >> week >> startTime >> endTime;
                inputFile.ignore();
                std::getline(inputFile, location);

                EventType eventType = static_cast<EventType>(eventTypeInteger);

                eventSkeleton event(eventType, paperCode, day, week, startTime, endTime, location);

                addNewEvent addNewEventManager(papers, this);

                this->addEvent(event);
            }
            // Deserialize assignments
            size_t numAssignments;
            inputFile >> numAssignments;
            inputFile.ignore(); // Ignore newline after the number of assignments

            for (size_t k = 0; k < numAssignments; ++k)
            {
                int eventTypeInteger;
                std::string paperCode, location;
                int day, week, startTime, endTime;

                inputFile >> eventTypeInteger;
                inputFile.ignore();

                std::getline(inputFile, paperCode);
                inputFile >> day >> week >> startTime >> endTime;
                inputFile.ignore();
                std::getline(inputFile, location);

                EventType eventType = static_cast<EventType>(eventTypeInteger);

                eventSkeleton event(eventType, paperCode, day, week, startTime, endTime, location);

                addNewEvent addNewEventManager(papers, this);

                this->addEvent(event);
            }

            // Deserialize exams
            size_t numExams;
            inputFile >> numExams;
            inputFile.ignore(); // Ignore newline after the number of exams

            for (size_t k = 0; k < numExams; ++k)
            {
                int eventTypeInteger;
                std::string paperCode, location;
                int day, week, startTime, endTime;

                inputFile >> eventTypeInteger;
                inputFile.ignore();

                std::getline(inputFile, paperCode);
                inputFile >> day >> week >> startTime >> endTime;
                inputFile.ignore();
                std::getline(inputFile, location);

                EventType eventType = static_cast<EventType>(eventTypeInteger);

                eventSkeleton event(eventType, paperCode, day, week, startTime, endTime, location);

                addNewEvent addNewEventManager(papers, this);

                this->addEvent(event);
            }

            week.days.push_back(dayObject); // Add the day to the current week
        }

        weeks.push_back(week); // Add the week to the calendar
    }
}

// int main() {
//     Calendar calendar;
//     calendar.display();
//     // Additional logic for testing
//     return 0;
// }
bool Calendar::test()
{
    bool passed = true;
    Calendar testCalendar;
    // Base event
    Lecture newLecture = Lecture("COSC203", 3, 7, 900, 1000, "Lecture Theatre");
    testCalendar.addEvent(newLecture);

    // Event that overlap

    // Event that overlap
    Lab newLab = Lab("COSC203", 3, 7, 930, 1030, "Lecture 23");

    // Event that exactly overlap
    Lab newLab2 = Lab("COSC203", 3, 7, 900, 1000, "Lecture 23");

    // Event that does not overlap
    Lecture newLecture1 = Lecture("COSC203", 3, 7, 1000, 1030, "Lecture 28");

    if (!(testCalendar.addEvent(newLab) == false && testCalendar.addEvent(newLab2) == false))
    { // Test that events cannot overlap
        passed = false;
    }
    if (!(testCalendar.addEvent(newLecture1) == true))
    { // Test that events that do not overlap can be added
        passed = false;
    }

    std::cout << "-----------------------" << std::endl;
    std::cout << "\n\n\nAdding events passed\n\n\n"
              << std::endl;
    std::cout << "-----------------------\n-----------------------" << std::endl;

    Assignment newAssignment = Assignment("COSC203", 3, 7, 900, 0, "");
    if (!testCalendar.addEvent(newAssignment))
    {
        passed = false;
    }

    Exam newExam = Exam("COSC203", 3, 7, 930, 1230, "Mellor labs g10");
    if (!testCalendar.addEvent(newExam))
    {
        passed = false;
    }

    Tutorial newtutorial = Tutorial("COSC300", 5, 10, 930, 1030, "Saint Daves");
    if (!testCalendar.addEvent(newtutorial))
    {
        passed = false;
    }

    testCalendar.displayWeek(7);
    testCalendar.displaySemester(1);
    testCalendar.display();

    // --- New Tests for getTotalStudyHours ---
    std::cout << "-----------------------" << std::endl;
    std::cout << "\n\n\nTesting getTotalStudyHours\n\n\n"
              << std::endl;
    std::cout << "-----------------------\n-----------------------" << std::endl;

    // Test Case 1: No events for the paper
    double hours1 = testCalendar.getTotalStudyHours("MATH101", 7);
    double expected1 = 0.0;
    if (hours1 != expected1)
    {
        std::cout << "Test Case 1 Failed: Expected " << expected1 << " hours, got " << hours1 << " hours." << std::endl;
        passed = false;
    }
    else
    {
        std::cout << "Test Case 1 Passed: No events for MATH101 in week 7." << std::endl;
    }

    // Test Case 2: Single event for the paper
    double hours2 = testCalendar.getTotalStudyHours("COSC203", 7);
    double expected2 = 1.5;
    if (hours2 != expected2)
    {
        std::cout << "Test Case 2 Failed: Expected " << expected2 << " hours, got " << hours2 << " hours." << std::endl;
        passed = false;
    }
    else
    {
        std::cout << "Test Case 2 Passed: Correct total study hours for COSC203 in week 7." << std::endl;
    }

    // Test Case 3: Multiple events for the same paper across different weeks
    // Adding events in week 8
    Lecture lectureWeek8 = Lecture("COSC203", 3, 8, 1000, 1200, "Lecture Theatre");
    testCalendar.addEvent(lectureWeek8);
    Exam examWeek8 = Exam("COSC203", 3, 8, 1400, 1600, "Mellor labs g10");

    testCalendar.addEvent(examWeek8);

    double hours3_week7 = testCalendar.getTotalStudyHours("COSC203", 7);
    double expected3_week7 = 1.5; // Same as Test Case 2
    double hours3_week8 = testCalendar.getTotalStudyHours("COSC203", 8);
    double expected3_week8 = 2.0;

    bool test3_passed = true;

    if (hours3_week7 != expected3_week7)
    {
        std::cout << "Test Case 3 Failed for Week 7: Expected " << expected3_week7 << " hours, got " << hours3_week7 << " hours." << std::endl;
        test3_passed = false;
    }
    if (hours3_week8 != expected3_week8)
    {
        std::cout << "Test Case 3 Failed for Week 8: Expected " << expected3_week8 << " hours, got " << hours3_week8 << " hours." << std::endl;
        test3_passed = false;
    }
    if (test3_passed)
    {
        std::cout << "Test Case 3 Passed: Correct total study hours for COSC203 across weeks 7 and 8." << std::endl;
    }
    else
    {
        passed = false;
    }

    // Test Case 5: Invalid week number
    double hours5 = testCalendar.getTotalStudyHours("COSC203", 60);
    double expected5 = 0.0;
    if (hours5 != expected5)
    {
        std::cout << "Test Case 5 Failed: Expected " << expected5 << " hours for invalid week, got " << hours5 << " hours." << std::endl;
        passed = false;
    }
    else
    {
        std::cout << "Test Case 5 Passed: Correctly handled invalid week number." << std::endl;
    }
    std::cout << "-----------------------" << std::endl;

    // Final Test Result
    if (passed)
    {
        cout << "" + getColour("green", true) + "Calender Test Passed" + getColour("reset", false) << endl;
    }
    else
    {
        cout << "" + getColour("red", true) + "Calender Test Failed" << getColour("reset", false) << endl;
    }
    return passed;
}

double Calendar::getTotalStudyHours(const std::string &paperCode, int week)
{
    double totalHours = 0.0;

    // Validate week number
    if (week < 1 || week > 52)
    {
        std::cerr << "Invalid week number: " << week << ". Please enter a value between 1 and 52." << std::endl;
        return totalHours;
    }

    // Access the target week
    Week &targetWeek = weeks[week - 1];

    // Iterate through each day in the week
    for (const Day &day : targetWeek.days)
    {
        // Iterate through each event in the day
        for (const auto &event : day.events)
        {
            // Check if the event is related to the specified paper
            if (event.getPaperCode() == paperCode)
            {
                int start = event.getStartTime();
                int end = event.getEndTime();

                // Convert HHMM to decimal hours
                int startHour = start / 100;
                int startMin = start % 100;
                int endHour = end / 100;
                int endMin = end % 100;

                double duration = (endHour + endMin / 60.0) - (startHour + startMin / 60.0);

                // Handle events that might cross midnight
                if (duration < 0)
                {
                    duration += 24;
                }

                totalHours += duration;
            }
        }
    }

    return totalHours;
}