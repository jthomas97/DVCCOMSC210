//PART 2 
// Its stops producing output around 90 as the recursion goes to deep and it takes a large amount of computing power
//

//Programmer Name: Jude Thomas
//Programmer ID: 1574815

#include <iostream>
using namespace std;

int golombSequence(int);

int main()
{
  int test1 = 1;
  int test2 = 2;
  int test4 = 15;
  int testFinal = 90;

  cout << "Test 1\n";
  for(int x = 1; x <= test1;x++)
  {
    cout << x << ": " << golombSequence(x) << endl;
  }

  cout << "\nTest 2\n";
  for(int y = 1; y <= test2;y++)
  {
    cout << y << ": " << golombSequence(y) << endl;
  }

  cout << "\nTest 15\n";
  for(int z = 1; z <= test4;z++)
  {
    cout << z << ": " << golombSequence(z) << endl;
  }

  cout << "\nTest 90\n";
  for(int k = 1; k <= testFinal;k++)
  {
    cout << k << ": " << golombSequence(k) << endl;
  }


  cout << endl << endl;
  return 0;
}

int golombSequence(int num)
{
  if(num == 1)
    return 1;
  if(num == 2)
    return 2;
  return (1 + golombSequence(num - golombSequence(golombSequence(num - 1))));
}