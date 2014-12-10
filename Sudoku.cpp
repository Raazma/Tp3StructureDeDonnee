/*	Projet: Sudoku
*	Fichier: Sudoku.cpp
*	Date: 2014-12-09
*	Fait Par: Frédéric Paquette et Francis Lemaire
*	Description: Fichier de définition des méthodes de la classe Sudoku qui représente un jeux de Sudoku pouvant se résoudre
*/

#include "Sudoku.h"



using namespace std;

// constructeur qui passe au constructeur de base le flux d'entrée
// et appelle ensuite Solutionner et lui passant le flux de sortie
Sudoku::Sudoku(ifstream &test, ostream & sortie) :Sudoku(test)
{
	Solutionner(sortie);
}

//Constructeur de base qui prend le flux d'entrée et copie le sudoku dans la structure pour le traitement
Sudoku::Sudoku(ifstream &test) 
{
	//le constructeur est a ameliorer on doit lui passer un ostream et un ifstream en
	//parametre oh lui de toute faire direct dedans comme je le fait
	
	char su;
	int i = 0;
	int j = 0;
	
	leSudoku_.SetNbLignes(NBLIGNE);
	leSudoku_.SetNbColonnes(NBCOLONE);

	while (!test.eof())
	{
		su = test.get();		
		if (su != '\n')
		{        
			if (i < NBLIGNE && j < NBCOLONE)
			{								
				leSudoku_[i][j] = atoi(&su); //atoi cast les char en int et ce qui est magique, * vaux 0 de base
				j++;
			}			
			if (j == NBCOLONE)
			{
				i++;
				j = 0;
			}				
		 }
	}
			
}

// Méthode public pour trouver la solution et compter le temps que cela prend
void Sudoku::Solutionner(ostream & sortie)
{
	this->horloge.Start();
	if (TrouverSolution(0, 0)) //si la solution a été trouver j'affiche
	{
		this->horloge.Stop();
		AfficherSolution(sortie);
		sortie <<"Temps(µs): "<< this->horloge.Read()<<endl;
	}
		
}

//Trouve la solution du Sudoku
inline bool Sudoku::TrouverSolution(int i, int j)
{
	if (SudokuPlein()) // si le sudoku est plein alors la solution est trouver
		  return true;
	
	if (Normaliser(i, j) && EstPositionValide(i, j)) // s'assure que la postion est dans la grille de jeu et verifie que la postion est une position a changer la valeur
	{

		for (size_t z = 1; z <= NBVALEUR; ++z)
		{
			if (ChiffreValide(i, j, z))
			{
				leSudoku_[i][j] = z;
				if (TrouverSolution(i, j + 1)) // rappele la fonction et return true si la solution est trouver
					return true;
			}
		}
		leSudoku_[i][j] = NULLVALUE; // aucun chiffre etait valide on doit la reinisialiser a 0 
		return false;

	}
	else
	  return TrouverSolution(i, j + 1); // la position etait pas valide donc rapelle la fonction avec une nouvelle pos

}

// Normalise s'assure que les valeur passé en paramêtre sons dans les bornes si non nous changeon de ligne
// et remettons la colone à 0 à moins que nous ayons dépasser alors elle retourne false (autre cas retourne true)
inline bool Sudoku::Normaliser(int &i,int &j)
{
	if (i < NBLIGNE && j < NBCOLONE)
		return true;
	if (j >= NBCOLONE)
	{
		++i;
		j = 0;
		return Normaliser(i,j);
	}   

 return false;
	
}

//Vérifie que la postion est valide (Égale à NULLVALUE)
inline bool Sudoku::EstPositionValide(int i, int j)
{
	if (leSudoku_[i][j] == NULLVALUE)
		return true;
	else 
	   return false;
}

// Vérifie que le chiffre est valide
inline bool Sudoku::ChiffreValide(int i, int j, int z)
{
	return VerificationVerticale(j, z) &&
		      VerificationHorizontal(i, z) &&
	            	VerificationCadran(i - i % 3, j - j % 3, z);	
}

// affiche le Sudoku dans une grille dans la sortie préciser
void Sudoku::AfficherSolution(ostream & sortie)
{
	sortie << StartStopSudokuDeco << endl << ValueSeparatorSudokuDeco << " "; //affichage des décoration
	
	for (size_t i = 0; i < NBLIGNE; i++)
	{
		if (i!=0)
			sortie << InterLigneSudokuDeco << endl << ValueSeparatorSudokuDeco << " "; //affichage des décoration

		for (size_t j = 0; j < NBCOLONE; j++)
		{
			sortie << leSudoku_[i][j] << 
				" " << ValueSeparatorSudokuDeco << " "; //affichage des décoration
		}
		sortie << endl;
	}
	sortie << StartStopSudokuDeco << endl;	//affichage des décoration
}

// Vérifie s'il reste des case vide dans le Sudoku
inline bool Sudoku::SudokuPlein()
{
	for (size_t i = 0; i < NBLIGNE; i++)
		if (find(leSudoku_[i].begin(), leSudoku_[i].end(), NULLVALUE) != leSudoku_[i].end())
			return false;

 return true;
}

//	Vérifie si la valeur de cellule (passé en paramêtre z) se trouve déjà sur la colone (passé en paramêtre j)
inline bool Sudoku::VerificationVerticale(int j, int z)
{
	for (size_t w = 0; w < NBLIGNE; w++)
	{
		if (leSudoku_[w][j] == z)
			return false;
	}
		 
	return true;

}

//	Vérifie si la valeur de cellule (passé en paramêtre z) se trouve déjà sur la ligne (passé en paramêtre i)
inline bool  Sudoku::VerificationHorizontal(int i, int z)
{

	if (find(leSudoku_[i].begin(), leSudoku_[i].end(), z) != leSudoku_[i].end())
		return false;

	return true;

}

//	Vérifie le cadran 3x3 ou se situe la cellule (passé en paramêtre [i,j]) 
//	et vérifie si le chiffre (passé en paramêtre z) s'y trouve déjà
inline bool Sudoku::VerificationCadran(int i, int j, int z)
{
	for (size_t w = 0; w < 3; w++)
		if (find(leSudoku_[i + w].begin() + j, leSudoku_[i + w].begin() + j + 3, z) != leSudoku_[i + w].begin() + j + 3)
			return false;
			
	return true;
}