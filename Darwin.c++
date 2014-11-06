#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cassert>

#include "gtest/gtest.h"

using namespace std;

// Creature Instructions
const int HOP = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int INFECT = 4;


// Control flow Instructions
const int IF_EMPTY = 5;
const int IF_WALL = 6;
const int IF_RANDOM = 7;
const int IF_ENEMY = 8;
const int GO = 9;

const int EAST = 0; // RIGHT
const int NORTH = 1; // UP
const int WEST = 2; // LEFT
const int SOUTH = 3; // DOWN

// enum Direction {EAST = 0, NORTH = 1, WEST = 2, SOUTH = 3};



class Instruction {
	public:
		int command;
		int target;

		Instruction(int c, int t = 0) :
		command(c), target(t)
		{}

		bool isInstructionControl() {
		if (command == HOP || command == LEFT || command == RIGHT || command == INFECT) 
			return false;
		return true;
	}
};

	

class Species {
	public:
		char symbol;
		std::vector<std::pair<int, int>> InstructionSet;

		Species() {}

		Species (char s) : symbol(s) {}

		void addInstruction (const int i, int n = -1)
		{
			std::pair<int, int> instruction(i, n);
			InstructionSet.push_back(instruction);
		}

		bool operator != (const Species& other) const {
			return (this->symbol != other.symbol);
		}


		
		
};

class Creature {
	public:
		Species* species;
		int direction;
		bool turnFlag;
		//bool isCreature; not needed for now
		int PC;


		Creature () {
			//cout << "default constructor<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		}

		// Creature (const Creature& other) :
		// species(other.species), direction(other.direction), turnFlag(other.turnFlag), PC(other.PC)
		// {
		// 	direction = 1;
		// }

		Creature(Species* s) :
		species(s), direction(0), turnFlag(false), PC(0)
		{
			// this->direction = direction;
			//cout << "copy constructor<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		}

		void infect(Creature* other) {
			if(species->symbol != other->species->symbol) {
				other->species = species;
				other->PC = 0; 
			}

		}

		void incrementPC()
		{
			PC = (PC+1) % (species->InstructionSet.size()-1);
		}

		// int receiveInstruction () {
		// 	return species->InstructionSet[PC];
		// }
};

class Darwin {
	

	public:
		int turn;
		int height;
		int width;
		bool darwinTurnFlag;
		//std::vector<Creature> creatures;

		std::vector<std::vector<Creature*>> board;


		Darwin (int height, int width) :
		turn(0), height(height), width(width), darwinTurnFlag(false), board(height, std::vector<Creature*>(width)) {}

		void darwin_print (ostream& w) {
			w << "Turn = " << turn << "." << endl;
			w << "  ";
			for (int i = 0; i < width; i++) {
				w  << i % 10;
			} 
			w << endl;
			for (int i = 0; i < height; i++) {
				w << i % 10 << " ";
				for (int j = 0; j < width; j++) {
					if((board[i][j]) == 0)
						w << '.';
					else
					{
						if(board[i][j]->species != 0)
							w << board[i][j]->species->symbol; 
					}
						
				}
				w << endl;
			}
			w << endl;
		}
		
		void addCreature(Creature& c, int direction, int row, int column) {
			//cout << "AddCreature: direction: " << direction << endl;
			//cout << "addCreature1: " << c.direction << endl;
			//darwin_print(std::cout);
			// creatures.push_back(c);
			board[row][column] = &c;
			//cout << "addCreature3: " << board[row][column]->direction << endl;
			//cout << "addCreature4.1: " << board[1][1]->direction << endl;
			board[row][column]->direction = direction;
			//darwin_print(std::cout);
		}

		void darwin_run(int moves, ostream& o) {

			//cout << "darwin_run "<< endl;
			darwin_print(o);
			while(turn < moves) {
				darwin_turn();
				darwinTurnFlag = !darwinTurnFlag;
				turn++;
				darwin_print(o);
			}
		}
		void darwin_turn() 
		{
			for (int i = 0; i < height; ++i) 
			{
				for (int j = 0; j < width; j++) 
				{
					while (board[i][j] != 0 && board[i][j]->turnFlag == darwinTurnFlag) {
						
						int instruction = board[i][j]->species->InstructionSet[board[i][j]->PC].first;
						//cout << "Creature: " << board[i][j]->species->symbol << " position: " << i << " " << j << " PC: " << board[i][j]->PC << endl;

						

						switch(instruction)
						{
							case 1: // HOP
								//cout << "HOP: " << "pos: " << i << ", " << j << endl;
								switch(board[i][j]->direction)
								{
									case EAST:
										//std::cout << "east" << endl;
										if(j < width-1 && board[i][j+1] == 0)
										{
											//std::cout << "east1" << endl;
											board[i][j+1] = board[i][j];
											board[i][j] = 0;
											board[i][j+1]->incrementPC();
											board[i][j+1]->turnFlag = !board[i][j+1]->turnFlag;
										}
										else {
											board[i][j]->incrementPC();
											board[i][j]->turnFlag = !board[i][j]->turnFlag;

										}
									break;
									
									case NORTH:
										
										//std::cout << "north >> : " << board[i-1][j] << endl;
										if(i > 0 && board[i-1][j] == 0)
										{
											//std::cout << "north1" << endl;
											board[i-1][j] = board[i][j];
											board[i][j] = 0;
											board[i-1][j]->incrementPC();
											//cout << "north turnFlag: " << board[i-1][j]->turnFlag << endl;
											board[i-1][j]->turnFlag = !board[i-1][j]->turnFlag;
											//cout << "north turnFlag2: " << board[i-1][j]->turnFlag << endl;
										}
										else {
											board[i][j]->incrementPC();
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;

									case WEST:
										
										//std::cout << "west" << endl;
										if(j > 0 && board[i][j-1] == 0)
										{
											//std::cout << "west1" << endl;
											board[i][j-1] = board[i][j];
											board[i][j] = 0;
											board[i][j-1]->incrementPC();
											board[i][j-1]->turnFlag = !board[i][j-1]->turnFlag;
										}
										else {
											board[i][j]->incrementPC();
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;

									case SOUTH:
										
										//std::cout << "south" << endl;
										if(i < height-1 && board[i+1][j] == 0)
										{
											//std::cout << "south1" << endl;
											board[i+1][j] = board[i][j];
											board[i][j] = 0;
											board[i+1][j]->incrementPC();
											board[i+1][j]->turnFlag = !board[i+1][j]->turnFlag;
										}
										else {
											board[i][j]->incrementPC();
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;

										
								}	
							break;
							
							case 2: // left
								//cout << "LEFT: " << "pos: " << i << ", " << j << endl;
								board[i][j]->direction = ((board[i][j]->direction) +1) % 4;
								board[i][j]->turnFlag = !board[i][j]->turnFlag;
								board[i][j]->incrementPC();
								//cout << "LEFT2: " << "pos: " << i << ", " << j << endl;
							break;
							
							case 3: // right
								//cout << "RIGHT: " << "pos: " << i << ", " << j << endl;
								if (board[i][j]->direction == EAST) {
									board[i][j]->direction = SOUTH;
									board[i][j]->turnFlag = !board[i][j]->turnFlag;
								}
								else {
									board[i][j]->direction--;
									board[i][j]->turnFlag = !board[i][j]->turnFlag;
								}

								board[i][j]->incrementPC();

							break;
							
							case 4: // infect
								//cout << "INFECT: " << "pos: " << i << ", " << j << endl;
								switch(board[i][j]->direction)
								{
									case EAST:
										//std::cout << "infect east" << endl;
										if(j < width-1 && board[i][j+1] != 0)
										{
											board[i][j]->infect(board[i][j+1]);
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
										else {
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;
									
									case NORTH:
										
										//std::cout << "infect north >> : " << board[i-1][j] << endl;
										if(i > 0 && board[i-1][j] != 0 && board[i-1][j])
										{
											board[i][j]->infect(board[i-1][j]);
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
										else {
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;

									case WEST:
										
										//std::cout << "infect west" << endl;
										if(j > 0 && board[i][j-1] == 0)
										{
											board[i][j]->infect(board[i][j-1]);
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
										else {
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;

									case SOUTH:
										
										//std::cout << "infect south" << endl;
										if(i < height-1 && board[i+1][j] == 0)
										{
											board[i][j]->infect(board[i+1][j]);
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
										else {
											board[i][j]->turnFlag = !board[i][j]->turnFlag;
										}
									break;
								}

								board[i][j]->incrementPC();
							break;

							case 5: // if_empty
								//cout << "IF_EMPTY: " << "pos: " << i << ", " << j << endl;


								if ((board[i][j]->direction == EAST && j < width -1 && board[i][j+1] == 0) ||
									(board[i][j]->direction == NORTH && i > 0 && board[i-1][j] == 0) ||
									(board[i][j]->direction == WEST && j > 0 && board[i][j-1] == 0) ||
									(board[i][j]->direction == SOUTH && i < height -1 && board[i+1][j] == 0)) 
								{
									// go to line N
									board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;
								}
								else
								{
									board[i][j]->incrementPC();
								}

							break;

							case 6: // if_wall
								//cout << "IF_WALL: " << "pos: " << i << ", " << j << endl;
								if ((board[i][j]->direction == EAST && j == width -1) ||
									(board[i][j]->direction == NORTH && i == 0) ||
									(board[i][j]->direction == WEST && j == 0) ||
									(board[i][j]->direction == SOUTH && i == height -1)) 
								{
									// go to line N
									board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;
								}
								else
								{
									board[i][j]->incrementPC();
								}
							break;

							case 7: // if_random
								//cout << "IF_RANDOM: " << "pos: " << i << ", " << j << endl;
								if (rand() % 2 == 1) {
									// go to line n
									board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;
								}
								else {
									// go to next line
									board[i][j]->incrementPC();
								}
							break;

							case 8: // if_enemy
								//cout << "IF_ENEMY: " << "pos: " << i << ", " << j << endl;
								if ((board[i][j]->direction == WEST && j > 0 && board[i][j-1] != 0 && board[i][j-1]->species != board[i][j]->species) || \
                        			(board[i][j]->direction == NORTH && i > 0 && board[i-1][j] != 0 && board[i-1][j]->species != board[i][j]->species) || \
                        			(board[i][j]->direction == EAST && j < width - 1 && board[i][j+1] != 0 && board[i][j+1]->species != board[i][j]->species)  || \
                        			(board[i][j]->direction == SOUTH && i < height - 1 && board[i+1][j] != 0 && board[i+1][j]->species != board[i][j]->species)) 
								{
									// go to line N
									board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;
								}
								else {
									// go to next line
									board[i][j]->incrementPC();
								}
							break;

							case 9:
								// GO to line N
							//cout << "GO: " << "pos: " << i << ", " << j << endl;
								board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;

						break;






						}

					}
					
				}
			}
		}
};
