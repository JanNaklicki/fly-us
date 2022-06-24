#include "Database.h"

string Database::selectedTable;
string Database::queryForDisplay;
void Database::createDatabase()
{
    // -- SQLite
    //    INSERT INTO FLIGHT (AIRPORT_START_ID, AIRPORT_DESTINATION_ID, TAKEOFF_DATE, ARRIVAL_DATE)
    //  VALUES ( "GDN", "LON", "2020-11-17 15:00", "2020-11-1 18:10");
    string flight = "CREATE TABLE FLIGHT("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "AIRPORT_START_ID TEXT NOT NULL, "
                    "AIRPORT_DESTINATION_ID TEXT NOT NULL, "
                    "TAKEOFF_DATE TEXT NOT NULL, "
                    "ARRIVAL_DATE TEXT NOT NULL ); ";

    string ticket = "CREATE TABLE TICKET("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "FLIGHT_ID TEXT NOT NULL, "
                    "NAME TEXT NOT NULL, "
                    "SURNAME TEXT NOT NULL, "
                    "SEAT INT NOT NULL, "
                    "CLASS TEXT NOT NULL); ";

    exit = sqlite3_exec(DB, flight.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, ticket.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Tables created Successfully" << endl;
    sqlite3_close(DB);
}
void Database::queryFlights()
{
    string query = "SELECT * FROM FLIGHT;";
    exit = sqlite3_exec(DB, query.c_str(), displayFlights, 0, &messaggeError);
}
void Database::queryTickets(string name, string surname)
{
    string query = "SELECT FLIGHT.AIRPORT_START_ID, FLIGHT.AIRPORT_DESTINATION_ID, FLIGHT.TAKEOFF_DATE, FLIGHT.ARRIVAL_DATE, TICKET.NAME, TICKET.SURNAME, TICKET.CLASS, TICKET.SEAT "
                   "FROM TICKET "
                   "INNER JOIN FLIGHT ON FLIGHT.ID=TICKET.FLIGHT_ID "
                   "WHERE TICKET.NAME LIKE '" +
                   name + "' AND TICKET.SURNAME LIKE '" + surname + "';";
    exit = sqlite3_exec(DB, query.c_str(), displayTickets, 0, &messaggeError);
}
int Database::displayFlights(void *data, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << "\t";
    }
    cout << '\n';
    return 0;
}
int Database::displayTickets(void *data, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << "\t";
    }
    cout << '\n';
    return 0;
}
void Database::insertTicket(string values)
{
    string query = "INSERT INTO TICKET (FLIGHT_ID, CLASS, NAME, SURNAME, SEAT) VALUES (" + values + ");";
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
}
void Database::insertFlight(string values)
{
    string query = "INSERT INTO FLIGHT (AIRPORT_START_ID, AIRPORT_DESTINATION_ID, TAKEOFF_DATE, ARRIVAL_DATE) VALUES (" + values + ");";
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
}
void Database::removeFlight(string ID)
{
    if (ID != "-1")
    {
        string query = "DELETE FROM FLIGHT WHERE ID = " + ID+";";
        exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    }
}
string Database::generateRandomSeat()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(1, 800);
    queryForDisplay += '\t' + to_string(dist6(rng));
    return to_string(dist6(rng));
}
string Database::appendNewValue(string values, bool last, bool date)
{
    string input = "";
    cin >> input;
    if (date)
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '_')
            {
                input[i] = ' ';
            }
        }
    }
    if (last)
    {
        queryForDisplay = queryForDisplay + '\t';
        return values + "'" + input + "'";
    }
    else if (values == "")
    {
        queryForDisplay = input;
        return "'" + input + "'" + ", ";
    }
    else
    {
        queryForDisplay = queryForDisplay + '\t' + input;
        return values + "'" + input + "'" + ", ";
    }
}
