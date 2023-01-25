#include <iostream>
#include "AdminUIBackend.h"
using namespace std;

bool validateFirstName(const char* firstName) {
	string firstNameStr = string(firstName);
	for (int i = 0; i < firstNameStr.length(); i++) {
		if (!isalpha(firstName[i])) {
			return false;
		}
	}
	return true;
}

bool validateLastName(const char* lastName) {
	string lastNameStr = string(lastName);
	for (int i = 0; i < lastNameStr.length(); i++) {
		if (!isalpha(lastName[i])) {
			return false;
		}
	}
	return true;
}

bool validatePassword(const char* password, const char* confirmPassword) {
	string passwordStr = string(password);
	string confirmPasswordStr = string(confirmPassword);

	if (passwordStr != confirmPasswordStr) {
		return false;
	}
	return true;
}

int generateID() {
	int id = 12345;
	return id++;
	id = id++;
}