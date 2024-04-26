
#include <fstream> 
#include <iostream>
#include <vector>  
#include <string> 
#include <iomanip> 
using namespace std; 

// objective make a mock social media system with information from an external file 

// constant data type set ups 
const int publicPostTarget = 0; 
struct post_t {
    int authorID; 
    int targetID;
    string message; 
};

// all function prototypes 
vector<post_t> readPostsFromFile(const string &fileName); 
string trim(string str); 

int numberOfPublicPosts (const vector<post_t> &allPosts);
int countPostsPerAuthor (const vector<post_t> &allPosts, int currentAuthorID); 
int mostPostsAuthorID (const vector<post_t> &allPosts); 
void makeAllPostsHappy (vector<post_t> &allPosts); 

void sharePost (const post_t &post); 
void shareAllPosts (const vector <post_t> &allpost);

int main() {
    // share demo post 
    post_t demoPost {101, 9999, "Just a test"}; 
    sharePost (demoPost); 
    cout << endl; 

    // read posts from file and store in vector 
    string fileName = "lab10Data.txt"; 
    vector <post_t> allPosts = readPostsFromFile(fileName);

    // find information on posts and share 
    int publicPostCount = numberOfPublicPosts(allPosts); 
    cout << "number of public posts: " << publicPostCount << endl; 
    int mostPostsAuthor = mostPostsAuthorID(allPosts); 
    cout << "most posts author: " << mostPostsAuthor << endl << endl; 

    // share all posts regularly 
    shareAllPosts (allPosts); 
    cout << endl; 

    // make all posts happy 
    makeAllPostsHappy(allPosts);

    shareAllPosts (allPosts);


    return 0; 
}


// trim all whitespace (space, tab, \r) removed from beginning and end of the string, returns string
string trim(string str) {    
    // beginning of string 
    while (!str.empty() && isspace(str.at(0))) {       
        str.erase(0, 1);    
    }    
    // end of string
    while (!str.empty() && isspace(str.at(str.size() - 1))) { 
        str.erase(str.size() - 1, 1);
    }    
    // return string 
    return str; 
}

vector<post_t> readPostsFromFile(const string &fileName) {    
    vector<post_t> posts;

    // open file 
    ifstream file(fileName);
    if (file.fail()) {        
        cout << "Unable to open data file.\n" ;        
        exit(EXIT_FAILURE);    
    }    
    
    while (true) {      

        // read file data for author 
        post_t post;        
        file >> post.authorID;       
        
        // check for data using both possible conditiosn    
        if (file.fail() && file.eof()) {            
            break;        
        }        
        
        // read rest of text file for pot         
        file >> post.targetID;        
        getline(file, post.message);  

        // Trim any tailing spaces ('\r' or '\n') and store
        post.message = trim(post.message);        
        posts.push_back(post);        
        
        // check for data
        if (file.fail()) {
            cout << "unable to read course info from file." << endl; 
            exit(EXIT_FAILURE);        
        }
   }

   // funciton closing 
    file.close();
    return posts; 
} 

int numberOfPublicPosts (const vector<post_t> &allPosts) {
    int numberOfPublicPosts = 0; 
    for (post_t post : allPosts) {
        if (!post.targetID) {
            numberOfPublicPosts++; 
        }
    }
    return numberOfPublicPosts; 
}

int countPostsPerAuthor (const vector<post_t> &allPosts, int currentAuthorID) {
    
    int postsPerAuthor = 0; 

    // count all posts of a certain author 
    for (post_t post : allPosts) {
        if (post.authorID == currentAuthorID) {
            postsPerAuthor++; 
        }
    }

    return postsPerAuthor; 
}

int mostPostsAuthorID (const vector<post_t> &allPosts) {
    
    // set all counters to 0 
    int mostPostsAuthor = 0; 
    int mostPostsAuthorID = 0; 
    int currentAuthorPostCount = 0;

    // go through all possible authors 
    for (post_t post : allPosts) {

        // update if found author with more posts 
        currentAuthorPostCount = countPostsPerAuthor(allPosts, post.authorID); 

        if (mostPostsAuthor < currentAuthorPostCount) {
            mostPostsAuthor = currentAuthorPostCount; 
            mostPostsAuthorID = post.authorID; 
        }
    }

    return mostPostsAuthorID; 
}

void makeAllPostsHappy (vector<post_t> &allPosts) {
    for (unsigned int i = 0; i < allPosts.size(); i++) {
        allPosts.at(i).message += " :)"; 
    }

}

void sharePost (const post_t &post) {
    const int authorIDSpace = 9; 
    const int targetIDSpace = 11; 
    cout << setw(authorIDSpace) << post.authorID; 
    cout << setw(targetIDSpace) << post.targetID; 
    cout << "  " << post.message; 
    cout << endl; 
}

void shareAllPosts (const vector <post_t> &allPosts) {
    cout << "Author ID  Target ID  Message" << endl; ; 
    cout << "---------  ---------  -------" << endl; 

    for (post_t post: allPosts) {
        sharePost(post); 
    }