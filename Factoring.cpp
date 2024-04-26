#include <iostream> 
#include <iomanip> 
#include <string> 
using namespace std; 

// objective print all factors and special factoring specifications between two given numbers [1, 999]

const int MIN_INTEGER = 1; 
const int MAX_INTEGER = 999; 

const int SMALLEST_FACTOR = 1; 
const int SPECIAL_FACTORING_CONDITION = 2; 

const int SPACING = 4; 
const int SPACING_BRACKET = 3; 

int collectProperInput (string messageStart); 
int factorNumberInRange (int currentNumberInRange);
void specialFactoringCheck (int factorCount); 

int main () {
    // collect input 
    int inputNumber1 = collectProperInput ("Enter a value "); 
    int inputNumber2 = collectProperInput ("Enter a second value "); 

    // set range to begin at least inputed number and end at greatest inputed number
    int currentNumberInRange = 0; 
    int endOfRange = 0; 

    if (inputNumber1 >= inputNumber2) {
        currentNumberInRange = inputNumber2; 
        endOfRange = inputNumber1; 
    } else {
        currentNumberInRange = inputNumber1; 
        endOfRange = inputNumber2; 
    }
    
    // factor all numbers in range
    while (currentNumberInRange <= endOfRange) {

        // print all numbers in range, all of their factors, and any of thier special factoring specifications 
        cout << setw (SPACING) << currentNumberInRange << " "; 
        int factorCount = factorNumberInRange (currentNumberInRange); 
        cout << setw (SPACING_BRACKET) << "(" << factorCount << ")";
        specialFactoringCheck (factorCount); 
        cout << endl; 

        currentNumberInRange++; 
    }

    return 0; 
}

// prompt user for two integers from 1 through 999, prompt again if out of restrictions
int collectProperInput (string messageStart) {

    int inputedNumber = 0; 
    cout << messageStart << "between " << MIN_INTEGER << " and " << MAX_INTEGER << ": "; 
    cin >> inputedNumber;

    while (inputedNumber < MIN_INTEGER || inputedNumber > MAX_INTEGER) { 
        cout << "The value must be between " << MIN_INTEGER << " and " << MAX_INTEGER << " inclusive: "; 
        cin >> inputedNumber; 
    }

    return inputedNumber; 
}

// find all factors of a number in the user specfied range 
int factorNumberInRange (int currentNumberInRange) {
    
    int possibleFactor = SMALLEST_FACTOR;
    int factorCount = 0; 

    // check all numbers between smallest factor 1 to specified number in range 
    while (possibleFactor <= currentNumberInRange) {
        if (!(currentNumberInRange % possibleFactor)) { 
            cout << setw(SPACING) << possibleFactor << " "; 
            factorCount++; 
        }
        possibleFactor++; 
    }

    return factorCount;
}

// use number of factors to check for special factoring 
void specialFactoringCheck (int factorCount) {

    bool isPerfectSquare = (factorCount % SPECIAL_FACTORING_CONDITION); 
    if (isPerfectSquare) {
        cout << "  **perfect square**"; 
    }

    bool isPrime = (factorCount == SPECIAL_FACTORING_CONDITION); 
    if (isPrime) {
        cout << "  **prime**"; 
    }
}
