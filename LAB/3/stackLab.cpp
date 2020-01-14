//Programmer: Jude Thomas
//Programmer's ID: 1574815

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
  cout << "Programmer: Jude Thomas\n";
  cout << "Programmer's ID: 1574815\n";
  cout << "File: " << __FILE__ << endl << endl;

  vector<int> Stack;
  int numLines = 0;


  ifstream infile("testcases.txt");

// Gets the number of lines for each test case from testcases.txt
  while(infile >> numLines)
  {
    int operation = 0, value = 0;
    bool isStack = false;
// Clear vector for each test case
    Stack.clear();

    cout << "Number of lines to read from file: " << numLines << endl;

// Loop for numLines from testcases.txt
    for(int x = 0;x < numLines; x++)
    {

      infile >> operation >> value;

      cout << "Line: " << x+1 << " operation: " << operation << " value: " << value << endl;

// If operation is a push to stack, push the value into vector
      if(operation == 1)
      {
        Stack.push_back(value);
      }
// If operation is a pop, get a reference to end of vector(stack top) and determine if value == stack top
      else if(operation == 2)
      {
        int stackTop = Stack.back();
        if(stackTop != value)
          isStack = false;
        else
        {
          isStack = true;
        }
        Stack.pop_back();
        
      }
// If operation isnt == 1 or 2, that is a invalid operation. Therefor not a stack
      else
      {
        isStack = false;
      }
      
      
    }

// Print if test case is a stack or not
    if(isStack)
      cout << "stack\n\n";
    else 
      cout << "not stack\n\n";
  }
  system("pause");
  return 0;
}