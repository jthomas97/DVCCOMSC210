#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "myHeap.h"

using namespace std;

int main()
{

  srand(time(0));
  
  myHeap<int> heap2;

  int tempArr[10], tempArr2[10];
  string bool1, bool2;

  for(int i = 0; i < 10; i++)
  {
    int tempNum = 1 + (rand()%100);
    tempArr[i] = tempNum;
  }

  myHeap<int> heap1(tempArr, 10);

  cout << "\nExisting Array Test\n";
  cout << "-------------------\n";
  cout << "Random Array:\n\t";
  for(int x = 0; x < 10; x++)
  {
    cout << tempArr[x] << " ";
  }
  if(heap1.isEmpty() == 0){
    bool1 = "FALSE";
  } else
  {
    bool1 = "TRUE";
  }
  
  cout << "\nNumber of nodes: (isEmpty() is " << bool1 << ")\n";
  int num1 = heap1.getNumberOfNodes();
  cout << "\t" <<num1 << endl;
  cout << "10 PeekTops/Removes:\n\t"; 

  for(int i = 0; i < 10; i++)
  {
    cout << heap1.peekTop() << " ";
    heap1.remove();
  }


//########################
  cout << "\n\nStarting with empty heap\n";
  cout << "------------------------\n";

  cout << "\nRandom array:\n\t";
  for(int z = 0; z < 10; z++)
  {
    int tempNum = 1 + (rand()%100);
    tempArr2[z] = tempNum;
    cout << tempArr2[z] << " ";
  }
    

  if(heap2.isEmpty() == 0)
  {
    bool2 = "FALSE";
  } else
  {
    bool2 = "TRUE";
  }
  int num2 = heap2.getNumberOfNodes();
  
  cout << "\nNumber of nodes: (isEmpty() is " << bool2 << ")\n";
  cout << "\t" <<num2 << endl;


  cout << "10 PeekTops/Removes:\n\t";
  for(int t = 0; t < 10; t++)
    heap2.add(tempArr2[t]);

  
  for(int i = 0; i < 10; i++)
  {
    cout << heap2.peekTop() << " ";
    heap2.remove();
  }


  return 0;
}

