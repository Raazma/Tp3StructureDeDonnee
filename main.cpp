/*	Projet: Sudoku
*	Fichier: main.cpp
*	Date: 2014-12-09
*	Fait Par: Frédéric Paquette et Francis Lemaire
*	Description: Fichier principal du projet qui résoue un Sudoku
*/
#pragma warning (disable : 4290)
#include"Sudoku.h"
#include <iostream>
#include <string>
using namespace std;


int main()
{
	setlocale(LC_ALL, ""); //Permet d'afficher le caractèr µ dans la console

	ifstream sudo("TheSudoku.txt");
	Sudoku lesudoku(sudo, cout);

}
