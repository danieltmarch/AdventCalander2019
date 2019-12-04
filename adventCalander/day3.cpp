#include "day3.h"

void day3Part1();
vector<int> getNextCoordinate(char direction, int distance, vector<int> previousCoord);
bool doCoordsConflict(vector<int>, vector<int>, vector<int>, vector<int>);
vector<int> getConflictCoord(vector<int> coord1begin, vector<int> coord1end, vector<int> coord2begin, vector<int> coord2end);

void day3Part2();
vector<int> getNextCoordinateWithSteps(char direction, int distance, vector<int> previousCoord);

int day3Main()
{
	int partNumber;
	cout << "Which part (1 or 2): ";
	cin >> partNumber;

	if (partNumber == 1)
	{
		day3Part1();
	}
	else { //part2
		day3Part2();
	}

	return 1;
}

void day3Part1()
{
	//get inputs
	string wire1Input;
	string wire2Input;
	cout << "Wire 1 input: ";
	cin >> wire1Input;
	cout << "Wire 2 input: ";
	cin >> wire2Input;
	wire1Input = wire1Input + ','; //add a comma to both input strings so we handle them correctly when we convert the string to the 2d array
	wire2Input = wire2Input + ',';

	//count how many total 'corners' there are for wire 1, u202,l500,d20 would have 4 total places
	int wire1Length = 1; //1 for initial 0,0 location
	for (char c : wire1Input)
	{
		if (c == ',')
		{
			wire1Length = wire1Length + 1;
		}
	}
	//count how many total 'corners' there are for wire 1, u202,l500,d20 would have 4 total places
	int wire2Length = 1; //1 for initial 0,0 location
	for (char c : wire2Input)
	{
		if (c == ',')
		{
			wire2Length = wire2Length + 1;
		}
	}

	vector< vector<int> > wire1(wire1Length, vector<int>(2, 0)); //make an 'array' (actually a vector) that is 2d, the first dimension is an array of an array of coordinates, the 2nd dimension is an x,y coord array
	vector< vector<int> > wire2(wire2Length, vector<int>(2, 0));

	//set the wire 1
	char direction;
	int distance;
	int index = 1; //index 0 is already set to {0,0}
	string turnInterpreter = ""; //a partial string used to find out how the string translates to wire moves.
	for (char c : wire1Input)
	{
		if (c == 'L' || c == 'R' || c == 'D' || c == 'U') //we must have just finished a turn command last iteration, so c must be our direction character.
		{
			direction = c;
		}
		else if (c != ',') //if c is not a direction character (proved by above if) and not a comma it must relate to the distance
		{
			turnInterpreter = turnInterpreter + c;
		}
		else
		{
			//we have finished reading this turn command, track the coordinate and move on.
			distance = stoi(turnInterpreter);
			wire1[index] = getNextCoordinate(direction, distance, wire1[index-1]);
			index++; //move to the next index

			turnInterpreter = ""; //reset the partial string, as a comma indicates that we just finished one turn command
		}
	}
	//set the wire 2
	index = 1; //index 0 is already set to {0,0}, reset to 1 again
	for (char c : wire2Input)
	{
		if (c == 'L' || c == 'R' || c == 'D' || c == 'U') //we must have just finished a turn command last iteration, so c must be our direction character.
		{
			direction = c;
		}
		else if (c != ',') //if c is not a direction character (proved by above if) and not a comma it must relate to the distance
		{
			turnInterpreter = turnInterpreter + c;
		}
		else
		{
			//we have finished reading this turn command, track the coordinate and move on.
			distance = stoi(turnInterpreter);
			wire2[index] = getNextCoordinate(direction, distance, wire2[index - 1]);
			index++; //move to the next index

			turnInterpreter = ""; //reset the partial string, as a comma indicates that we just finished one turn command
		}
	}

	//the arrays are set, now we need to find out if they conflict
	int minDistance = 0;
	distance = 0; //represents manhatten distance of a wire crossing
	for (int index1 = 1; index1 < wire1Length; index1++)
	{
		for (int index2 = 1; index2 < wire2Length; index2++)
		{
			if (doCoordsConflict(wire1[index1 - 1], wire1[index1], wire2[index2 - 1], wire2[index2]))
			{
				vector<int> crossCoord = getConflictCoord( wire1[index1 - 1], wire1[index1], wire2[index2 - 1], wire2[index2] );
				distance = abs(crossCoord[0]) + abs(crossCoord[1]);
				if ( (distance != 0 && distance < minDistance) || minDistance == 0)
				{
					minDistance = distance;
				}
			}
		}
	}
	cout << minDistance << endl;
}

//based off of the input info, get the next coordinate, and return it.
vector<int> getNextCoordinate(char direction, int distance, vector<int> previousCoord)
{
	vector<int> coord(2); //a vector of size 2, structured like {xCoord, yCoord}
	if (direction == 'L') //left
	{
		coord[0] = previousCoord[0] - distance; //left moves our x coord to the left (negative direction)
		coord[1] = previousCoord[1]; //we move left, so the y coord does not change.

	}
	else if (direction == 'R') //right
	{
		coord[0] = previousCoord[0] + distance; //right moves our x coord to the right (positive direction)
		coord[1] = previousCoord[1]; //we move left, so the y coord does not change.
	}
	else if (direction == 'D') //down
	{
		coord[0] = previousCoord[0]; //we move down, so the x coord does not change
		coord[1] = previousCoord[1] - distance; //down moves our y coord down (negative direction)
	}
	else //direction must be 'U' //up
	{
		coord[0] = previousCoord[0]; //we move up, so the x coord does not change
		coord[1] = previousCoord[1] + distance; //down moves our y coord up (positive direction)
	}
	return coord;
}

//return if 2 'lines' conflict each other, we assume that the lines are perpendicular to eachother (but they are finite 'width'), if we find they are parallel, they we return that they don't conflict.
bool doCoordsConflict(vector<int> coord1begin, vector<int> coord1end, vector<int> coord2begin, vector<int> coord2end)
{
	bool conflict = false; //assume that the coords don't conflict unless proven otherwise.

	bool coord1XMovement = (coord1begin[1] == coord1end[1]);
	bool coord2XMovement = (coord2begin[1] == coord2end[1]);

	if ( (coord1XMovement == coord2XMovement)) //if so the lines are parallel here, if they did cross, they would cross infinitely times, this seems incorrect according to the rules.
	{
		return false;
	}

	/*to prove that 2 lines cross, we need to show that they are perpendicular (we did this above), and that the 2nd line is within the beginning and ending coordinates of the first line
	and that it begins above/below the 2nd line and ends below/above the 2nd line.
	*/
	if (coord1XMovement) //the first line is left/right and the second line is up/down
	{
		if ((coord2begin[0] >= coord1begin[0] && coord2begin[0] <= coord1end[0]) || (coord2begin[0] >= coord1end[0] && coord2begin[0] <= coord1begin[0])) //if so this the 2nd line within the correct range
		{
			if ((coord2begin[1] >= coord1begin[1] && coord2end[1] <= coord1begin[1]) || (coord2end[1] >= coord1begin[1] && coord2begin[1] <= coord1begin[1])) //if so the second line must cross the first
			{
				return true; //the lines cross eachother.
			}
		}
	}
	else //the first line is up/down and the second line is left/right
	{
		if ((coord2begin[1] >= coord1begin[1] && coord2begin[1] <= coord1end[1]) || (coord2begin[1] >= coord1end[1] && coord2begin[1] <= coord1begin[1])) //if so this the 2nd line within the correct range
		{
			if ((coord2begin[0] >= coord1begin[0] && coord2end[0] <= coord1begin[0]) || (coord2end[0] >= coord1begin[0] && coord2begin[0] <= coord1begin[0])) //if so the second line must cross the first
			{
				return true; //the lines cross eachother.
			}
		}
	}
	return false; //the lines don't conflict.
}

//return the coordinate where 2 lines cross, this assumes the lines are perpendicular and that they indeed do cross.
vector<int> getConflictCoord(vector<int> coord1begin, vector<int> coord1end, vector<int> coord2begin, vector<int> coord2end)
{
	bool coord1XMovement = (coord1begin[1] == coord1end[1]);

	if (coord1XMovement) //wire1 moves left/right and wire2 moves up/down. 
	{
		return { coord2begin[0], coord1begin[1] };
	}
	else //wire2 moves up/down and wire2 move left/right
	{
		return { coord1begin[0], coord2begin[1] };
	}
}


//very similar to part 1 with some minor tweaks.
void day3Part2()
{
	//get inputs
	string wire1Input;
	string wire2Input;
	cout << "Wire 1 input: ";
	cin >> wire1Input;
	cout << "Wire 2 input: ";
	cin >> wire2Input;
	wire1Input = wire1Input + ','; //add a comma to both input strings so we handle them correctly when we convert the string to the 2d array
	wire2Input = wire2Input + ',';

	//count how many total 'corners' there are for wire 1, u202,l500,d20 would have 4 total places
	int wire1Length = 1; //1 for initial 0,0 location
	for (char c : wire1Input)
	{
		if (c == ',')
		{
			wire1Length = wire1Length + 1;
		}
	}
	//count how many total 'corners' there are for wire 1, u202,l500,d20 would have 4 total places
	int wire2Length = 1; //1 for initial 0,0 location
	for (char c : wire2Input)
	{
		if (c == ',')
		{
			wire2Length = wire2Length + 1;
		}
	}

	//the 3rd element in these vectors represent the total steps taken for each point.
	vector< vector<int> > wire1(wire1Length, vector<int>(3, 0)); //make an 'array' (actually a vector) that is 2d, the first dimension is an array of an array of coordinates, the 2nd dimension is an x,y coord array
	vector< vector<int> > wire2(wire2Length, vector<int>(3, 0));

	//set the wire 1
	char direction;
	int distance;
	int index = 1; //index 0 is already set to {0,0}
	string turnInterpreter = ""; //a partial string used to find out how the string translates to wire moves.
	for (char c : wire1Input)
	{
		if (c == 'L' || c == 'R' || c == 'D' || c == 'U') //we must have just finished a turn command last iteration, so c must be our direction character.
		{
			direction = c;
		}
		else if (c != ',') //if c is not a direction character (proved by above if) and not a comma it must relate to the distance
		{
			turnInterpreter = turnInterpreter + c;
		}
		else
		{
			//we have finished reading this turn command, track the coordinate and move on.
			distance = stoi(turnInterpreter);
			wire1[index] = getNextCoordinateWithSteps(direction, distance, wire1[index - 1]);
			index++; //move to the next index

			turnInterpreter = ""; //reset the partial string, as a comma indicates that we just finished one turn command
		}
	}

	//set the wire 2
	index = 1; //index 0 is already set to {0,0}, reset to 1 again
	for (char c : wire2Input)
	{
		if (c == 'L' || c == 'R' || c == 'D' || c == 'U') //we must have just finished a turn command last iteration, so c must be our direction character.
		{
			direction = c;
		}
		else if (c != ',') //if c is not a direction character (proved by above if) and not a comma it must relate to the distance
		{
			turnInterpreter = turnInterpreter + c;
		}
		else
		{
			//we have finished reading this turn command, track the coordinate and move on.
			distance = stoi(turnInterpreter);
			wire2[index] = getNextCoordinateWithSteps(direction, distance, wire2[index - 1]);
			index++; //move to the next index

			turnInterpreter = ""; //reset the partial string, as a comma indicates that we just finished one turn command
		}
	}


	//the arrays are set, now we need to find out if they conflict
	int minDistance = 0;
	distance = 0; //represents step distance of a crossing
	for (int index1 = 1; index1 < wire1Length; index1++)
	{
		for (int index2 = 1; index2 < wire2Length; index2++)
		{
			if (doCoordsConflict(wire1[index1 - 1], wire1[index1], wire2[index2 - 1], wire2[index2]))
			{
				vector<int> crossCoord = getConflictCoord(wire1[index1 - 1], wire1[index1], wire2[index2 - 1], wire2[index2]);

				distance = wire1[index1 - 1][2] + wire2[index2 - 1][2];
				distance = distance
					+ abs(crossCoord[0] - wire1[index1 - 1][0]) + abs(crossCoord[1] - wire1[index1 - 1][1])
					+ abs(crossCoord[0] - wire2[index2 - 1][0]) + abs(crossCoord[1] - wire2[index2 - 1][1]);
				if((distance != 0 && distance < minDistance) || minDistance == 0)
				{
					minDistance = distance;
				}
			}
		}
	}
	cout << minDistance << endl;
}

//based off of the input info, get the next coordinate, and return it.
vector<int> getNextCoordinateWithSteps(char direction, int distance, vector<int> previousCoord)
{
	vector<int> coord(3); //a vector of size 2, structured like {xCoord, yCoord}
	if (direction == 'L') //left
	{
		coord[0] = previousCoord[0] - distance; //left moves our x coord to the left (negative direction)
		coord[1] = previousCoord[1]; //we move left, so the y coord does not change.
	}
	else if (direction == 'R') //right
	{
		coord[0] = previousCoord[0] + distance; //right moves our x coord to the right (positive direction)
		coord[1] = previousCoord[1]; //we move left, so the y coord does not change.
	}
	else if (direction == 'D') //down
	{
		coord[0] = previousCoord[0]; //we move down, so the x coord does not change
		coord[1] = previousCoord[1] - distance; //down moves our y coord down (negative direction)
	}
	else //direction must be 'U' //up
	{
		coord[0] = previousCoord[0]; //we move up, so the x coord does not change
		coord[1] = previousCoord[1] + distance; //down moves our y coord up (positive direction)
	}
	coord[2] = previousCoord[2] + distance;
	return coord;
}