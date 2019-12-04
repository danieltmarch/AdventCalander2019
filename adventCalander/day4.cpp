#include "day4.h"

void day4Part1();
bool isAscending(int n);
bool hasTwinNumber(int n);

void day4Part2();
bool hasOnlyTwinNumber(int n);

int day4Main()
{
	int partNumber;
	cout << "Which part (1 or 2): ";
	cin >> partNumber;

	if (partNumber == 1)
	{
		day4Part1();
	}
	else { //part2
		day4Part2();
	}

	return 1;
}

void day4Part1()
{
	int startRange, endRange;
	cout << "Range (seperate with a -): ";
	cin >> startRange;
	cin >> endRange;
	endRange = endRange * -1; //the - seperator makes the program think the endRange is negative.

	cout << endl; //for spacing

	int optionCount = 0;
	for (int numOption = startRange; numOption <= endRange; numOption++) //check each option.
	{
		if (isAscending(numOption) && hasTwinNumber(numOption))
		{
			//cout << numOption << endl; //for debugging
			optionCount++;
		}
	}
	cout << endl; //for spacing
	cout << optionCount;
}

//is the number in ascending order? (i.e. 111123 would be)
bool isAscending(int n)
{
	//convert int to array
	int numArray[6];
	numArray[0] = n / 100000;
	n = n % 100000; //remove the first digit from n
	numArray[1] = n / 10000;
	n = n % 10000; //remove the second digit from n
	numArray[2] = n / 1000;
	n = n % 1000; //remove the third digit from n
	numArray[3] = n / 100;
	n = n % 100; //remove the fourth digit from n
	numArray[4] = n / 10;
	n = n % 10; //remove the fifth digit from n
	numArray[5] = n;

	for (int index = 0; index < 5; index++)
	{
		if (numArray[index] > numArray[index + 1]) //is the current number greater than the next, if so the test fails?
		{
			return false;
		}
	}
	return true; //we found that all numbers are not greater than the next
}

//is there a pair of neighbouring digits that are the same?
bool hasTwinNumber(int n)
{
	//convert int to array
	int numArray[6];
	numArray[0] = n / 100000;
	n = n % 100000; //remove the first digit from n
	numArray[1] = n / 10000;
	n = n % 10000; //remove the second digit from n
	numArray[2] = n / 1000;
	n = n % 1000; //remove the third digit from n
	numArray[3] = n / 100;
	n = n % 100; //remove the fourth digit from n
	numArray[4] = n / 10;
	n = n % 10; //remove the fifth digit from n
	numArray[5] = n;

	for (int index = 0; index < 5; index++)
	{
		if (numArray[index] == numArray[index + 1]) //is the current number equal to the next?
		{
			return true;
		}
	}
	return false; //we didn't find a twin number, return false.
}


//almost the same as part 1, just a different twinNumberFunction
void day4Part2()
{
	int startRange, endRange;
	cout << "Range (seperate with a -): ";
	cin >> startRange;
	cin >> endRange;
	endRange = endRange * -1; //the - seperator makes the program think the endRange is negative.

	cout << endl; //for spacing

	int optionCount = 0;
	for (int numOption = startRange; numOption <= endRange; numOption++) //check each option.
	{
		if (isAscending(numOption) && hasOnlyTwinNumber(numOption))
		{
			//cout << numOption << endl; //for debugging
			optionCount++;
		}
	}
	cout << endl; //for spacing
	cout << optionCount;
}

//if the function has a twin number (and that twin is not a triplet or more) then return true;
bool hasOnlyTwinNumber(int n)
{
	//convert int to array
	int numArray[6];
	numArray[0] = n / 100000;
	n = n % 100000; //remove the first digit from n
	numArray[1] = n / 10000;
	n = n % 10000; //remove the second digit from n
	numArray[2] = n / 1000;
	n = n % 1000; //remove the third digit from n
	numArray[3] = n / 100;
	n = n % 100; //remove the fourth digit from n
	numArray[4] = n / 10;
	n = n % 10; //remove the fifth digit from n
	numArray[5] = n;

	for (int index = 0; index < 5; index++)
	{
		if (numArray[index] == numArray[index + 1]) //is the current number equal to the next?
		{
			//make sure that the neighbouring numbers are not the same, check that the index is too close to the bounds
			if ((numArray[index - 1] != numArray[index]) && (numArray[index + 2] != numArray[index]) && index != 0 && index != 5)
			{
				return true;
			}
			else if (index == 0 && (numArray[index + 2] != numArray[index]) ) //beginning of array case
			{
				return true;
			}
			else if (index == 5 && (numArray[index - 1] != numArray[index])) //end of array case
			{
				return true;
			}
		}
	}
	return false; //we didn't find a twin number, return false.
}