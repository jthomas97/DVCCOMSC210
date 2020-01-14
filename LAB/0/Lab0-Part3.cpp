#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    const int MAX = 100;
    srand(time(NULL));

    int randomArr[MAX] = {0};
    int oddArr[MAX] = {0};
    int evenArr[MAX] = {0};
    
    for(int index = 0; index < MAX; index++)
    {
        randomArr[index] = (rand()%100) + 1;
    }

    for(int x=0;x<MAX;x++)
    {
        int randomNum = (rand()%100) + 1;
        while(randomNum % 2 > 0)
        {
            randomNum = (rand()%100) + 1;
        }
        evenArr[x] = randomNum;
    }

    for(int x=0;x<MAX;x++)
    {
        int randomNum = (rand()%100) + 1;
        while(randomNum % 2 == 0)
        {
            randomNum = (rand()%100) + 1;
        }
        oddArr[x] = randomNum;
    }
    
    for(int x=0; x < MAX; x++)
    {
        cout << "Random: " << randomArr[x] << endl;
        cout << "Even: " << evenArr[x] << endl;
        cout << "Odd: " << oddArr[x] << endl << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}