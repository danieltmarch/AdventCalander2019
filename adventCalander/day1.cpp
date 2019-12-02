// adventCalander.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "day1.h"

int handleMass(int mass, int sum);

int day1Main()
{
	int mass = 1; //mass of the rocket
	int fuelTotal = 0;
	while (mass != 0)
	{
		cout << "mass: ";
		cin >> mass; // get input
		fuelTotal = handleMass(mass, fuelTotal);
		cout << " Fuel Total: " << fuelTotal << endl;
	}
	return 1;
}

//adds mass of a module and subsequent fuel mass until fuel mass is 0 or less.
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
