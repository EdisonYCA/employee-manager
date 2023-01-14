#include <iostream>
using namespace std;

int loginMenu() {
	int response;
	cout << "Select a valid menu option."<<endl;
	cout << "1. Sign Up\n2. Sign In\n-> ";
	cin >> response;

	return response;
}

void signUp() {
	int id = 123;
		//generateID();
	string first_name, last_name;
	double pay_rate;

	cout << "Enter employee first name: ";
	cin >> first_name;

	cout << "Enter employee last name: ";
	cin >> last_name;

	cout << "Enter employee pay_rate: ";
	cin >> pay_rate;


}

int main() {
	if (loginMenu() == 1) {
		signUp();
	}

	return 0;
}