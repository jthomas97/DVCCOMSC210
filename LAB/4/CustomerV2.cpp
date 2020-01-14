#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

#include <cstdlib>
#include <ctime>

using namespace std;

bool randomChance(double);
int randomInt(int, int);

struct Customer{
  int waitTime;
//Default Constructor
  Customer(){
    waitTime = 0;
  }
};

int main()
{
  srand(time(0));
  ifstream infile("simulation.txt");

//Given Inputs
  int SimulationTime, MinServiceTime, MaxServiceTime, MaxLineSize, IrateCustomerThreshold;
  double ArrivalRate;

//Vars for keeping Track
  int customersLeft = 0;
  int timeRemaining = 0;
  int irateCustomer = 0;
  int numCustomers = 0;
  float avgCustomerLine = 0.0;
  float avgWait = 0.0;

//Two data Structures
  deque<size_t> queue;
  vector<Customer> customers;

//Read File
  infile >> SimulationTime;
  infile >> ArrivalRate;
  infile >> MinServiceTime;
  infile >> MaxServiceTime;
  infile >> MaxLineSize;
  infile >> IrateCustomerThreshold;

//Main Loop for each Simulation
  for(int x = 0; x < SimulationTime; x++)
  {
//If Customer Determine if they stay
//If so add them to queue and initialize wait time
    if(randomChance(ArrivalRate))
    {
      if(queue.size() >= MaxLineSize)
        customersLeft++;
      else
      {
        Customer temp;
        customers.push_back(temp);
        queue.push_back(customers.size()-1);
        numCustomers++;
      }
    }

//Check on Checkout Line
    if(timeRemaining <= 0 && !queue.empty())
    {
      queue.pop_front();
      timeRemaining = randomInt(MinServiceTime, MaxServiceTime);
    }
    else
    {
      timeRemaining--;
    }

//Increment Wait time for everyone(Remeber its reveresed for vector)
    for(int i = 0; i < queue.size(); i++)
    {
      customers[i].waitTime++;
    }

    avgCustomerLine += queue.size();
  }

  for(int j = 0; j < customers.size(); j++)
  {
    if(customers[j].waitTime >= IrateCustomerThreshold)
      irateCustomer++;
    avgWait += customers[j].waitTime;
  }
  avgWait = avgWait / numCustomers;
  avgCustomerLine = avgCustomerLine / SimulationTime;

  infile.close();
  
// All Output
  cout<<"Simulation Results\n";
  cout<<"------------------"<<endl;
  cout<<"Overall simulation time:\t"<<SimulationTime<<endl;
  cout<<"Arrival rate:\t"<<ArrivalRate<<endl;
  cout<<"Minimum service time:\t"<<MinServiceTime<<endl;
  cout<<"Maximum service time:\t"<<MaxServiceTime<<endl;
  cout<<"Maximum line size:\t"<<MaxLineSize<<endl;
  cout<<endl;
  cout<<"Customers serviced:\t\t"<< numCustomers<<endl;
  cout<<"Customers leaving:\t\t"<<customersLeft<<endl;
  cout<<"Average time spent in line:\t"<<avgWait<<endl;
  cout<<"Average line length:\t\t"<<avgCustomerLine<<endl;
  cout<<"Irate customers:\t\t"<<irateCustomer<<endl;
  cout<<"------------------"<<endl<<endl;

  return 0;
}

bool randomChance(double prob) {
	double rv = rand() / (double(RAND_MAX) + 1);
	return (rv < prob);
}

int randomInt(int min, int max) {
	return (rand() % (max - min) + min);
}