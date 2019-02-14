#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include"header.h"

using namespace std;
/*--------------------------------------------------
*
* nimi: ships_from_file
* toiminta: tarkistaa ammuttua kohtaa/tulostaa pelin tilanteen/lataa pelin tilanteen 
*			poimimalla laivojen sijainnit tiedostosta
* parametri(t): string-poiminnon syy, string-laivojen sijainnit
* paluuarvo(t): string-laivojen sijainnit/ammutun kohdan sisältö poiminnon syyn mukaan
*
*--------------------------------------------------*/
string ships_from_file(string file_choice_f, string coordinate_f) {

	int a = 0;
	int battle_area_row, battle_area_column = 0;
	char rowIndex;
	char battle_area[7][7];
	string shot_f = " ";
	string battle_area_1line = "                                                 ";
	string columnCode[2] = { "    1 2 3 4 5 6 7    ", "  -----------------  " };
	string line;
	string directory;
	ifstream myfile;

	if (file_choice_f == "check coordinate") {
		directory = "C:\\Users\\Gamze\\Desktop\\TAMK\\2017-2018\\Ohjelmointikielet.Jatko\\Laivanupotus\\Laivanupotus\\laivanupotus_sijoitus.txt";
	}
	if (file_choice_f == "sneak peek") {
		directory = "C:\\Users\\Gamze\\Desktop\\TAMK\\2017-2018\\Ohjelmointikielet.Jatko\\Laivanupotus\\Laivanupotus\\laivanupotus_sijoitus.txt";
	}
	if (file_choice_f == "hits" && coordinate_f != "osuma") {
		directory = "C:\\Users\\Gamze\\Desktop\\TAMK\\2017-2018\\Ohjelmointikielet.Jatko\\Laivanupotus\\Laivanupotus\\osuma.txt";
	}
	if (coordinate_f == "osuma") {
		directory = "C:\\Users\\Gamze\\Desktop\\TAMK\\2017-2018\\Ohjelmointikielet.Jatko\\Laivanupotus\\Laivanupotus\\osuma.txt";
	}
	if (file_choice_f == "load game") {
		directory = "C:\\Users\\Gamze\\Desktop\\TAMK\\2017-2018\\Ohjelmointikielet.Jatko\\Laivanupotus\\Laivanupotus\\pelitilanne.txt";
	}
	myfile.open(directory);

	if (myfile.is_open()) {
		while (getline(myfile, line))
		{
			for (int b = 0; b < 7; b++) {
				battle_area_1line.at((a * 7) + b) = line.at(b * 2);
			}
			a++;
		}
		myfile.close();
	}
	else {
		cout << "Tiedosto ei loydy, ole hyva ja syota koodiin laivanupotus.txt:n koko directory" << endl;
		cout << "*****       muista 2x'\\'      *****" << endl;
	}

	if (file_choice_f == "check coordinate") {
		shot_f.at(0) = battle_area_1line.at((int(coordinate_f.at(0)) - 65) * 7 + (int(coordinate_f.at(1)) - 49));
	}

	if (coordinate_f == "osuma" || file_choice_f == "load game") {
		shot_f = battle_area_1line;
	}

	if (file_choice_f == "sneak peek" || (file_choice_f == "hits" && coordinate_f != "osuma")) {
		rowIndex = 'A';
		for (int i = 0; i < 7; i++) {
			battle_area[0][i] = battle_area_1line[i];
		}
		for (int i = 7; i < 49; i++) {
			battle_area_row = (i - (i % 7)) / 7;

			battle_area[battle_area_row][battle_area_column] = battle_area_1line[i];
			battle_area_column++;

			if (battle_area_column == 7)
				battle_area_column = 0;
		}
		for (int a = 0; a < 2; a++) {
			cout << columnCode[a] << endl;
		}

		for (int i = 0; i < 7; i++) {
			cout << rowIndex << " | ";
			for (int j = 0; j < 7; j++) {
				cout << battle_area[i][j] << " ";
			}
			cout << "| " << rowIndex;
			rowIndex++;
			cout << endl;
		}

		for (int a = 1; a >= 0; a--) {
			cout << columnCode[a] << endl;
		}
		cout << endl;
	}	
	return shot_f;
}