#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <queue>
#include <string>
using namespace std;


// The graph is a simple adjacency list format -- each node (struct Person) 
// contains a string vector of all of its friend nodes.
//

#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "facebook.csv"
using namespace std;

struct Person {
    vector<string> friends;
};

void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;
    queue<string> myQueue;
    map<string,int> visited;

    // Verify that the file open was OK
    if (!inFile.good()) {
        cerr << "Invalid file." << endl;
        return (-1);
    }

    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names in the
    // below loop.
    getline(inFile, inputLine);
    parse_line(inputLine, names);

    // Reach each subsequent entry
    while (getline(inFile, inputLine)) {
        if (inFile.eof())
            break;
        vector<string> row;
        Person p;
        parse_line(inputLine, row);
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status == 1)
                p.friends.push_back(names[i]);
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }


    string name1, name2;
    for(;;)
    {
    //Check for Name1
        cout << endl << "Enter the starting name(X to quit): ";
        getline(cin, name1);
        if (IS_QUIT(name1))
        break;
        if (everyone.count(name1) == 0)
        {
            cout << "That person is not in the map. \n";
            continue;
        }

    //Check for Name2
        cout << endl << "Enter the ending name(X to quit): ";
        getline(cin, name2);
        if(IS_QUIT(name2))
        break;
        if(everyone.count(name2) == 0)
        {
            cout << "That person is not in the map. \n";
            continue;
        }

        while (!myQueue.empty())
        {
            myQueue.pop();
        }
        myQueue.push(name1);
        visited[name1] = 1;
        bool found = false;
        while(!myQueue.empty())
        {
            string front = myQueue.front();
            myQueue.pop();
            Person tempPerson = everyone[front];

            for(size_t i = 0; i < tempPerson.friends.size(); i++){
                string tempFriend = tempPerson.friends[i];
                if(tempFriend.compare(name2) == 0){
                    cout << "There Is a path between these two people. \n";
                    found = true;
                    break;
                }

                if(visited.count(tempFriend) == 0){
                    myQueue.push(tempFriend);
                    visited[tempFriend] = 1;
                }
                if(found == true) break;
            }
        }
        if(!found)
            cout << "There is NOT a path between these two people. \n";

    }

    cout << "Exiting..." << endl;
    return (0);
}
