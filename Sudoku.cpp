#include "Sudoku.h"
#include <string>

using namespace std;

Sudoku::Sudoku()
{
	//le constructeur est a ameliorer on doit lui passer un ostream et un ifstream en
	//parametre oh lui de toute faire direct dedans comme je le fait
	ifstream test;
	test.open("TheSudoku.txt");
	char su;
	int i = 0;
	int j = 0;
	//int tesfft = 0;
	leSudoku_.SetNbLignes(9);
	leSudoku_.SetNbColonnes(9);

	while (!test.eof())
	{
		su = test.get();		
		if (su != '\n')
		{        
			if (i <= 8 && j <= 8)
			{								
				leSudoku_[i][j] = atoi(&su); //atoi cast les char en int et ce qui est magique * vaux 0 de base thats magic
				j++;
			}			
			if (j == 9)
			{
				i++;
				j = 0;
			}				
		 }
	}
			
}

void Sudoku::Solutionner()
{
	this->horloge.Start();
	if (TrouverSolution(0, 0)) //si la solution a ete trouver jaffiche
	{
		this->horloge.Stop();
		AfficherSolution();
	}
		
}

bool Sudoku::TrouverSolution(int i, int j)
{
	if (SudokuPlein()) // si le sudoku est plein alors la solution est trouver
		  return true;

	if (Normaliser(i, j) && PositionValide(i, j)) //sassure que la postion est dans le board et verifie que la postion est une position a changer la valeur
	{

		for (size_t z = 1; z <= 9; ++z)
		{
			if (ChiffreValide(i, j, z))
			{
				leSudoku_[i][j] = z;
				if (TrouverSolution(i, j + 1)) // rappele la fonction et return true si la solution est trouver
					return true;
			}
		}
		leSudoku_[i][j] = 0; // aucun chiffre etait valide on doit la reinisialiser a 0 
		return false;

	}
	else
	   TrouverSolution(i, j + 1); // la position etait pas valide donc rapelle la fonction avec une nouvelle pos

}
bool Sudoku::Normaliser(int &i,int &j)
{
	// normaliser sassure que je suis dans les borns et incremente le i en fonction ou quon est rendu
	if (i < 9 && j < 9)
		return true;
	if (j >= 9)
	{
		++i;
		j = 0;
		return true;
	}   
	if (i < 9)
		return true;

 return false;
	
}

bool Sudoku::PositionValide(int i, int j)
{
	//verfie si la postion est valide 
	if (leSudoku_[i][j] == 0)
		return true;
	else 
	   return false;

}
bool Sudoku::ChiffreValide( int i, int j,int z)
{
	//verifie que le chiffre est legit
	return VerificationVerticale(i, j, z) &&
		      VerificationHorizontal(i, j, z) &&
	            	VerificationCadran(i - i % 3, j - j % 3, z);
	
	//return true;
}

bool Sudoku::SolutionTrouver()
{
	//fonction useless on va pouvoir lefaccer
	return true;
}

void Sudoku::AfficherSolution()
{
	//a ameliorer laffichage
	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			cout << leSudoku_[i][j];
		}
		cout << endl;
	}

	cout << endl;
	cout << this->horloge.Read() << endl;
}

bool Sudoku::SudokuPlein()
{
	//verifie que aucune case est a 0
	for (size_t i = 0; i < 9; i++)
	   for (size_t j = 0; j < 9; j++)
	    if (leSudoku_[i][j] == 0)
		    return false;	

 return true;
}

bool Sudoku::VerificationVerticale(int i, int j, int z)
{
	for (size_t w = 0; w < 9; w++)
	{
		if (leSudoku_[w][j] == z)
			return false;
	}

	   return true;

}
bool  Sudoku::VerificationHorizontal(int i, int j, int z)
{

	for (size_t w = 0; w < 9; w++)
		if (leSudoku_[i][w] == z)
			return false;

	return true;

}
bool Sudoku::VerificationCadran(int i, int j, int z)
{
	for (size_t w = 0; w < 3; w++)
		for (size_t x = 0; x < 3; x++)		
			if (leSudoku_[i + w][j + x] == z)
				return false;
			
	return true;
}