#pragma once
#include <iostream>
#include <string>
using namespace std;
class Pieza {
	private: 
		int Player;
		int XPos;
		int YPos;
		bool General;
		char Model;
	public: 
		Pieza(int, int, int);
		void  setPlayer(int);
		void  setXPos(int);
		void  setYPos(int);
		void  setChar(char);
		bool  isGeneral();
		void  setGeneral(bool);
		char getChar();
		int getPlayer();
		int getXPos();
		int getYPos();
};
