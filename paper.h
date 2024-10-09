/**
 * @file paper.h
 * @brief Header file for the paper class
 */

#include <string>
#include <vector>
#include "lecture.h"
#include "tutorial.h"
#include "lab.h"
#include <fstream>
#pragma once

/**
 * @class paper
 * @brief Represents a paper (course) in the academic context
 */
class paper
{
private:
    std::string paperName;
    std::string paperCode;
    int paperPoints;
    std::vector<eventSkeleton> events;

public:
    /**
     * @brief Construct a new paper object
     * @param paperName The name of the paper
     * @param paperCode The code of the paper
     * @param paperPoints The number of points for the paper
     */
    paper(std::string paperName, std::string paperCode, int paperPoints);

    /**
     * @brief Get the name of the paper
     *
     * @return string The name of the paper
     */
    std::string getPaperName();

    /**
     * @brief Get the code of the paper
     *
     * @return string The code of the paper
     */
    std::string getPaperCode() const;

    /**
     * @brief Get the number of points for the paper
     *
     * @return int The number of points for the paper
     */
    int getPaperPoints();

    /**
     * @brief Set the name of the paper
     *
     * @param paperName The new name for the paper
     */
    void setPaperName(std::string &paperName);

    /**
     * @brief Set the code of the paper
     *
     * @param paperCode The new code for the paper
     */
    void setPaperCode(std::string &paperCode);

    /**
     * @brief Set the number of points for the paper
     *
     * @param paperPoints The new number of points (credits) for the paper
     */
    void setPaperPoints(int paperPoints);

    /**
     * @brief Add an event to the paper
     *
     * @param event The event to be added to the paper
     */
    void addEvent(eventSkeleton &event);

    /**
     * @brief Serialize the paper to a file
     *
     * @param outputFile The file to output to
     */
    void serialize(std::ofstream &outputFile) const;

    /**
     * @brief Deserialize the paper from a file
     *
     * @param inputFile File to input from
     */
    void deserialize(std::ifstream &inputFile);

    /**
     * @brief Display information about the paper
     *
     * This method prints out details about the paper, including its name, code,
     * points, and associated events.
     */
    void displayInfo();

    bool test();

      /**
     * @brief Calculates the total hours of study sessions in a specified week.
     *
     * @param week The week number for which to calculate total study hours.
     * @return double Total study hours in the specified week.
     */
    double getTotalStudyHours(int week) const;
};
