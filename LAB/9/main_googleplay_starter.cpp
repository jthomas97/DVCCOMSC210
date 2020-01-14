#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define FILENAME "googleplay.csv"

// A single app in the Google Play Store.  If you are using
// chaining, you may need to add an additional structure here (or a 
// 'next' pointer within this structure) to maintain the chains in
// each bucket.
struct PlaystoreApp {
    string name;
    string category;
    double rating;
    int reviews;
    struct PlaystoreApp *next;
};

typedef struct PlaystoreApp googlePlayApp;

// Starting size.  Don't adjust this unless absolutely necessary.
const int HASH_SIZE = 10007;

int genHash(string s)
{
  unsigned long n = 0;
  std::hash<string> h;
  n^= h(s) + 0x9e3779b9 + (n<< 6);
  return n%HASH_SIZE;
}

// Hash table for all of the apps -- static so it's zeroed.  This
// is an array of pointers (change as needed).
static googlePlayApp *appHash[HASH_SIZE];

// Reads a single app, filling in the
// fields (name, etc.) passed by the caller.  The caller
// is expected to pass a single line (row) from the csv file.
void readSingleApp(const string &str,
        googlePlayApp &newApp) {

    istringstream istr(str);
    string fields[5];
    string tmp;
    int i = 0;

    // Read in each csv column
    while (getline(istr, tmp, ',')) {
        fields[i++] = tmp;
    }

    // Populate the new item with the   column info
    newApp.name = fields[0];
    newApp.category = fields[1];
    newApp.rating = atof(fields[2].c_str());
    newApp.reviews = atoi(fields[3].c_str());
}

int totalCompares;

// Insert a new app into the hash table.  You may want to add a
// reference variable here to track number of comparisons.
void appInsert(googlePlayApp &newApp) {
    googlePlayApp *addApp = new googlePlayApp();

    addApp->name = newApp.name;
    addApp->category =newApp.category;
    addApp->rating = newApp.rating;
    addApp->reviews = newApp.reviews;

    int hashKey = genHash(addApp->name);

    addApp->next = NULL;

    if(appHash[hashKey] == NULL)
    {
        appHash[hashKey] = addApp;
        return;
    }

    googlePlayApp *temp = appHash[hashKey];

    while (temp->next != NULL)
    {
        temp = temp->next;
        totalCompares++;
    }
    temp->next = addApp;
    totalCompares++;
    
}

// Find an app in the hash table
// Returns 'true' if the app was found, filling in the
// fields of 'foundApp', else false.  You may want to add a reference
// variable here to track number of comparisons.
bool appFind(const string &name, googlePlayApp &foundApp) {
    int compares = 0;
    int hashKey = genHash(name);
    googlePlayApp *ptr = appHash[hashKey];
    if(ptr == NULL) return false;
    while(ptr!=NULL)
    {
        compares++;
        if(name.compare(ptr->name) == 0)
        {
            foundApp.name = name;
            foundApp.category = ptr->category;
	        foundApp.rating = ptr->rating;
	        foundApp.reviews = ptr->reviews;
	        cout<<"\n\nFound, comparisons required:"<<compares<<"\n";
	        return true;
        }
        ptr= ptr->next;
    }
    cout<<"\nNot found in table. Comparisons required:"<<compares<<"\n";
    return false;
}

int main() {
    ifstream inFile(FILENAME);
    string inputLine, inputStr;
    int linesRead = 0;

    totalCompares = 0;
    // Read in each app entry
    while (getline(inFile, inputLine)) {
        googlePlayApp newApp;
        readSingleApp(inputLine, newApp);
        appInsert(newApp);
        linesRead++;
        // For extra debugging output
        //if (linesRead % 1000 == 0)
        //    cout << "Inserted " << linesRead << " entries"
        //         << endl;
    }
    if (linesRead == 0) {
        cerr << "Reading failed." << endl;
        return (-1);
    } else {
        cout << "Read " << linesRead << " apps." << endl;
        cout << "Average comparisons required:" << totalCompares*1.0/linesRead << endl;
    }

    for (;;) {
        string tmp;
        googlePlayApp foundApp;
        cout << "Enter an app name (<return> to quit): ";
        getline(cin, tmp);
        if (tmp == "") {
            break;
        }
        if (appFind(tmp, foundApp) == false) {
            cout << "Not found in the database." << endl;
            continue;
        }

        // Output the app info here
        cout << "Name: " << foundApp.name << endl;
        cout << "Category: " << foundApp.category << endl;
        cout << "Rating: " << foundApp.rating << endl;
        cout << "Number of reviews: " << foundApp.reviews << endl;
        // ...
    }
    return (0);
}
