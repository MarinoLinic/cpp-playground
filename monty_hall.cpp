#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int doors[] = {1, 2, 3};
	int car_door, player_door_original, player_door, opened_door;
	double attempts = 100000000; // number of attempts
	double switching, not_switching = 0;
	srand(0); // seed for the random function
	
	for(int i = 1; i < attempts; i++){
			
		// the car is randomly assigned to one of the 3 doors
		car_door = doors[rand() % 3]; 
		
		// the player randomly chooses one of the 3 doors
		player_door = doors[rand() % 3];
		player_door_original = player_door;
		
		// opening one of the doors
		for(int j = 0; j < 2; j++){
			if(doors[j] != car_door && doors[j] != player_door) opened_door = doors[j];
		}
		
		// player switching
		for(int k = 0; k < 2; k++){
			if(doors[k] != player_door && doors[k] != opened_door) player_door = doors[k];
		}
		
		// adding up the results
		if(player_door == car_door) switching++;
		if(player_door_original == car_door) not_switching++;
	}
	
	cout << "After " << attempts << " attempts:" << endl 
	<< "\tSwitching percentage correct: " << (switching/attempts)*100 << "%" << endl 
	<< "\tNot switching percentage correct: " << (not_switching/attempts)*100 << "%";
	
	return 0;
}
