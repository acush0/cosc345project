#include <iostream>
#include <vector>
#include <string>
#include "Calendar.h"
#include "Event.h"
#include "AddEvent.h"
#include "paper.h"
#include "addPaper.h"
#include "eventSkeleton.h"
#include "addNewEvent.h"
#include <limits>
using namespace std;
// g++ -o menu menu.cpp
// ./menu

Calendar calendar = Calendar();
vector<paper> papers;
addPaper paperHandler = (papers);

void displayMenuOptions(){
    cout << "\n"
        " ____  _             _         ____  _                             \n"
        "/ ___|| |_ _   _  __| |_   _  |  _ \\| | __ _ _ __  _ __   ___ _ __ \n"
        "\\___ \\| __| | | |/ _` | | | | | |_) | |/ _` | '_ \\| '_ \\ / _ \\ '__|\n"
        " ___) | |_| |_| | (_| | |_| | |  __/| | (_| | | | | | | |  __/ |   \n"
        "|____/ \\__|\\__,_|\\__,_|\\__, | |_|   |_|\\__,_|_| |_|_| |_|\\___|_|   \n"
        "                       |___/                                        \n";
    cout << "1. Display papers\n";
    cout << "2. Display calendar\n";
    cout << "3. Add event\n";
    cout << "4. Start study session\n";
    cout << "5. Add paper\n";
    cout << "6. Exit\n";
}

void displayMenu()
{   
    bool running = true;
    int number;

    // basic switch statements using a boolean to control the loop
    while (running)
    {
        displayMenuOptions();
        cout << "Enter a number: ";

        if (cin >> number)
        {
            switch (number)
            {
                case 1: {
                    // display papers
                    cout << "Adding event" << endl;
                    // Event e = Event("test", 1, 2, 3, 4);
                    // calendar.addEvent(e);
                    
                    break;
                }
                case 2: {
                    // display calendar
                    break;
                }
                case 3: {
                    // add event
                    addNewEvent eventHandler(papers);
                    eventHandler.addNewEventMenu();

                    //AddEvent eventHandler; // Create an instance of AddEvent
                    //calendar.addEvent(eventHandler.AddEventMenu());
                    break;
                }
                case 4: {
                    //start study session
                    break;
                }
                case 5: {
                    paperHandler.addPaperMenu();

                    break;
                }
                case 6: {
                    //exit
                    running = false;
                    break;
                }
                default: {
                    cout << "Invalid input. Please enter an integer." << endl;
                   // cin.clear();                                                   // Clear error flags
                    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                }
            }
        }
        if(running){
            cout << "Press enter to go back to main menu";
            cin.ignore();
            cin.get();
        }
    }
}


int main()
{
    displayMenu();

    return 0;
}
