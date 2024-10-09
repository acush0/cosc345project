#include <iostream>
#include <vector>
#include <string>
#include "Calendar.h"
#include "paper.h"
#include "addPaper.h"
#include "eventSkeleton.h"
#include "addNewEvent.h"
#include <limits>
#include "StudySession.h"
#include "MenuItem.h"
#include "validation.h"
#include <iomanip>
#include "CalendarFile.h"
using namespace std;

bool running = true;
Calendar *calendar = new Calendar();
validation validate;

void clearScreen()
{
#ifdef _WIN32
    // For Windows
    std::cout << "\033[2J\033[1;1H";
#else
    // For Unix-like systems
    std::cout << "\033[2J\033[1;1H";
#endif
    std::cout.flush();
}

// Study session variables
StudySession *studySession = nullptr;

// Menu items
// To add a menu item, add a declaration first here so they are recognised as a function.
void displayMenuOptions();
void startStudySession();
void endStudySession();
void addEventMenuItem();
void exitMenu();
void addPaperMenuItem();
void viewCalendarMenuItem();
void saveToFileMenu();
void loadFromFileMenu();
void calculateTotalStudyHoursMenuItem();

vector<MenuItem> menuItems = {
    // Add a MenuItem() here, linking to a pointer to the function that manages the item.
    // Do not include the parentheses as it is a pointer to a function.
    // When the user selects the item, it will execute the function.
    MenuItem("Display all menu options", displayMenuOptions),
    MenuItem("View calendar", viewCalendarMenuItem),
    MenuItem("Add event", addEventMenuItem),
    MenuItem("Add paper", addPaperMenuItem),
    MenuItem("Start study session", startStudySession),
    MenuItem("End study session", endStudySession),
    MenuItem("Save calendar to file", saveToFileMenu),
    MenuItem("Load calendar from file", loadFromFileMenu),
    MenuItem("Calculate Total Study Hours", calculateTotalStudyHoursMenuItem),
    MenuItem("Exit", exitMenu)};
void displayMenuOptions()
{
    clearScreen();
    // commented out to see build errors
    // clearScreen();
    cout << "\n\033[31m" // Red
            " ____  _             _         "
            "\033[33m____  _                             \033[0m\n"
            "\033[31m/ ___|| |_ _   _  __| |_   _  "
            "\033[33m|  _ \\| | __ _ _ __  _ __   ___ _ __ \033[0m\n"
            "\033[33m\\___ \\| __| | | |/ _` | | | | "
            "\033[32m| |_) | |/ _` | '_ \\| '_ \\ / _ \\ '__|\033[0m\n"
            "\033[32m ___) | |_| |_| | (_| | |_| | "
            "\033[34m|  __/| | (_| | | | | | | |  __/ |   \033[0m\n"
            "\033[34m|____/ \\__|\\__,_|\\__,_|\\__, | "
            "\033[35m|_|   |_|\\__,_|_| |_|_| |_|\\___|_|   \033[0m\n"
            "                       \033[35m|___/ \033[0m\n";

    cout << "\033[34m";

    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        cout << i + 1 << ". " << menuItems[i].getName() << "\n";
    }
    cout << "Enter a number: ";
}

void displayMenu()
{
    int input;
    string p = "";

    displayMenuOptions();

    while (running)
    {

        input = validate.getValidInteger(1, menuItems.size(), p);
        if (input >= 1 && input <= menuItems.size())
        {
            clearScreen();
            menuItems[input - 1].execute();
        }
        else
        {
            cout << "Invalid input. Please enter a number between 1 and " << menuItems.size() << "." << endl;
        }
    }

    if (running)
    {
        cout << "Press enter to go back to main menu.";
        cin.ignore();
        cin.get();
    }
}

int main()
{
    displayMenu();
    return 0;
}

void startStudySession()
{
    clearScreen();
    std::cout << "\n"
                 "  ____  _             _     ____  _             _         ____                _             \n"
                 " / ___|| |_ __ _ _ __| |_  / ___|| |_ _   _  __| |_   _  / ___|  ___  ___ ___(_) ___  _ __  \n"
                 " \\___ \\| __/ _` | '__| __| \\___ \\| __| | | |/ _` | | | | \\___ \\ / _ \\/ __/ __| |/ _ \\| '_ \\ \n"
                 "  ___) | || (_| | |  | |_   ___) | |_| |_| | (_| | |_| |  ___) |  __/\\__ \\__ \\ | (_) | | | |\n"
                 " |____/ \\__\\__,_|_|   \\__| |____/ \\__|\\__,_|\\__,_|\\__, | |____/ \\___||___/___/_|\\___/|_| |_|\n"
                 "                                                  |___/                                      \n";
    if (calendar->getPapers().empty())
    {
        string choicePrompt = "\nYou can't start a study sesion as no papers have been added yet. What would you like to do?\n1. Add a paper\n2. Return to main menu\n";
        int choice = validate.getValidInteger(1, 2, choicePrompt);

        switch (choice)
        {
        case 1:
            addPaperMenuItem();
            break;
        case 2:
            displayMenuOptions();
            break;
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            displayMenuOptions();
            break;
        }
    }
    else
    {
        // Start the study session
        if (studySession == nullptr)
        {
            string paperCode;
            int day, week;

            cout << "Available papers:\n";
            cout << left << setw(8) << "Code" << setw(50) << "Name" << "\n";
            cout << "-----------------------------------------------------";
            // displays paper codes by getting menu's vector<paper> papers
            for (auto &paper : calendar->getPapers())
            {
                cout << "\n"
                     << left << setw(8) << paper.getPaperCode() << setw(50) << paper.getPaperName() << endl;
            }
            cout << "\n-----------------------------------------------------\n";
            paperCode = validate.getValidPaperCode(calendar->getPapers());

            string dayPrompt = "Enter the day of the week (1-7): ";
            string weekPrompt = "Enter the week of the year (1-52): ";

            day = validate.getValidInteger(1, 7, dayPrompt);
            week = validate.getValidInteger(1, 52, weekPrompt);

            studySession = new StudySession(paperCode, day, week);
            studySession->startSession();
        }
        else
        {
            cout << "A study session is already in progress. Please end the current session before starting a new one." << endl;
        }
        cout << "Press 1 to display menu options" << endl;
    }
}

void endStudySession()
{
    clearScreen();
    std::cout << " _____           _   ____  _             _         ____                _             \n"
                 "| ____|_ __   __| | / ___|| |_ _   _  __| |_   _  / ___|  ___  ___ ___(_) ___  _ __ \n"
                 "|  _| | '_ \\ / _` | \\___ \\| __| | | |/ _` | | | | \\___ \\ / _ \\/ __/ __| |/ _ \\| '_ \\ \n"
                 "| |___| | | | (_| |  ___) | |_| |_| | (_| | |_| |  ___) |  __/\\__ \\__ \\ | (_) | | | |\n"
                 "|_____|_| |_|\\__,_| |____/ \\__|\\__,_|\\__,_|\\__, | |____/ \\___||___/___/_|\\___/|_| |_|\n"
                 "                                            |___/                                      \n";
    // End study session
    if (studySession != nullptr)
    {
        studySession->endSession();
        calendar->addEvent(*studySession);
        double duration = studySession->getDuration();
        cout << "Study session duration: " << duration << " seconds." << endl;

        // Now for cleanup
        delete studySession;    // Delete from memory
        studySession = nullptr; // Assign to null pointer.
    }
    else
    {
        // No study sessions are in progress so ask user to start one or return to menu
        string choicePrompt = "\nThere isn't a study session in progress. Would you like to begin one?\n1. Start study session\n2. Return to main menu\n";
        int choice = validate.getValidInteger(1, 2, choicePrompt);

        switch (choice)
        {
        case 1:
            startStudySession();
            break;
        case 2:
            displayMenuOptions();
            break;
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            displayMenuOptions();
            break;
        }
    }
}

void addEventMenuItem()
{
    clearScreen();
    std::cout << "\n"
                 "     _       _     _   _____                 _   \n"
                 "    / \\   __| | __| | | ____|_   _____ _ __ | |_ \n"
                 "   / _ \\ / _` |/ _` | |  _| \\ \\ / / _ \\ '_ \\| __|\n"
                 "  / ___ \\ (_| | (_| | | |___ \\ V /  __/ | | | |_ \n"
                 " /_/   \\_\\__,_|\\__,_| |_____| \\_/ \\___|_| |_|\\__|\n"
                 "                                                 \n";
    if (calendar->getPapers().empty())
    {
        string choicePrompt = "No papers have been added yet. What would you like to do?\n1. Add a paper\n2. Return to main menu\n";
        int choice = validate.getValidInteger(1, 2, choicePrompt);

        switch (choice)
        {
        case 1:
            addPaperMenuItem();
            break;
        case 2:
            // clearScreen();
            displayMenuOptions();
            break;
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            // clearScreen();
            displayMenuOptions();
            break;
        }
    }
    else
    {
        addNewEvent newEvent(calendar->getPapers(), calendar);
        newEvent.addNewEventMenu();
        cout << "Enter 1 to go back to the main menu" << endl;
    }
}
void addPaperMenuItem()
{
    clearScreen();
    std::cout << "\n"
                 "    _       _     _   ____                       \n"
                 "   / \\   __| | __| | |  _ \\ __ _ _ __   ___ _ __ \n"
                 "  / _ \\ / _` |/ _` | | |_) / _` | '_ \\ / _ \\ '__|\n"
                 " / ___ \\ (_| | (_| | |  __/ (_| | |_) |  __/ |   \n"
                 "/_/   \\_\\__,_|\\__,_| |_|   \\__,_| .__/ \\___|_|   \n"
                 "                                |_|               \n";

    addPaper newPaper(calendar->getPapers());
    newPaper.addPaperMenu();
    cout << "Enter 1 to go back to the main menu" << endl;
}

void exitMenu()
{
    // Exits the program.
    running = false;
    cout << "Exiting menu..." << endl;
}

void viewCalendarMenuItem()
{
    clearScreen();
    string choicePrompt = "Type the week you would like to display, or type 0 to display whole year\n";
    int choice = validate.getValidInteger(0, 52, choicePrompt);

    if (choice == 0)
    {
        calendar->display();
    }
    else
    {
        calendar->displayWeek(choice);
    }
    cout << "\nEnter 1 to go back to the main menu" << endl;
}

void saveToFileMenu()
{
    CalendarFile::saveToFile(*calendar, "calendar.txt");
    cout << "\nEnter 1 to go back to the main menu" << endl;
}
void loadFromFileMenu()
{
    CalendarFile::loadFromFile(*calendar, "calendar.txt");
    cout << "\nEnter 1 to go back to the main menu" << endl;
}

void calculateTotalStudyHoursMenuItem()
{
    clearScreen();
    std::cout << "\n"
              << "  _____             _        _____ _                _           _ \n"
              << " / ____|           | |      / ____| |              | |         | |\n"
              << "| |     ___  _ __  | |_ ___| |    | |__   ___  __ _| | ___  ___| |\n"
              << "| |    / _ \\| '__| | __/ _ \\ |    | '_ \\ / _ \\/ _` | |/ _ \\/ __| |\n"
              << "| |___| (_) | |    | ||  __/ |____| | | |  __/ (_| | |  __/ (__|_|\n"
              << " \\_____\\___/|_|     \\__\\___|\\_____|_| |_|\\___|\\__,_|_|\\___|\\___(_)\n"
              << "\n";

    if (calendar->getPapers().empty())
    {
        std::cout << "No papers available. Please add a paper first.\n";
        std::string choicePrompt = "Please enter 1 to go back to the main menu or 2 to exit the program.";
        int choice = validate.getValidInteger(1, 2, choicePrompt);
        if (choice == 1)
        {
            displayMenuOptions();
        }
        return;
    }

    // Display available papers
    std::cout << "Available Papers:\n";
    for (size_t i = 0; i < calendar->getPapers().size(); ++i)
    {
        std::cout << i + 1 << ". " << calendar->getPapers()[i].getPaperName()
                  << " (" << calendar->getPapers()[i].getPaperCode() << ")\n";
    }

    // Prompt user to select a paper
    string paperPrompt = "Select a paper by number: ";
    int paperChoice = validate.getValidInteger(1, calendar->getPapers().size(), paperPrompt);
    paper selectedPaper = calendar->getPapers()[paperChoice - 1];

    // Prompt user to enter the week number
    string weekPrompt = "Enter the week number (1-52) to calculate total study hours: ";
    int weekNumber = validate.getValidInteger(1, 52, weekPrompt);

    // Calculate total study hours
    double totalHours = selectedPaper.getTotalStudyHours(weekNumber);

    // Display the result
    std::cout << "\nTotal study hours for " << selectedPaper.getPaperName()
              << " in week " << weekNumber << ": " << totalHours << " hours.\n";

    int backChoice = validate.getValidInteger(1, 1, "Please enter 1 to go back to the main menu.");
    if (backChoice == 1)
    {
        displayMenuOptions();
    }
}