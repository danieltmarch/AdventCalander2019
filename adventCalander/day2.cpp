#include "day2.h"

void part1();
void part2();

int day2Main()
{
	int partNumber;
	cout << "Which part (1 or 2): ";
	cin >> partNumber;
	
	if (partNumber == 1)
	{
		part1();
	}
	else { //part2
		part2();
	}

	return 1;
}

void part1()
{
	string input;
	string partialString; //used to find each seperate input number so we can place into the array (actually a vector)
	vector<int> inputCommands;

	cin >> input;
	input = input + ','; //add a comma so the final number is handled correctly.
	//string to the vector array
	int count = 0;
	for (char c : input)
	{
		if (c == ',')
		{
			inputCommands.push_back(stoi(partialString));
			partialString = ""; //reset the partialString.
		}
		else
		{
			partialString = partialString + c; //this character is a part of the input number since it is not a comma
		}
	}
	//end string to the vector array

	//fix the 'mistakes' of the input
	inputCommands[1] = 12;
	inputCommands[2] = 2;

	//execute command codes
	for (int i = 0; i < inputCommands.size(); i = i + 4)
	{
		if (inputCommands[i] == 1) //addition code
		{
			inputCommands[(inputCommands[i + 3])] = inputCommands[(inputCommands[i + 1])] + inputCommands[(inputCommands[i + 2])];
		}
		if (inputCommands[i] == 2) //multiplication code
		{
			inputCommands[(inputCommands[i + 3])] = inputCommands[(inputCommands[i + 1])] * inputCommands[(inputCommands[i + 2])];
		}
		if (inputCommands[i] == 99) //end command execution code
		{
			break; //99 is the break command, stop here
		}
	}

	cout << endl << endl << "Answer: " << endl; //formatting

	//print out the resulting array after the commands are executed.
	for (int n : inputCommands)
	{
		cout << n << ',';
	}
	cout << '\b'; //erase comma
}

void part2()
{

}