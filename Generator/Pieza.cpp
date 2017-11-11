#include "Pieza.h"
#include <iostream>
#include <string>
using namespace std;
	Pieza::Pieza(int Player, int XPos, int Ypos) { 
		setPlayer(Player);
		setXPos(XPos);
		setYpos(Ypos);
	}
	void Pieza::setPlayer(int a) {
		this->Player = a;
	}
	void Pieza::setXPos(int a) {
		this->XPos = a;
	}
	void Pieza::setYpos(int a) {
		this->Ypos = a;
	}
	int Pieza::getPlayer() {
		return this->Player;
	}
	int Pieza::getXPos() {
		return this->XPos;
	}
	int Pieza::getYpos() {
		return this->Ypos;
	}
