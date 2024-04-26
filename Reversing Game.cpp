#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

// objective create a reversal game with permutations of 1 to n 

bool isPermutation(const int arr[], int n);
void checkPermutation ();
void initalizePermutation (int arr[], int n); 
void copyArray (int destinationArr[], int sourceArr[], int n); 
void reverseArray (int arr[], int indexesToReverse); 
int scorePermutation (int arr[], int size); 
bool nextPermutation(int arr[], int n); 
void printPermutationsAndScore(int permutation[], int score, int size); 
void findOptimalPermutation (int arr[], int n); 
void playReversalGame (int minNValue, int maxNValue); 

int main() {

    // simple tests for isPermutation(), add more for better testing
    checkPermutation(); 

    // print reversal game to screen 
    const int MIN_N_VALUE = 1; 
    const int MAX_N_VALUE = 11; 
    playReversalGame (MIN_N_VALUE, MAX_N_VALUE); 

    cout << endl;
	return 0; 
}

bool isPermutation(const int arr[], int n){

    // comparing factorial of length against product of all values in array 
    int productOfArray = 1; 
    int nFactorial = 1; 
    for (int i = 1; i <= n; i++) {
        productOfArray *= arr[i-1]; 
        nFactorial *= i; 
    }

    // return true if arr is a permutation of 1 to n, else return false 
    if (nFactorial == productOfArray) {
        return true; 
    } else {
	    return false;
    }  
}

void checkPermutation () {

	cout << "some isPermutation() tests (perhaps add more!)" << endl;
	int arr1[] = {4, 2, 3, 1, 5};
	cout << "isPerm 1? " << boolalpha << isPermutation(arr1, 5) << endl;
	int arr2[] = {4, 2, 3, 5, 5};
	cout << "isPerm 2? " << boolalpha << isPermutation(arr2, 5) << endl;
	int arr3[] = {4, 2, 0, 1};
	cout << "isPerm 3? " << boolalpha << isPermutation(arr3, 4) << endl;
	cout << endl;
}

// initlize permutation backwards using recursion
void initalizePermutation (int arr[], int n) {

    if (n != 0) {
        arr [n-1] = n;
        initalizePermutation (arr, n-1); 
    }
}   

void copyArray (int destinationArr[], int sourceArr[], int n) {

    for (int i = 0; i < n; i++) {
        destinationArr[i] = sourceArr[i]; 
    }
}

// "m" variable switched with indexesToReverse for clarity 
void reverseArray (int arr[], int indexesToReverse) {

    for (int i = 0; i < (indexesToReverse/2); i++) {
        int temporary = arr[i]; 
        arr[i] = arr[indexesToReverse-1-i]; 
        arr[indexesToReverse-1-i] = temporary; 
    }
}

// count switches needed for array to begin with 1 
int scorePermutation (int permutation[], int size) {

    // initalize all variables
    int changingPermutation[size]; 
    copyArray (changingPermutation, permutation, size); 
    int score = 0; 

    // play reversal games 
    while (changingPermutation[0] != 1) {
        reverseArray (changingPermutation, changingPermutation[0]);  
        score++;      
    }
    return score; 
}

bool nextPermutation(int arr[], int n) {

    // check if array is still possible to permutate
    assert (isPermutation(arr, n)); 

    // calculate next hightest permutation by built in C++ algorithm header
    return next_permutation(&arr[0], &arr[n]);
}

// print display to match that given in examples
void printPermutationsAndScore(int permutation[], int score, int size) {
    
    cout << "[n = " << size << "] Score of {";  
    for (int i = 0; i < size; i++) {
        if (i != 0) {
            cout << ", "; 
        }
        cout << permutation[i]; 
    }
    cout << "} = " << score << endl; 
}

void findOptimalPermutation (int optimalPermutation[], int size) {

    // initalize all variables 
    int currentPermutation[size];
    initalizePermutation (currentPermutation, size);  
    bool morePermutations = true;
    int optimalScore = 0; 

    // score all possible permutations 
    while (morePermutations) {
        int permutationScore = scorePermutation(currentPermutation, size);
        if (permutationScore > optimalScore) {
            copyArray (optimalPermutation, currentPermutation, size); 
            optimalScore = permutationScore; 
        }
        morePermutations = nextPermutation(currentPermutation, size);
    }

    // if nothing changed score 
    if (optimalScore == 0) {
        copyArray (optimalPermutation, currentPermutation, size); 
    }

    printPermutationsAndScore(optimalPermutation, optimalScore, size); 
} 

// run reversal game from min to max value 
void playReversalGame (int minNValue, int maxNValue) {
    
    for (int n = minNValue; n <= maxNValue; n++) {
        int optimalPermutation[n]; 
        findOptimalPermutation (optimalPermutation, n); 
    }
}
