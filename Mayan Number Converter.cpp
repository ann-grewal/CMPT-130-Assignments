#include <iostream> 
#include <iomanip>
#include <cmath>
#include <ctime> 
#include <cstdlib> 
#include <vector>
using namespace std;

// objective write a mayan number guessing game 

const int TEST_NUMBER = 2072025; 
const int MAYAN_BASE = 20;
const int MAX_POWER = 7; 
const int DECIMAL_MIN = 4; 
char mayanGameRoundOptions(int correctDecimal); 
bool mayanGameRoundInput (char correctOption); 
void mayanNumberConverter (int decimalNumber); 
void printMayanNumber (vector <int> mayanNumber); 
void printMayan5Symbol (int amountOfSymbol); 
void printMayan1Symbol (int amountOfSymbol); 
int randomNumber (int rangeStarting, int rangeEnding); 

int main () {
    // mayan number test
    cout << "In order to test this program, the number " << TEST_NUMBER << " is printed in Mayan Base 20:" << endl; 
    mayanNumberConverter(TEST_NUMBER);
    cout << endl << endl; 

    // game set up 
    cout << "MAYAN NUMBER GAME" << endl << "=================" << endl; 
    cout << "You\'ll first enter a number (>= 10) to be the maximum number to guess." << endl;
    cout << "You\'ll then match a decimal number to its Maya equivalent." << endl; 
    srand (time(nullptr)); 

    // game running
    while (true) {

        // round set up
        int decimalMax = 0; 
        int correctDecimal = 0;  
        bool winner = false; 
        cout << "Enter a maximum to guess from (< 10 exists): ";
        cin >> decimalMax;  
        cout << endl; 

        // round play 
        if (decimalMax >=10) {
            correctDecimal = randomNumber(DECIMAL_MIN, decimalMax); 
            char correctOption = mayanGameRoundOptions(correctDecimal);
            winner = mayanGameRoundInput (correctOption); 
        } else {
            break; 
        }

        // round result 
        if (winner) {
            cout << "CORRECT! "; 
        } else {
            cout << "INCORRECT! "; 
        }
        cout << "The Mayan representation of " << correctDecimal << " is" << endl; 
        mayanNumberConverter(correctDecimal); 
        cout << endl; 
    }
}

char mayanGameRoundOptions (int correctDecimal) {
    
    const double INCORRECT_MIN_ERROR = 0.5; 
    const double INCORRECT_MAX_ERROR = 1.5;
    const int AMOUNT_OF_CHOICES = 3; 

    // create incorrect options 
    int incorrectAnswer1 = randomNumber (correctDecimal*INCORRECT_MIN_ERROR, correctDecimal*INCORRECT_MAX_ERROR); 
    int incorrectAnswer2 = randomNumber (correctDecimal*INCORRECT_MIN_ERROR, correctDecimal*INCORRECT_MAX_ERROR); 
    while (incorrectAnswer1 == incorrectAnswer2) {
        incorrectAnswer2 = randomNumber (correctDecimal*INCORRECT_MIN_ERROR, correctDecimal*INCORRECT_MAX_ERROR); 
    }

    // randomly assign values
    int optionA = 0; 
    int optionB = 0; 
    int optionC = 0; 
    char correctOption = '0'; 

    int correctAnswerPlace = randomNumber (1, AMOUNT_OF_CHOICES); 
    if (correctAnswerPlace == 1) {
        optionA = correctDecimal; 
        optionB = incorrectAnswer1; 
        optionC = incorrectAnswer2; 
        correctOption = 'a';
    } else if (correctAnswerPlace == AMOUNT_OF_CHOICES) {
        optionA = incorrectAnswer1; 
        optionB = correctDecimal;
        optionC = incorrectAnswer2; 
        correctOption = 'b';
    } else {
        optionA = incorrectAnswer1; 
        optionB = incorrectAnswer2; 
        optionC = correctDecimal;  
        correctOption = 'c'; 
    }

    // print options 
    cout << "Which of these Mayan numbers is equal to " << correctDecimal << "?" << endl; 
    cout << "a." << endl; 
    mayanNumberConverter(optionA);
    cout << endl; 
    cout << "b." << endl; 
    mayanNumberConverter(optionB); 
    cout << endl; 
    cout << "c." << endl; 
    mayanNumberConverter (optionC); 
    cout << endl; 

    return correctOption; 
}

bool mayanGameRoundInput (char correctOption) {
    char userInput = '0'; 

    // take in correct type of input
    while (userInput != 'a' && userInput != 'b' && userInput != 'c') {
        cout << "Enter a, b, or c: "; 
        cin >> userInput; 
    }

    // return result of round 
    if (userInput == correctOption) {
        return true; 
    } else {
        return false; 
    }
}

void mayanNumberConverter (int decimalNumber) {

    vector<int> mayanNumber; 
    int decimalLeft = decimalNumber; 
    int amountOfMayanPower = 0; 
    int mayanPower = 0; 

    // distribute decimal number between powers of mayan base (20) 
    for (int i = MAX_POWER; i >= 0; i--) {
        mayanPower = pow (MAYAN_BASE, i);
        amountOfMayanPower = decimalLeft / mayanPower; 
        decimalLeft -= amountOfMayanPower * mayanPower;

        // save conversion of each mayan power 
        mayanNumber.push_back(amountOfMayanPower);
    }

    printMayanNumber(mayanNumber); 
}

void printMayanNumber (vector <int> mayanNumber) {

    const int MAX_MAYAN_SYMBOL_VALUE = 5;  
    const string MAYAN_SYMBOL_0 = "00"; 
    const string DIVIDER = "------";
    bool leading0s = true; 

    // printing number backwards, top to bottom 
    for (int i = 0; i <= MAX_POWER; i++) {
        int amountOfMayanPower = mayanNumber.at(i);
        
        if (amountOfMayanPower) {
            printMayan1Symbol (amountOfMayanPower % MAX_MAYAN_SYMBOL_VALUE); 
            printMayan5Symbol (amountOfMayanPower / MAX_MAYAN_SYMBOL_VALUE);
            leading0s = false; 
        // restrict printing of leading blank powers 
        } else if (!leading0s || i == MAX_POWER) {
            cout << MAYAN_SYMBOL_0 << endl; 
        } else {
            continue; 
        }

        // print divider for clarity except at bottom 
        if ( i < MAX_POWER) {
            cout << DIVIDER << endl; 
        }         
    }
}

void printMayan5Symbol (int amountOfSymbol) {
    const char* MAYAN_SYMBOL_5 = "\u2580\u2580\u2580\u2580\u2580"; 
    for (int i = 0; i < amountOfSymbol; i++) {
        cout << MAYAN_SYMBOL_5 << endl;
    }
}

void printMayan1Symbol (int amountOfSymbol) {
    const char* MAYAN_SYMBOL_1 = "o"; 
    for (int i = 0; i < amountOfSymbol; i++) {
        cout << MAYAN_SYMBOL_1; 
    }
    if (amountOfSymbol) {
        cout << endl;
    }     
}

int randomNumber (int rangeStarting, int rangeEnding) {
    return rand() % (rangeEnding-rangeStarting) + rangeStarting; 
}