#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

void parse_line(const string &, vector<string>&);

int main()
{
  ifstream infile("customers.csv");

  string line;
  vector<vector<string>> contents;
  map<string, string> data;

  while(getline(infile, line))
  {
    vector<string> row;
    parse_line(line, row);
    contents.push_back(row);
  }

  bool first = true;
  for(const auto &item:contents)
  {
    if(first)
    {
      first = false;
      continue;
    }
    data.insert(make_pair(item[0], item[18]));
  }

  string lowerBound, upperBound;

  cout << "Enter the lower and upper values of the range (X to quit): \n";
  cin >> lowerBound;
  cin >> upperBound;

  do
  {

    map<string, string>::iterator item, low, high;
    low = data.lower_bound(lowerBound);
    high = data.upper_bound(upperBound);

    cout << setprecision(2) << fixed;
    cout << "The customers in this range are:\n";
    for(item = low; item != high; ++item)
    {
      cout << "\t" << item->first << ": $" << item->second << "\n";
    }
    
    cout << "Enter the lower and upper values of the range (X to quit): \n";
    cin >> lowerBound;
    cin >> upperBound;
    
  } while((lowerBound !=  "X" && lowerBound != "x") || (upperBound !=  "x" && upperBound != "X"));
  //} while((lowerBound !=  "X" || upperBound != "X") && (lowerBound !=  "x" || upperBound != "x"));
  

  infile.close();
  return 0;
}

void parse_line(const string &str, vector<string> &row)
{
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ','))
    {
        row.push_back(tmp);
    }
}