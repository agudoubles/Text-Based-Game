#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

enum AreaState {
	FOREST,
	CABIN,
	BASEMENT,
	ESCAPE,
	MONSTER,
	REST,
	INVENTORY,
	GAME_OVER
};

void battle(double& health, double& stamina);
void rest(double& health, double& stamina);
void tired(double& stamina, int& input, int& again, AreaState& scene, double& health);
void death(double& health, int& input, int& again, AreaState& scene, double& stamina);
void currentStats(double& health, double& stamina);
void restart(double& health, double& stamina, int& input, int& again, AreaState& scene);
void itemList(string arr[], int& inventoryCount, int& input, const int MAX_CAP);
void newItem(string arr[], double& health, double& stamina, int& inventoryCount, int& input, int& again, AreaState& scene, const int MAX_CAP, string item);
void removeItem(string arr[], int index, int& inventoryCount, const int MAX_CAP);
bool itemSearch(string arr[], int inventoryNum, string item);
double randomNum();

int main() {
	const int MAX_ITEMS = 5;
	string inventory[MAX_ITEMS];
	string itemName;
	int inventoryCount = 0, again = 1, input;
	char sceneChar;
	char temp;
	double health = 100.0, stamina = 100.0;
	srand(time(0));

	AreaState scene = FOREST;

	do {
		switch(scene) {
			case FOREST:
				sceneChar = 'f';

				cout << "You wake up in the middle of a forest with no memory.\n";
				cout << "What do you do? Pick a number:\n";
				cout << "1. Go straight ahead.\n2. Turn around and walk that way.\n\n";
				//cout << "Enter 0 to open the inventory at any time.\n\n"; //complicated for this game
				cin >> input;

				if (input == 1) {
					cout << "You were attacked by a monster!\n\n";
					scene = MONSTER;
				}
				else if (input == 2) {
					scene = CABIN;
				}
				else if (input == 0) {
					scene = INVENTORY;
				}
				else {
					cout << "Not an option.\n\n";
					restart(health, stamina, input, again, scene);
				}
				break;
			case CABIN:
				sceneChar = 'c';

				if(temp == 'e' && sceneChar == 'c') {
					cout << "You find canned food way past expiration. Keep it?\n";
					cout << "1. Yes.\n2. Eat.\n\n";
					cin >> input;

					if (input == 1) {
						temp = 'b';
						itemName = "Old Canned Food";
						newItem(inventory, health, stamina, inventoryCount, input, again, scene, MAX_ITEMS, itemName);
					}
					else if (input == 2) {
						temp = 'b';
						cout << "You keep exploring...\n\n";

						cout << "Press any key to continue:";
						cin.get();
						cin.ignore();

						cout << "until you dropped.\n\n";
						scene = GAME_OVER;
					}
					else if (input == 0) {
						temp = 'b';
						scene = INVENTORY;
					}
					else {
						cout << "Not an option.\n\n";
						restart(health, stamina, input, again, scene);
					}
				}
				else if(temp == 'b' && sceneChar == 'c') {
					cout << "You find a door at the end of a hallway.\nKick it open or find a key?\n";
					cout << "1. Force open.\n2. Look for key.\n\n";
					cin >> input;

					if (input == 1) {
						sceneChar = 'b';

						cout << "You make a lot of noise doing so.\n";
						cout << "It's stairs going down.\n";
						cout << "Something reels you in, so you go down against your will.\n\n";

						scene = BASEMENT;
					}
					else if (input == 2) {
						temp = 'k';

						cout << "You keep exploring.\n\n";
						cout << "You find a room with a rotting bed and nightstand.\n";
						cout << "Without a second thought, you check the drawers for anything to help.\n";
						cout << "Just a key. You keep it to open the mysterious door.\n\n";

						itemName = "Key";
						newItem(inventory, health, stamina, inventoryCount, input, again, scene, MAX_ITEMS, itemName);

						scene = BASEMENT;
					}
					else if (input == 0) {
						scene = INVENTORY;
					}
					else {
						cout << "Not an option.\n\n";
						restart(health, stamina, input, again, scene);
					}
				}
				else if(sceneChar == 'c') {
					cout << "You walk until you see a dim-lit wooden cabin. You need to rest." << endl;
					cout << "Do you choose to rest in the cabin?\n";
					cout << "1. Yes.\n2. No.\n\n";
					cin >> input;

					if (input == 1) {
						scene = REST;
					}
					else if (input == 2) {
						temp = 'e';
					}
					else if (input == 0) {
						scene = INVENTORY;
					}
					else {
						cout << "Not an option.\n\n";
						restart(health, stamina, input, again, scene);
					}
				}
				break;
			case BASEMENT:
				cout << "Press any key to continue:";
				cin.get();
				cin.ignore();

				cout << "The door behind you closes shut... it's dark in here.\n";
				cout << "You feel the wall for some kind of switch.\n";

				cout << "Press any key to continue:";
				cin.get();
				cin.ignore();

				cout << "One single light bulb in the middle of the room flicker but it's good enough to see a note on a lonely table.\n";
				cout << "1. Pick it up\n2. Search the room\n\n";
				cin >> input;

				if (input == 1) {
					cout << "It's in a language you do not understand, yet somehow you faint.\n";
					cout << "Everything goes dark ever so slowly.\n\n";

					scene = GAME_OVER;
				}
				else if (input == 2) {
					cout << "Looking around, you find a hammer and a chest with a lock.\n\n";

					if(itemSearch(inventory, inventoryCount, "Key")) {
						temp = 'r';

						cout << "You kept the hammer, and was able to open the chest with the same key.\n";
						cout << "Inside, you found a rifle. You feel a sense of relief.\n\n";

						itemName = "Rifle";
						newItem(inventory, health, stamina, inventoryCount, input, again, scene, MAX_ITEMS, itemName);
						itemName = "Hammer";
						newItem(inventory, health, stamina, inventoryCount, input, again, scene, MAX_ITEMS, itemName);
					}
					else {
						temp = 'h';

						cout << "You tried to break the lock with the hammer, but the iron broke off, rendering it useless.\n\n";
					}

					cout << "Could open the door again with the hammer, maybe.\n";
					cout << "1. Desperate escape.\n2. Keep exploring.\n\n";
					cin >> input;

					if (input == 1) {
						if(temp == 'r') {
							cout << "You smash the door knob with the hammer, and after a few attempts the door opens.\n";
						}
						else if (temp == 'h') {
							cout << "You smash the door knob with the hammer head, and eventually, opening the door.\n";
						}
						cout << "You make a run for it but a strange creature stands in your way.\n";
						cout << "Take the chance to fight it?\n\n";
						cout << "1. Fight.\n2. Flight.\n\n";
						cin >> input;

						if (input == 1) {
							scene = MONSTER;
						}
						else if (input == 2) {
							cout << "You try to make a run for it by going around this creature... better luck next time.\n\n";

							scene = GAME_OVER;
						}
						else if (input == 0) {
							scene = INVENTORY;
						}
						else {
							cout << "Not an option.\n\n";
							restart(health, stamina, input, again, scene);
						}
					}
					else if (input == 2) {
						cout << "Looks like your time ran out. Someone or something walks down the stairs.\n";
						cout << "Lights turn off. You're defenseless in the dark. You can only imagine what happened.\n\n";

						scene = GAME_OVER;
					}
					else if (input == 0) {
						scene = INVENTORY;
					}
					else {
						cout << "Not an option.\n\n";
						restart(health, stamina, input, again, scene);
					}
				}
				else if (input == 0) {
					scene = INVENTORY;
				}
				else {
					cout << "Not an option.\n\n";
					restart(health, stamina, input, again, scene);
				}
				break;
			case ESCAPE:
				cout << "With the rest of your stamina, you ran until you found lights and people screaming your name\n"; //make one bad ending where stamina is low
				cout << "You run towards them as fast as you can. ";
				cout << "They see you and they show glee in doing so, asking you where you've been.\n";
				cout << "Last time they saw you was at the lake together with your friends, until you walked away into the forest on your own.\n";

				again = 2;
				break;
			case GAME_OVER:
				cout << "GAME OVER\n";
				again = 2;
				break;
			case MONSTER:
				if(itemSearch(inventory, inventoryCount, "Rifle")) {
					cout << "One shot from the rifle was more than enough to lay down this creature.\n\n";
					scene = ESCAPE;
				}
				else {
					battle(health, stamina);
					//stamina = 0; //test
					//health = 0;
					currentStats(health, stamina);
					cout << endl;

					if(health <= 0) {
						death(health, input, again, scene, stamina);
					}
					else if(stamina <= 0) {
						tired(stamina, input, again, scene, health);
					}
					else if(sceneChar == 'f'){
						cout << "Your instincts told you to go the opposite direction.\n\n";
						scene = CABIN;
					}
					else if(sceneChar == 'c'){
						// needs info
					}
				}

				break;

			case REST:
				rest(health, stamina);
				currentStats(health, stamina);

				cout << "You have successfully rested.\n";

				if(sceneChar == 'c') {
					temp = 'e';

					cout << "You wake up and explore the old cabin. ";

					scene = CABIN;
				}
				else {
					cout << "Not an option.\n\n";
					restart(health, stamina, input, again, scene);
				}
				break;
			case INVENTORY: //make this work anywhere in game and make sense
				itemList(inventory, inventoryCount, input, MAX_ITEMS);

				if (sceneChar == 'c') {
					scene = CABIN;
				}
				else if (sceneChar == 'f') {
					scene = FOREST;
				}
				break;
			default:
				cout << "Not an option.\n\n";
				restart(health, stamina, input, again, scene);
		}
	} while (again == 1);

	return 0;
}

void currentStats(double& health, double& stamina) {
	cout << "Health: " << health << ".\n";
	cout << "Stamina: " << stamina << ".\n\n";
}

void restart(double& health, double& stamina, int& input, int& again, AreaState& scene) { //finish
	cout << "Play again?\n1. Yes.\n2. No.\n\n";
	cin >> input;

	if(input == 1) {
		health = 100;
		stamina = 100;

		scene = FOREST;
		again = 1;
	}
	else if(input == 2) {
		scene = GAME_OVER;
	}
	else {
		cout << "Not an option.\n\n";
		//how to repeat function from here?
	}
}

void rest(double& health, double& stamina) {
	health += 30;
	stamina += 50;

	if(health > 100) {
		health = 100;
	}

	if(stamina > 100) {
		stamina = 100;
	}
}

void tired(double& stamina, int& input, int& again, AreaState& scene, double& health) {
	if(stamina <= 0) {
		stamina = 0;
	}

	currentStats(health, stamina);
	cout << "You ran out of stamina! You collapsed.\n\n";
	restart(health, stamina, input, again, scene);
}

void death(double& health, int& input, int& again, AreaState& scene, double& stamina) {
	if(health <= 0) {
		health = 0;
	}

	currentStats(health, stamina);
	cout << "You ran out of health! You died.\n\n";
	restart(health, stamina, input, again, scene);
}

void battle(double& health, double& stamina) {
	health -= randomNum();
	stamina -= randomNum();
}

void itemList(string arr[], int& inventoryCount, int& input, const int MAX_CAP) {
	int i;

	if(inventoryCount > 0) {
		for(i = 0; i < MAX_CAP; i++) {
			cout << i + 1 << ". " << arr[i] << endl;
		}

		cout << endl;
		cout << "Want to discard something?\n";
		cout << "1. Yes\n2. No\n\n";
		cin >> input;

		if(input == 1) {
			cout << "What would you like to leave behind?\n\n";
			for(i = 0; i < MAX_CAP; i++) {
				cout << i + 1 << ". " << arr[i] << endl;
			}

			cout << endl;
			cin >> input;

			removeItem(arr, input, inventoryCount, MAX_CAP);

			cout << "Done.\n\n";
		}
		else if(input == 2) {
			cout << "Let's continue.\n\n";
		}
	}
	else {
		cout << "Nothing yet.\n\n";
	}
}

void removeItem(string arr[], int userIn, int& inventoryCount, const int MAX_CAP) {
    for(int i = userIn; i < inventoryCount - 1; i++) {
        arr[i] = arr[i + 1];
    }
    inventoryCount--;
}

void newItem(string arr[], double& health, double& stamina, int& inventoryCount, int& input, int& again, AreaState& scene, const int MAX_CAP, string item) {
	if(inventoryCount < MAX_CAP) {
		arr[inventoryCount] = item;
		inventoryCount++;

		cout << item << " was kept.\n";
		//cout << "You have " << MAX_CAP - inventoryCount << " spaces left in your inventory.\n\n";
	}
	else if(inventoryCount >= MAX_CAP) {
		cout << "Your inventory is full! Want to discard something?\n";
		cout << "1. Yes\n2. No\n\n";
		cin >> input;

		if (input == 1) {
			cout << "What would you like to leave behind?\n\n";
			itemList(arr, inventoryCount, input, MAX_CAP);
			cout << endl;
			cin >> input;

			removeItem(arr, input, inventoryCount, MAX_CAP);
			if(inventoryCount < MAX_CAP) {
					arr[inventoryCount] = item;
					inventoryCount++;

					cout << item << " was kept.\n\n";
			}
		}
	}
	else if (input == 2) {
		//finish
	}
	else {
		cout << "Not an option.\n\n";
		restart(health, stamina, input, again, scene);
	}
}

bool itemSearch(string arr[], int inventoryNum, string item) {
	for(int i = 0; i < inventoryNum; i++) {
		if(arr[i] == item) {
			return true;
		}
	}
	return false;
}

double randomNum() {
	return (rand() % 701) / 10.0;
}
