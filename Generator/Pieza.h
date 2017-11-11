#pragma once
#include <iostream>
#include <string>
using namespace std;
class Pieza {
	private: 
		int Player;
		int XPos;
		int Ypos;
	public: 
		Pieza(int, int, int);
		void  setPlayer(int);
		void  setXPos(int);
		void  setYpos(int);
		int getPlayer();
		int getXPos();
		int getYpos();
};
