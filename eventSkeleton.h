/**
 * @file eventSkeleton.h
 * @brief Defines the eventSkeleton class, which serves as a base class for all event types in the calendar system.
 */

#include <string>
#pragma once

/**
 * @brief Enumeration of event types
 */
enum class EventType
{
    LECTURE,
    TUTORIAL,
    LAB,
    ASSIGNMENT,
    EXAM,
    STUDY_SESSION,
};

/**
 * @brief Class representing the skeleton of an event
 */
class eventSkeleton
{
private:
    std::string paperCode, location;
    int day, week, startTime, endTime;
    EventType eventType;

public:
    /**
     * @brief Constructor for eventSkeleton
     * @param eventType The type of the event
     * @param paperCode The code of the paper associated with the event
     * @param day The day of the event
     * @param week The week of the event
     * @param startTime The start time of the event
     * @param endTime The end time of the event
     * @param location The location of the event
     */
    eventSkeleton(EventType eventType, std::string paperCode, int day, int week, int startTime, int endTime, std::string location);

    /**
     * @brief Get the event type
     * @return The event type
     */
    EventType getEventType();

    /**
     * @brief Get the string representation of the event type
     * @param type The event type
     * @return String representation of the event type
     */
    std::string getEventTypeString(EventType type);

    /**
     * @brief Get the paper code
     * @return The paper code
     */
    std::string getPaperCode();

    /**
     * @brief Get the day of the event
     * @return The day of the event
     */
    int getDay();

    /**
     * @brief Get the week of the event
     * @return The week of the event
     */
    int getWeek() const; // Add const qualifier here

    /**
     * @brief Get the start time of the event
     * @return The start time of the event
     */
    int getStartTime() const;

    /**
     * @brief Get the end time of the event
     * @return The end time of the event
     */
    int getEndTime() const;

    /**
     * @brief Get the location of the event
     * @return The location of the event
     */
    std::string getLocation();

    /**
     * @brief Set the event type
     * @param eventType The new event type
     */
    void setEventType(EventType eventType);

    /**
     * @brief Set the paper code
     * @param paperCode The new paper code
     */
    void setPaperCode(std::string &paperCode);

    /**
     * @brief Set the day of the event
     * @param day The new day
     */
    void setDay(int day);

    /**
     * @brief Set the week of the event
     * @param week The new week
     */
    void setWeek(int week);

    /**
     * @brief Set the start time of the event
     * @param startTime The new start time
     */
    void setStartTime(int startTime);

    /**
     * @brief Set the end time of the event
     * @param endTime The new end time
     */
    void setEndTime(int endTime);

    /**
     * @brief Set the location of the event
     * @param location The new location
     */
    void setLocation(std::string &location);

    /**
     * @brief Display information about the event
     */
    void displayInfo();

    /**
     * @brief Serialises the event to a file
     * @param outputFile The file to output to
     */
    void serialize(std::ofstream &outputFile) const;

    /**
     * @brief Test the event
     * @return True if the test passes, false otherwise
     */
    bool test();
};