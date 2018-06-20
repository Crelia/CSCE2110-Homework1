#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"
#include "functions.h"

using namespace std;

hash::hash() {
	dcnt = 0;

	for (int i = 0; i < tableSize; i++) {
		HashTable[i] = new item;
		HashTable[i]->card = "empty";
		HashTable[i]->id = 0;
		HashTable[i]->next = NULL;
	}
}//constructor: set everything to 0

int hash::Hash(string key) {
	int hash = 0;
	int index;

	for (int i = 0; i < key.length(); i++) {
		hash = hash + (int)key[i];
	}

	index = hash % tableSize;

	return index;
} //hash function, store items in the bucket of the modula

void hash::addItem(ofstream& out_s, ifstream& in_s) {
	string card;
	char temp;
	int id;
	dcnt++;
	id = dcnt;

	while(in_s >> temp) { //while you can read the file

		getline(in_s, card);//get the face and suite
		card = temp + card;
//		cout << card << endl;
		int index = Hash(card); //find what bucket to place the card into

		if(HashTable[index]->card == "empty") { //if empty bucket set item info
			HashTable[index]->card = card;
			HashTable[index]->id = id;
		}
		else { //if the bucket is filled, use chaining and add another item
			item* ptr = HashTable[index];
			item* n = new item;
			n->card = card;
			n->id = id;
			n->next = NULL;

			while(ptr->next != NULL) { //et next bucket
				ptr = ptr->next;
			}
			ptr->next = n;
		}
	}

}

int hash::numofItems(int index) {
	int cnt = 0;

	if(HashTable[index]->card == "empty") { //if empty count is 0
		return cnt;
	}
	else {
		cnt++;
		item* ptr = HashTable[index];

		while(ptr->next != NULL) { //get next bucket untill NULL, add to count
			ptr = ptr->next;
			cnt++;
		}
	}
	return cnt;
}

void hash::prtTable() { //print the contents of each bucket in the hash table
	int number;
	for(int i = 0; i < tableSize; i++) {
		number = numofItems(i);
		cout << "================================\n";
		cout << "index = " << i << endl;
		cout << HashTable[i]->card << endl;
		cout << "Deck Number = " << HashTable[i]->id << endl;
		cout << "# of items in bucket = " << number << endl;
		cout << "================================\n";
	}
}

void hash::prtIndex(int index) { //print the contents of each bucket in more detail
	item* ptr = HashTable[index];

	if(ptr->card == "empty") {
		cout << "Nothing in bucket" << endl << endl;
	}
	else {
		cout << "Index " << index << "contains: " << endl;

		while(ptr != NULL) {
			cout << "================\n";
			cout << ptr->card << endl;
			cout << ptr->id << endl;
			cout << "================\n";

			ptr = ptr->next;
		}
	}
}

void hash::prtHand(int id) { //print all the cards that lie in a ahnd
	cout << "\nAll cards in set " << id << " :\n";
	cout << "================\n";

	for (int i = 0; i < tableSize; i++) {
		item* ptr = HashTable[i];

		while(ptr != NULL) {
			if (ptr->id == id) {
				cout << ptr->card << endl;
				ptr = ptr->next;
			}
			else {
				ptr = ptr->next;
			}
		}
	}
	cout << "================\n";
}

void hash::findUniv() {
	int ucnt = 0;

	for(int i = 0; i < tableSize; i++) {
		item* ptr = HashTable[i];//ptr to bucket object

		while(ptr != NULL) {
			if (ptr->id == 5) {
				for(int j = 0; j < tableSize; j++) {
					item* ptr2 = HashTable[j];//second pointer

					while(ptr2 != NULL) {
						if(ptr2->id != 5) {
							if(!ptr2->card.compare(ptr->card)) {//if the items are equivalenbt
								ucnt++;
								ptr2 = ptr2->next;
							}
							else {
								ptr2 = ptr2->next;
							}
						}
						else {
							ptr2 = ptr2->next;
						}
					}
				}
				ptr = ptr->next;
			}
			else {
				ptr  = ptr->next;
			}
		}
	}

	if(ucnt >= 52) {
		cout << "\nUniveral set found!\n\n";
	}
	else {
		cout << "\nUniversal set not found.\n\n";
	}
}

void hash::findExtra() { //check for ectra cards
        int ucnt = 0;
        int max = 0;

        for(int i = 0; i < tableSize; i++) {
                item* ptr = HashTable[i];//pointer to object

                while(ptr != NULL) {
                        if (ptr->id == 5) {
                                for(int j = 0; j < tableSize; j++) {
                                        item* ptr2 = HashTable[j];//second pointer

                                        while(ptr2 != NULL) {
                                                if(ptr2->id != ptr->id) {
                                                        if(!ptr2->card.compare(ptr->card)) {//if the items are equal
                                                                ucnt++;
                                                                if(ucnt > max) {max = ucnt;}
                                                                ptr2 = ptr2->next;
                                                        }
                                                        else {
                                                                ptr2 = ptr2->next;
                                                        }
                                                }
                                                else {
                                                        ptr2 = ptr2->next;
                                                }
                                        }
                                }
                                if(ucnt > 1) {
                                        cout << "\n================================\n";
                                        cout << ptr->card << " is an extra card!\n";
                                        cout << "================================\n";
                                }
                                ucnt = 0;
                                ptr = ptr->next;
                        }
                        else {
                                ptr = ptr->next;
                        }
                }
        }
}

void hash::findUniq() {//find unique cards
        int ucnt = 0;
	int max = 0;

        for(int i = 0; i < tableSize; i++) {
                item* ptr = HashTable[i];//pointer to bucket object

                while(ptr != NULL) {
			if (ptr->id == 5) {
				for(int j = 0; j < tableSize; j++) {
					item* ptr2 = HashTable[j];//second poiunter to buxket object

					while(ptr2 != NULL) {
						if(ptr2->id != ptr->id) {
							if(!ptr2->card.compare(ptr->card)) {
								ucnt++;
								if(ucnt > max) {max = ucnt;}
								ptr2 = ptr2->next;
							}
							else {
								ptr2 = ptr2->next;
							}
						}
						else {
							ptr2 = ptr2->next;
						}
					}
				}
				if(ucnt == 1) {
					cout << "\n================================\n";
					cout << ptr->card << " is a unique card!\n";
					cout << "================================\n";
				}
				ucnt = 0;
				ptr = ptr->next;
			}
			else {
				ptr = ptr->next;
			}
		}
	}
}
