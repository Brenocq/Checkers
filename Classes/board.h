#ifndef BOARD_H
#define BOARD_H

#include <vector>
using namespace std;

class Board
{
public:
	Board();
	~Board();

	void draw();
	void setClick(vector<int> _click);

	int getSize(){return size;}	
private:
	void drawSquare(int x, int y, vector<float>color); 
	float size;
	vector<vector<int> > pos;
	vector<vector<int> > possible;

	vector<int> click;
	bool action;
	vector<int> selected;

	int turn;
	bool repeat;
};
#endif// BOARD_H
