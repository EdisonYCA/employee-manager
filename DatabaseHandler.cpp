#include <iostream>
#include "C:/Users/Ediso/Desktop/ROAD TO INTERNSHIP/C++/SQLAPI/include/SQLAPI.h"
using namespace std;

int main() {
	SAConnection conn;
	try {
		conn.Connect(_TSA("test1"), _TSA("root"), _TSA("Ma3a6euv0!"), SA_MySQL_Client);
		cout << "We are connected!\n";

		conn.Disconnect();
		cout << "we are disconnected!\n";
	}
	catch (SAException& e) {
		conn.Rollback();
		cout << "\n" << e.ErrText().GetMultiByteChars();
	}

	return 0;
}