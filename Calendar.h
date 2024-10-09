/**
 * @file Calendar.h
 * @brief Header file for the Calendar class
 */
#pragma once

#include <vector>
#include "eventSkeleton.h"
#include "assignment.h"
#include "exam.h"
#include "paper.h"

// Forward declaration of classes
class Day;
class Week;
class Calendar;

/**
 * @class Day
 * @brief Represents a single day in a calendar, containing events, assignments, and exams.
 */
class Day
{
public:
    vector<eventSkeleton> events;
    vector<Assignment> assignments;
    vector<Exam> exams;
    int dayNumber;

public:
    /**
     * @brief Construct a new Day object
     * @param dayNumber The number of the day
     */
    Day(int dayNumber);
    /**
     * @brief Add an event to the day
     * @param e The event to add
     * @return true if the event was added successfully, false otherwise
     */
    bool addEvent(eventSkeleton &e);

private:
    /**
     * @brief Add an event to the calendar
     * @param d The event to add
     * @return true if the event was added successfully, false otherwise
     */
    bool addEventToCalendar(eventSkeleton &d);
};

/**
 * @class Week
 * @brief Represents a week in a calendar, containing multiple days.
 */
class Week
{
public:
    std::vector<Day> days;
    int weekNumber;

public:
    /**
     * @brief Construct a new Week object
     * @param weekNumber The number of the week
     */
    Week(int weekNumber);
    /**
     * @brief Add an event to the week
     * @param e The event to add
     * @return true if the event was added successfully, false otherwise
     */
    bool addEvent(eventSkeleton &e);
};

/**
 * @class Calendar
 * @brief Represents a calendar, containing multiple weeks.
 */
class Calendar
{
private:
    std::vector<Week> weeks;
    vector<paper> papers;

public:
    /**
     * @brief Construct a new Calendar object
     */
    Calendar();

    /**
     * @brief Display the entire calendar
     */
    void display();

    /**
     * @brief Add an event to the calendar
     * @param e The event to add
     * @return true if the event was added successfully, false otherwise
     */
    bool addEvent(eventSkeleton &e);

    /**
     * @brief Remove an event from the calendar
     * @param e The event to remove
     * @return true if the event was removed successfully, false otherwise
     */
    bool removeEvent(eventSkeleton &e);

    /**
     * @brief Edits an existing event in the calendar.
     * @param e The event to be edited.
     * @return true if the event was successfully edited, false otherwise.
     */
    bool editEvent(eventSkeleton &e);

    /**
     * @brief Displays a specific week of the calendar.
     * @param week The week number to display.
     */
    void displayWeek(int week);

    /**
     * @brief Displays a specific semester.
     * @param semester The semester number to display.
     */
    void displaySemester(int semester);

    /**
     * @brief Returns all papers for the calendar
     * @return All papers for the calendar
     */
    vector<paper> &getPapers();

    /**
     * @brief Serialises the calendar to a file
     * @param outputFile The file to output to
     */
    void serialize(std::ofstream &outputFile) const;

    /**
     * @brief Deserialises the calendar to a variable
     * @param inputFile The calendar file to input
     */
    void deserialize(std::ifstream &inputFile);

    /**
     * @brief Tests the functionality of the Calendar class.
     * @return true if all tests pass, false otherwise.
     */
    bool test();

    /**
     * @brief Returns a color code for display purposes.
     * @param colour The color name.
     * @param background Whether the color is for background or foreground.
     * @return A string representing the color code.
     */
    std::string getColour(string colour, bool background);
};
