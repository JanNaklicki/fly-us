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
    static int displayFlights(void *data, int argc, char **argv, char **azColName);
    static int displayTickets(void *data, int argc, char **argv, char **azColName);

public:
    static string queryForDisplay;
    void createDatabase();
    static int callback(void *ptr, int argc, char **argv, char **azColName);
    void createRecord(string tableName);
    void queryFlights();
    void queryTickets(string name, string surname);
    void insertTicket(string values);
    void insertFlight(string values);
    void removeFlight(string value);
    string generateRandomSeat();
    string appendNewValue(string values, bool last, bool date);
};
