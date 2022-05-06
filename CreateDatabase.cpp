#include <iostream>
#include <sqlite3.h>
using namespace std;

int main(int argc, char **argv)
{

    sqlite3 *DB;
    string flight = "CREATE TABLE FLIGHT("
                    "ID INT PRIMARY KEY NOT NULL, "
                    "AIRPLANE_ID INT NOT NULL, "
                    "AIRPORT_START_ID TEXT NOT NULL, "
                    "AIRPORT_DESTINATION_ID TEXT NOT NULL, "
                    "TAKEOFF_DATE DATETIME NOT NULL, "
                    "ARRIVAL_DATE DATETIME NOT NULL ); ";

    string plane = "CREATE TABLE PLANE("
                   "ID INT PRIMARY KEY NOT NULL, "
                   "NAME TEXT NOT NULL, "
                   "PILOT_ID INT NOT NULL, "
                   "SEATS INT NOT NULL ); ";

    string person = "CREATE TABLE PERSON("
                    "ID INT PRIMARY KEY NOT NULL, "
                    "NAME TEXT NOT NULL, "
                    "SURNAME TEXT NOT NULL, "
                    "AGE INT NOT NULL ); ";

    string ticket = "CREATE TABLE TICKET("
                    "ID INT PRIMARY KEY NOT NULL, "
                    "PASSAGER_ID INT NOT NULL, "
                    "SEAT INT NOT NULL, "
                    "CLASS INT NOT NULL, "
                    "CASHIER_ID INT NOT NULL ); ";

    string airport = "CREATE TABLE AIRPORT("
                     "ID INT PRIMARY KEY NOT NULL, "
                     "RUNWAY TEXT NOT NULL, "
                     "CITY TEXT NOT NULL ); ";

    int exit = 0;
    exit = sqlite3_open("FlyUs.sqlite", &DB);
    char *messaggeError;
    exit = sqlite3_exec(DB, flight.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, plane.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, person.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, ticket.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, airport.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Tables created Successfully" << endl;
    sqlite3_close(DB);
    return (0);
}