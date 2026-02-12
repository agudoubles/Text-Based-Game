#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void fight(double& health, double& stamina);
void rest(double& health, double& stamina);
void currentStats(double& health, double& stamina);
double randomNum(double& val);

int main() {
	int input;
	double health = 100;
	double stamina = 100;

	srand(time(0));

	cout << "You wake up in the middle of a forest with no memory.\n";
	cout << "What do you do? Pick a number:\n";
	cout << "1. Go straight ahead.\n2. Turn around and walk that way.\n";
	cin >> input;

		switch(input) {
	case 1: fight(health, stamina);
			cout << "You had to fight a monster!\n";
			currentStats(health, stamina);
			break;
	case 2: cout << "You walk until you see a dim-lit wooden cabin. You need to rest." << endl;
			cout << "Do you choose to rest in the cabin?\n";
			cout << "1. Yes\n2. No\n";
			cin >> input;
			break;
	default: cout << "Not an option.";
	}

		switch(input) {
	case 1: fight(health, stamina);
			cout << "You see the cabin is old and rusty. Somewhere in there, you see a couch.\n";
			cout << "You rested there till tomorrow.\n";
			rest(health, stamina);
			currentStats(health, stamina);
			break;
	case 2: cout << "You keep walking past the cabin in search for help.\n";
			cout << "You hear voices coming up ahead. Do you follow them?\n";
			cout << "1. Yes\n2. No.\n";
			break;
	default: cout << "Not an option.";
	}

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

void fight(double& health, double& stamina) {
		health -= randomNum(health);
		stamina -= randomNum(stamina);
	}

double randomNum(double& val) {
	double newNum;

	newNum = ((rand() % 201) / 10.0);

	return newNum;
}
