//Jefferson Crelia
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


#ifndef hash_h
#define hash_h

class hash {
	private:
		static const int tableSize = 10; //keep table size at a constant number of 10

		int dcnt; //count of hands

		struct item {
			string card; //holds the  face and suite of a card
			int id; //id of the hand
			item* next; //next node (for chaining collision detection)
		};

		item* HashTable[tableSize];//table of 10 buckets
	public:
		hash();
		int Hash(string key); //hash function
		void addItem(ofstream& out_s, ifstream& in_s); //add cards from a file
		int numofItems(int index); //find the number of items in each bucket
		void prtTable(); //print the hash table
		void prtIndex(int index); //print cards
		void prtHand(int id); //print a ahand of cards
		void findUniv(); //find universal set
		void findUniq(); //find unique cards
		void findExtra();//find extra cards
};

#endif /*hash_h*/
