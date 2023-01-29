#include <iostream>
#include "AdminUIBackend.h"
using namespace std;

bool validateFirstName(const char* firstName) {
	string firstNameStr = string(firstName);
	for (int i = 0; i < firstNameStr.length(); i++) {
		if (!isalpha(firstName[i])) {
			cout << "Error: first names must only consist of alphanumeric characters." << endl;
			return false;
		}
	}
	return true;
}

bool validateLastName(const char* lastName) {
	string lastNameStr = string(lastName);
	for (int i = 0; i < lastNameStr.length(); i++) {
		if (!isalpha(lastName[i])) {
			cout << "Error: last names must only consist of alphanumeric characters." << endl;
			return false;
		}
	}
	return true;
}

bool validatePassword(const char* password, const char* confirmPassword) {
	string passwordStr = string(password);
	string confirmPasswordStr = string(confirmPassword);

	if (passwordStr.length() < 7 || confirmPasswordStr.length() < 7) {
		cout << "Error: passwords must be longer than length 7." << endl;
		return false;
	}

	if (passwordStr != confirmPasswordStr) {
		cout << "Error: passwords must match." << endl;
		return false;
	}
	return true;
}