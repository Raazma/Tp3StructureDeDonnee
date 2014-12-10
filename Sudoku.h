/*	Projet: Sudoku
*	Fichier: Sudoku.h
*	Date: 2014-12-09
*	Fait Par: Frédéric Paquette et Francis Lemaire
*	Description: Fichier de déclaration des méthodes de la classe Sudoku qui représente un jeux de Sudoku pouvant se résoudre
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
	//Constante Numérique du Sudoku
	const int NBCOLONE = 9;
	const int NBLIGNE = 9;
	const int NBVALEUR = 9;
	const int NULLVALUE = 0;

	//Constante de décoration de l'affichage du Sudoku
	const string StartStopSudokuDeco = "-------------------------------------";
	const string InterLigneSudokuDeco = "|---+---+---+---+---+---+---+---+---|";
	const string ValueSeparatorSudokuDeco = "|";

private:
	Chrono horloge;
	Matrice<int> leSudoku_;

	//Trouve la solution du Sudoku
	bool TrouverSolution(int i, int j);

	// Vérifie s'il reste des case vide dans le Sudoku
	bool SudokuPlein();

	// Normalise s'assure que les valeur passé en paramêtre sons dans les bornes si non nous changeon de ligne
	// et remettons la colone à 0 à moins que nous ayons dépasser alors elle retourne false (autre cas retourne true)
	bool Normaliser(int &i,int &j);

	//Vérifie que la postion est valide (Égale à NULLVALUE)
	bool EstPositionValide(int i,int j);

	// Vérifie que le chiffre est valide
	bool ChiffreValide( int i, int j,int z);

	//	Vérifie si la valeur de cellule (passé en paramêtre z) se trouve déjà sur la colone (passé en paramêtre j)
	bool VerificationVerticale(int j, int z);

	//	Vérifie si la valeur de cellule (passé en paramêtre z) se trouve déjà sur la ligne (passé en paramêtre i)
	bool VerificationHorizontal(int i, int z);

	//	Vérifie le cadran 3x3 ou se situe la cellule (passé en paramêtre [i,j]) 
	//	et vérifie si le chiffre (passé en paramêtre z) s'y trouve déjà
	bool VerificationCadran(int i, int j, int z);

	// affiche le Sudoku dans une grille dans la sortie préciser
	void AfficherSolution(ostream & sortie);
public:

	//Constructeur de base qui prend le flux d'entrée et copie le sudoku dans la structure pour le traitement
	Sudoku(ifstream &test);

	// constructeur qui passe au constructeur de base le flux d'entrée
	// et appelle ensuite Solutionner et lui passant le flux de sortie
	Sudoku(ifstream &test, ostream & sortie);

	// Méthode public pour trouver la solution et compter le temps que cela prend
	void Solutionner(ostream & sortie);
	
};