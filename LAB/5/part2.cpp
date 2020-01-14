#include <iostream>
#include <string>
using namespace std;

#include <cassert> // for assert
#include <cmath>   // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime> 
#include <vector>
#include <fstream>  // for clock( ), clock_t,
// time, and CLOCKS_PER_SEC

#define INFILE "names.txt"

int main() {
    srand(time(0));
    rand(); // seed the RNG (we'll need it)

    // programmer customizations go here
    int x;
    string temp;
    int n = 500; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
    string bigOh = "O(n squared)"; // YOUR PREDICTION: O(n),
    // O(n log n), or O(n squared)

    cout.setf(ios::fixed);
    cout.precision(4);
    double elapsedSecondsNorm = 0;
    double expectedSeconds = 0;
    for (int cycle = 0; cycle < 4; cycle++, n*= 2) {
        // problem setup goes here -- create a data
        // structure of size n
        vector<string> names(n);

        // assert that n is the size of the data
        // structure if applicable
        // assert(a.size( ) == n); // or something like that...
        assert(names.size()==n);
        // start the timer, do something, and stop the time

        ifstream infile;
        infile.open(INFILE);

    //    while(getline(infile, temp))
    //    {
    //        names.push_back(temp);
    //    }

    //    }
    //    cout << "Size of vector is: " << names.size()<<endl;

        for(x = 0; x < n; x++)
        {
            if(infile)
            {
                getline(infile, temp);
                names[x] = temp;
            } else
            {
                break;
            }
        }
        infile.close();

        // do something where n is the "size" of the problem

        // for(int q = 0; q < names.size(); q++)
        //     cout << names[q] << " \n";

        // validation block -- assure that process worked
        // if applicable
        // cout << "X is: " << x << endl;
        // cout << "N is: " << n << endl;
        // cout << "Number of names in names Vector: " << names.size() << endl;
        if(x==n)
        {
            cout << "Successful\n";
        } else
        {
            cout << "Unsuccessful\n";
        }

        clock_t startTime = clock();

        for(int t = 0; t < n; t++)
        {
          for(int y = 0; y < t + 1; y++)
          {
            if(names[y] < names[t])
            {
              swap(names[t], names[y]);
            }
          }
        }

        clock_t endTime = clock();
        
        // for (int i = 1; i < n; i++){
        //   if(assert(names[i - 1] <= names[i]));
        // }
          
        names.clear();
        // cleanup if applicable
        // compute timing results
        double elapsedSeconds = (double)
                                (endTime - startTime) / CLOCKS_PER_SEC;
        double factor = pow(2.0, double(cycle));
        if (cycle == 0)
            elapsedSecondsNorm = elapsedSeconds;
        else if (bigOh == "O(n)")
            expectedSeconds = factor * elapsedSecondsNorm;
        else if (bigOh == "O(n log n)")
            expectedSeconds = factor *
                              log(double(n)) / log(n / factor) *
                              elapsedSecondsNorm;
        else if (bigOh == "O(n squared)")
            expectedSeconds = factor * factor * elapsedSecondsNorm;

        // reporting block
        cout << elapsedSeconds;
        if (cycle == 0)
          cout << " (expected " << bigOh << ')';
        else
          cout << " (expected " << expectedSeconds << ')';
        cout << " for n=" << n << endl;
    }

    system("pause");
    return 0;
}