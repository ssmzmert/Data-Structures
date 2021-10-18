#pragma once
#include "LinkedList.h"
#include "Rectangle.h"
class TwoDimTreeNode
{
public:
	void insert(Rectangle & r);
	TwoDimTreeNode(int Top, int Left, int Bottom, int Right);
	TwoDimTreeNode(Rectangle r);
	void intersection(int x, int y);
	~TwoDimTreeNode();
private:
	Rectangle Extent;
	vector<TwoDimTreeNode *> leaves;
	LinkedList<Rectangle> Horizontal;
	LinkedList<Rectangle> Vertical;
};

