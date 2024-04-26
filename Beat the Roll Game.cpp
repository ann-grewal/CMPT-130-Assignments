#include <iostream> 
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
using namespace std; 

// objective dice game between player and computer 0 to 100 points 

const int startingScore = 50; 
const int winningScore = 100;
const int losingScore = 0; 
const int minimumBet = 1; 
const int sidesOfDie = 6; 
const int secondColumnWidth = 40; 

void welcomeMessage();
string getName();  
void getSeedRandom(); 
int getMaxBet();
int getUserBet(int maxBet, int userScore); 
int randomRoll(); 
int rollDie(string player); 
 
int main () {

    // get all information needed for start of game 
    welcomeMessage(); 
    string name = getName(); 
    getSeedRandom(); 
    int maxBet = getMaxBet(); 
    int userScore = startingScore; 
    int roundNumber = 1; 

    while (userScore > losingScore && userScore < winningScore) {
        
        // get all information needed for roumd
        cout << endl << "Round " << roundNumber << " You have " << userScore << " points." << endl; 
        int dealerRoll = rollDie("Dealer Rolls: "); 
        int userBet = getUserBet (maxBet, userScore); 
        int userRoll = rollDie ("You roll:     ");

        // compare rolls and change points accordingly 
        if (userRoll > dealerRoll) {
            userScore += userBet;
            cout << endl << name << ", you won! :-)" << endl; 
        } else if (userRoll < dealerRoll) {
            userScore -= userBet;
            cout << endl << name << ", you lost :-(" << endl; 
        } else {
            cout << endl << name << ", you tied. :-|" << endl; 
        }   
        cout << "Current score: " << userScore << endl;  

        roundNumber++; 
    }

    // specify why game ended, winner or loser 
    if (userScore >= 100) {
        cout << "Congratulations " << name << "! You win the game with a score of " << userScore << "." << endl << endl; 
    } else {
        cout << "I\'m sorry, " << name << "; you are out of points so you lose." << endl << endl;
    }

    return 0; 
}

void welcomeMessage() {
    cout << "********************************************" << endl; 
    cout << "Welcome to Roller\'s Un-Random house of dice!" << endl; 
    cout << "********************************************" << endl; 
}

// user input name 
string getName() {
    string name = ""; 
    cout << "What is your first name? "; 
    cin >> name; 
    return name; 
}

// seed random based on time for regular games and based on number for testing game
void getSeedRandom() {
    int choiceOfRandom = 0; 
    cout << "Would you like to pick an un-random game, or let the timer pick? " << endl; 
    cout << "Enter 0 for timer, or pick your own un-random game: "; 
    cin >> choiceOfRandom;  

    if (choiceOfRandom) {
        srand(choiceOfRandom); 
        cout << choiceOfRandom << "! A wise and safe choice." << endl << endl; 
    } else {
        srand(time(nullptr)); 
        cout << "THE TIMER! A daring choice!" << endl << endl; 
    }
}

// user input max bet 
int getMaxBet() {
    int maxBet = 0; 
    while (true)  {
        cout << "What would you like to be the maximum bet? "; 
        cin >> maxBet; 
        if (maxBet >= minimumBet) {
            return maxBet; 
        } else {
            cout << "The maximum bet must be greater than or equal to " << minimumBet << "." << endl; 
        }
    }
}

// user input current bet 
int getUserBet(int maxBet, int userScore) {
    int userBet = 0; 
    cout << setw(secondColumnWidth) << "Enter your bet: "; 
    cin >> userBet;  

    while (true) {
        if (userBet <= userScore && userBet <= maxBet && userBet > 0) {
            return userBet; 
        } else if (userBet > userScore) {
            cout << "Your bet must not be more than your score (" << userScore << ")." << endl; 
        } else if (userBet > maxBet) {
            cout << "Your bet must not bet more than the maximum bet (" << maxBet << ")." << endl;
        } else {
            cout << "Your bet must be at least 1." << endl; 
        }
        cout << "Enter your bet: "; 
        cin >> userBet; 
    }
} 

// structured to allow change of amount of sides to die
int randomRoll() {
    return rand() % sidesOfDie + 1; 
}

// extra function for each time dice need to be rolled 
int rollDie(string playerRolling) {
    int roll1 = randomRoll();
    int roll2 = randomRoll(); 
    int rollTotal = roll1 + roll2; 
    cout << playerRolling << roll1 << " + " << roll2 << " = " << rollTotal;  
    return rollTotal; 
}


