#include <iostream>
#include <string>
#include <fstream>
#include "ClassMaker.h"
using namespace std;
void ClassMaker::MakeClass() {
	//declaracion
	string ClassName;
	string HeaderName;
	string CppName;
	int NumAtr;
	//Pedir caracteristicas:
	cout << "Nombre de la clase: ";
	cin >> ClassName;
	cout << "Numero de Atributos: ";
	cin >> NumAtr;
	HeaderName = ClassName+".h";
	CppName = ClassName+".cpp";
	//Pedir Tipo y nombre de atributos:
	string* ArAtr = new string[NumAtr+1];
	string* tipo = new string[NumAtr+1];
	for (int i = 0;i<NumAtr;i++) {
		cout << "Tipo?: ";		
		cin >> tipo[i];
		cout << "Nombre?: ";
		cin >> ArAtr[i];
	}	
//Empieza a Escribir header:	
	ofstream writeFile(HeaderName.c_str());
	writeFile <<"#pragma once" << "\n";
	writeFile <<"#include <iostream>" << "\n";
	writeFile <<"#include <string>" << "\n";
	writeFile <<"using namespace std;" << "\n";
	writeFile << "class " << ClassName << " {" << "\n";
	//Atributos privados
	writeFile << "	private: " << "\n";
	for (int i = 0; i<NumAtr; i++) {
		writeFile << "		" << tipo[i] << " " << ArAtr[i] << ";" << "\n";
	}
	//atributos publicos
	writeFile << "	public: " << "\n";
		//constructor
	writeFile << "		" << ClassName << "(";
	for (int i = 0;i<NumAtr;i++) {
		writeFile << tipo[i];
		if (i < (NumAtr-1)) {
			writeFile << ", ";
		}
	}
	writeFile << ");" << "\n";
		//setters
	for (int i = 0;i<NumAtr;i++) {
		writeFile << "		void " << " set" << ArAtr[i] << "(" << tipo[i] << ");" << "\n";
	}
		//getters
	for (int i = 0;i<NumAtr;i++) {
		writeFile << "		" << tipo[i] << " get" << ArAtr[i] << "();" << "\n";	
	}
	writeFile<< "};" << "\n";
	writeFile.close();
//Empieza a escribir cpp
	//includes
	ofstream writeFile2(CppName.c_str());
	writeFile2 << "#include " << (char)34 << HeaderName << (char)34 << "\n";
	writeFile2 <<"#include <iostream>" << "\n";
	writeFile2 <<"#include <string>" << "\n";
	writeFile2 <<"using namespace std;" << "\n";
//constructor
	writeFile2 << "	" << ClassName << "::" << ClassName << "(";
	for (int i = 0;i<NumAtr;i++) {
		writeFile2 << tipo[i] << " " << ArAtr[i];
		if (i < (NumAtr-1)) {
			writeFile2 << ", ";
		}
	}
	writeFile2 << ") { \n";
	for (int i = 0;i<NumAtr;i++) {
		writeFile2 << "		" << "set" << ArAtr[i] << "(" << "" << ArAtr[i] << ");\n";
	}
	writeFile2 << "	}\n";
//setters
	for (int i = 0;i<NumAtr;i++) {
		writeFile2 << "	void " << ClassName << "::set" << ArAtr[i] << "(" << tipo[i] << " a) {" << "\n";
		writeFile2 << "		this->" << ArAtr[i] << " = a;"<< "\n";
		writeFile2 << "	}" << "\n";
	}
//getters
	for (int i = 0;i<NumAtr;i++) {
		writeFile2 << "	"<< tipo[i] << " " << ClassName << "::get" << ArAtr[i] << "() {" << "\n";
		writeFile2 << "		return this->" << ArAtr[i] << ";" << "\n";
		writeFile2 << "	}" << "\n";
	}
	writeFile2.close();
//delete
	delete[] ArAtr;
	delete[] tipo;
}
