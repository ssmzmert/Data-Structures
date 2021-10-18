#include "TwoDimTreeNode.h"
void TwoDimTreeNode::insert(Rectangle & r)
{
	int intersection = r.match(Extent.center()[0], Extent.center()[1]);
	if ((intersection == 1) || (intersection == 2)) {
		Vertical.add(r);	//The point is either vertical or inside the rectangle
	}
	else if (intersection == 3) {
		Horizontal.add(r);	//The point intersects as horizontaþ
	}
	vector<Rectangle> quadrants = Extent.createQuadrants();
	vector<int> xPairs = r.xPairs();	//Will be used later for intersection purposes
	vector<int> yPairs = r.yPairs();
	for (int i = 0; i < quadrants.size(); i++) {
		if ((quadrants[i].height() >= 1) && (quadrants[i].width() >= 1)) {
			for (int j = 0; j < 2; j++) {
				if (quadrants[i].match(xPairs[j], yPairs[j]) == 1) {	//The rectangle has any points in that quadrant
					if (leaves[i] == nullptr) {
						leaves[i] = new TwoDimTreeNode(quadrants[i]);
						leaves[i]->insert(r);	//Inserting that node to the subleaves
						j = 2;
					}
					else {
						leaves[i]->insert(r);
						j = 2;
					}
				}
			}
		}
	}
}


void TwoDimTreeNode::intersection(int x, int y) {
	TwoDimTreeNode * result=this;
	bool isChanged = true;
	while (isChanged) {
		isChanged = false;
		for (int i = 0; i < result->leaves.size(); i++) {
			if (result->leaves[i] != nullptr) {
				if (result->leaves[i]->Extent.match(x, y) == 1) {
					isChanged = true;
					result = result->leaves[i];	//Result quadrant is in leaves
				}
			}
		}
	}
	vector<Rectangle> intersections;
	for (node<Rectangle> * i = result->Horizontal.first; i != NULL; i = i->next) {
		if (i->data.match(x, y)==1) {
			intersections.push_back(i->data);	//Horizontal Linked List
		}
	}
	for (node<Rectangle> * i = result->Vertical.first; i != NULL; i = i->next) {
		if (i->data.match(x, y)==1) {
			intersections.push_back(i->data);	//Vertical Linked List
		}
	}
	int size = intersections.size();
	cout << x << " " << y << endl << size << endl;
	for (int i = 0; i < size; i++) {
		intersections[i].printRectangle();		//Printing every Rectangle
	}
}

TwoDimTreeNode::TwoDimTreeNode(int Top, int Left, int Bottom, int Right): Extent(Rectangle(Top, Left, Bottom, Right))
{
	for (int i = 0; i < 4; i++) {
		TwoDimTreeNode * nullNode = nullptr;
		leaves.push_back(nullNode);
	}
}

TwoDimTreeNode::TwoDimTreeNode(Rectangle r): Extent(r)
{
	for (int i = 0; i < 4; i++) {
		TwoDimTreeNode * nullNode = nullptr;
		leaves.push_back(nullNode);
	}
}


TwoDimTreeNode::~TwoDimTreeNode()
{
}
