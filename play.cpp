#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<ctime>
#include<thread>
#include<conio.h>
#include"header.h"

using namespace std;
/*--------------------------------------------------
*
* nimi: play
* toiminta: suorittaa peliä käyttäjän valitsemalla pelitavalla
* parametri(t): int-pelin tilanne, string-laivojen sijainnit
* paluuarvo(t): int-pelin tilanne
*
*--------------------------------------------------*/
int play(int game_phase_f, string battle_area_1line_f) {

	//game_phase_f--- 0: game didn't start, 1: game ongoing, 2: game ended
	int check1 = 1, check2 = 1;
	int between_shots;
	int shot_no;
	int counter_sunk = 0;
	int a = 0, index = 0;
	int counter[4] = { 0 };
	int already_shot = 0;
	char shot;
	char simu_row[7] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char simu_column[7] = { '1', '2', '3', '4', '5', '6', '7' };
	char battle_area_1line[49];
	string between_shots_string;
	string play_type;
	string shot_f;
	string coordinate = "  ";
	string simulate_coordinate = { "  " };
	string coordinate_list[49] = { " " };
	string file_choice;
	string sunk_ships[4] = { "", "", "", "" };
	string line;
	ifstream myfile;

	srand((unsigned)time(NULL));

	if (game_phase_f == 1) {
		for (int i = 0; i < 49; i++) {
			battle_area_1line[i] = battle_area_1line_f.at(i);
		}
		cout << endl;
	}

	if (game_phase_f == 0 || game_phase_f == 2) {
		for (int i = 0; i < 49; i++) {
			battle_area_1line[i] = ' ';
		}
	}

	do {
		if (check1 == 0)
			cout << "Ole hyva ja valitse 1 tai 2" << endl;

		cout << "Haluaisitko ampua itse(1) vai simuloidaanko ampuminen(2)?";
		cin >> play_type;
		cout << endl;

		if (!(play_type.at(0) == '1' || play_type.at(0) == '2') || play_type.size() != 1) {
			check1 = 0;
		}
		else
			check1 = 1;
	} while (check1 == 0);

	if (play_type.at(0) == '2') {
		do {
			if (check2 == 0) {
				cout << "Ole hyva ja valitse 0, 2, 3 tai 4" << endl;
				cout << endl;
			}
			cout << "Montako sekunttia haluaisit jattaa ampumisten valilla? (:2 - 4)" << endl;
			cout << "Tai paina '0', jos haluaisit edeta painamalla jotakin nappainta: ";
			cin >> between_shots_string;

			between_shots = int(between_shots_string.at(0)) - 48;

			if ((between_shots < 2 && between_shots != 0) || between_shots > 4 || between_shots_string.size() != 1) {
				check2 = 0;
			}
			else
				check2 = 1;
		} while (check2 == 0);
	}

	for (;;) {
		for (;;) {
			if (play_type.at(0) == '1') {
				cout << "Anna ampumiskoordinaatit (A1...G7): ";
				cin >> coordinate;
				cout << endl;
				if (((coordinate.at(0) == 'a' || coordinate.at(0) == 'b' ||
					coordinate.at(0) == 'c' || coordinate.at(0) == 'd' ||
					coordinate.at(0) == 'e' || coordinate.at(0) == 'f' ||
					coordinate.at(0) == 'g') && coordinate.size() == 2)
					|| (coordinate.at(0) == 'p')) {
					coordinate.at(0) = char(int(coordinate.at(0)) - 32);
				}
				if (coordinate.at(0) == '\\' && coordinate.at(1) == '@') {
					file_choice = "sneak peek";
					cout << "Laivat sijaitsevat seuraavissa paikoissa:" << endl;
					cout << endl;
					shot_f = ships_from_file(file_choice, "doesn't matter");
					break;
				}
				if (coordinate.at(0) == 'P') {
					break;
				}
				if (!(coordinate.at(0) < char(72) && coordinate.at(0) > char(64)) ||
					!(coordinate.at(1) < char(56) && coordinate.at(1) > char(48)) ||
					coordinate.size() > 2 || coordinate.size() < 2) {
					cout << "---Virheellinen koordinaatti, ole hyva ja yrita uudelleen" << endl;
					cout << endl;
					break;
				}
				else
					game_phase_f = 1;
			}
			else {
				simulate_coordinate.at(0) = simu_row[rand() % 7 + 0];
				simulate_coordinate.at(1) = simu_column[rand() % 7 + 0];
				
				coordinate = simulate_coordinate;
				game_phase_f = 1;
				}

			
			for (int i = 0; i < index; i++) {
				if (coordinate_list[i] == coordinate) {
					//cout << "---" << coordinate <<" on jo ammuttu." << endl;
					cout << endl;
					already_shot = 1;
					break;
				}
			}

			if (already_shot == 0) {
				coordinate_list[index] = coordinate;
				index++;

				shot_f = ships_from_file("check coordinate", coordinate);
				shot = shot_f.at(0);

				if (shot == ' ') {
					cout << endl;
					cout << "Laukaus kohtaan " << coordinate << " ei osunut." << endl;
					shot = 'x';
					battle_area_1line[(int(coordinate.at(0)) - 65) * 7 + (int(coordinate.at(1)) - 49)] = shot;

					ships_to_file("miss_hit", battle_area_1line);
					cout << endl;
				}
				else if (shot == '2' || shot == '3' || shot == '4' || shot == '5') {
					shot_no = int(shot) - 50;
					counter[shot_no]++;
					sunk_ships[shot_no] = sunk_ships[shot_no] + coordinate;

					if (counter[shot_no] == int(shot) - 48) {
						counter_sunk++;

						cout << "Laukaus kohtaan " << coordinate << " upotti laivan." << endl;
						for (int j = 0; j < counter[shot_no]; j++) {
							battle_area_1line[(int(sunk_ships[shot_no].at(2 * j)) - 65) * 7 + (int(sunk_ships[shot_no].at(2 * j + 1)) - 49)] = '#';
						}
					}
					else if (counter[shot_no] > int(shot) - 48) {
						cout << "Laiva on jo upotettu!" << endl;
					}
					else {
						cout << endl;
						cout << "Laukaus kohtaan " << coordinate << " osui laivaan." << endl;
						battle_area_1line[(int(coordinate.at(0)) - 65) * 7 + (int(coordinate.at(1)) - 49)] = '*';
					}
					cout << endl;
					ships_to_file("miss_hit", battle_area_1line);
				}
				if (counter_sunk == 4) {
					game_phase_f = 2;
					break;
				}
			}
			else {
				already_shot = 0;
				break;
			}
			cout << "Peli tilanne on seuraava:" << endl;
			cout << endl;

			file_choice = "hits";

			shot_f = ships_from_file(file_choice, "doesn't matter");
			cout << endl;

			if (between_shots != 0) {
				this_thread::sleep_for(chrono::seconds(between_shots));
			}
			else {
				cout << "Paina jotakin nappainta";
				cout << endl;
				_getch();
			}
		}
		if (coordinate.at(0) == 'P') {
			cout << "Valitsit poistua pelista..." << endl;
			if (game_phase_f != 2) {
				ships_to_file("miss_hit", battle_area_1line);
			}
			break;
		}
		if (game_phase_f == 2) {
			cout << "Onneksi olkoon! Kaikki laivat ovat upotettu!" << endl;
			for (int i = 0; i < 49; i++) {
				battle_area_1line[i] = ' ';
			}

			file_choice = "hits";
			shot_f = ships_from_file(file_choice, "doesn't matter");
			cout << endl;
			break;
		}
	}
	return game_phase_f;
}