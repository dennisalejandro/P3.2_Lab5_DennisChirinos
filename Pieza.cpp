#include "Pieza.h"
#include <iostream>
#include <string>
using namespace std;
	Pieza::Pieza(int Player, int Ypos, int Xpos) { 
		setPlayer(Player);
		this->XPos = Xpos;
		this->YPos = Ypos;
		if (Player == -1) {
			setChar(' ');
		}
		if (Player == 1) {
			setChar('x');
		}
		if (Player == 2) {
			setChar('o');
		}
	}
	bool  Pieza::isGeneral() {
		return this->General;
	}
	void  Pieza::setGeneral(bool a) {
		if (a) {
			if (getChar()=='x') {
				setChar('W');
			}
			if (getChar()=='o') {
				setChar('C');
			}
		}
		this->General = a;
	}
	void Pieza::setChar(char a) {
		this->Model = a;
	}
	char Pieza::getChar() {
		return this->Model;
	}
	void Pieza::setPlayer(int a) {
		this->Player = a;
	}
	void Pieza::setXPos(int a) {
		this->XPos = a;
	}
	void Pieza::setYPos(int a) {
		this->YPos = a;
	}
	int Pieza::getPlayer() {
		return this->Player;
	}
	int Pieza::getXPos() {
		return this->XPos;
	}
	int Pieza::getYPos() {
		return this->YPos;
	}
