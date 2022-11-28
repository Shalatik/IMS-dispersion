#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <cmath>

using namespace std;

// int sigmaZ(int distance)
// {
//   map<int, int> mapD = {
//       {5, 0.1},
//       {8, 0.2},
//       {15, 0.4},
//       {24, 0.7},
//       {32, 1},
//       {50, 2},
//       {77, 4},
//       {109, 7},
//       {135, 10},
//       {205, 20}};
//   for (auto it = mapD.begin(); it != mapD.end(); ++it)
//     if (it->second == distance)
//       return it->first;
//   return 1; //FIXME:
// }

// emise za jeden usek cesty
double emissionCalculate(int experiment)
{
  // mg/km
  double electro = 90.975;
  double gas = 89.2;
  double diesel = 87.9;

  double result;
  // average emissions
  // mg/km
  switch (experiment)
  {
  case 'S':
    result = (0.525 * diesel + 0.444 * gas + 0.031 * electro) * 0.1;
    break;
  case 'E':
    result = (0.44 * diesel + 0.36 * gas + 0.2 * electro) * 0.1;
    break;
  case 'W':
    result = (0.525 * diesel + 0.444 * gas + 0.031 * electro - 5.6) * 0.1;
    break;

  default:
    break;
  }

  int cars_per_hour = 8000; // 35000
  // int average_speed = 80; // / 3.6; // m/s
  // g/m
  double q = cars_per_hour * result;
  return q;
}

// mg/m^3
double concentration(int q)
{
  // m
  int sigma_z = 5; // 15 ... 0.4

  int windSpeed = 4; // m/s
  // * windSpeed
  double c = (2 * q) / (sqrt(M_PI * 2) * sigma_z); //*windSpeed
  return c;
}

// |1|     50
// |*|
// |*|
// |*|
// |*|
// |*|
// |*|

int main()
{
  // Number of rows and columns
  const int cols = 51;

  double expStandartParticulate[cols];
  double expElectroParticulate[cols];
  double expWeightParticulate[cols];

  double expStandartCO2[cols];
  double expElectroCO2[cols];
  double expWeightCO2[cols];

  double emissionsSCO2 = emissionCalculate('S');
  double emissionsECO2 = emissionCalculate('E');
  double emissionsWCO2 = emissionCalculate('W');

  // i rows
  for (int t = 0; t < 24; t++)
  {
    for (int j = 0; j < cols; j++)
    {
      // int x = std::abs((int)(j - 50));
      if (j != 0)
      {
        expStandartParticulate[j] = expStandartParticulate[j] + concentration(expStandartParticulate[j - 1]); // mg/m^3
        expElectroParticulate[j] = expElectroParticulate[j] + concentration(expElectroParticulate[j - 1]); // mg/m^3
        expWeightParticulate[j] = expWeightParticulate[j] + concentration(expWeightParticulate[j - 1]);    // mg/m^3
      
        expStandartCO2[j] = expStandartParticulate[j] + concentration(expStandartCO2[j - 1]); // mg/m^3
        expElectroCO2[j] = expElectroParticulate[j] + concentration(expElectroCO2[j - 1]); // mg/m^3
        expWeightCO2[j] = expWeightParticulate[j] + concentration(expWeightCO2[j - 1]);    // mg/m^3
      
      }
      else
      {
        expStandartParticulate[j] = expStandartParticulate[j] + concentration(emissionsSParticular);
        expElectroParticulate[j] = expElectroParticulate[j] + concentration(emissionsEParticular);
        expWeightParticulate[j] = expWeightParticulate[j] + concentration(emissionsWParticular);
      
        expStandartCO2[j] = expStandartParticulate[j] + concentration(emissionsSParticular);
        expElectroCO2[j] = expElectroParticulate[j] + concentration(emissionsEParticular);
        expWeightCO2[j] = expWeightParticulate[j] + concentration(emissionsWParticular);
      }
    }
  }

  // i collumns

  return 0;
}