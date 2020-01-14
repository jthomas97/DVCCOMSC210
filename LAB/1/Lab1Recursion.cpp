#include <iostream>
#include <cstring>
using namespace std;

//Protoype
int arrayBack(const char*, int, int, int);

int main()
{
  int first = 0;

//C strings
  const char *test1 = "abc123";
  const char *test2 = "hello";
  const char *test3 = "hello";
  const char *test4 = "c1c1c1";

//Display Output
  int store1 = arrayBack(test1, first, strlen(test1)-1, 2);
  cout << " (sum of numbers removed: " << store1 << ")\n";

  int store2 = arrayBack(test2, first, strlen(test2)-1, 1);
  cout << " (sum of numbers removed: " << store2 << ")\n";

  int store3 = arrayBack(test3, first, strlen(test3)-1, 3);
  cout << " (sum of numbers removed: " << store3 << ")\n";

  int store4 = arrayBack(test4, first, strlen(test4)-1, 2);
  cout << " (sum of numbers removed: " << store4 << ")\n";

  return 0;
}

int arrayBack(const char* string , int first, int last, int nth)
{
  int sum = 0;

  //Check for base case
  if(last < first)
    return 0;
  
  //Determine if to skip char
  if((strlen(string)-last) % nth == 0)
    cout << string[last];

  //If skipped, try to convert to int
  else
  {
    if(string[last] >= '0' && string[last] <= '9')
      sum += (string[last] - '0');
    
  }
  
  sum += arrayBack(string, 0, last-1, nth);

  return sum;
  
}