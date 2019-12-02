// adventCalander.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int handleMass(int, int	);

int main()
{
	int mass = 1; //mass of the rocket
	int fuelTotal = 0;
	while (mass != 0)
	{
		cout << "mass: ";
		cin >> mass;
		fuelTotal = handleMass(mass, fuelTotal);
		cout << " Fuel Total: " << fuelTotal << endl;
	}
}

int handleMass(int mass, int sum)
{
	int fuel = (mass / 3) - 2;
	if (fuel < 0)
	{
		return sum;
	}
	else 
	{
		sum = sum + fuel;
		sum = handleMass(fuel, sum);
	}
}
