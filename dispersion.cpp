#include <iostream>
#include <cstdlib>
#include <time.h>
#include <map>
#include <cmath>
#include <unistd.h>
#include <string.h>
using namespace std;

// emissions from one section of road
double emissionCalculate(int experiment)
{
  // mg/km
  double electroP = 90.975;
  double gasP = 89.2;
  double dieselP = 87.9;

  double electroNOx = 0;
  double gasNOx = 60;
  double dieselNOx = 100;

  double coeficient = 5.04; 
  double weightReduction = 0.86;

  double result;
  // average emissions per 0,1 km long section of road  ... [mg]
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
  // *********************************************************************************
  case 4:
    result = (0.525 * dieselNOx + 0.444 * gasNOx + 0.031 * electroNOx) * 0.1;
    break;
  case 5:
    result = (0.44 * dieselNOx + 0.36 * gasNOx + 0.2 * electroNOx) * 0.1;
    break;
  case 6:
    result = (0.525 * dieselNOx + 0.444 * gasNOx + 0.031 * electroNOx) * weightReduction * 0.1;
    break;
  // *********************************************************************************
  case 7:
    result = (0.525 * (dieselNOx + dieselP*coeficient) + 0.444 * (gasNOx + gasP*coeficient) + 0.031 * (electroNOx + electroP*coeficient)) * 0.1;
    break;
  case 8:
    result = (0.44 * (dieselNOx + dieselP*coeficient) + 0.36 * (gasNOx + gasP*coeficient) + 0.2 * (electroNOx + electroP*coeficient)) * 0.1;
    break;
  case 9:
    result = (0.525 * (dieselNOx * weightReduction  + dieselP*coeficient) + 0.444 * (gasNOx * weightReduction  + gasP*coeficient) + 0.031 * (electroNOx * weightReduction  + electroP*coeficient) - 5.6) * 0.1;
    break;
  }

  int carsPerHour = 2290;
  double q = carsPerHour * result;
  return q;
}

// mg/m^3
double concentration(int q)
{
  int sigma_z = 5; // 15 ... 0.4
  int windSpeed = 4; // m/s

  double c = (2 * q) / (sqrt(M_PI * 2) * sigma_z * windSpeed);
  return c;
}

int main()
{

  // Number of rows and columns
  const int cols = 10;

  double expStandartP[cols];
  double expElectroP[cols];
  double expWeightP[cols];

  double expStandartNOx[cols];
  double expElectroNOx[cols];
  double expWeightNOx[cols];

  double expStandartAll[cols];
  double expElectroAll[cols];
  double expWeightAll[cols];


 for(int n =0; n<cols; n++){
    expStandartP[n] = 0;
    expElectroP[n] = 0;
    expWeightP[n] = 0;
    expStandartNOx[n] = 0;
    expElectroNOx[n] = 0;
    expWeightNOx[n] = 0;
    expStandartAll[n] = 0;
    expElectroAll[n] = 0;
    expWeightAll[n] = 0;
  }

  double emissionsSP = emissionCalculate(1);
  double emissionsEP = emissionCalculate(2);
  double emissionsWP = emissionCalculate(3);

  double emissionsSNOx = emissionCalculate(4);
  double emissionsENOx = emissionCalculate(5);
  double emissionsWNOx = emissionCalculate(6);

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

        expStandartNOx[j] = expStandartNOx[j] + concentration(expStandartNOx[j - 1]); // mg/m^3
        expElectroNOx[j] = expElectroNOx[j] + concentration(expElectroNOx[j - 1]);    // mg/m^3
        expWeightNOx[j] = expWeightNOx[j] + concentration(expWeightNOx[j - 1]);       // mg/m^3
     
        expStandartAll[j] = expStandartAll[j] + concentration(expStandartAll[j - 1]); // mg/m^3
        expElectroAll[j] = expElectroAll[j] + concentration(expElectroAll[j - 1]);    // mg/m^3
        expWeightAll[j] = expWeightAll[j] + concentration(expWeightAll[j - 1]);       // mg/m^3
      }
      else
      {
        expStandartP[j] = expStandartP[j] + concentration(emissionsSP);
        expElectroP[j] = expElectroP[j] + concentration(emissionsEP);
        expWeightP[j] = expWeightP[j] + concentration(emissionsWP);

        expStandartNOx[j] = expStandartNOx[j] + concentration(emissionsSNOx);
        expElectroNOx[j] = expElectroNOx[j] + concentration(emissionsENOx);
        expWeightNOx[j] = expWeightNOx[j] + concentration(emissionsWNOx);
      
        expStandartAll[j] = expStandartAll[j] + concentration(emissionsSAll);
        expElectroAll[j] = expElectroAll[j] + concentration(emissionsEAll);
        expWeightAll[j] = expWeightAll[j] + concentration(emissionsWAll);
      }
    }
  }

  //Print results
  printf("V rámci referenčního scénáře bylo dosaženo maximálních hodnot (mg/100m3): \n");
  printf("Koncentrace pevných částic:\t\t %.2f \n", expStandartP[0]);
  printf("Koncentrace dusičnanů:\t\t\t %.2f \n", expStandartNOx[0]);
  printf("Vážená koncentrace kombinovaných emisí:\t %.2f \n", expStandartAll[0]);

  printf("\n\nZvýšením zastoupení elektromobilů na 0.2 vozového parku bylo dosaženo maximálních hodnot (mg/100m3): \n");
  printf("Koncentrace pevných částic:\t\t %.2f \n", expElectroP[0]);
  printf("Koncentrace dusičnanů:\t\t\t %.2f \n", expElectroNOx[0]);
  printf("Vážená koncentrace kombinovaných emisí:\t %.2f \n", expElectroAll[0]);
  printf("\nProti referenčnímu scénáři se jedná o %.3f násobek množství pevných částic, %.2f množství dusičnanů a %.2f množství vážených kombinovaých emisí.\n", expElectroP[0]/expStandartP[0], expElectroNOx[0]/expStandartNOx[0], expElectroAll[0]/expStandartAll[0]);

  printf("\n\nSnížením průměrné hmotnosti vozidla o 280kg bylo dosaženo maximálních hodnot (mg/100m3): \n");
  printf("Koncentrace pevných částic:\t\t %.2f \n", expWeightP[0]);
  printf("Koncentrace dusičnanů:\t\t\t %.2f \n", expWeightNOx[0]);
  printf("Vážená koncentrace kombinovaných emisí:\t %.2f \n", expWeightAll[0]);
  printf("\nProti referenčnímu scénáři se jedná o %.3f násobek množství pevných částic, %.2f množství dusičnanů a %.2f množství vážených kombinovaých emisí.\n", expWeightP[0]/expStandartP[0], expWeightNOx[0]/expStandartNOx[0], expWeightAll[0]/expStandartAll[0]);
  
  return 0;
}