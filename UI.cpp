#include <iostream>
using namespace std;

int main() {
	int ID;

	cout << "Loading E Punch Manager...\n" << endl;
	cout << "Enter ID: ";
	cin >> ID;
	// validate ID func
	if (ID == 123) { // if ID is unknown
		int response;
		cout << "This ID is unrecognized. Sign Up?\n" << endl;
		cout << "1. Yes\n2. No" << endl;
		cin >> response;

		// if sign up is yes
		if (response == 1) {
			showSignUpMenu();
		}
		
	}

	return 0;
}

void showSignUpMenu() {
}