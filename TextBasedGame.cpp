#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum AreaState {
	FOREST,
	CABIN,
	MONSTER,
	REST,
	DEATH
};

void fight(double& health, double& stamina);
void rest(double& health, double& stamina);
void tired(double& stamina, int& again, AreaState& scene);
void currentStats(double& health, double& stamina);
double randomNum();

int main() {
	const int MAX_ITEMS = 5;
	string inventory[MAX_ITEMS];
	int inventoryCount = 0;
	int input;
	int again = 1;
	char temp;
	double health = 100.0;
	double stamina = 100.0;
	srand(time(0));

	AreaState scene = FOREST;

	do {
		switch(scene) {
			case FOREST:
				temp = 'f';

				cout << "You wake up in the middle of a forest with no memory.\n";
				cout << "What do you do? Pick a number:\n";
				cout << "1. Go straight ahead.\n2. Turn around and walk that way.\n";
				cin >> input;

				if (input == 1) {
					scene = MONSTER;
				}
				else if (input == 2) {
					scene = CABIN;
				}
				else {
					cout << "Not an option. Try again?\n";
					cout << "1. Yes.\n2. No.\n";
					cin >> again;
				}
				break;

			case DEATH:
				cout << "You died!\n";

				again = 2;
				break;

			case MONSTER:
				cout << "You had to fight a monster!\n";

				fight(health, stamina);
				currentStats(health, stamina);
				cout << endl;

				if(health <= 0) {
					scene = DEATH;
				}
				else if(stamina <= 0) {
					tired(stamina, again, scene);
				}
				else if(temp == 'f'){
					cout << "Your instincts told you to go the opposite direction.\n"; // FIX to update with area
					scene = CABIN;
				}
				else if(temp == 'c'){
					// needs info
				}
				break;

			case REST:
				rest(health, stamina);
				currentStats(health, stamina);

				cout << "You have successfully rested. Shall we continue?\n";
				cout << "1. Yes.\n2. No.\n";
				cin >> input; //temp

				if(temp == 'c' && input == 1) {
					//needs info
				}
				break;

			case CABIN:
				temp = 'c';

				cout << "You walk until you see a dim-lit wooden cabin. You need to rest." << endl;
				cout << "Do you choose to rest in the cabin?\n";
				cout << "1. Yes\n2. No\n";
				cin >> input;

				if (input == 1) {
					scene = REST;
				}
				else if (input == 2) {
					scene = DEATH; //temp
				}
				else {
					cout << "Not an option. Try again?\n";
					cout << "1. Yes.\n2. No.\n";
					cin >> again;
				}
				break;

			default:
				cout << "Not an option. Try again?\n";
				cout << "1. Yes.\n2. No.\n";
				cin >> again;
		}
	} while (again == 1);

	cout << "GAME OVER\n";

	return 0;
}

void currentStats(double& health, double& stamina) {
	cout << "Health: " << health << ".\n";
	cout << "Stamina: " << stamina << ".\n";
}

void rest(double& health, double& stamina) {
	health += 70;
	stamina = 100;

	if(health > 100) {
		health = 100;
	}
}

void tired(double& stamina, int& again, AreaState& scene) {
	if(stamina <= 0) {
		stamina = 0;
	}

	cout << "Looks like you ran out of energy. You collapsed.\n";
	scene = FOREST;
	again = 1;
}

void fight(double& health, double& stamina) {
		health -= randomNum();
		stamina -= randomNum();
	}

double randomNum() {
	return (rand() % 401) / 10.0;
}
