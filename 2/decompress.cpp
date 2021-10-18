#include <iostream>
#include <string>
#include <fstream>
#define not_found "thIsIteMisSReaLLyNotInString"
using namespace std;
string uncompress[4096] = { not_found };	//initially all strings are unfound
int main() {
	ifstream input("compout");
	ofstream output("decompout");
	for (int i = 0; i < 256; i++) {
		uncompress[i] = string(1, i);	//the alphabet is found in the dictionary
	}
	int start = 256;
	int p, n;
	input >> n;
	p = n;
	string outputString = "";
	outputString += uncompress[n];	//adding first char as it is for sure that it is in dictionary
	while (input >> n) {
		if (n < 4096) {
			if (uncompress[n] != not_found) {
				outputString += uncompress[n];
				//outputString += " ";	//No need since blank is also a char
				uncompress[start++] = uncompress[p] + uncompress[n][0];
				p = n;
			}
			else {
				outputString += uncompress[p] + uncompress[p][0];
				uncompress[start++] = uncompress[p] + uncompress[p][0];
				p = n;	//Previous one is now updated
			}
		}
		else {
			cout << "Limit is reached" << endl;
		}
	}
	output << outputString;//Writing to the file
}