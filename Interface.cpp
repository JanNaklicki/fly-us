#include "Interface.h"

// UI
void Interface::displayInterface(string content)
{
    system("clear");
    cout << "--------------\n";
    cout << content;
    cout << "\n\n> 0. Main menu\n";
    cout << "--------------\n";
    cin >> currentScreen;
}
void Interface::displayHeader(string content)
{
    system("clear");
    cout << "\n-------------\n";
    cout << content;
    cout << "\n--------------\n";
}
void Interface::displaySpacer(string above, string below)
{
    if (above != "")
    {
        cout << '\n' + above + '\n';
    }
    cout << "--------------";
    if (below != "")
    {
        cout << '\n' + below;
    }
}
// Screens
void Interface::mainMenu()
{
    string content = "  User panel\n\n"
                     "1. Buy tickets\n"
                     "2. My tickets\n\n\n"
                     "  Admin panel\n\n"
                     "3. Add new flight\n"
                     "4. Remove flight\n";
    displayInterface(content);
}
void Interface::searchFlight()
{
    string selectedFlight;
    string selectedClass;
    string values = "";
    string input;

    displayHeader("Choose flight");
    displayHeader("FLIGHT\tSOURCE\tDEST\tDEPARTURE\t\tARRIVAL");
    database.queryFlights();
    displaySpacer("Do you want to buy a ticket?","\n");
    cin >> input; 
    if (input == "n" || input == "N")
    {
        currentScreen = 0;
        return;
    }
    displaySpacer("", "Select: ");
    values = database.appendNewValue(values, false, false);

    displayHeader("Choose class (1 or 2)");
    values = database.appendNewValue(values, false, false);

    displayHeader("First name");
    values = database.appendNewValue(values, false, false);

    displayHeader("Surname");
    values = database.appendNewValue(values, false, false);
    values += database.generateRandomSeat();

    displayHeader("Do you accept purchase? (Y/n)"
                  "\n\nFLIGHT\tCLASS\tNAME\tSURNAME\tSEAT\n\n" +
                  database.queryForDisplay);
    cin >> input;
    if (input == "y" || input == "Y")
    {
        database.insertTicket(values);
        displayHeader("Thanks for purchase! (To continue enter 1)");
        cin >> input;
    }
    currentScreen = 0;
}
void Interface::myTickets()
{
    string name;
    string surname;
    string input;
    displayHeader("Input your name");
    cin >> name;
    displayHeader("Input your surname");
    cin >> surname;
    displayHeader("\n\nSOURCE\tDEST\tDEPA\t\t\tARRIVAL\t\t\tNAME\tSURNAME\t\tCLASS\tSEAT\n\n");
    database.queryTickets(name, surname);
    displaySpacer("\n> 0. Main menu\n", "\n");
    cin >> input;
    currentScreen = 0;
}
void Interface::addNewFlight()
{
    string values = "";
    displayHeader("Enter short code of takeoff airport");
    values = database.appendNewValue(values, false, false);

    displayHeader("Enter short code of destination airport");
    values = database.appendNewValue(values, false, false);

    displayHeader("Enter take off date (yyyy-mm-dd_hh:mm separated with '_')");
    values = database.appendNewValue(values, false, true);

    displayHeader("Enter arrival date (yyyy-mm-dd hh:mm separated with '_')");
    values = database.appendNewValue(values, true, true);

    database.insertFlight(values);
    displayHeader("Done (To continue enter 1)");
    cin >> values;
    currentScreen = 0;
}
void Interface::removeFlight()
{
    string input;
    displayHeader("Are you sure you want to delete flight? Y/n");
    cin >> input;
    if (input == "n" || input == "N")
    {
        currentScreen = 0;
        return;
    }
    displayHeader("FLIGHT\tSOURCE\tDEST\tDEPARTURE\t\tARRIVAL");
    database.queryFlights();
    displaySpacer("", "Choose flight you want to remove:\nTo cancel enter -1\n");
    cin >> input;
    database.removeFlight(input);
    if (input == "-1")
    {
        currentScreen = 0;
        return;
    }
    displayHeader("Flight removed (To continue enter 1)");
    cin >> input;
    currentScreen = 0;
}