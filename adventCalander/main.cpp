#include <iostream>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
//#include "day6.h"
//#include "day7.h"
//#include "day8.h"
//#include "day9.h"
//#include "day10.h"
//#include "day11.h"
//#include "day12.h"
//#include "day13.h"

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
			break;
		case 2:
			cout << "Day 2:" << endl << endl;
			day2Main();
			break;
		case 3:
			cout << "Day 3:" << endl << endl;
			day3Main();
			break;
		case 4:
			cout << "Day 4:" << endl << endl;
			day4Main();
			break;
		case 5:
			cout << "Day 5:" << endl << endl;
			day5Main();
			break;
		/*
		case 6:
			cout << "Day 5:" << endl << endl;
			day6Main();
			break;
		case 7:
			cout << "Day 5:" << endl << endl;
			day7Main();
			break;
		case 8:
			cout << "Day 5:" << endl << endl;
			day8Main();
			break;
		case 9:
			cout << "Day 5:" << endl << endl;
			day9Main();
			break;
		*/
	}
}