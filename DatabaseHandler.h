#ifndef DATABASEHANDLER_H_INCLUDE
#define DATABASEHANDLER_H_INCLUDE


void initalizeDatabase();
void createDB(const char* databaseName); // create a database
void createEmployeeTable(const char* databaseName); // create table to record employee information
void viewDatabase(const char* databaseName); // show all records in database
static int callback(void* NotUsed, int agrc, char** argv, char** azColName);
void insertEmployee(const char* databaseName, int employeeID, const char* firstName, const char* lastName, const char* password);
bool searchForEmployee(const char* databaseName, int employeeID, const char* password);
void setFirstName(const char* databaseName, int id, const char* password, const char* newFirstName);
void setLastName(const char* databaseName, int id, const char* password, const char* newLastName);
void setPayRate(const char* databaseName, int id, const char* password, float newPayRate);
void setId(const char* databaseName, int id, const char* password, int newId);
void setPassword(const char* databaseName, int id, const char* password, const char* newPassword);
void deleteEmployee(const char* databaseName, int id);

#endif // !DATABASEHANDLER_H_INCLUDE;
