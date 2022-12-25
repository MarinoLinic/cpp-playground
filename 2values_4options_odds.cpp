#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	int val1 = 20;
	int val2 = 30;
	int val3 = 10;
	
	int a = val3;
	int b = val1;
	int c = val2;
	int d = val3;
	
	int values[3] = {val1, val2, val3};
	int options[4] = {a, b, c, d};
	
	int correct_value;
	int chosen_option;
	double history = 0;
	double iterations = 1000000000;
	srand(time(0));
	
	for (int i = 0; i < iterations; i++){
		correct_value = values[rand() % 3];
		chosen_option = options[rand() % 4];
		
		if(correct_value == chosen_option){
			// cout << correct_value << " = " << chosen_option << endl;
			history++;	
		}
	}
	
	cout << "Percentage: " << (history/iterations)*100 << "%" << endl;
	
	return 0;
}
