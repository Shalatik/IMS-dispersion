#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <cmath>

using namespace std;

int sigmaZ(int distance){
  map<int, int> mapD = {
      {5, 0.1},
      {8, 0.2},
      {15, 0.4},
      {24, 0.7},
      {32, 1},
      {50, 2},
      {77, 4},
      {109, 7},
      {135, 10},
      {205, 20}
  };
}

int emissionCalculate()
{
  // mg/km
  int electro = 90.975;
  int gas = 89.2;
  int diesel = 87.9;

  //average emissions
  int result = 0.525*diesel + 0.444*gas + 0.031*electro;
  return result;
}


int concentration(int distance)
{
  int cars_per_hour = 35000;
  int average_speed = 80/3.6; // m/s
  int emissions = emissionCalculate();
  int q = cars_per_hour/average_speed*emissions;
  
  int sigma_z = sigmaZ(distance); 
  int c = (2*q)/(sqrt(M_PI*2)*sigma_z); //*u
}


//    50      |1|       50
//            |*|
//            |*|
//            |*|
//            |*|
//            |*|
//            |*|

int main()
{
  // Number of rows and columns
  // const char particle = '*';
  // const char clean = ' ';
  const int rows = 50;
  const int cols = 101;
  char space[rows][cols];
  

  // i rows
  for(int i = 0; i < rows; i++){
    for(int j = 20; j < cols; j++){
      int x = std::abs((int)(j-50));
      // cout << x;
      exit(0);
      space[i][j] = concentration(x);
    }
  }  

  // i collumns

  return 0;
}