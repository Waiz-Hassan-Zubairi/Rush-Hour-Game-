//============================================================================
 /*
 
 
Student name : waiz hassan zubairi. 
roll number # i21-0751
"final semester project"


*/
//Game Name        : game.cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int score = 0, board = -1, ytaxi = 0, s1 = 0, stotal = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0, s8 = 0, s9 = 0, s10 = 0, random_number, rtaxi = 0, b = 0, s = 0, x = 0, y = 0, z = 0, z1 = 0, o = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, z2 = 0, z3 = 0, z4 = 0, z5 = 0, z6 = 0, z7 = 0, z8 = 0, z9 = 0, distance_cover_speed = 1, m1 = 0, m2 = 0;
char press, press1;
int xI = 5, yI = 730;
int menu = 1, menu1 = 0;
bool point3 = true;
bool point2 = true;
bool point1 = true;
bool point4 = true;
bool point5 = true;
bool point6 = true;
bool point7 = true;
bool point8 = true;
bool point9 = true;
bool point10 = true;
bool car_color = true;
void points3();
void points2();
void points1();
void points4();
void points5();
void points6();
void points7();
void points8();
void points9();
void points10();
void random_car();
void score_setting();

string name = "";
int name_entry = -1;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu_display()
{
	if (ytaxi == 1)
	{
		distance_cover_speed = 3;
	}
	glClearColor(0 /*Red Component*/, 1,					   //148.0/255/*Green Component*/,
				 1 /*Blue Component*/, 0 /*Alpha component*/); //Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);							   //Update the colors
															   //Display Score
	DrawCircle(420, 420, 450, colors[BLACK]);
	string s_welcome = "WELCOME TO RUSH HOUR";
	DrawString(255, 770, s_welcome, colors[DARK_TURQUOISE]);
	string s_leaderboard = "For Leader Board Press "
						   "'L'";
	DrawString(255, 470, s_leaderboard, colors[DARK_TURQUOISE]);
	string s_taxi = "For Yelllow Taxi Press "
					"'Y'";
	DrawString(70, 170, s_taxi, colors[DARK_TURQUOISE]);
	string s_taxi1 = "For Red Taxi Press "
					 "'R'";
	DrawString(560, 170, s_taxi1, colors[DARK_TURQUOISE]);
	glutPostRedisplay();
}

void leader_board_display()
{

	ifstream FileRead;
	FileRead.open("highscores.txt");

	string Player_Names[100];

	for (int i = 0; i < 100; i++)
	{
		Player_Names[i] = "";
	}

	int Player_Score[100] = {0};

	string tmp_Scores[100];
	string line = "";

	int array_index = 0;
	while (getline(FileRead, line))
	{
		if (line != "")
		{
			int i = 0;
			int commacount = 0;

			while (i < line.length())
			{
				if (line[i] == ',')
				{
					commacount++;
				}
				else if (commacount == 0)
				{
					Player_Names[array_index] += line[i];
				}
				else if (commacount == 1)
				{
					tmp_Scores[array_index] += line[i];
				}
				i++;
			}
			array_index++;
		}
	}

	FileRead.close();

	for (int i = 0; i < array_index; i++)
	{
		if (tmp_Scores[i] == "")
		{
			Player_Score[i] = 0;
		}
		else
		{
			Player_Score[i] = atoi(tmp_Scores[i].c_str());
		}
	}

	glClearColor(0 /*Red Component*/, 1,					   //148.0/255/*Green Component*/,
				 1 /*Blue Component*/, 0 /*Alpha component*/); //Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);							   //Update the colors
															   //Display Score
	DrawCircle(420, 420, 450, colors[BLACK]);

	string s_taxi = "For Yelllow Taxi Press "
					"'Y'";
	DrawString(70, 170, s_taxi, colors[DARK_TURQUOISE]);
	string s_taxi1 = "For Red Taxi Press "
					 "'R'";
	DrawString(560, 170, s_taxi1, colors[DARK_TURQUOISE]);

	//If file is empty
	if (array_index == 0)
	{

		DrawString(280, 600, "No High Scores Available", colors[DARK_TURQUOISE]);
	}

	else //File is read with high scores
	{

		DrawString(280, 700, "HighScores: ", colors[DARK_TURQUOISE]);

		//Sorting the players
		string s_tmp;
		int i_tmp;

		int j = 0;
		for (i = 0; i < array_index; i++)
		{
			for (j = i + 1; j < array_index; j++)
			{
				if (Player_Score[i] > Player_Score[j])
				{
					i_tmp = Player_Score[i];
					Player_Score[i] = Player_Score[j];
					Player_Score[j] = i_tmp;

					s_tmp = Player_Names[i];
					Player_Names[i] = Player_Names[j];
					Player_Names[j] = s_tmp;
				}
			}
		}

		//Diplaying the top 10;
		int y_scoreindex = 650;

		int loop_check_break = 0;
		for (int i = array_index - 1; i >= 0; i--)
		{
			if (loop_check_break == 10)
			{
				break;
			}
			string displayscore = "";
			displayscore = Player_Names[i] + " " + to_string(Player_Score[i]);
			DrawString(300, y_scoreindex, displayscore, colors[DARK_TURQUOISE]);
			y_scoreindex -= 40;
			loop_check_break++;
		}
	}
	glutPostRedisplay();
}

void getUserName()
{
	glClearColor(0 /*Red Component*/, 1,					   //148.0/255/*Green Component*/,
				 1 /*Blue Component*/, 0 /*Alpha component*/); //Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawCircle(420, 420, 450, colors[BLACK]);
	string s_welcome = "WELCOME TO RUSH HOUR";
	DrawString(255, 770, s_welcome, colors[DARK_TURQUOISE]);

	DrawString(255, 670, "Enter your name: ", colors[DARK_TURQUOISE]);
	DrawString(260, 630, name, colors[DARK_TURQUOISE]);

	glutPostRedisplay();
}

void drawYCar()
{
	DrawCircle(xI + 5, yI - 2, 4, colors[BLACK]);
	DrawCircle(xI + 25, yI - 2, 4, colors[BLACK]);
	DrawRoundRect(xI, yI, 10, 13, colors[ORANGE]);
	DrawRoundRect(xI + 5, yI, 20, 20, colors[ORANGE]);
	DrawRoundRect(xI + 8, yI + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xI + 20, yI, 10, 13, colors[ORANGE]);
	DrawRoundRect(xI + 17, yI + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
void drawRCar()
{
	DrawCircle(xI + 5, yI - 2, 4, colors[BLACK]);
	DrawCircle(xI + 25, yI - 2, 4, colors[BLACK]);
	DrawRoundRect(xI, yI, 10, 13, colors[RED]);
	DrawRoundRect(xI + 5, yI, 20, 20, colors[RED]);
	DrawRoundRect(xI + 8, yI + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xI + 20, yI, 10, 13, colors[RED]);
	DrawRoundRect(xI + 17, yI + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar1 = 210, ycar1 = 460;
void drawCar1()
{
	DrawCircle(xcar1 + 5, ycar1 - 2, 4, colors[BLACK]);
	DrawCircle(xcar1 + 25, ycar1 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar1, ycar1, 10, 13, colors[ROYAL_BLUE]);
	DrawRoundRect(xcar1 + 5, ycar1, 20, 20, colors[ROYAL_BLUE]);
	DrawRoundRect(xcar1 + 8, ycar1 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar1 + 20, ycar1, 10, 13, colors[ROYAL_BLUE]);
	DrawRoundRect(xcar1 + 17, ycar1 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar2 = 520, ycar2 = 375;
void drawCar2()
{
	DrawCircle(xcar2 + 5, ycar2 - 2, 4, colors[BLACK]);
	DrawCircle(xcar2 + 25, ycar2 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar2, ycar2, 10, 13, colors[MAGENTA]);
	DrawRoundRect(xcar2 + 5, ycar2, 20, 20, colors[MAGENTA]);
	DrawRoundRect(xcar2 + 8, ycar2 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar2 + 20, ycar2, 10, 13, colors[MAGENTA]);
	DrawRoundRect(xcar2 + 17, ycar2 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar3 = 370, ycar3 = 175;
void drawCar3()
{
	DrawCircle(xcar3 + 5, ycar3 - 2, 4, colors[BLACK]);
	DrawCircle(xcar3 + 25, ycar3 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar3, ycar3, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar3 + 5, ycar3, 20, 20, colors[POWDER_BLUE]);
	DrawRoundRect(xcar3 + 8, ycar3 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar3 + 20, ycar3, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar3 + 17, ycar3 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar4 = 125, ycar4 = 155;
void drawCar4()
{
	DrawCircle(xcar4 + 5, ycar4 - 2, 4, colors[BLACK]);
	DrawCircle(xcar4 + 25, ycar4 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar4, ycar4, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar4 + 5, ycar4, 20, 20, colors[POWDER_BLUE]);
	DrawRoundRect(xcar4 + 8, ycar4 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar4 + 20, ycar4, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar4 + 17, ycar4 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar5 = 330, ycar5 = 600;
void drawCar5()
{
	DrawCircle(xcar5 + 5, ycar5 - 2, 4, colors[BLACK]);
	DrawCircle(xcar5 + 25, ycar5 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar5, ycar5, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar5 + 5, ycar5, 20, 20, colors[POWDER_BLUE]);
	DrawRoundRect(xcar5 + 8, ycar5 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar5 + 20, ycar5, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar5 + 17, ycar5 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}
int xcar6 = 663, ycar6 = 105;
void drawCar6()
{
	DrawCircle(xcar6 + 5, ycar6 - 2, 4, colors[BLACK]);
	DrawCircle(xcar6 + 25, ycar6 - 2, 4, colors[BLACK]);
	DrawRoundRect(xcar6, ycar6, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar6 + 5, ycar6, 20, 20, colors[POWDER_BLUE]);
	DrawRoundRect(xcar6 + 8, ycar6 + 11, 5, 5, colors[BLACK]);
	DrawRoundRect(xcar6 + 20, ycar6, 10, 13, colors[POWDER_BLUE]);
	DrawRoundRect(xcar6 + 17, ycar6 + 11, 5, 5, colors[BLACK]);

	glutPostRedisplay();
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay() /**/
{
	int value;

	// tell library which function to call for drawing Canvas.
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	if (board == -1)
	{
		getUserName();
	}
	if (board == 0)
	{
		menu_display();
	}
	if (board == 1)
	{
		leader_board_display();
	}

	if (ytaxi == 1)
	{
		menu = 2;
	}
	else if (rtaxi == 1)
	{
		menu = 2;
	}
	if (menu == 2)
	{
		glClearColor(1 /*Red Component*/, 1,					   //148.0/255/*Green Component*/,
					 1 /*Blue Component*/, 0 /*Alpha component*/); //Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);							   //Update the colors
																   //Display Score

		string s_score = "Score = " + to_string(score);
		DrawString(10, 780, s_score, colors[RED]);
		DrawLine(0, 817, 820, 817, 4, colors[BLACK]);			   //lines
		DrawLine(0, 765, 817, 765, 5, colors[BLACK]);			   //lines
		DrawLine(2, 0, 2, 816, 4, colors[BLACK]);				   //lines
		DrawLine(816, 0, 816, 816, 4, colors[BLACK]);			   //lines
		DrawLine(0, 2, 816, 2, 4, colors[BLACK]);				   //lines
		DrawRoundRect(38, 718, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 666, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 614, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 563, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 512, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 460, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(38, 409, 41, 50, colors[BLACK]);			   //Wall 1
		DrawRoundRect(0, 231, 37, 50, colors[BLACK]);			   //Wall 2
		DrawRoundRect(40, 231, 37, 50, colors[BLACK]);			   //Wall 2
		DrawRoundRect(80, 231, 37, 50, colors[BLACK]);			   //Wall 2
		DrawSquare(78, 281, 40, colors[BLUE]);					   // for box
		DrawRoundRect(235, 120, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRoundRect(274, 120, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRoundRect(313, 120, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRoundRect(235, 173, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRoundRect(274, 173, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRectangle(274, 223, 10, 17, colors[BROWN]);			   // for tree
		DrawCircle(278, 253, 16, colors[GREEN]);				   // for tree
		DrawTriangle(270, 223, 278, 233, 287, 223, colors[BROWN]); //for tree
		DrawRoundRect(313, 173, 37, 50, colors[BLACK]);			   //Wall 3
		DrawRoundRect(157, 600, 37, 50, colors[BLACK]);			   //Wall 4
		DrawRoundRect(196, 600, 37, 50, colors[BLACK]);			   //Wall 4
		DrawRectangle(213, 650, 10, 17, colors[BROWN]);			   // for tree
		DrawCircle(217, 680, 16, colors[GREEN]);				   // for tree
		DrawTriangle(209, 650, 217, 660, 226, 650, colors[BROWN]); //for tree
		DrawRoundRect(235, 600, 37, 50, colors[BLACK]);			   //Wall 4
		DrawRoundRect(274, 600, 37, 50, colors[BLACK]);			   //Wall 4
		DrawRoundRect(312, 400, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(351, 400, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(390, 400, 37, 50, colors[BLACK]);			   //Wall 5
		DrawSquare(351, 450, 40, colors[BLUE]);					   // for box
		DrawRoundRect(429, 400, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(468, 400, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(468, 451, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(468, 502, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(468, 554, 37, 50, colors[BLACK]);			   //Wall 5
		DrawRoundRect(624, 605, 37, 50, colors[BLACK]);			   //Wall 6
		DrawRoundRect(663, 605, 37, 50, colors[BLACK]);			   //Wall 6
		DrawSquare(663, 655, 40, colors[BLUE]);					   // for box
		DrawRoundRect(702, 605, 37, 50, colors[BLACK]);			   //Wall 6
		DrawRoundRect(624, 553, 37, 50, colors[BLACK]);			   //Wall 6
		DrawRoundRect(663, 553, 37, 50, colors[BLACK]);			   //Wall 6
		DrawRoundRect(702, 553, 37, 50, colors[BLACK]);			   //Wall 6
		DrawRoundRect(546, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRoundRect(585, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRoundRect(624, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRectangle(641, 350, 10, 17, colors[BROWN]);			   // for tree
		DrawCircle(645, 380, 16, colors[GREEN]);				   // for tree
		DrawTriangle(637, 350, 645, 360, 654, 350, colors[BROWN]); //for tree
		DrawRoundRect(663, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRoundRect(702, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRoundRect(741, 300, 37, 50, colors[BLACK]);			   //Wall 7
		DrawRoundRect(468, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(507, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(546, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawSquare(507, 150, 40, colors[BLUE]);					   // for box
		DrawRoundRect(585, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(624, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(663, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(702, 100, 37, 50, colors[BLACK]);			   //Wall 8
		DrawRoundRect(585, 50, 37, 49, colors[BLACK]);			   //Wall 8
		DrawRoundRect(585, 0, 37, 48, colors[BLACK]);			   //Wall 8
		DrawRoundRect(155, 409, 41, 50, colors[BLACK]);			   //Wall 9
		DrawRoundRect(155, 358, 41, 50, colors[BLACK]);			   //Wall 9
		DrawRoundRect(155, 307, 41, 50, colors[BLACK]);			   //Wall 9
		DrawRoundRect(352, 700, 37, 50, colors[BLACK]);			   //Wall 10
		DrawRoundRect(391, 700, 37, 50, colors[BLACK]);			   //Wall 10
		DrawRoundRect(430, 700, 37, 50, colors[BLACK]);			   //Wall 10
		DrawRoundRect(469, 700, 37, 50, colors[BLACK]);			   //Wall 10
		DrawRoundRect(508, 700, 37, 50, colors[BLACK]);			   //Wall 10
		DrawRoundRect(78, 104, 37, 50, colors[BLACK]);			   //Wall 11
		DrawRoundRect(78, 52, 37, 50, colors[BLACK]);			   //Wall 11
		DrawRoundRect(78, 0, 37, 50, colors[BLACK]);			   //wall 11
		srand(time(0));
		if (ytaxi == 1)
		{
			drawYCar();
		}
		else if (rtaxi == 1)
		{
			drawRCar();
		}
		if (menu1 == 1)
		{
			drawRCar();
		}
		for (int i = 0; i <= 820; i += 39)
		{
			DrawLine(i, 0, i, 765, 1, colors[BLACK]); //lines
		}
		//passenger 1
		//
		//
		//
		//
		if (xI <= 690 && xI >= 620 && yI >= 60 && yI <= 120 && press == ' ') //condition of passenger
		{
			x = 1;

			DrawRoundRect(10, 10, 40, 40, colors[LIME_GREEN]); //end point
		}
		else
		{
			if (x == 1)
			{
				if (xI >= 0 && xI <= 60 && yI <= 60 && yI >= 0 && press == 's') //condition of block
				{
					if (point1 == true)
					{
						points1();
					}
					s1 = 1;
					DrawLine(20, 10, 20, 50, 5, colors[GREEN]); // for passenger
					z = 1;
					score = s;
				}
				else
				{
					if (z == 0)
					{
						DrawRoundRect(10, 10, 40, 40, colors[LIME_GREEN]); //for passenger
					}
					else
					{
						DrawLine(20, 10, 20, 50, 5, colors[GREEN]); // for passenger
					}
				}
			}
			else
			{
				DrawLine(645, 50, 645, 90, 5, colors[BLACK]); // for passenger
			}
		}
		//passenger 2
		//
		//
		//
		//
		if (xI <= 200 && xI >= 100 && yI >= 650 && yI <= 680 && press == ' ') //condition of passenger
		{
			y = 1;
			DrawRoundRect(720, 350, 40, 40, colors[LIME_GREEN]); //end point
		}
		else
		{
			if (y == 1)
			{
				if (xI >= 680 && xI <= 750 && yI <= 370 && yI >= 350 && press == 's') //condition of block
				{
					if (point2 == true)
					{
						points2();
					}
					s2 = 1;
					DrawLine(750, 350, 750, 390, 5, colors[GREEN]); // for passenger
					z1 = 1;
					score = s;
				}
				else
				{
					if (z1 == 0)
					{
						DrawRoundRect(720, 350, 40, 40, colors[LIME_GREEN]); //for passenger
					}
					else
					{
						DrawLine(750, 350, 750, 390, 5, colors[GREEN]); // for passenger
					}
				}
			}
			else
			{
				DrawLine(180, 660, 180, 700, 5, colors[BLACK]); // for passenger
			}
		}
		//passenger 3
		//
		//
		//
		//
		if (xI <= 590 && xI >= 550 && yI >= 300 && yI <= 370 && press == ' ') //condition of passenger
		{
			o = 1;

			DrawRoundRect(10, 281, 40, 40, colors[LIME_GREEN]); //end point
		}
		else
		{
			if (o == 1)
			{
				if (xI >= 10 && xI <= 60 && yI <= 330 && yI >= 280 && press == 's') //condition of block
				{
					if (point3 == true)
					{
						points3();
					}
					s3 = 1;
					DrawLine(30, 286, 30, 321, 5, colors[GREEN]); // for passenger
					z2 = 1;
					score = s;
				}
				else
				{
					if (z2 == 0)
					{
						DrawRoundRect(10, 281, 40, 40, colors[LIME_GREEN]); //for passenger
					}
					else
					{
						DrawLine(30, 286, 30, 321, 5, colors[GREEN]); // for passenger
					}
				}
			}
			else
			{
				DrawLine(570, 360, 570, 400, 5, colors[BLACK]); // for passenger
			}
		}
		if (stotal >= 1)
		{
			//passenger 4
			//
			//
			//
			//
			if (stotal >= 1)
			{
				if (xI >= 300 && xI <= 360 && yI <= 270 && yI >= 200 && press == ' ') //condition of passenger
				{
					c = 1;
					DrawRoundRect(700, 655, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (c == 1)
					{
						if (xI >= 700 && xI <= 741 && yI <= 700 && yI >= 656 && press == 's') //condition of block
						{
							if (point4 == true)
							{
								points4();
							}
							s4 = 1;
							DrawLine(720, 655, 720, 700, 5, colors[GREEN]); // for passenger
							z3 = 1;
							score = s;
						}
						else
						{
							if (z3 == 0)
							{
								DrawRoundRect(700, 655, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(720, 655, 720, 700, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(330, 225, 330, 265, 5, colors[BLACK]); // for passenger
					}
				}
			}
			if (stotal >= 2)
			{
				//passenger 5
				//
				//
				//
				//
				if (xI <= 441 && xI >= 391 && yI >= 450 && yI <= 470 && press == ' ') //condition of passenger
				{
					d = 1;

					DrawRoundRect(507, 50, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (d == 1)
					{
						if (xI >= 507 && xI <= 547 && yI <= 100 && yI >= 50 && press == 's') //condition of block
						{
							if (point5 == true)
							{
								points5();
							}
							s5 = 1;
							DrawLine(527, 50, 527, 90, 5, colors[GREEN]); // for passenger
							z4 = 1;
							score = s;
						}
						else
						{
							if (z4 == 0)
							{
								DrawRoundRect(507, 50, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(527, 50, 527, 90, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(421, 455, 421, 495, 5, colors[BLACK]); // for passenger
					}
				}
			}
			if (stotal >= 3)
			{
				//passenger 6
				//
				//
				//
				//
				if (xI <= 590 && xI >= 550 && yI >= 350 && yI <= 410 && press == ' ') //condition of passenger
				{
					e = 1;

					DrawRoundRect(5, 481, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (e == 1)
					{
						if (xI >= 0 && xI <= 50 && yI <= 500 && yI >= 450 && press == 's') //condition of block
						{
							if (point6 == true)
							{
								points6();
							}
							s6 = 1;
							DrawLine(20, 481, 20, 521, 5, colors[GREEN]); // for passenger
							z5 = 1;
							score = s;
						}
						else
						{
							if (z5 == 0)
							{
								DrawRoundRect(5, 481, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(20, 481, 20, 521, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(570, 360, 570, 404, 5, colors[BLACK]); // for passenger
					}
				}
			}
			if (stotal >= 4)
			{
				//passenger 7
				//
				//
				//
				//
				if (xI <= 790 && xI >= 740 && yI >= 40 && yI <= 100 && press == ' ') //condition of passenger
				{
					f = 1;

					DrawRoundRect(5, 110, 30, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (f == 1)
					{
						if (xI >= 0 && xI <= 60 && yI <= 150 && yI >= 100 && press == 's') //condition of block
						{
							if (point7 == true)
							{
								points7();
							}
							s7 = 1;
							DrawLine(20, 110, 20, 150, 5, colors[GREEN]); // for passenger
							z6 = 1;
							score = s;
						}
						else
						{
							if (z6 == 0)
							{
								DrawRoundRect(5, 110, 30, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(20, 110, 20, 150, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(765, 50, 765, 90, 5, colors[BLACK]); // for passenger
					}
				}
			}
			if (stotal >= 5)
			{
				//passenger 8
				//
				//
				//
				//
				if (xI <= 190 && xI >= 130 && yI >= 60 && yI <= 120 && press == ' ') //condition of passenger
				{
					g = 1;

					DrawRoundRect(274, 650, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (g == 1)
					{
						if (xI >= 274 && xI <= 304 && yI <= 700 && yI >= 650 && press == 's') //condition of block
						{
							if (point8 == true)
							{
								points8();
							}
							s8 = 1;
							DrawLine(294, 660, 294, 700, 5, colors[GREEN]); // for passenger
							z7 = 1;
							score = s;
						}
						else
						{
							if (z7 == 0)
							{
								DrawRoundRect(274, 650, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(294, 660, 294, 700, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(170, 60, 170, 100, 5, colors[BLACK]); // for passenger
					}
				}
			}

			if (stotal >= 6)
			{
				//passenger 9
				//
				//
				//
				//
				if (xI <= 190 && xI >= 130 && yI >= 60 && yI <= 120 && press == ' ') //condition of passenger
				{
					h = 1;

					DrawRoundRect(130, 5, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (h == 1)
					{
						if (xI >= 100 && xI <= 150 && yI <= 50 && yI >= 0 && press == 's') //condition of block
						{
							if (point9 == true)
							{
								points9();
							}
							s9 = 1;
							DrawLine(120, 5, 120, 4, 5, colors[GREEN]); // for passenger
							z8 = 1;
							score = s;
						}
						else
						{
							if (z8 == 0)
							{
								DrawRoundRect(130, 5, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(120, 5, 120, 45, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(170, 60, 170, 100, 5, colors[BLACK]); // for passenger
					}
				}
			}
			if (stotal >= 7)
			{
				//passenger 10
				//
				//
				//
				//
				if (xI <= 590 && xI >= 550 && yI >= 300 && yI <= 370 && press == ' ') //condition of passenger
				{
					i = 1;

					DrawRoundRect(5, 720, 40, 40, colors[LIME_GREEN]); //end point
				}
				else
				{
					if (i == 1)
					{
						if (xI >= 0 && xI <= 60 && yI <= 760 && yI >= 710 && press == 's') //condition of block
						{
							if (point10 == true)
							{
								points10();
							}
							s10 = 1;
							DrawLine(10, 720, 10, 760, 5, colors[GREEN]); // for passenger
							z9 = 1;
							score = s;
						}
						else
						{
							if (z9 == 0)
							{
								DrawRoundRect(5, 720, 40, 40, colors[LIME_GREEN]); //for passenger
							}
							else
							{
								DrawLine(10, 720, 10, 760, 5, colors[GREEN]); // for passenger
							}
						}
					}
					else
					{
						DrawLine(570, 360, 570, 404, 5, colors[BLACK]); // for passenger
					}
				}
			}
		}
		drawCar1();
		drawCar2();
		if (stotal >= 2)
		{
			drawCar3();
		}
		if (stotal >= 4)
		{
			drawCar4();
		}
		if (stotal >= 6)
		{
			drawCar5();
		}
		if (stotal >= 8)
		{
			drawCar6();
		}
	}
	if (s == 100)
	{
		exit(1);
	}
	stotal = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10;
	glutPostRedisplay();
	// for passenger picking up and dropdown (up till line number 217)
	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void points1() // score increment for droping player 1
{
	point1 = false;
	s = s + 10;										 // for increasing the score
	distance_cover_speed = distance_cover_speed + 1; // for increasing th distance_cover_speed
}
void points2() // score increment for droping player 2
{
	point2 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points3() // score increment for droping player 3
{
	point3 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points4() // score increment for droping player 3
{
	point4 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points5() // score increment for droping player 3
{
	point5 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points6() // score increment for droping player 3
{
	point6 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points7() // score increment for droping player 3
{
	point7 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points8() // score increment for droping player 3
{
	point8 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points9() // score increment for droping player 3
{
	point9 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}
void points10() // score increment for droping player 3
{
	point10 = false;
	s = s + 10; // for increasing the score
	distance_cover_speed = distance_cover_speed + 1;
}

void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		// what to do when left key is pressed...
		if (xI >= 8) /*condition for boundary*/
		{
			if ((xI <= 667 && xI >= 597 && yI < 411 && yI >= 345) /*condition of tree 3*/ || (xI <= 239 && xI >= 159 && yI < 711 && yI >= 645) /*condition of tree 2*/ || (xI <= 300 && xI >= 230 && yI < 284 && yI >= 218) /*condition of tree 1*/ || (xI <= 87 && yI > 395) /*condition for wall 1*/ || (yI >= 203 && yI <= 285 && xI <= 120) /*condition of second wall*/ || (yI < 150 && xI <= 130 && xI >= 80) /*condition of eleventh wall */ || (xI <= 318 && xI >= 120 && yI <= 655 && yI >= 575) /*condition of wall 4*/ || (xI <= 199 && xI >= 130 && yI <= 465 && yI >= 283) /*condition of wall 9*/ || (xI <= 360 && xI >= 210 && yI < 232 && yI >= 96) /*condition of wall 3*/ || (xI < 552 && xI >= 327 && yI <= 756 && yI >= 676) /*condition of wall 10*/ || (xI <= 473 && xI >= 287 && yI <= 458 && yI >= 376) /*condition of wall 5 (1)*/ || (xI <= 512 && xI >= 443 && yI <= 611 && yI >= 376) /*condition of wall 5 (2)*/ || (xI <= 746 && xI >= 599 && yI <= 661 && yI >= 529) /*condition of wall 6*/ || (xI <= 787 && xI >= 521 && yI <= 356 && yI >= 276) /*condition of wall 7*/ || (xI <= 746 && xI >= 443 && yI <= 156 && yI >= 76) /*condition of wall 8 (1)*/ || (xI <= 640 && xI >= 561 && yI <= 107 && yI >= 0) /*condition of wall 8 (2)*/ || (xI <= 118 && xI >= 53 && yI <= 325 && yI >= 257) /*condition of box 1*/ || (xI <= 396 && xI >= 327 && yI <= 495 && yI >= 426) /*condition of box 2*/ || (xI <= 708 && xI >= 639 && yI <= 700 && yI >= 631) /*condition of box 3*/ || (xI <= 552 && xI >= 482 && yI <= 200 && yI >= 126) /*condition of box 4*/)
			{
				xI -= 0;
			}
			else
			{
				(xI -= 6);
			}
		}
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
		if (xI <= 782) /*condition for boundary*/
		{
			if ((xI <= 652 && xI >= 592 && yI < 411 && yI >= 345) /*condition of tree 3*/ || (xI <= 224 && xI >= 159 && yI < 711 && yI >= 645) /*condition of tree 2*/ || (xI <= 285 && xI >= 225 && yI < 284 && yI >= 218) /*condition of tree 1*/ || (xI <= 35 && xI >= 4 && yI > 375) /*condition of second wall*/ || (yI <= 158 && xI <= 110 && xI >= 40) /*condition of eleventh wall */ || (xI <= 300 && xI >= 115 && yI <= 655 && yI >= 575) /*condition of wall 4*/ || (xI <= 189 && xI >= 115 && yI <= 465 && yI >= 283) /*condition of wall 9*/ || (xI <= 355 && xI >= 195 && yI < 232 && yI >= 96) /*condition of wall 3*/ || (xI < 552 && xI >= 317 && yI <= 756 && yI >= 676) /*condition of wall 10*/ || (xI <= 473 && xI >= 275 && yI <= 458 && yI >= 376) /*condition of wall 5 (1)*/ || (xI <= 500 && xI >= 430 && yI <= 611 && yI >= 376) /*condition of wall 5 (2)*/ || (xI <= 746 && xI >= 584 && yI <= 661 && yI >= 529) /*condition of wall 6*/ || (xI <= 785 && xI >= 506 && yI <= 356 && yI >= 276) /*condition of wall 7*/ || (xI <= 746 && xI >= 428 && yI <= 156 && yI >= 76) /*condition of wall 8 (1)*/ || (xI <= 620 && xI >= 546 && yI <= 107 && yI >= 0) /*condition of wall 8 (2)*/ || (xI <= 110 && xI >= 45 && yI <= 325 && yI >= 257) /*condition of box 1*/ || (xI <= 391 && xI >= 312 && yI <= 495 && yI >= 426) /*condition of box 2*/ || (xI <= 703 && xI >= 624 && yI <= 700 && yI >= 631) /*condition of box 3*/ || (xI <= 550 && xI >= 467 && yI <= 200 && yI >= 126) /*condition of box 4*/)

			{
				xI += 0;
			}
			else
			{
				(xI += 6);
			}
		}
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
		if (yI <= 730) /*condition for boundary*/
		{
			if ((yI > 378 && xI <= 80 && xI > 10) /*condition for wall 1*/ || (yI >= 195 && yI <= 270 && xI <= 110) /*condition of second wall*/ || (xI <= 313 && xI >= 125 && yI <= 655 && yI >= 570) /*condition of wall 4*/ || (xI <= 194 && xI >= 125 && yI <= 465 && yI >= 278) /*condition of wall 9*/ || (xI <= 354 && xI >= 200 && yI < 230 && yI >= 87) /*condition of wall 3*/ || (xI < 547 && xI >= 322 && yI <= 756 && yI >= 671) /*condition of wall 10*/ || (xI <= 468 && xI >= 277 && yI <= 458 && yI >= 366) /*condition of wall 5 (1)*/ || (xI <= 507 && xI >= 448 && yI <= 611 && yI >= 371) /*condition of wall 5 (2)*/ || (xI <= 741 && xI >= 589 && yI <= 661 && yI >= 524) /*condition of wall 6*/ || (xI <= 780 && xI >= 511 && yI <= 356 && yI >= 271) /*condition of wall 7*/ || (xI <= 741 && xI >= 438 && yI <= 156 && yI >= 71) /*condition of wall 8 (1)*/ || (xI <= 620 && xI >= 556 && yI <= 107 && yI >= 0) /*condition of wall 8 (2)*/ || (xI <= 115 && xI >= 45 && yI <= 316 && yI >= 252) /*condition of box 1*/ || (xI <= 391 && xI >= 322 && yI <= 495 && yI >= 421) /*condition of box 2*/ || (xI <= 703 && xI >= 634 && yI <= 700 && yI >= 626) /*condition of box 3*/ || (xI <= 547 && xI >= 477 && yI <= 200 && yI >= 121) /*condition of box 4*/)
			{
				yI += 0;
			}
			else
			{
				(yI += 6);
			}
		}
	}

	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		void move_down();
		if (yI >= 15) /*condition for boundary*/
		{
			if ((xI <= 662 && xI >= 597 && yI < 411 && yI >= 345) /*condition of tree 3*/ || (xI <= 234 && xI >= 159 && yI < 716 && yI >= 645) /*condition of tree 2*/ || (xI <= 295 && xI >= 230 && yI < 289 && yI >= 218) /*condition of tree 1*/ || (xI >= 0 && xI <= 50 && yI <= 60) /*condition of passenger 1*/ || (yI >= 250 && yI <= 290 && xI <= 115) /*condition of second wall*/ || (yI <= 165 && xI <= 110 && xI >= 45) /*condition of eleventh wall*/ || (xI <= 313 && xI >= 125 && yI <= 665 && yI >= 570) /*condition of wall 4*/ || (xI <= 194 && xI >= 125 && yI <= 470 && yI >= 283) /*condition of wall 9*/ || (xI <= 354 && xI >= 200 && yI < 238 && yI >= 87) /*condition of wall 3*/ || (xI < 547 && xI >= 322 && yI <= 762 && yI >= 676) /*condition of wall 10*/ || (xI <= 468 && xI >= 277 && yI <= 466 && yI >= 376) /*condition of wall 5 (1)*/ || (xI <= 507 && xI >= 440 && yI <= 618 && yI >= 376) /*condition of wall 5 (2)*/ || (xI <= 741 && xI >= 589 && yI <= 671 && yI >= 529) /*condition of wall 6*/ || (xI <= 780 && xI >= 511 && yI <= 366 && yI >= 276) /*condition of wall 7*/ || (xI <= 742 && xI >= 438 && yI <= 165 && yI >= 80) /*condition od wall 8 (1)*/ || (xI <= 620 && xI >= 556 && yI <= 102 && yI >= 35) /*condition of wall 8 (2)*/ || (xI <= 115 && xI >= 45 && yI <= 326 && yI >= 252) /*condition of box 1*/ || (xI <= 391 && xI >= 322 && yI <= 501 && yI >= 426) /*condition of box 2*/ || (xI <= 703 && xI >= 634 && yI <= 705 && yI >= 631) /*condition of box 3*/ || (xI <= 550 && xI >= 477 && yI <= 205 && yI >= 126) /*condition of box 4*/)
			{
				yI -= 0;
			}
			else
			{
				yI -= 7;
			}
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

int space_counter = 0;

void PrintableKeys(unsigned char key, int x, int y)
{
	//Asci escape
	if (key == 27)
	{
		ofstream FileWrite;
		FileWrite.open("highscores.txt", ios::app);

		FileWrite << name;
		FileWrite << ',';
		FileWrite << score;
		FileWrite << '\n';

		FileWrite.close();
		exit(1); // exit the program when escape key is pressed.
	}

	bool space_namekey = false;
	if (name_entry == -1)
	{

		//Trimming string by one
		if (key == 8)
		{
			if (name.length() != 0)
			{
				name = name.substr(0, name.length() - 1);
			}
		}

		bool alphabet = false;
		for (int i = 0; i <= 25; i++)
		{
			if (key == (97 + i) || key == (65 + i)) //Ascii of a and A
			{
				name += key;
				alphabet = true;
			}
		}

		if (alphabet == false)
		{
			if (key == 32)
			{
				name += key;
				space_namekey = true;
			}
		}
	}

	if (key == 32 && space_namekey == false)
	{

		if ((space_counter % 2) == 0)
		{
			press = ' ';
		}
		else
		{
			press = 's';
		}
		space_counter++;
	}

	if (name_entry == 1)
	{

		if (key == 121 || key == 89) //ascii of y
		{
			ytaxi = 1;
		}
		if (key == 114 || key == 82) //ascii of r
		{
			rtaxi = 1;
		}

		if (key == 13)
		{
			if (board == 0)
			{
				menu = 2;
				menu1 = 1;
			}

			if (board == -1)
			{
				board = 0;
			}

			if (board == 1)
			{
				menu = 2;
				menu1 = 1;
			}
		}

		else if (key == 76 || key == 108)
		{
			if (board == 0)
			{
				board = 1;
			}
		}
	}
	else if (key == 13)
	{
		if (name != "")
		{
			name_entry = 1;

			if (key == 13)
			{
				if (board == -1)
				{
					board = 0;
				}

				if (board == 1)
				{
					menu = 2;
					menu1 = 1;
				}
			}

			else if (key == 76 || key == 108)
			{
				if (board == 0)
				{
					board = 1;
				}
			}
		}
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * distance_cover_speed of different moving objects by varying the constant FPS.
 *
 * */

bool flag = true;
void moveCar1()
{

	if (xcar1 >= 10 && flag)
	{
		xcar1 -= distance_cover_speed; // for moving random vehicles
		if (xcar1 < 210)			   // FOR GOING LEFT

			flag = false;
	}
	else if (xcar1 < 310 && !flag)
	{
		xcar1 += distance_cover_speed; // for moving random vehicles
		if (xcar1 > 270)			   // FOR GOING RIGHT
			flag = true;
	}
}
bool flag2 = true;
void moveCar2()
{

	if (ycar2 >= 10 && flag2)
	{
		ycar2 -= distance_cover_speed; // for moving random vehicles
		if (ycar2 < 370)			   //FOR GOING LEFT

			flag2 = false;
	}
	else if (ycar2 < 580 && !flag2)
	{
		ycar2 += distance_cover_speed; // for moving random vehicles
		if (ycar2 > 470)			   // FOR GOING RIGHT
			flag2 = true;
	}
}
bool flag3 = true;
void moveCar3()
{
	srand(time(0));
	if (xcar3 >= 10 && flag3)
	{
		xcar3 -= distance_cover_speed; // for moving random vehicles
		if (xcar3 < 370)			   //FOR GOING LEFT

			flag3 = false;
	}
	else if (xcar3 < 580 && !flag3)
	{
		xcar3 += distance_cover_speed; // for moving random vehicles
		if (xcar3 > 450)			   // FOR GOING RIGHT
			flag3 = true;
	}
}
bool flag4 = true;
void moveCar4()
{
	srand(time(0));
	if (ycar4 >= 10 && flag4)
	{
		ycar4 += distance_cover_speed; // for moving random vehicles
		if (ycar4 >= 370)			   //FOR GOING LEFT

			flag4 = false;
	}
	else if (ycar4 < 380 && !flag4)
	{
		ycar4 -= distance_cover_speed; // for moving random vehicles
		if (ycar4 <= 155)			   // FOR GOING RIGHT
			flag4 = true;
	}
}
bool flag5 = true;
void moveCar5()
{
	srand(time(0));
	if (xcar5 >= 10 && flag5)
	{
		xcar5 -= distance_cover_speed; // for moving random vehicles
		if (xcar5 < 370)			   //FOR GOING LEFT

			flag5 = false;
	}
	else if (xcar5 < 580 && !flag5)
	{
		xcar5 += distance_cover_speed; // for moving random vehicles
		if (xcar5 > 450)			   // FOR GOING RIGHT
			flag5 = true;
	}
}
bool flag6 = true;
void moveCar6()
{
	srand(time(0));
	if (ycar6 >= 10 && flag6)
	{
		ycar6 -= distance_cover_speed; // for moving random vehicles
		if (ycar6 < 370)			   //FOR GOING LEFT

			flag6 = false;
	}
	else if (ycar6 < 380 && !flag6)
	{
		xcar3 += distance_cover_speed; // for moving random vehicles
		if (ycar3 > 155)			   // FOR GOING RIGHT
			flag3 = true;
	}
}
void Timer(int m)
{

	// implement your functionality here
	moveCar1();
	moveCar2();
	if (stotal >= 2)
	{
		moveCar3();
	}
	if (stotal >= 4)
	{
		moveCar4();
	}
	if (stotal >= 6)
	{
		moveCar5();
	}
	if (stotal >= 8)
	{
		moveCar6();
	}

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(20, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y)
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */

void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{

	int width = 818, height = 820; // i have set my window size to be 800 x 600

	InitRandomizer();							   // seed the random number generator...
	glutInit(&argc, argv);						   // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // we will be using color display mode
	glutInitWindowPosition(50, 50);				   // set the initial position of our window
	glutInitWindowSize(width, height);			   // set the size of our window
	glutCreateWindow("Rush Hour by Waiz Zubairi"); // set the title of our game window
	SetCanvasSize(width, height);				   // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	// tell library which function to call for drawing enu Canvas.
	glutDisplayFunc(GameDisplay);	   // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...

	glutMainLoop();

	return 1;
}
#endif /* RushHour_CPP_ */
