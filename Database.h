#pragma once
#include <sqlite3.h>
#include <random>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Database
{
private:
    sqlite3 *DB;
    int exit = sqlite3_open("FlyUs.sqlite", &DB);
    char *messaggeError;
    static string selectedTable;
    //Database callbacks
    static int displayFlights(void *data, int argc, char **argv, char **azColName);
    static int displayTickets(void *data, int argc, char **argv, char **azColName);

public:
    static string queryForDisplay;
    void createDatabase();
    void queryFlights();
    void queryTickets(string name, string surname);
    void insertTicket(string values);
    void insertFlight(string values);
    void removeFlight(string value);
    // Helpers
    string generateRandomSeat();
    string appendNewValue(string values, bool last, bool date);
};
