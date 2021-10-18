#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
bool checkPrime(int n) {
	bool isPrime=true;
	for (int i = 2; i <= n / 2; ++i)
	{
		if (n % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

int nextPrime(int n) {
	while (!checkPrime(n++));
	return n;
}
template<class HashedObj>
int hashh(const HashedObj & hashedObj, int size, int y=131) {
	int val = 0;
	for (int i = 0; i < hashedObj.first.size(); i++) {
		if (hashedObj.first[i] > 0) {
			val += hashedObj.first[i] * y;
		}
	}
	return val % size;
}
using namespace std;
//HASHTABLE CLASS TAKEN FROM SLIDES
template <class HashedObj>
class HashTable{
public:
	int findCode(const HashedObj &x);
    explicit HashTable(const HashedObj & notFound, int size = 101);
    HashTable(const HashTable &rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), array(rhs.array), currentSize(rhs.currentSize) { }
    const HashedObj & find( const HashedObj & x );
    void makeEmpty();
	bool operator==(const HashedObj &rhs);
	bool operator!=(const HashedObj &rhs);
    void insert(const HashedObj &x);
    void remove(const HashedObj &x);
    const HashTable & operator=(const HashTable & rhs);
    enum EntryType {ACTIVE, EMPTY, DELETED};
private:
    struct HashEntry{
        HashedObj element;
        EntryType info;
        HashEntry(const HashedObj &e=HashedObj(), EntryType i=EMPTY): element(e), info(i) { }
    };
    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;
    bool isActive( int currentPos);
    int findPos(const HashedObj &x);
    void rehash();
};

template <class HashedObj>

HashTable<HashedObj>::HashTable(const HashedObj &notFound, int size): ITEM_NOT_FOUND(notFound), array(nextPrime(size)){
    makeEmpty();
}

template <class HashedObj>

int HashTable<HashedObj>::findPos( const HashedObj & x){
    int collisionNum = 0;
    int currentPos = hashh(x, array.size());
    while(array[currentPos].info != EMPTY && array[currentPos].element.first != x.first ){
        currentPos += 1; // add the difference
        if( currentPos >= array.size( ) ) // perform the mod
            currentPos -= array.size( );  // if necessary
    }
    return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos){
    return array[currentPos].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj &x){
    int currentPos = findPos( x );
    if(isActive(currentPos))
        array[currentPos].info = DELETED;
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ){
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return array[currentPos].element;
    return ITEM_NOT_FOUND;
}

template <class HashedObj>
int HashTable<HashedObj>::findCode(const HashedObj & x) {
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return array[currentPos].element.second;
	return ITEM_NOT_FOUND.second;
}

template<class HashedObj>
inline void HashTable<HashedObj>::makeEmpty()
{
	currentSize = 0;
	array.resize(array.size());
	for (int i = 0; i < array.size(); i++) {
		array[i].info = EMPTY;
	}
}

template<class HashedObj>
inline bool HashTable<HashedObj>::operator==(const HashedObj & rhs)
{
	if (currentSize == rhs.currentSize) {
		if (rhs.array.size() == array.size()) {
			for (int i = 0; i < array.size(); i++) {
				if (array[i].info == ACTIVE) {
					if (rhs.array[i].info != ACTIVE) {
						return false;
					}
				}
			}
			return true;
		}
	}
	return false;
}

template<class HashedObj>
inline bool HashTable<HashedObj>::operator!=(const HashedObj & rhs)
{
	bool notResult = *this == rhs;
	return !notResult;
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x){
    // Insert x as active
    int currentPos = findPos(x);
    if(isActive(currentPos))
        return;
    array[currentPos] = HashEntry(x, ACTIVE);
    // enlarge the hash table if necessary
    if(++currentSize >= array.size()/2)
        rehash();
}


template <class HashedObj>
void HashTable<HashedObj>::rehash(){
    vector<HashEntry> oldArray = array;
    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));
    for(int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;
    // Copy table over
    currentSize = 0;
    for(int i = 0; i < oldArray.size(); i++)
        if(oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);
}



int main() {
	//I will use c++ standard pairs to insert into tables so I can store both string and code that string is associated with
	pair<string, int> notFound("", -1);
	HashTable<pair<string, int>> table(notFound);
	ifstream input("compin");
	ofstream output("compout");
	for (int i = 0; i < 256; i++) {
		pair<string, int> p(string(1, i), i);	//Creating every primitive pair
		table.insert(p);
	}
	int newCode = 255;	//Last pair from alphabet as alphabet[255]
	string previous = "", next = "";
	char currentChar;
	int currentCode=0;
	input.get(currentChar);
	next = currentChar;
	while (input.get(currentChar)) {
		pair<string, int> searchPair(next + currentChar, 1);
		if (table.findCode(searchPair) != -1) {
			next += currentChar;
			//If the pair is in table
		}
		else {
			//If the pair is not in table
			newCode++;
			pair<string, int> previousPair(next, 1);
			int dummy = table.findCode(previousPair);
			table.insert(pair<string, int>(next + currentChar, newCode));
			output << dummy << " ";
			next = currentChar;
		}
	}
	output << table.findCode(pair<string, int>(next, 1));
	return 0;
}

















