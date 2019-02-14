#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include"header.h"

using namespace std;
/*--------------------------------------------------
*
* nimi: ships_to_file
* toiminta: syöttää laivojen sijainnit tiedostoon
* parametri(t): string-syöttelyn syy, string-laivojen sijainnit
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void ships_to_file(string reason_to_fill_f, char *battle_area_1line_f) {

	int return_value = 0;
	int battle_area_row_f;
	int battle_area_column_f = 0;
	char battle_area_f[7][7];
	string line;
	string directory;

	for (int i = 0; i < 7; i++) {
		battle_area_f[0][i] = *(battle_area_1line_f + i);
	}
	for (int i = 7; i < 49; i++) {
		battle_area_row_f = (i - (i % 7)) / 7;
		
		battle_area_f[battle_area_row_f][battle_area_column_f] = *(battle_area_1line_f + i);
		battle_area_column_f++;

		if (battle_area_column_f == 7)
			battle_area_column_f = 0;
	}

	if (reason_to_fill_f == "placement") {
		directory = "laivanupotus_sijoitus.txt";
	}
	if (reason_to_fill_f == "miss_hit") {
		directory = "osuma.txt";
	}
	ofstream myfile(directory);
	if (myfile.is_open())
	{
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				myfile << battle_area_f[i][j];
				if (j != 6)
				{
					myfile << " ";
				}
			}
			if (i == 6)
				break;
			myfile << "\n";
		}
		myfile.close();
	}
	else
		cout << "Tiedosto ei loydy" << endl;
	
	if (reason_to_fill_f == "save game") {
		ifstream    inFile("osuma.txt");
		ofstream    outFile("pelitilanne.txt");
		outFile << inFile.rdbuf();
	}
}