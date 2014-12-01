#pragma once

#include <iostream>
#include "Matrice.h"
#include "Chrono.h"
#include <fstream>
using namespace std;



class Sudoku
{

public:
	Sudoku();
	void Solutionner();
	Chrono horloge;

private:
	Matrice<int> leSudoku_;
	bool TrouverSolution(int i, int j);
	bool SudokuPlein();
	bool Normaliser(int &i,int &j);
	bool PositionValide(int i,int j);
	bool ChiffreValide( int i, int j,int z);
	bool VerificationVerticale(int i, int j, int z);
	bool  VerificationHorizontal(int i, int j, int z);
	bool VerificationCadran(int i, int j, int z);
	bool SolutionTrouver();
	void AfficherSolution();

};