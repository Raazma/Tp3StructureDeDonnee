/*	Projet: Sudoku
*	Fichier: Sudoku.h
*	Date: 2014-12-09
*	Fait Par: Fr�d�ric Paquette et Francis Lemaire
*	Description: Fichier de d�claration des m�thodes de la classe Sudoku qui repr�sente un jeux de Sudoku pouvant se r�soudre
*/
#pragma once

#include <iostream>
#include "Matrice.h"
#include "Chrono.h"
#include <fstream>
#include <string>

using namespace std;



class Sudoku
{
	//Constante Num�rique du Sudoku
	const int NBCOLONE = 9;
	const int NBLIGNE = 9;
	const int NBVALEUR = 9;
	const int NULLVALUE = 0;

	//Constante de d�coration de l'affichage du Sudoku
	const string StartStopSudokuDeco = "-------------------------------------";
	const string InterLigneSudokuDeco = "|---+---+---+---+---+---+---+---+---|";
	const string ValueSeparatorSudokuDeco = "|";

private:
	Chrono horloge;
	Matrice<int> leSudoku_;

	//Trouve la solution du Sudoku
	bool TrouverSolution(int i, int j);

	// V�rifie s'il reste des case vide dans le Sudoku
	bool SudokuPlein();

	// Normalise s'assure que les valeur pass� en param�tre sons dans les bornes si non nous changeon de ligne
	// et remettons la colone � 0 � moins que nous ayons d�passer alors elle retourne false (autre cas retourne true)
	bool Normaliser(int &i,int &j);

	//V�rifie que la postion est valide (�gale � NULLVALUE)
	bool EstPositionValide(int i,int j);

	// V�rifie que le chiffre est valide
	bool ChiffreValide( int i, int j,int z);

	//	V�rifie si la valeur de cellule (pass� en param�tre z) se trouve d�j� sur la colone (pass� en param�tre j)
	bool VerificationVerticale(int j, int z);

	//	V�rifie si la valeur de cellule (pass� en param�tre z) se trouve d�j� sur la ligne (pass� en param�tre i)
	bool VerificationHorizontal(int i, int z);

	//	V�rifie le cadran 3x3 ou se situe la cellule (pass� en param�tre [i,j]) 
	//	et v�rifie si le chiffre (pass� en param�tre z) s'y trouve d�j�
	bool VerificationCadran(int i, int j, int z);

	// affiche le Sudoku dans une grille dans la sortie pr�ciser
	void AfficherSolution(ostream & sortie);
public:

	//Constructeur de base qui prend le flux d'entr�e et copie le sudoku dans la structure pour le traitement
	Sudoku(ifstream &test);

	// constructeur qui passe au constructeur de base le flux d'entr�e
	// et appelle ensuite Solutionner et lui passant le flux de sortie
	Sudoku(ifstream &test, ostream & sortie);

	// M�thode public pour trouver la solution et compter le temps que cela prend
	void Solutionner(ostream & sortie);
	
};