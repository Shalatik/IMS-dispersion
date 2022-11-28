#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <cmath>
#include <unistd.h>
#include <string.h>
using namespace std;

// emise za jeden usek cesty
double emissionCalculate(int experiment)
{
  // mg/km
  double electroP = 90.975;
  double gasP = 89.2;
  double dieselP = 87.9;

  double electroCO2 = 0;
  double gasCO2 = 1000;
  double dieselCO2 = 500;

  double coeficient = 3.53; 

  double result;
  // average emissions
  // mg/km
  switch (experiment)
  {
  case 1:
    result = (0.525 * dieselP + 0.444 * gasP + 0.031 * electroP) * 0.1;
    break;
  case 2:
    result = (0.44 * dieselP + 0.36 * gasP + 0.2 * electroP) * 0.1;
    break;
  case 3:
    result = (0.525 * dieselP + 0.444 * gasP + 0.031 * electroP - 5.6) * 0.1;
    break;
  case 4:
    result = (0.525 * dieselCO2 + 0.444 * gasCO2 + 0.031 * electroCO2) * 0.1;
    break;
  case 5:
    result = (0.44 * dieselCO2 + 0.36 * gasCO2 + 0.2 * electroCO2) * 0.1;
    break;
  case 6:
    result = (0.525 * dieselCO2 + 0.444 * gasCO2 + 0.031 * electroCO2 - 5.6) * 0.1;
    break;
  case 7:
    result = (0.525 * (dieselCO2 + dieselP*coeficient) + 0.444 * (gasCO2 + gasP*coeficient) + 0.031 * (electroCO2 + electroP*coeficient)) * 0.1;
    break;
  case 8:
    result = (0.44 * (dieselCO2 + dieselP*coeficient) + 0.36 * (gasCO2 + gasP*coeficient) + 0.2 * (electroCO2 + electroP*coeficient)) * 0.1;
    break;
  case 9:
    result = (0.525 * (dieselCO2 + dieselP*coeficient) + 0.444 * (gasCO2 + gasP*coeficient) + 0.031 * (electroCO2 + electroP*coeficient) - 5.6) * 0.1;
    break;
  default:
    break;
  }

  int carsPerHour = 8000; // 35000
  // int average_speed = 80; // / 3.6; // m/s
  // g/m
  double q = carsPerHour * result;
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


  double expStandartP[cols];
  //std::fill(expStandartP, expStandartP + sizeof(expStandartP), 0 );
  double expElectroP[cols];
  double expWeightP[cols];

  double expStandartCO2[cols];
  double expElectroCO2[cols];
  double expWeightCO2[cols];

  double expStandartAll[cols];
  double expElectroAll[cols];
  double expWeightAll[cols];

  double emissionsSP = emissionCalculate(1);
  double emissionsEP = emissionCalculate(2);
  double emissionsWP = emissionCalculate(3);

  double emissionsSCO2 = emissionCalculate(4);
  double emissionsECO2 = emissionCalculate(5);
  double emissionsWCO2 = emissionCalculate(6);

  double emissionsSAll = emissionCalculate(7);
  double emissionsEAll = emissionCalculate(8);
  double emissionsWAll = emissionCalculate(9);

  for (int t = 0; t < 24; t++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (j != 0)
      {
        expStandartP[j] = expStandartP[j] + concentration(expStandartP[j - 1]); // mg/m^3
        expElectroP[j] = expElectroP[j] + concentration(expElectroP[j - 1]);    // mg/m^3
        expWeightP[j] = expWeightP[j] + concentration(expWeightP[j - 1]);       // mg/m^3

        expStandartCO2[j] = expStandartCO2[j] + concentration(expStandartCO2[j - 1]); // mg/m^3
        expElectroCO2[j] = expElectroCO2[j] + concentration(expElectroCO2[j - 1]);    // mg/m^3
        expWeightCO2[j] = expWeightCO2[j] + concentration(expWeightCO2[j - 1]);       // mg/m^3
     
        expStandartAll[j] = expStandartAll[j] + concentration(expStandartAll[j - 1]); // mg/m^3
        expElectroAll[j] = expElectroAll[j] + concentration(expElectroAll[j - 1]);    // mg/m^3
        expWeightAll[j] = expWeightAll[j] + concentration(expWeightAll[j - 1]);       // mg/m^3
      }
      else
      {
        expStandartP[j] = expStandartP[j] + concentration(emissionsSP);
        expElectroP[j] = expElectroP[j] + concentration(emissionsEP);
        expWeightP[j] = expWeightP[j] + concentration(emissionsWP);

        expStandartCO2[j] = expStandartCO2[j] + concentration(emissionsSCO2);
        expElectroCO2[j] = expElectroCO2[j] + concentration(emissionsECO2);
        expWeightCO2[j] = expWeightCO2[j] + concentration(emissionsWCO2);
      
        expStandartAll[j] = expStandartAll[j] + concentration(emissionsSAll);
        expElectroAll[j] = expElectroAll[j] + concentration(emissionsEAll);
        expWeightAll[j] = expWeightAll[j] + concentration(emissionsWAll);
      }
      cout<<("aaaaaaa\n");
    }
  }

  for(int i = 0; i < cols; i++){
    cout<<expStandartP[i];
    cout<<("\n");
  }

  return 0;
}