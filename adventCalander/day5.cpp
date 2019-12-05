#include "day2.h"

struct OpCodeHandler
{
	vector<int> array;
	int readPos;
};

void day5Part1();
void day5Part2();

int getCurrentOpCode(OpCodeHandler);
OpCodeHandler handleNextOpCode(OpCodeHandler);
OpCodeHandler handleNextOpCodePart2(OpCodeHandler);
vector<int> getVectorFromInput(string input);


int day5Main()
{
	int partNumber;
	cout << "Which part (1 or 2): ";
	cin >> partNumber;

	if (partNumber == 1)
	{
		day5Part1();
	}
	else { //part2
		day5Part2();
	}

	return 1;
}

void day5Part1()
{
	string input;
	string partialString; //used to find each seperate input number so we can place into the array (actually a vector)

	cout << "Input: ";
	cin >> input;
	input = input + ','; //add a comma so the final number is handled correctly.

	OpCodeHandler codes;
	codes.array = getVectorFromInput(input);
	codes.readPos = 0;

	//execute command codes
	int i = 0; //the index
	while (codes.array[i] != 99) //stop when the command is 99.
	{
		codes = handleNextOpCode(codes);
	}
}

vector<int> getVectorFromInput(string input)
{
	vector<int> commandList;

	string partialString; //used to find each seperate input number so we can place into the array (actually a vector)
	for (char c : input)
	{
		if (c == ',')
		{
			commandList.push_back(stoi(partialString));
			partialString = ""; //reset the partialString.
		}
		else
		{
			partialString = partialString + c; //this character is a part of the input number since it is not a comma
		}
	}
	return commandList;
}

//handle the opcode, and increase the index accordingly
OpCodeHandler handleNextOpCode(OpCodeHandler opCodes)
{
	int opCode = getCurrentOpCode(opCodes) % 100; //returns 00-99 number
	int parameterMode1 = (getCurrentOpCode(opCodes) / 100) % 10; //the parameter mode for the first parameter, i.e.  (21402 / 100) % 10 would be 4
	int parameterMode2 = (getCurrentOpCode(opCodes) / 1000) % 10; //the parameter mode for the second parameter, i.e.  (21402 / 1000) % 10 would be 
	int parameterMode3 = (getCurrentOpCode(opCodes) / 10000); //the parameter mode for the third parameter, i.e.  (21402 / 10000) would be 2

	//get the parameter indexes based on what their modes are.
	int parameter1Index; //stores the index of the parameter 1
	if (parameterMode1 == 0) //position mode
	{
		parameter1Index = opCodes.array[opCodes.readPos + 1];
	}
	else { //immediate mode
		parameter1Index = opCodes.readPos + 1;
	}

	int parameter2Index; //stores the index of the parameter 1
	if (parameterMode2 == 0) //position mode
	{
		parameter2Index = opCodes.array[opCodes.readPos + 2];
	}
	else { //immediate mode
		parameter2Index = opCodes.readPos + 2;
	}

	int parameter3Index; //stores the index of the parameter 1
	if (parameterMode3 == 0) //position mode
	{
		parameter3Index = opCodes.array[opCodes.readPos + 3];
	}
	else { //immediate mode
		parameter3Index = opCodes.readPos + 3;
	}


	switch (opCode)
	{
		case 1: //addition opcode
			opCodes.array[parameter3Index] = opCodes.array[parameter1Index] + opCodes.array[parameter2Index];
			opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
			break;

		case 2: //multiplication opCode
			opCodes.array[parameter3Index] = opCodes.array[parameter1Index] * opCodes.array[parameter2Index];
			opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
			break;

		case 3: //get input opcode
			int input;
			cout << "Input requested: ";
			cin >> input;
			opCodes.array[ parameter1Index ] = input;
			opCodes.readPos = opCodes.readPos + 2; //1 for the opCode, 1 for the paramter
			break;

		case 4: //output opcode
			cout << "Code output: " << opCodes.array[ parameter1Index ] << endl; //output the address given
			opCodes.readPos = opCodes.readPos + 2; //1 for the opCode, 1 for the paramter
			break;

		//no case needed for 99, that is handled in the main while loop.
	}

	return opCodes;
}

OpCodeHandler handleNextOpCodePart2(OpCodeHandler opCodes)
{
	int opCode = getCurrentOpCode(opCodes) % 100; //returns 00-99 number
	int parameterMode1 = (getCurrentOpCode(opCodes) / 100) % 10; //the parameter mode for the first parameter, i.e.  (21402 / 100) % 10 would be 4
	int parameterMode2 = (getCurrentOpCode(opCodes) / 1000) % 10; //the parameter mode for the second parameter, i.e.  (21402 / 1000) % 10 would be 
	int parameterMode3 = (getCurrentOpCode(opCodes) / 10000); //the parameter mode for the third parameter, i.e.  (21402 / 10000) would be 2

	//get the parameter indexes based on what their modes are, before getting the index, we have to make sure that we are within the range of the array
	int parameter1Index = 0; //stores the index of the parameter 1
	if (parameterMode1 == 0 && (opCodes.array.size() > opCodes.readPos+1)) //position mode
	{
		parameter1Index = opCodes.array[opCodes.readPos + 1];
	}
	else if((opCodes.array.size() > opCodes.readPos + 1)) { //immediate mode
		parameter1Index = opCodes.readPos + 1;
	}

	int parameter2Index = 0; //stores the index of the parameter 1
	if (parameterMode2 == 0 && (opCodes.array.size() > opCodes.readPos + 2)) //position mode
	{
		parameter2Index = opCodes.array[opCodes.readPos + 2];
	}
	else if ((opCodes.array.size() > opCodes.readPos + 1)) { //immediate mode
		parameter2Index = opCodes.readPos + 2;
	}

	int parameter3Index = 0; //stores the index of the parameter 1
	if (parameterMode3 == 0 && (opCodes.array.size() > opCodes.readPos + 3)) //position mode
	{
		parameter3Index = opCodes.array[opCodes.readPos + 3];
	}
	else if((opCodes.array.size() > opCodes.readPos + 3)) { //immediate mode
		parameter3Index = opCodes.readPos + 3;
	}


	switch (opCode)
	{
	case 1: //addition opcode
		opCodes.array[parameter3Index] = opCodes.array[parameter1Index] + opCodes.array[parameter2Index];
		opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
		break;

	case 2: //multiplication opCode
		opCodes.array[parameter3Index] = opCodes.array[parameter1Index] * opCodes.array[parameter2Index];
		opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
		break;

	case 3: //get input opcode
		int input;
		cout << "Input requested: ";
		cin >> input;
		opCodes.array[parameter1Index] = input;
		opCodes.readPos = opCodes.readPos + 2; //1 for the opCode, 1 for the paramter
		break;

	case 4: //output opcode
		cout << "Code output: " << opCodes.array[parameter1Index] << endl; //output the address given
		opCodes.readPos = opCodes.readPos + 2; //1 for the opCode, 1 for the paramter
		break;

	case 5: //jump if true opcode
		if (opCodes.array[parameter1Index] != 0)
		{
			opCodes.readPos = opCodes.array[parameter2Index];
		}
		else { //proceed without jumping
			opCodes.readPos = opCodes.readPos + 3; //1 for the opCode, 2 for the paramters
		}
		break;

	case 6: //jump if false opcode
		if (opCodes.array[parameter1Index] == 0)
		{
			opCodes.readPos = opCodes.array[parameter2Index];
		}
		else { //proceed without jumping
			opCodes.readPos = opCodes.readPos + 3; //1 for the opCode, 2 for the paramters
		}
		break;

	case 7: //less than opcode
		opCodes.array[parameter3Index] = (opCodes.array[parameter1Index] < opCodes.array[parameter2Index]); //store 1 if less than, 0 if not
		opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
		break;

	case 8: //equal to opcode
		opCodes.array[parameter3Index] = (opCodes.array[parameter1Index] == opCodes.array[parameter2Index]); //store 1 if less than, 0 if not
		opCodes.readPos = opCodes.readPos + 4; //1 for the opCode, 3 for the paramters
		break;

		//no case needed for 99, that is handled in the main while loop.
	}

	return opCodes;
}

//read the current position of the opCode, and return whatever is stored there.
int getCurrentOpCode(OpCodeHandler codes)
{
	return codes.array[codes.readPos];
}

void day5Part2()
{
	string input;
	string partialString; //used to find each seperate input number so we can place into the array (actually a vector)

	cout << "Input: ";
	cin >> input;
	input = input + ','; //add a comma so the final number is handled correctly.

	OpCodeHandler codes;
	codes.array = getVectorFromInput(input);
	codes.readPos = 0;

	//execute command codes
	int i = 0; //the index
	while (codes.array[i] != 99) //stop when the command is 99.
	{
		codes = handleNextOpCodePart2(codes);
	}
}