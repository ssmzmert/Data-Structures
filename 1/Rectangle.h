#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Rectangle
{
public:
	Rectangle(int Top, int Left, int Bottom, int Right);
	Rectangle();
	vector<int> center();
	vector<int> xPairs();
	vector<int> yPairs();
	int width();
	int height();
	vector<Rectangle> createQuadrants();
	int match(int x, int y);
	void printRectangle();
	~Rectangle();
private:
	int Top, Left, Bottom, Right;
};

