#include<iostream>
#include<iomanip>
#include<string>
#include"header.h"

using namespace std;

int main() {

	int ships_entered = 0;
	int game_phase = 0;
	int new_game = 0;
	int saved_game = 0;
	char choice;
	string battle_area;
	string valid = "12345lL";

	cout << "Laivanupotuspeli" << endl;
	cout << "================" << endl;

	for (;;) {

		choice = menu(valid);

		if (choice == '1') {
			if (game_phase == 1) {
				new_game = 1;
				game_phase = 0;
			}
			ships_entered = enter_ships();
			if (game_phase == 2 && ships_entered == 1)
				game_phase = 0;
		}
		if (choice == '2') {
			if (ships_entered == 1) {
				if (new_game == 0 && game_phase == 1) {
					battle_area = ships_from_file("hits", "osuma");
					game_phase = play(game_phase, battle_area);
				}
				else {
					game_phase = play(game_phase, "doesn't matter");
					new_game = 0;
				}
			}
			else 
				cout << "Ole hyva ja syota ensin laivojen sijainnit valitsemalla valikko 1 tai 3" << endl;
			if (game_phase == 2)
				ships_entered = 0;
		}
		if (choice == '3') {
			if (game_phase == 1) {
				new_game = 1;
				game_phase = 0;
			}
			ships_entered = allot_location();
		}
		if (choice == '4') {
			if (game_phase == 0)
				cout << "Tallennettavaa pelia ei loydy. Ole hyva ja valitse uusi toiminto" << endl;
			else if (game_phase == 1) {
				ships_to_file("save game", "doesn't matter");
				cout << "Pelitilanne on tallennettu" << endl;
				saved_game = 1;
			}
			else
				cout << "Peli on pelattu loppuun asti. Ole hyva ja valitse uusi toiminto" << endl;
		}
		if (choice == '5') {
			if (ships_entered == 1 && saved_game == 1) {
				battle_area = ships_from_file("load game", "doesn't matter");
				cout << "Ennen tallennettu pelitilanne on ladattu" << endl;
				game_phase = play(1, battle_area);
			}
			else
				cout << "Ladattavaa pelia ei loydy. Ole hyva ja valitse uusi toiminto" << endl;
		}
		if (choice == 'V') {
			cout << "*****Vaara syotto*****" << endl;
		}
		if (choice == 'L' || choice == 'l') {
			break;
		}
		cout << endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}