#include <iostream>
#include <iomanip>
using namespace std;

void displayDefaultMenu(); // display default menu interface
void handleDefaultMenu(int response); // perform action based on response from menu interface
void displayLoginUI(); // display login menu

int main() {

	for (int i = 0; i < 5; i++) {
		displayLoginUI();
		displayDefaultMenu();
	}

	return 0;
}

void displayDefaultMenu() {
	int response = 0; 
	
	while (response != 4) {
		cout << "Enter a valid digit from the menu below." << endl;
		cout << setw(41) << "1. \"View hours worked this pay period\"" << endl;
		cout << setw(41) << "2. \"View estimate pay this pay period\"" << endl;
		cout << setw(13) << "3. \"Punch\"" << endl;
		cout << setw(12) << "4. \"Quit\"" << endl;
		cout << "-> ";
		cin >> response;

		handleDefaultMenu(response);
		cout << endl;
	}

}

void handleDefaultMenu(int response) {
	switch (response) {
		case 1:
			break;
			// call getter func
		case 2:
			break;
			// call getter func
		case 3:
			break;
			// call db func
	}
	
	return; 
}

void displayLoginUI() {
	int id;
	string password, confirmPassword;

	cout << "Enter ID: ";
	cin >> id;
	cout << "Enter password: ";
	cin >> password;
	cout << "Confirm Password: ";
	cin >> confirmPassword;
	cout << "log in successful" << endl;
	cout << endl;
}
