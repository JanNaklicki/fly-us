#include <iostream>
#include <stdlib.h>
#include "Interface.h"
#include "Database.h"
using namespace std;

int main(int argc, char **argv)
{
    Database database;
    Interface interface;
    while (true)
    {
        switch (interface.getCurrnetScreen())
        {
        case 0:
            interface.mainMenu();
            break;
        case 1:
            interface.searchFlight();
            break;
        case 2:
            interface.myTickets();
            break;
        case 3:
            interface.addNewFlight();
            break;
        case 4:
            interface.removeFlight();
            break;
        default:
            interface.mainMenu();
            break;
        }
    }
    // database.createDatabase();
    // database.createRecord("FLIGHT");
}