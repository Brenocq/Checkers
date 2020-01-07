#include "board.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

Board::Board()
{
	size = 10;
	selected = {-1,-1};
	click = {-1,-1};
	action = false;
	turn = 1;

	// Init board positions 
	for(int i=0;i<size;i++)
	{
		vector<int>_pos;
		vector<int>_possible;
		for(int j=0;j<size;j++)
		{
			_pos.push_back(0);
			_possible.push_back(0);
		}
		pos.push_back(_pos);
		possible.push_back(_possible);
	}

	// Init Pieces
	for(int y=0;y<size;y++)
	{
		for(int x=0;x<size;x++)
		{
			if((x+y)%2==0)
			{
				y<2?pos[x][y]=1:pos[x][y];
				y>size-3?pos[x][y]=2:pos[x][y];
			}
		}
	}
}

Board::~Board()
{}

void Board::draw()
{
	// Clean possibles
	for(int y=0;y<size;y++)
	{
		for(int x=0;x<size;x++)
		{
			possible[x][y]=0;
		}
	}
	// Draw board
	float sizeSquare = 2/size;
	glColor3f(1,1,1);

	for(int i=0;i<size;i++)
	{
		for(int j=(i%2==0?0:1);j<size;j+=2)
		{
  		glBegin(GL_POLYGON);
			glVertex2d(-1+sizeSquare*j, -1+sizeSquare*i);	
			glVertex2d(-1+sizeSquare*j, -1+sizeSquare*(i+1));	
			glVertex2d(-1+sizeSquare*(j+1), -1+sizeSquare*(i+1));	
			glVertex2d(-1+sizeSquare*(j+1), -1+sizeSquare*i);	
  		glEnd();
		}
	}
	// Draw possible moves
	for(int y=0;y<size;y++)
	{
		for(int x=0;x<size;x++)
		{
			if(x==selected[0] && y==selected[1] && (x+y)%2==0 && pos[x][y]!=0)
			{
				vector<float> _color = {0.8,0.8,0.5};
				vector<float> atk  = {0.9,0.1,0.1};
				drawSquare(x, y, _color);
				if(x+1<size && y+1<size && pos[x][y]==1)
				{
					if(pos[x+1][y+1]==0)
					{
						drawSquare(x+1, y+1, _color);
						possible[x+1][y+1]=1;
					}
					else if(pos[x+1][y+1]==(turn==1?2:1))
					{
						if(x+2<size && y+2<size && pos[x+2][y+2]==0)
						{
							drawSquare(x+1, y+1, atk);
							drawSquare(x+2, y+2, _color);
							possible[x+2][y+2]=2;
						}
					}
				}
				if(x+1<size && y-1>=0 && pos[x][y]==2)
				{
					if(pos[x+1][y-1]==0)
					{
						drawSquare(x+1, y-1, _color);
						possible[x+1][y-1]=1;
					}
					else if(pos[x+1][y-1]==(turn==1?2:1))
					{
						if(x+2<size && y-2<size && pos[x+2][y-2]==0)
						{
							drawSquare(x+1, y-1, atk);
							drawSquare(x+2, y-2, _color);
							possible[x+2][y-2]=3;
						}
					}
				}
				if(x-1>=0 && y+1<size && pos[x][y]==1)
				{
					if(pos[x-1][y+1]==0)
					{
						drawSquare(x-1, y+1, _color);
						possible[x-1][y+1]=1;
					}
					else if(pos[x-1][y+1]==(turn==1?2:1))
					{
						if(x-2<size && y+2<size && pos[x-2][y+2]==0)
						{
							drawSquare(x-1, y+1, atk);
							drawSquare(x-2, y+2, _color);
							possible[x-2][y+2]=4;
						}
					}
				}
				if(x-1>=0 && y-1>=0 && pos[x][y]==2)
				{
					if(pos[x-1][y-1]==0)
					{
						drawSquare(x-1, y-1, _color);
						possible[x-1][y-1]=1;
					}
					else if(pos[x-1][y-1]==(turn==1?2:1))
					{
						if(x-2<size && y-2<size && pos[x-2][y-2]==0)
						{
							drawSquare(x-1, y-1, atk);
							drawSquare(x-2, y-2, _color);
							possible[x-2][y-2]=5;
						}
					}
				}
			}
		}
	}	
	// Draw pieces
	for(int y=0;y<size;y++)
	{
		for(int x=0;x<size;x++)
		{
			if(pos[x][y]==1)
			{
  				glColor3f(0.6,0.3,0.1);
  				glBegin(GL_POLYGON);
  				for (int i = 0; i < 360; i+=10) {
  				  glVertex2d( sizeSquare*0.35f*cos(i/180.0*M_PI) + sizeSquare*(x+0.5)-1,
						      sizeSquare*0.35f*sin(i/180.0*M_PI) + sizeSquare*(y+0.5)-1);
  				}
  				glEnd();
			}
			else if(pos[x][y]==2)
			{
  				glColor3f(0.1,0.3,0.6);
  				glBegin(GL_POLYGON);
  				for (int i = 0; i < 360; i+=10) {
  				  glVertex2d( sizeSquare*0.35f*cos(i/180.0*M_PI) + sizeSquare*(x+0.5)-1,
						      sizeSquare*0.35f*sin(i/180.0*M_PI) + sizeSquare*(y+0.5)-1);
  				}
  				glEnd();

			}
		}
	}
}

void Board::setClick(vector<int> _click)
{
	if(pos[_click[0]][_click[1]]!=0)
	{
		action=false;
	}

	if(action==false)
	{
		if(pos[_click[0]][_click[1]]==turn)
		{
			selected = _click;
			action = true;
		}
	}
	else
	{
		click=_click;	
		switch(possible[click[0]][click[1]])
		{
			case 1:
				pos[click[0]][click[1]]=pos[selected[0]][selected[1]];
				pos[selected[0]][selected[1]]=0;
				action = false;
				turn==1?turn=2:turn=1;
				break;
			case 2:
				pos[click[0]][click[1]]=pos[selected[0]][selected[1]];
				pos[click[0]-1][click[1]-1]=0;
				pos[selected[0]][selected[1]]=0;
				action = false;
				break;
			case 3:
				pos[click[0]][click[1]]=pos[selected[0]][selected[1]];
				pos[click[0]-1][click[1]+1]=0;
				pos[selected[0]][selected[1]]=0;
				action = false;
				break;
			case 4:
				pos[click[0]][click[1]]=pos[selected[0]][selected[1]];
				pos[click[0]+1][click[1]-1]=0;
				pos[selected[0]][selected[1]]=0;
				action = false;
				break;
			case 5:
				pos[click[0]][click[1]]=pos[selected[0]][selected[1]];
				pos[click[0]+1][click[1]+1]=0;
				pos[selected[0]][selected[1]]=0;
				action = false;
				break;
		}
	}
}

void Board::drawSquare(int x, int y, vector<float>color){
	float sizeSquare = 2/size;
	glColor3f(color[0], color[1], color[2]);
  	glBegin(GL_POLYGON);
  		glVertex2d(-1+sizeSquare*x, -1+sizeSquare*y);	
  		glVertex2d(-1+sizeSquare*x, -1+sizeSquare*(y+1));	
  		glVertex2d(-1+sizeSquare*(x+1), -1+sizeSquare*(y+1));	
  		glVertex2d(-1+sizeSquare*(x+1), -1+sizeSquare*y);	
  	glEnd();
}
