#include <string>
#include <iostream>
#include <ncurses.h>
#include "Pieza.h"
#include <exception>
using namespace std;
Pieza* show(Pieza***);
int* Move(Pieza***);
Pieza*** setGame();
bool NoCollision(int*, Pieza***);
bool CanMove(Pieza*, int*);
bool CanEat(Pieza*, int*, Pieza***);
bool Crown(Pieza*, int*);
int main() {
	int P1Alive;
	int P2Alive;
	initscr();
	Pieza*** Tabla = setGame();
	Pieza* NullPiece;
	//set P1 Pieces
	//row1
	Tabla[0][1] = new Pieza(1, 0, 1);
	Tabla[0][3] = new Pieza(1, 0, 3);
	Tabla[0][5] = new Pieza(1, 0, 5);
	Tabla[0][7] = new Pieza(1, 0, 7);
	//row2
	Tabla[1][0] = new Pieza(1, 1, 0);
	Tabla[1][2] = new Pieza(1, 1, 2);
	Tabla[1][4] = new Pieza(1, 1, 4);
	Tabla[1][6] = new Pieza(1, 1, 5);
	//row3
	Tabla[2][1] = new Pieza(1, 2, 1);
	Tabla[2][3] = new Pieza(1, 2, 3);
	Tabla[2][5] = new Pieza(1, 2, 5);
	Tabla[2][7] = new Pieza(1, 2, 7);
	//set P2 Pieces
	Tabla[7][0] = new Pieza(2, 7, 0);
	Tabla[7][2] = new Pieza(2, 7, 2);
	Tabla[7][4] = new Pieza(2, 7, 4);
	Tabla[7][6] = new Pieza(2, 7, 6);
	Pieza* Selected;
	int* Position;
	bool EndGame = true;
	int Turn = 1;
	int X = 1;
	while (EndGame) {
		Selected = show(Tabla);
		addstr(to_string(Selected->getXPos()).c_str());
		//getch();
		switch (Turn) {
			case 1: {
				/*while (Selected->get) {

				}*/
				Position = Move(Tabla);
				addstr(to_string(Position[0]).c_str());
				getch();
				if (CanMove(Selected, Position)&&(NoCollision(Position, Tabla))) {
					Tabla[Position[1]][Position[0]] = Selected;
					NullPiece = new Pieza(-1, Position[1], Position[0]);
					Tabla[Selected->getYPos()][Selected->getXPos()] = NullPiece;
					Selected->setXPos(Position[0]);
					Selected->setYPos(Position[1]);
					Crown(Selected, Position);
					//Turn = 2;
				}
				if (CanEat(Selected, Position, Tabla)&&(NoCollision(Position, Tabla))) {
					Tabla[Position[1]][Position[0]] = Selected;
					NullPiece = new Pieza(-1, Position[1], Position[0]);
					Tabla[Selected->getYPos()][Selected->getXPos()] = NullPiece;
					Selected->setXPos(Position[0]);
					Selected->setYPos(Position[1]);
					Crown(Selected, Position);
				}
				if (Selected->isGeneral()&&NoCollision(Position, Tabla)) {
					Tabla[Position[1]][Position[0]] = Selected;
					NullPiece = new Pieza(-1, Position[1], Position[0]);
					Tabla[Selected->getYPos()][Selected->getXPos()] = NullPiece;
					Selected->setXPos(Position[0]);
					Selected->setYPos(Position[1]);
					//Crown(Selected, Position);
				}
			} break;
			case 2: {

			} break;
		}
		P1Alive = 0;
		P2Alive = 0;
		for (int i = 0;i<8;i++) {
			for (int j = 0;j<8;j++) {
				if (Tabla[i][j]->getPlayer()==1) {
					P1Alive++;
				}
				if (Tabla[i][j]->getPlayer()==2) {
					P2Alive++;
				}	
			}
		}
		addstr(("P1 pieces:"+(to_string(P1Alive))).c_str());
		addstr("\n");
		addstr(("P2 pieces:"+(to_string(P2Alive))).c_str());
		getch();
		if ((P1Alive == 0)||(P2Alive == 0)) {
			EndGame = false;
		}
	}
	if (P1Alive==0) {
		addstr("\n Gano el jugador 2!");
	}	
	if (P2Alive==0) {
		addstr("\n Gano el jugador 1!");
	}

	endwin();
	return 0;
}
Pieza*** setGame() {
	Pieza*** Matriz = new Pieza**[8];
	for (int i = 0;i<8;i++) {
		Matriz[i] = new Pieza*[8];
	}
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			Matriz[i][j] = new Pieza(-1, i, j);
		}
	}
	return Matriz;
}
Pieza* show(Pieza*** Tabla) {
	//Se le ingresa la matriz, y las longitudes de la tabla
	//Devuelve un arreglo, la posicion [0] es la pos. X, la posicion [1] es el Y
	Pieza* Selected;	
	char ch = '.';
	int x = 0;
	int y = 0;
	while (ch !='\n') {	
		clear();
		addstr("Select: \n");
		for (int i = 0;i<8;i++) {
			for (int j = 0;j<8;j++) {
				string Esto = "[";
				Esto += (Tabla[i][j]->getChar());
				Esto += "]";
				if ((x==j)&&(y==i)) {
					Esto+= "<-";
				} else {
					Esto+= "  ";
				}
				addstr(Esto.c_str());
			}
			addstr("\n");
		}
		addstr(("x: "+to_string(x)+"\n").c_str());
		addstr(("y: "+to_string(y)+"\n").c_str());
		ch = getch();
		//Key Down == 66
		if (ch == 66) {
			y++;
			if (y >= 8) {
				y = 0;
			}
		}
		//Key UP == 65
		if (ch == 65) {
			y--;
			if (y < 0) {
				y = 7;
			}
		}
		//Key Left == 68
		if (ch == 68) {
			x--;
			if (x < 0) {
				x = 7;
			}
		}
		//Key Right == 67
		if (ch == 67) {
			x++;
			if (x >= 8) {
				x = 0;
			}
		}
	}
	Selected = Tabla[y][x];
	return Selected;
}
int* Move(Pieza*** Tabla) {
	//Se le ingresa la matriz, y las longitudes de la tabla
	//Devuelve un arreglo, la posicion [0] es la pos. X, la posicion [1] es el Y
	int* XY = new int[2];
	char ch = '.';
	int x = 0;
	int y = 0;
	while (ch !='\n') {	
		clear();
		addstr("Move: \n");
		for (int i = 0;i<8;i++) {
			for (int j = 0;j<8;j++) {
				string Esto = "[";
				Esto += (Tabla[i][j]->getChar());
				Esto += "]";
				if ((x==j)&&(y==i)) {
					Esto+= "<-";
				} else {
					Esto+= "  ";
				}
				addstr(Esto.c_str());
			}
			addstr("\n");
		}
		addstr(("x: "+to_string(x)+"\n").c_str());
		addstr(("y: "+to_string(y)+"\n").c_str());
		ch = getch();
		//Key Down == 66
		if (ch == 66) {
			y++;
			if (y >= 8) {
				y = 0;
			}
		}
		//Key UP == 65
		if (ch == 65) {
			y--;
			if (y < 0) {
				y = 7;
			}
		}
		//Key Left == 68
		if (ch == 68) {
			x--;
			if (x < 0) {
				x = 7;
			}
		}
		//Key Right == 67
		if (ch == 67) {
			x++;
			if (x >= 8) {
				x = 0;
			}
		}
	}
	XY[0] = x;
	XY[1] = y;
	return XY;
}
bool Crown(Pieza* Selected, int* Position) {
	bool InEnd;
	if (Selected->getPlayer()==2) {
		if (Selected->getYPos()==0) {
			Selected->setGeneral(true);
		}
	}
	if (Selected->getPlayer()==1) {
		if (Selected->getYPos()==7) {
			Selected->setGeneral(true);
		}
	}
	return true;
}
bool CanMove(Pieza* Selected, int* Position) {
	return(				
	((Selected->getXPos()+1)==Position[0])&&((Selected->getYPos()+1)==Position[1]) ||
	((Selected->getXPos()+1)==Position[0])&&((Selected->getYPos()-1)==Position[1]) ||
	((Selected->getXPos()-1)==Position[0])&&((Selected->getYPos()-1)==Position[1]) ||
	((Selected->getXPos()-1)==Position[0])&&((Selected->getYPos()+1)==Position[1])
	);
}
bool CanEat(Pieza* Selected, int* Position, Pieza*** Tabla) {
	int Enemy = 0;
	if (Selected->getPlayer() == 1) {
		Enemy = 2;
	}
	if (Selected->getPlayer() == 2) {
		Enemy = 1;
	}
	if (((Selected->getXPos()+2)==Position[0])&&((Selected->getYPos()+2)==Position[1])) {
		if ((Tabla[Position[1]-1][Position[0]-1])->getPlayer()==Enemy) {
			Tabla[Position[1]-1][Position[0]-1] = new Pieza(-1, 0, 0);
			return true;
		}
	}
	if (((Selected->getXPos()-2)==Position[0])&&((Selected->getYPos()-2)==Position[1])) {
		if ((Tabla[Position[1]+1][Position[0]+1])->getPlayer()==Enemy) {
			Tabla[Position[1]+1][Position[0]+1] = new Pieza(-1, 0, 0);
			return true;
		}
	}
	if (((Selected->getXPos()+2)==Position[0])&&((Selected->getYPos()-2)==Position[1])) {
		if ((Tabla[Position[1]+1][Position[0]-1])->getPlayer()==Enemy) {
			Tabla[Position[1]+1][Position[0]-1] = new Pieza(-1, 0, 0);
			return true;
		}
	}
	if (((Selected->getXPos()-2)==Position[0])&&((Selected->getYPos()+2)==Position[1])) {
		if ((Tabla[Position[1]-1][Position[0]+1])->getPlayer()==Enemy) {
			Tabla[Position[1]-1][Position[0]+1] = new Pieza(-1, 0, 0);
			return true;
		}
	}
	return false;
}
bool NoCollision(int* Position, Pieza*** Tabla) {
	if ((Tabla[Position[1]][Position[0]]->getPlayer())==-1)	{
		return true;
	} else {
		return false;
	}
}

