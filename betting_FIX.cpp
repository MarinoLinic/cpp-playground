#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#define _WIN32_WINNT 0x0500
#include <windows.h>
using namespace std;

int main() {
    
    double coins = 5000;
    double initialCoins = coins;
    float attempts = 1000000;
    int bet = 0, initialBet = 20, counter = 0;
    int guesser, currentValue, lastBet;
    string state;
    srand(0);
    string limit = "There is no betting limit.";
    
    cout << "Coins: " << coins << " (attempts: " << attempts << ")" << endl << endl;
    
    for (int i = 0; i < attempts; i++){
        currentValue = rand() % 2;
        guesser = rand() % 2;
        
        // Initializing the bet
        if (bet == 0) bet = initialBet;
        
        //Successful bet
        if (guesser == currentValue){
            state = "True";
            coins += bet;
            lastBet = bet;
            bet = 0;
        }
        
        //Unsuccessful bet
        else {
            state = "False";
            coins -= bet;
            lastBet = bet;

            if (coins < initialBet) i = attempts;
            else if ((coins - bet*2) > initialBet) bet = bet*2; 
            
            if (bet > 1000) bet = 0; limit = "The limit of no more than 1000 per bet is >>on<<.";
        }
        
        counter++;
                
        //cout << state << "\t" << "Guess: " << guesser << "\t" << "Value: " << currentValue << "\t" 
        //     << "Bet: " << lastBet << "   \t" << "Coins: " << coins << endl;
        
    } 
    
    cout << "\nCoins after " << counter << " attempts: " << coins << endl << "Gain: " << coins - initialCoins << endl << "Gain per attempt: " << (coins - initialCoins)/attempts;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << endl << endl << limit;
    SetConsoleTextAttribute(hConsole, 15); //set back to black background and white text
    
    return 0;
}
