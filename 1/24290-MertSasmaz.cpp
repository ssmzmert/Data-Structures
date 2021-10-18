#include "TwoDimTreeNode.h"		
#include <fstream>
#include <sstream>
using namespace std;

int main() {
	ifstream ifstrm("recdb.txt");	//File name
	string line;
	int rT, rL, rB, rR;
	ifstrm >> rT >> rL >> rB >> rR;	//With order root's Top, Left, Bottom, Right
	TwoDimTreeNode * start = new TwoDimTreeNode(rT, rL, rB, rR);
	int Top=1, Left, Bottom, Right;
	while (Top >= 0) {
		ifstrm >> Top;
		if (Top < 0) {
			break;	//Rectangle input is ended
		}
		else {
			ifstrm >> Left >> Bottom >> Right;
			Rectangle insertRectangle(Top, Left, Bottom, Right);	//Inserting rectangle to the quad-tree
			start->insert(insertRectangle);
		}
	}
	LinkedList<vector<int>> queryPoints;
	while (getline(cin, line)) {
		int x, y;
		istringstream myLine(line);
		myLine >> x >> y;
		if (x == -1) {
			break;	//Query input is ended
		}
		vector<int> point;
		point.push_back(x);
		point.push_back(y);
		queryPoints.add(point);
	}
	for (node<vector<int>> *query = queryPoints.first; query != NULL; query = query->next) {
		start->intersection(query->data[0], query->data[1]);	//Searching every input in the query input
	}
}