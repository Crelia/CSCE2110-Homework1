#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "hash.h"
#include "functions.h"

using namespace std;

int main() {
	ofstream out_s; //out stream file
	ifstream in_s; //in stream file

	hash hashObj; //hash object

	int choice = -1;
	int id = 0;

	while (choice != 0) { //loop until user decides to quit
		cout << "What do you want to do?\n";
		cout << " 0  - quit\n 1  - Add cards to hand\n 2  - Print list of cards in a hand\n 3  - Print list of hash\n 4  - Find extra cards\n 5  - Check for universal set\n 6  - Check for unique cards\n";
		cout << "Enter your selection: ";
		cin >> choice;

		switch (choice) {
			case 1: //get the instream file, add the item, close the file
				get_stream(in_s, out_s);
				hashObj.addItem(out_s, in_s);
				in_s.close();
				break;
			case 2: //enter the hand id, print cards in hand
				cout << "Enter hand ID: ";
				cin >> id;
				cout << endl;
				hashObj.prtHand(id);
				break;
			case 3: hashObj.prtTable();break; //print hash table
			case 4: hashObj.findExtra();break;//find extra cards
			case 5: hashObj.findUniv();break;//find universal cards
			case 6: hashObj.findUniq();break;//find unique cards
		}
	}




	return 0;
}
