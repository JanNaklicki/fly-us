#pragma once
#include <stdlib.h>
#include <iostream>
#include "Database.h"

using namespace std;

class Interface
{
private:
    int currentScreen = 0;
    string query;
    Database database;

public:
    int getCurrnetScreen();
    // UI elements
    void displayInterface(string content);
    void displayHeader(string content);
    void displaySpacer(string above, string below);
    // Pages
    void mainMenu();
    void searchFlight();
    void myTickets();
    void addNewFlight();
    void removeFlight();
};
