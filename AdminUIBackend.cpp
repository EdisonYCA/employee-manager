#include <iostream>
using namespace std;

bool validateFirstName(string firstName) {
	for (int i = 0; i < firstName.length(); i++) {
		if (!isalpha(firstName[i])) {
			return false;
		}
	}
	return true;
}

bool validateLastName(string lastName) {
	for (int i = 0; i < lastName.length(); i++) {
		if (!isalpha(lastName[i])) {
			return false;
		}
	}
	return true;
}

bool validatePassword(string password, string confirmPassword) {
	if (password != confirmPassword) {
		return false;
	}
	return true;
}