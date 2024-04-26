#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <vector> 
#include <string> 
#include <algorithm> 
#include <iomanip> 
using namespace std; 

// objective given file of words generate and analyze all for permutation and anagrams

struct stastics_t {
    double numberOfGivenWords; 
    double numberOfEnglishWords; 
    double numberOfCharacters; 
    double numberOfPermutations; 
};

void removeSpace (string &givenWord); 
string toLowerCase (string givenWord);
void getWordList (vector <string> &givenWordsList); 
void swap(string &word, int i, int j); 
void permute(vector<string> &allPermuations, string &word, int left, int right);
void collectionOfGivenPermutations(string word);
void getEnglishWordsList (vector <string> &englishWordsList);  
void collectionOfGivenEnglishWords (string word); 
void createWordFiles (string givenWord, stastics_t &stasticCounter); 
void outputStastics (stastics_t &stasticCounter); 

int main () {

    // get input of word list 
    vector <string> givenWordsList; 
    getWordList (givenWordsList); 

    // create output of word files of permutations anagrams for each, collect stastics 
    // additionally print words to screen
    stastics_t stasticCounter {0, 0, 0, 0}; 
    for (string givenWord : givenWordsList) {
        cout << endl << givenWord; 
        createWordFiles(givenWord, stasticCounter);
    }

    // print stastics 
    outputStastics (stasticCounter); 

    // end main function
    return 0;  
}

void removeSpace (string &givenWord) {

    // remove whitespace at start of string
    while (!givenWord.empty() && isspace(givenWord.at(0))) {
        givenWord.erase(0, 1);
    }

    // remove whitespace at end of string
    while (!givenWord.empty() && isspace(givenWord.at(givenWord.size() - 1))) {
        givenWord.erase(givenWord.size() - 1, 1);
    }
}

string toLowerCase (string givenWord) {
    
    string fixedWord; 

    for (char letter : givenWord) {
        letter = tolower(letter); 
        fixedWord += letter; 
    }

    return fixedWord; 
}

void getWordList (vector <string> &givenWordsList) {

    // initialize variables 
    bool fileClosed = true; 
    bool startOfFile = true; 
    string fileName;
    string content; 

    while (fileClosed) {
        // ask for user input 
        cout << "enter file name of strings: "; 
        cin >> fileName; 

        // try to open file 
        ifstream givenWordsListFileTrial (fileName);
        if (!(givenWordsListFileTrial.fail())) {        
            fileClosed = false; 
        }              
        givenWordsListFileTrial.close(); 
    }  

    // reopen file
    ifstream givenWordsListFile (fileName);
    string givenWord;  

    while (true) {   

        // read file
        givenWord.clear(); 
        getline (givenWordsListFile, givenWord); 

        // close entire program if empty file handed at start 
        if (givenWord.empty() && startOfFile) {
            cout << endl << "exited program"; 
            exit(EXIT_FAILURE); 
        }
        // manipulate string and add to list
        removeSpace(givenWord); 
        givenWord = toLowerCase (givenWord); 
        givenWordsList.push_back(givenWord);       
        
        
        if (givenWordsListFile.fail()) {      
            break;        
        }        

        // update whether at start of file 
        startOfFile = false; 
    }
    // close file 
    givenWordsListFile.close(); 
}

// swap for permutation (given code)
void swap(string &word, int i, int j) {
	int temporary = word.at(i);
	word.at(i) = word.at(j);
	word.at(j) = temporary;
}

// all permutaions of a word (given code)
void permute (vector<string> &allPermutations, string &word, int left, int right) {
	if (left == right) {
		allPermutations.push_back(word);
	}
	else {
		for (int i = left; i <= right; i++) {
			swap(word, i, left);
			permute(allPermutations, word, left + 1, right);
			swap(word, i, left);
		}
	}
}

void collectionOfGivenPermutations(string word, vector <string> &sortedAllPermutations) {
    
    // collect permutations
    vector<string> allPermutations;
    permute(allPermutations, word, 0, word.size() - 1);
    sort (allPermutations.begin(), allPermutations.end()); 

    // remove all repeats, repeats will be next to each other 
    string lastPermutation = " "; 
    for (string permutation : allPermutations) {
        if (permutation != lastPermutation) {
            sortedAllPermutations.push_back(permutation);
        }
        lastPermutation = permutation; 
    }

}

void getEnglishWordsList(vector <string> &englishWordsList) {

    // open english word list
    ifstream englishWordsListFile ("englishWordsList.txt");
    if (englishWordsListFile.fail()) {        
        cout << "unable to open data file" << endl;        
        exit(EXIT_FAILURE);    
    }    

    // read in word list 
    while (true) {      
        string englishWord;     
        englishWordsListFile >> englishWord; 
        englishWordsList.push_back(englishWord);       
        
        if (englishWordsListFile.fail()) {            
            break;        
        }        
    }

    // close file 
    englishWordsListFile.close(); 
}

void collectionOfGivenEnglishWords (const vector <string> wordPremutations, vector <string> &wordsInEnglish) {

    // get english word list 
    vector <string> englishWordsList;
    getEnglishWordsList(englishWordsList); 

    // compare premutations to english words 
    for (string premutations: wordPremutations) {
        bool inEnglishWordList = binary_search(englishWordsList.begin(), englishWordsList.end(), premutations);

        // collect all premutations that are english words in vector 
        if (inEnglishWordList) {
            wordsInEnglish.push_back(premutations);
        }
    }
}

void createWordFiles (string givenWord, stastics_t &stasticCounter) {
    
    // open file 
    ofstream createdWordFile (givenWord + ".txt"); 
    if (createdWordFile.fail()) {        
        cout << "unable to open data file" << endl;        
        exit(EXIT_FAILURE);
    } 

    // count words and characters (spaces and repeats not included) 
    stasticCounter.numberOfGivenWords++; 
    stasticCounter.numberOfCharacters += givenWord.size(); 

    // write permutations and permutations that are english words to file
    vector<string> wordPermutations; 
    collectionOfGivenPermutations(givenWord, wordPermutations);
    for (string permutation : wordPermutations) {
        createdWordFile << permutation << endl; 
        stasticCounter.numberOfPermutations++; 
    }
    createdWordFile << "*" << endl; 
    vector<string> wordsInEnglish; 
    collectionOfGivenEnglishWords (wordPermutations, wordsInEnglish); 
    for (string englishWords : wordsInEnglish) {
        createdWordFile << englishWords << endl; 
        stasticCounter.numberOfEnglishWords ++; 
    }

    // close file
    createdWordFile.close(); 
}

// output stastics to file 
void outputStastics (stastics_t &stasticCounter) {
    const int precision = 2; 

    // open file 
    ofstream stasticsFile ("stasticsFile.txt"); 
    if (stasticsFile.fail()) {        
        cout << "unable to open data file" << endl;        
        exit(EXIT_FAILURE);
    } 

    // write to file 
    stasticsFile << "Number of given strings: " << stasticCounter.numberOfGivenWords << endl; 
    stasticsFile << "Number of given characters: " << stasticCounter.numberOfCharacters << endl; 
    stasticsFile << "Number of permutations possible: " << stasticCounter.numberOfPermutations << endl; 
    stasticsFile << fixed << "Average number of permutations per string: " << setprecision(precision) <<(stasticCounter.numberOfPermutations/stasticCounter.numberOfGivenWords) << endl; 
    stasticsFile << "Number of anagrams possible: " << stasticCounter.numberOfEnglishWords << endl; 
    stasticsFile << fixed <<"Average number of permutations per string: " << setprecision(precision) << (stasticCounter.numberOfEnglishWords/stasticCounter.numberOfGivenWords) << endl; 
    
    // close file 
    stasticsFile.close(); 
} 