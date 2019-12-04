#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"

using namespace std;

int main()
{
	int day;
	cout << "Which day are we doing: ";
	cin >> day;
	switch(day)
	{
		case 1:
			cout << "Day 1:" << endl << endl;
			day1Main();
		case 2:
			cout << "Day 2:" << endl << endl;
			day2Main();
		case 3:
			cout << "Day 3:" << endl << endl;
			day3Main();
	}
}