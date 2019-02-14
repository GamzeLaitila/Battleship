#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include"header.h"

using namespace std;
/*--------------------------------------------------
*
* nimi: allot_location
* toiminta: m‰‰ritt‰‰ laivojen sijainnit satunnaisesti 
* parametri(t): ei ole
* paluuarvo(t): int-'1' varmistusta varten, ett‰ laivat ovat m‰‰ritetyt
*
*--------------------------------------------------*/
int allot_location() {

	int j = 0;
	int battle_area_row, battle_area_column;
	int counter_sp = 0, counter_d = 0;
	int error_sp = 0, error_d = 0;
	int correct_sp = 0, correct_d = 0;
	int out_of_border = 0, already_filled = 0;
	int ships_clash_i = 0, ships_clash_l = 0, ships_clash_p = 0, ships_clash_e = 0, ships_clash = 0;
	char battle_area[7][7];
	char battle_area_1line[49];
	char direction_choice[4] = { 'E', 'I', 'L', 'P' };
	char direction[4] = { ' ' };
	string reason_to_fill;
	string start_point[4][2] = { { "kahden", "  " },{ "kolmen", "  " },{ "neljan", "  " },{ "viiden", "  " } };

	srand(time(NULL));

	for (int a = 0; a < 7; a++) {
		for (int b = 0; b < 7; b++) {
			battle_area[a][b] = ' ';
		}
	}
	for (;;) {
		for (int i = 3; i >= 0; i--) {
			if (error_sp == 0 && error_d == 0) {
				if (correct_sp == correct_d && correct_sp != 0 && correct_d != 0) {
					j = 3 - correct_d;
				}
				else {
					j = i - correct_d;
				}
			}
			else if (error_sp == 1 && error_d == 0) {
				if (correct_sp == correct_d) {
					j = i - counter_sp;
				}
				else {
					j = i - correct_sp;
				}
			}
			if (error_sp == error_d || error_sp == 1) {
				start_point[j][1].at(0) = char(rand() % 7 + 65);
				start_point[j][1].at(1) = char(rand() % 7 + 49);

				counter_sp = 0;
				error_sp = 0;
				correct_sp++;

				battle_area_row = int(start_point[j][1].at(0)) - 65;
				battle_area_column = int(start_point[j][1].at(1)) - 49;

				if (j != 3 && battle_area[battle_area_row][battle_area_column] != ' ') {
					counter_sp = 3 - j;
					error_sp = 1;
					correct_sp--;
					break;
				}
			}
			if (error_sp == 1) {
				break;
			}
				
			//*********************************************************************************
			if (error_d == 1 || correct_sp == correct_d) {
				j = i - counter_d;
			}

			direction[j] = direction_choice[rand() % 4 + 0];

			out_of_border = 0;

			if (counter_d != 0) {
				ships_clash_i = 0;
				ships_clash_l = 0;
				ships_clash_p = 0;
				ships_clash_e = 0;
			}

			for (int a = 0; a < (j + 2); a++) {

				if (direction[j] == 'I') {
					if ((int(start_point[j][1].at(1)) + a) > 55) {
						out_of_border = 1;
					}
				}
				if (direction[j] == 'L') {
					if ((int(start_point[j][1].at(1)) - a) < 49) {
						out_of_border = 1;
					}
				}
				if (direction[j] == 'P') {
					if ((int(start_point[j][1].at(0)) - a) < 65) {
						out_of_border = 1;
					}
				}
				if (direction[j] == 'E') {
					if ((int(start_point[j][1].at(0)) + a) > 71) {
						out_of_border = 1;
					}
				}
			}

			if (out_of_border == 1) {
				counter_d = 3 - j;
				error_d = 1;
				break;
			}
			else {
				battle_area_row = int(start_point[j][1].at(0)) - 65;
				battle_area_column = int(start_point[j][1].at(1)) - 49;

				//gemilerde carpisma var mi??
				if (j != 3) {
					if (direction[j] == 'I') {
						for (int a = 0; a < j + 2; a++) {
							if (battle_area[battle_area_row][battle_area_column + a] != ' ') {
								ships_clash_i = 1;
								ships_clash = ships_clash_i + ships_clash_l + ships_clash_p + ships_clash_e;
								if (ships_clash == 4) {
									counter_sp = 3 - j;
								}
								else {
									counter_d = 3 - j;
								}
								error_d = 1;
								break;
							}
							else
								error_d = 0;
						}
					}
					if (direction[j] == 'L') {
						for (int a = 0; a < j + 2; a++) {
							if (battle_area[battle_area_row][battle_area_column - a] != ' ') {
								ships_clash_l = 1;
								ships_clash = ships_clash_i + ships_clash_l + ships_clash_p + ships_clash_e;
								if (ships_clash == 4) {
									counter_sp = 3 - j;
								}
								else {
									counter_d = 3 - j;
								}
								error_d = 1;
								break;
							}
							else
								error_d = 0;
						}
					}
					if (direction[j] == 'P') {
						for (int a = 0; a < j + 2; a++) {
							if (battle_area[battle_area_row - a][battle_area_column] != ' ') {
								ships_clash_p = 1;
								ships_clash = ships_clash_i + ships_clash_l + ships_clash_p + ships_clash_e;
								if (ships_clash == 4) {
									counter_sp = 3 - j;
								}
								else {
									counter_d = 3 - j;
								}
								error_d = 1;
								break;
							}
							else
								error_d = 0;
						}
					}
					if (direction[j] == 'E') {
						for (int a = 0; a < j + 2; a++) {
							if (battle_area[battle_area_row + a][battle_area_column] != ' ') {
								ships_clash_e = 1;
								ships_clash = ships_clash_i + ships_clash_l + ships_clash_p + ships_clash_e;
								if (ships_clash == 4) {
									counter_sp = 3 - j;
								}
								else {
									counter_d = 3 - j;
								}
								error_d = 1;
								break;
							}
							else
								error_d = 0;
						}
					}
					if (error_d == 1)
						break;
					if (error_d != 1) {

						counter_d = 0;
						error_d = 0;
						correct_d++;
						for (int a = 0; a < j + 2; a++) {
							if (direction[j] == 'I') {
								battle_area[battle_area_row][battle_area_column + a] = char(j + 50);
							}
							if (direction[j] == 'L') {
								battle_area[battle_area_row][battle_area_column - a] = char(j + 50);
							}
							if (direction[j] == 'P') {
								battle_area[battle_area_row - a][battle_area_column] = char(j + 50);
							}
							if (direction[j] == 'E') {
								battle_area[battle_area_row + a][battle_area_column] = char(j + 50);
							}
						}
					}
				}
				else {
					counter_d = 0;
					error_d = 0;
					correct_d++;
					for (int a = 0; a < j + 2; a++) {
						if (direction[j] == 'I') {
							battle_area[battle_area_row][battle_area_column + a] = char(j + 50);
						}
						if (direction[j] == 'L') {
							battle_area[battle_area_row][battle_area_column - a] = char(j + 50);
						}
						if (direction[j] == 'P') {
							battle_area[battle_area_row - a][battle_area_column] = char(j + 50);
						}
						if (direction[j] == 'E') {
							battle_area[battle_area_row + a][battle_area_column] = char(j + 50);
						}
					}
				}
			}
			if (error_sp == 1 || error_d == 1 || out_of_border == 1)
				break;
			if (correct_sp == 4 && correct_d == 4)
				break;
		}
		if (correct_sp == 4 && correct_d == 4)
			break;
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			battle_area_1line[i * 7 + j] = battle_area[i][j];
		}
	}
	

	reason_to_fill = "placement";
	ships_to_file(reason_to_fill, battle_area_1line);
	cout << endl;
	cout << "Arvotut laivat ovat sijoitettu pelialueeseen, ole hyva ja valitse uusi toiminto: " << endl;

	return 1;
}