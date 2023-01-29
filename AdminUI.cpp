#include <iomanip>
#include "AdminUIBackend.h"
#include "DatabaseHandler.h"
#include <iostream>
using namespace std;

// function def'n
int displayDefaultMenu(); // interface for default menu
void handleDefaultMenu(int response); // handle responses from default menu
void displaySignUpMenu(); // display employee sign up interface
void displaySignInMenu(int id, string password); // display employee sign in interface
void deleteEmployeeUI(); // interface for deleting an employee
void loginUI(); // interface for logining into a user account
void handleResponseFromSignIn(int response, int id, string password); // handle responses from sign in menu

int main() {
	int responseDefaultMenu = 0; // user response from default menu

	while (responseDefaultMenu != 4) { // while user hasn't quit
		responseDefaultMenu = displayDefaultMenu();
		handleDefaultMenu(responseDefaultMenu);
		cout << endl;
	}

	return 0;
}

int displayDefaultMenu() {
	int res;
	cout << "Enter a valid menu digit from below." << endl;
	cout << setw(15) << "1. \"Sign Up\"" << endl;
	cout << setw(15) << "2. \"Sign In\"" << endl;
	cout << setw(23) << "3. \"Delete Employee\"" << endl;
	cout << setw(12) << "4. \"Quit\"" << endl;
	cout << "-> ";
	cin >> res;

	if (!cin) {
		cout << "Please a valid response. "<< endl;
		cout << "Ending program..." << endl;
		return 4;
	}
	else if (res > 4 || res < 1){
		cout << "Please only enter integer's that are a menu option." << endl;
		return res;
	}
	
	return res;
}

void handleDefaultMenu(int response) {
	switch (response) {
	case 1:
		displaySignUpMenu();
		break;
	case 2:
		loginUI();
		break;
	case 3:
		deleteEmployeeUI();
		break;
	}
	return;
}

void displaySignInMenu(int id, string password) {

	int responseFromSignIn = 0;
	while (responseFromSignIn != 6) {
		cout << "Enter a valid menu digit from below." << endl;
		cout << setw(34) << "1. \"Update employee's pay rate\"" << endl;
		cout << setw(36) << "2. \"Update employee's first name\"" << endl;
		cout << setw(35) << "3. \"Update employee's last name\"" << endl;
		cout << setw(28) << "4. \"Update employee's ID\"" << endl;
		cout << setw(34) << "5. \"Update employee's password\"" << endl;
		cout << setw(12) << "6. \"Quit\"" << endl;
		cout << "-> ";
		cin >> responseFromSignIn;

		if (!cin) {
			cout << "Please a valid response." << endl;
			cout << "Ending program..." << endl;
			exit(0);
		}
		else {
			handleResponseFromSignIn(responseFromSignIn, id, password);
			cout << endl;
		}
	}
}

void displaySignUpMenu() {
	string firstName, lastName, password, confirmPassword;
	bool inputValidated = true;

	while (true) {
		cout << "\n" << "Enter valid employee information below." << endl;
		cout << endl;
		cout << "Enter employee's first name: ";
		cin >> firstName;

		if (!validateFirstName(firstName.c_str())) {
			inputValidated = false;
			break;
		}

		cout << "Enter employee's last name: ";
		cin >> lastName;

		if (!validateLastName(lastName.c_str())) {
			inputValidated = false;
			break;
		}
		
		cout << "Enter a password: ";
		cin >> password;
		cout << "Confirm password: ";
		cin >> confirmPassword;

		if (!validatePassword(password.c_str(), confirmPassword.c_str())) {
			inputValidated = false;
			break;
		}

		if (inputValidated) {
			initalizeDatabase();
			insertEmployee("PunchesDB.db", 12345, firstName.c_str(), lastName.c_str(), password.c_str());
			cout << firstName << "'s ID: " << endl;
			break;
		}
	}
}

void deleteEmployeeUI() {
	int id;
	cout << endl;
	cout << "Enter ID: ";
	cin >> id;

	string confirm;
	cout << "Are you sure you want to remove this from database [y/n]: ";
	cin >> confirm;
	
	if (confirm == "y") {
		deleteEmployee("PunchesDB.db", id);
	}

	return;
}

void loginUI() {
	int id;
	string password;
	bool searchForEmployeeRes = false;

	cout << "Enter a valid ID and password below." << endl;

	while (!searchForEmployeeRes) {
		cout << endl;
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter password: ";
		cin >> password;
		searchForEmployeeRes = searchForEmployee("PunchesDB.db", id, password.c_str());
	}

	displaySignInMenu(id, password);
}

void handleResponseFromSignIn(int res, int id, string password) {
	switch (res) {
	case 1:
	{
		float payRate;
		cout << "Enter updated pay rate: ";
		cin >> payRate;

		if (!cin) {
			cout << "Please enter a valid response." << endl;
			exit(0);
		}
		else {
			setPayRate("PunchesDB.db", id, password.c_str(), payRate);
			break;
		}
	}

	case 2:
	{
		string firstName;
		cout << "Enter updated first name: ";
		cin >> firstName;

		if (!cin) {
			cout << "Please enter a valid response." << endl;
			exit(0);
		}
		else {
			setFirstName("PunchesDB.db", id, password.c_str(), firstName.c_str());
			break;
		}
	}
	case 3:
	{
		string lastName;
		cout << "Enter updated last name: ";
		cin >> lastName;

		if (!cin) {
			cout << "Please enter a valid response." << endl;
			exit(0);
		}
		else {
			setLastName("PunchesDB.db", id, password.c_str(), lastName.c_str());
			break;
		}
	}

	case 4:
	{
		int newId;
		cout << "Enter updated id: ";
		cin >> newId;

		if (!cin) {
			cout << "Please enter a valid response." << endl;
			exit(0);
		}
		else {
			setId("PunchesDB.db", id, password.c_str(), newId);
			break;
		}
	}
	case 5:
	{
		string password;
		cout << "Enter updated password: ";
		cin >> password;

		if (!cin) {
			cout << "Please enter a valid response." << endl;
			exit(0);
		}
		else {
			setPassword("PunchesDB.db", id, password.c_str(), password.c_str());
			break;
		}
	}

	case 6:
	{
		break;
	}
	default:
	{
		cout << "Please only enter integer's that are a menu option." << endl;
		cout << endl;
	}
	}
}