#include <iomanip>
#include "AdminUIBackend.h"
#include "DatabaseHandler.h"
#include <iostream>
using namespace std;

// function def'n
int displayDefaultMenu(); // interface for default menu
void handleDefaultMenu(int response); // handle responses from default menu
void displaySignUpMenu(); // display employee sign up interface
void displaySignInMenu(); // display employee sign in interface
void deleteEmployeeUI(); // interface for deleting an employee
void loginUI(); // interface for logining into a user account
void handleResponseFromSignIn(int response); // handle responses from sign in menu



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
	// handle invalid input responses
	int res;
	cout << "Enter a valid menu digit from below." << endl;
	cout << setw(15) << "1. \"Sign Up\"" << endl;
	cout << setw(15) << "2. \"Sign In\"" << endl;
	cout << setw(23) << "3. \"Delete Employee\"" << endl;
	cout << setw(12) << "4. \"Quit\"" << endl;
	cout << "-> ";
	cin >> res;
	return res;

	//while (true) {
		//try {
			//if (!isdigit(res)) {
				//throw "Invalid menu option.";
				//if(floor(int(res)) < 1 or floor(int(res)) > 4) {
					//throw "Invalid menu option.";
				//}
			//}
			//else {
				//return res;
			//}
		//}
		//catch (const char* e) {
		//	cout << e << " Please try again.\n" << endl;
		//}
	//}
}

void handleDefaultMenu(int response) {
	switch (response) {
	case 1:
		displaySignUpMenu();
		break;
	case 2:
		displaySignInMenu();
		break;
	case 3:
		deleteEmployeeUI();
		break;
	}
	return;
}

void displaySignInMenu() {
	loginUI(); // if login ui is true

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

		handleResponseFromSignIn(responseFromSignIn);
		cout << endl;
	}
}

void displaySignUpMenu() {
	string firstName = " ", lastName = " ", password = "!", confirmPassword = ".";

	while (!validateFirstName(firstName.c_str()) || !validateLastName(lastName.c_str())
		|| !validatePassword(password.c_str(), confirmPassword.c_str())) {
		cout << "\n" << "Enter valid employee information below." << endl;
		cout << endl;
		cout << "Enter employee's first name: ";
		cin >> firstName;
		cout << "Enter employee's last name: ";
		cin >> lastName;
		cout << "Enter a password: ";
		cin >> password;
		cout << "Confirm password: ";
		cin >> confirmPassword;
	}

	initalizeDatabase();
	insertEmployee("PunchesDB.db", generateID(), firstName.c_str(), lastName.c_str(), password.c_str());
	cout << firstName << "'s ID: " << endl;
}



void deleteEmployeeUI() {
	int id;
	cout << endl;
	cout << "Enter ID: ";
	cin >> id;

	// validate ID
	string confirm;
	cout << "Are you sure you want to remove [employee name] from database [y/n]: ";
	cin >> confirm;
	// delete employee
	cout << "operation successful" << endl;
}

void loginUI() {
	int id;
	string password;

	cout << endl;
	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter password: ";
	cin >> password;
	// validate credentials BE func
	cout << "log in successful" << endl;
	cout << endl;
}

void handleResponseFromSignIn(int res) {
	return;
	// user object setters for case handling
}