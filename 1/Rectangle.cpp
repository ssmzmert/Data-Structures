#include "Rectangle.h"

Rectangle::Rectangle(int Top, int Left, int Bottom, int Right): Top(Top), Left(Left), Bottom(Bottom), Right(Right)
{
}

Rectangle::Rectangle()
{
	Top = -1;
	Left = -1;
	Bottom = -1;
	Right = -1;
}

vector<int> Rectangle::center()
{
	vector<int> cen;
	cen.push_back((Right + Left) / 2);	//Center x point
	cen.push_back((Top + Bottom) / 2);	//Center y point
	return cen;
}

vector<int> Rectangle::xPairs()
{
	vector<int> xpair;
	xpair.push_back(Left);
	xpair.push_back(Right);
	return xpair;
}

vector<int> Rectangle::yPairs()
{
	vector<int> ypairs;
	ypairs.push_back(Top);
	ypairs.push_back(Bottom);
	return ypairs;
}

int Rectangle::width()
{
	return (Right-Left)/2;	//Integer division
}

int Rectangle::height()
{
	return (Bottom-Top)/2;	//Integer division
}

vector<Rectangle> Rectangle::createQuadrants()
{
	int x, y;
	x = center()[0];
	y = center()[1];
	vector<Rectangle> quadrants;
	quadrants.push_back(Rectangle(Top, Left, y, x));	//TOPLEFT
	quadrants.push_back(Rectangle(y, Left, Bottom, x));	//BOTTOMLEFT
	quadrants.push_back(Rectangle(y, x, Bottom, Right));//BOTTOMRIGHT
	quadrants.push_back(Rectangle(Top, x, y, Right));	//TOPRIGHT
	return quadrants;
}

int Rectangle::match(int x, int y)
{
	if (Left <= x && x < Right) {
		if (Top <= y && y < Bottom) {
			return 1;					//The point is inside square
		}
		return 2;						//Vertical match
	}
	if (Top <= y && y < Bottom) {
		return 3;						//Horizontal match
	}
	return 0;							//No possible match
}

void Rectangle::printRectangle(){
	string output = "";
	output = output + to_string(Top) + " ";
	output = output + to_string(Left) + " ";
	output = output + to_string(Bottom) + " ";
	output = output + to_string(Right);
	cout << output << endl;
}

Rectangle::~Rectangle()
{
}
