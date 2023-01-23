#include <iostream>
#include "DatabaseHandler.h"
#include "sqlite/sqlite3.h"
using namespace std;

void createDB(const char* databaseName); // create a database
void createPunchTable(const char* databaseName); // create table to record punch ins
void createInfoTable(const char* databaseName); // create table to record employee information
void viewDatabase(const char* databaseName); // show all records in database
static int callback(void* NotUsed, int agrc, char** argv, char** azColName);
void insertData(const char* databaseName); // insert data into database
void insertEmployee(const char* databaseName, const char* firstName, const char* lastName, const char* password);


/*
int main(int argc, char* argv[])

{
    createDB("PunchesDB");
    createPunchTable("PunchesDB");
    createInfoTable("PunchesDB");
    //insertData("PunchesDB");
    //viewDatabase("PunchesDB");

    return 0;

}
*/

void createDB(const char* databaseName) {
    sqlite3* db;

    sqlite3_open( // create database if DNE
        databaseName,
        &db
    );

    sqlite3_close(db);
}

void createPunchTable(const char* databaseName) {
    sqlite3 *db;

    string query = "CREATE TABLE IF NOT EXISTS PUNCHES("
        "Id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "PunchDate DATE, " 
        "InTime TIME, " 
        "OutTime TIME, " 
        "Hours FLOAT, "
        "PayPeriodStart DATE, "
        "PayPeriodEnd DATE);";

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
   else {
       cout << "Punch table created succesfully!" << endl;
   }
        
   sqlite3_close(db);
}

void createInfoTable(const char* databaseName) {
    sqlite3* db;

    string query = "CREATE TABLE IF NOT EXISTS EMPLOYEES("
        "Id INTEGER, "
        "FirstName TEXT, "
        "LastName TEXT, "
        "PayRate FLOAT DEFAULT 15.00, "
        "Password TEXT, "
        "FOREIGN KEY(Id) REFERENCES EMPLOYEES(Id));";

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
    else {
        cout << "Employee table created succesfully!" << endl;
    }

    sqlite3_close(db);
}

void viewDatabase(const char* databaseName) {
    
    sqlite3* db;

    string query = "SELECT * FROM PUNCHES";


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

void insertEmployee(const char* databaseName, const char* firstName, const char* lastName, const char* password){
    sqlite3* db;

    sqlite3_open(databaseName, &db);

    string query = string("INSERT INTO EMPLOYEES(FirstName, LastName, Password) VALUES(") + "\"" +
        firstName + "\"," + "\"" + lastName + "\"," + "\"" + password + "\"" + ");";

    char* err;
    int result = sqlite3_exec(db, query.c_str(), NULL, 0, &err);

    if (result != SQLITE_OK) {
        cout << "Error inserting employee into database: " << err << endl;
    }
    else {
        cout << "Data inserted!" << endl;
    }
}



