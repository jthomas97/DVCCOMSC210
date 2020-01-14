#include "SortableBag.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;



int main()
{
  srand(time(0)) ;

	SortableBag<int> bag ; 

	for(int i=0;i<100;i++) 
	{
		int k=1+(rand()%100) ;
		bag.add(k) ;
	}

	bag.sortBag() ; 

	vector<int> bagItems=bag.toVector() ; 

	int i=0 ;

	for(i=0;i<bagItems.size()-1;i++) 
	{
		if(!(bagItems[i]<=bagItems[i+1]))
		{
			cout << "Bag is not sorted. Sorting Failed." << endl ;
			break ;
		}

		// cout << bagItems[i] << " " << endl ;
	}

	if(i==bagItems.size()-1)
	{
		cout << "Bag is sorted. Sorting succeeded." << endl ;
	}
  return 0;
}