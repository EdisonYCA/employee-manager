#ifndef DATABASEHANDLER_H_INCLUDE
#define DATABASEHANDLER_H_INCLUDE


void initalizeDatabase();
void createDB(const char* databaseName); // create a database
void createPunchTable(const char* databaseName); // create table to record punch ins
void createEmployeeTable(const char* databaseName); // create table to record employee information
void viewDatabase(const char* databaseName); // show all records in database
static int callback(void* NotUsed, int agrc, char** argv, char** azColName);
void insertData(const char* databaseName); // insert data into database
void insertEmployee(const char* databaseName, const char* firstName, const char* lastName, const char* password);




#endif // !DATABASEHANDLER_H_INCLUDE;
