#include <string>
#include <vector>
#include "paper.h"
#pragma once

using namespace std;

class addNewEvent{
private:
    vector<paper>& papers;

public:
    addNewEvent(vector<paper>& papers);
    
    void addNewEventMenu();
};