#include<iostream>
#include<iomanip>
#include<string>
#include"header.h"
using namespace std;
/*--------------------------------------------------
*
* nimi: menu
* toiminta: n‰ytt‰‰ k‰ytt‰j‰lle peliss‰ k‰ytett‰vi‰ vaihtoehtoja
* parametri(t): string-mahdolliset char valinnat mitk‰ k‰ytt‰j‰ voi valita
* paluuarvo(t): char-k‰ytt‰j‰n valitsema valinta
*
*--------------------------------------------------*/
char menu(string valid_f) {

	int error = 0;
	string choice_f;

	cout << endl;
	cout << "Valinnat:" << endl;
	cout << "1) Syota laivat" << endl;
	cout << "2) Pelaa" << endl;
	cout << "3) Arvo laivojen sijainnit" << endl;
	cout << "4) Talleta pelitilanne" << endl;
	cout << "5) Lataa pelitilanne" << endl;
	cout << "L) Lopeta" << endl;
	cout << endl;
	cout << "Valintasi: ";
	
	if (cin >> choice_f && choice_f.size() == 1) {
		for (string::size_type i = 0; i < valid_f.size(); i++) {
			if (choice_f.at(0) == valid_f.at(i)) {
				cout << endl;
				return choice_f.at(0);
				break;
			}
			else {
				error++;
				if (error == 7) {
					cout << endl;
					return 'V';
					break;
				}
			}
		}
	}
	else {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;
		return 'V';
	}
	return choice_f.at(0);
}