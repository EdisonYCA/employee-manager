#include <iostream>
#include "DatabaseHandler.h"
#include "sqlite/sqlite3.h"
#include <string>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

void createDB(const char* databaseName); // create a database
void createPunchTable(const char* databaseName); // create table to record punch ins
void createEmployeeTable(const char* databaseName); // create table to record employee information
void viewDatabase(const char* databaseName); // show all records in database
static int callback(void* NotUsed, int agrc, char** argv, char** azColName);
// void insertData(const char* databaseName); // insert data into database
void insertEmployee(const char* databaseName, int employeeID, const char* firstName, const char* lastName, const char* password);
void insertDummyData(const char* databaseName);
bool searchForEmployee(const char* databaseName, int employeeID, const char* password);
void setFirstName(const char* databaseName, int id, const char* password, const char* newFirstName);
void setLastName(const char* databaseName, int id, const char* password, const char* newLastName);
void setPayRate(const char* databaseName, int id, const char* password, float newPayRate);
void setId(const char* databaseName, int id, const char* password, int newId);
void setPassword(const char* databaseName, int id, const char* password, const char* newPassword);
void deleteEmployee(const char* databaseName, int id);
void storePunchIn(const char* databaseName);
void checkPayPeriod(string payPeriodEnd);
string formatMonth(int month);
string formatDay(int day);

string payPeriodEnd = "2023-01-26";

int main() {
    checkPayPeriod(payPeriodEnd);
    return 0;
}

void initalizeDatabase()
{
    createDB("PunchesDB.db");
    createPunchTable("PunchesDB.db");
    createEmployeeTable("PunchesDB.db");
    //viewDatabase("PunchesDB");
}

void createDB(const char* databaseName) {
    sqlite3* db;

    sqlite3_open( // create database if DNE
        databaseName,
        &db
    );

    sqlite3_close(db);
}

void createPunchTable(const char* databaseName) {
    sqlite3* db;

    string query = "CREATE TABLE IF NOT EXISTS PUNCHES("
        "Id INTEGER, "
        "PunchDate TEXT, "
        "InTime TEXT, "
        "OutTime TEXT, "
        "Hours FLOAT, "
        "PayPeriodStart TEXT, "
        "PayPeriodEnd TEXT, "
        "FOREIGN KEY(Id) REFERENCES EMPLOYEES(Id));";

    sqlite3_open(databaseName, &db);

    char* err;
    int result = sqlite3_exec(db,
        query.c_str(),
        NULL,
        NULL,
        &err);

    if (result != SQLITE_OK) {
        cout << "Error while create punch table: " << err << endl;
    }

    sqlite3_close(db);
}

void createEmployeeTable(const char* databaseName) {
    sqlite3* db;

    string query = "CREATE TABLE IF NOT EXISTS EMPLOYEES("
        "Id INTEGER PRIMARY KEY, "
        "FirstName TEXT, "
        "LastName TEXT, "
        "PayRate FLOAT DEFAULT 15.00, "
        "Password TEXT);";

    sqlite3_open(databaseName, &db);

    char* err;
    int result = sqlite3_exec(db,
        query.c_str(),
        NULL,
        NULL,
        &err);

    if (result != SQLITE_OK) {
        cout << "Error while create employees table: " << err << endl;
    }

    sqlite3_close(db);
}

void viewDatabase(const char* databaseName) {

    sqlite3* db;

    string query = "SELECT * FROM EMPLOYEES";

    sqlite3_open(databaseName, &db);

    char* err;
    int result = sqlite3_exec(db, query.c_str(), callback, NULL, &err);

    if (result != SQLITE_OK) {
        cout << "Error selecting data: " << err << endl;
    }
    sqlite3_close(db);
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}

void insertEmployee(const char* databaseName, int employeeID, const char* firstName, const char* lastName, const char* password) {
    sqlite3* db;

    sqlite3_open(databaseName, &db);

    string query = string("INSERT INTO EMPLOYEES(Id, FirstName, LastName, Password) VALUES(") + to_string(employeeID) +"," + "\"" +
        string(firstName) + "\"," + "\"" + string(lastName) + "\"," + "\"" + string(password) + "\"" + ");";

    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error inserting employee into database: " << err << endl;
    }
    else {
        cout << "Employee information succesfully stored!" << endl;
    }
}

void insertDummyData(const char* databaseName) {
    sqlite3* db;

    sqlite3_open(databaseName, &db);

    string query = "INSERT INTO PUNCHES(Id) VALUES(12345);";

    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error inserting dummy data into punches: " << err << endl;
    }
    else {
        cout << "Dummy Data Succesfully Stored!" << endl;
    }
}

bool searchForEmployee(const char* databaseName, int employeeID, const char* password) {
    sqlite3* db;

    string query = "SELECT Id, FirstName, LastName, PayRate, Password FROM EMPLOYEES WHERE Id = " +
        to_string(employeeID) + " AND Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);

    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);

    if (result != SQLITE_OK) {
        cout << "Error: " << err;
        return false;
    }
    else {
        cout << "Logged In Succesfully!" << endl;
        return true;
    }

    sqlite3_close(db);
}

void setFirstName(const char* databaseName, int id, const char *password, const char *newFirstName) {
    sqlite3* db;

    string query = string("UPDATE EMPLOYEES SET FirstName = ") + "\"" + string(newFirstName) + "\"" + " WHERE Id = " 
        + to_string(id) + " AND " + "Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error setting first name: " << err << endl;
    }
    else {
        cout << "Updated first name succesfully!" << endl;
    }
}

void setLastName(const char* databaseName, int id, const char* password, const char* newLastName) {
    sqlite3* db;

    string query = string("UPDATE EMPLOYEES SET LastName = ") + "\"" + string(newLastName) + "\"" + " WHERE Id = "
        + to_string(id) + " AND " + "Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error setting last name: " << err << endl;
    }
    else {
        cout << "Updated last name succesfully!" << endl;
    }
}

void setPayRate(const char* databaseName, int id, const char* password, float newPayRate) {
    sqlite3* db;

    string query = string("UPDATE EMPLOYEES SET PayRate = ") + "\"" + to_string(newPayRate) + "\"" + " WHERE Id = "
        + to_string(id) + " AND " + "Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error setting pay rate: " << err << endl;
    }
    else {
        cout << "Updated pay rate succesfully!" << endl;
    }
}

void setId(const char* databaseName, int id, const char* password, int newId) {
    sqlite3* db;

    string query = string("UPDATE EMPLOYEES SET Id = ") + "\"" + to_string(newId) + "\"" + " WHERE Id = "
        + to_string(id) + " AND " + "Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error setting id: " << err << endl;
    }
    else {
        cout << "Updated id succesfully!" << endl;
    }
}

void setPassword(const char* databaseName, int id, const char* password, const char* newPassword) {
    sqlite3* db;

    string query = string("UPDATE EMPLOYEES SET Password = ") + "\"" + string(newPassword) + "\"" + " WHERE Id = "
        + to_string(id) + " AND " + "Password = " + "\"" + string(password) + "\"";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error setting password: " << err << endl;
    }
    else {
        cout << "Updated password succesfully!" << endl;
    }
}

void deleteEmployee(const char* databaseName, int id) {
    sqlite3* db;

    string query = "DELETE FROM EMPLOYEES WHERE Id = " + to_string(id);

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error deleting employee: " << err << endl;
    }
    else {
        cout << "Deleted employee successfully!" << endl;
    }
}

void storePunchIn(const char* databaseName) {
    // store todays date, and format it into YYYY-MM-DD
    time_t now = time(NULL);
    struct tm nowLocal;

    nowLocal = *localtime(&now);

    string date;
    string timeIn;

    date += to_string(nowLocal.tm_year + 1900) + "-";
    date += formatMonth(nowLocal.tm_mon + 1) + "-";
    date += formatDay(nowLocal.tm_mday);
    timeIn += to_string(nowLocal.tm_hour) + ":";
    timeIn += to_string(nowLocal.tm_min) + ":";
    timeIn += to_string(nowLocal.tm_sec);

    // make query
    sqlite3* db;

    string query = string("INSERT INTO PUNCHES(PunchDate, InTime) VALUES(") + "\"" + date + "\", " + "\"" + timeIn + "\"" + ");";

    sqlite3_open(databaseName, &db);
    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error punching in: " << err << endl;
    }
    else {
        cout << "Punched in" << endl;
    }
}

string formatMonth(int month) {
    if (month < 10) {
        return string("0" + to_string(month));
    }
    else {
        return to_string(month);
    }
}

string formatDay(int day) {
    if (day < 10) {
        return string("0" + to_string(day));
    }
    else {
        return to_string(day);
    }
}

void checkPayPeriod(string payPeriodEnd) {
    time_t now = time(NULL);
    struct tm nowLocal;

    nowLocal = *localtime(&now);

    string date;

    date += to_string(nowLocal.tm_year + 1900) + "-";
    date += formatMonth(nowLocal.tm_mon + 1) + "-";
    date += formatDay(nowLocal.tm_mday);

    if (payPeriodEnd == date) {
        cout << "Today is the end of the pay period";

        string newPayPeriod;
        date += to_string(nowLocal.tm_year + 1900) + "-";
        date += formatMonth(nowLocal.tm_mon + 1) + "-";
        date += formatDay(nowLocal.tm_mday);
    }
}

