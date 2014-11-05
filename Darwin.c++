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

		Instruction(int c) :
		command(c)
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
		std::vector<int> InstructionSet;

		Species() {}

		Species (char s) : symbol(s) {}

		void addInstruction (const int i)
		{
			InstructionSet.push_back(i);
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
			cout << "default constructor<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		}

		// Creature (const Creature& other) :
		// species(other.species), direction(other.direction), turnFlag(other.turnFlag), PC(other.PC)
		// {
		// 	direction = 1;
		// }

		Creature(Species* s, int direction) :
		species(s), direction(0), turnFlag(false), PC(0)
		{
			this->direction = direction;
			cout << "copy constructor<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		}

		void infect(Creature& c) {
			if(species->symbol == c->species->symbol) {
				species = c.species;
				PC = 0; 
			}

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
		std::vector<Creature> creatures;

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
		
		void addCreature(Creature c, int direction, int row, int column) {
			//cout << "AddCreature: direction: " << direction << endl;
			//cout << "addCreature1: " << c.direction << endl;
			darwin_print(std::cout);
			creatures.push_back(c);
			board[row][column] = &creatures.back();
			cout << "addCreature3: " << board[row][column]->direction << endl;
			cout << "addCreature4.1: " << board[1][1]->direction << endl;
			board[row][column]->direction = direction;
			cout << "addCreature4.2: " << board[1][1]->direction << endl;
			cout << "addCreature4.3: " << board[row][column]->direction << endl;
			darwin_print(std::cout);
		}

		void darwin_run(int moves, ostream& o) {

			cout << "darwin_run "<< endl;
			for (int i = 1; i <= moves; ++i) {
				darwin_turn();
				darwin_print(o);
				darwinTurnFlag = !darwinTurnFlag;
			}
		}
		void darwin_turn() {
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; j++) {
					
					
					if(board[i][j] != 0 )
					{
						printf(">>>%d  %d\n", i,j );

						cout << "turnFlag: " << board[i][j]->turnFlag << "darwinTurn" << darwinTurnFlag<< endl;
						cout << "direction>: " << board[i][j]->direction << endl;
					}

					if (board[i][j] != 0 && board[i][j]->turnFlag == darwinTurnFlag) {
						
						int instruction = board[i][j]->species->InstructionSet[board[i][j]->PC];
						

						switch(instruction)
						{
							case 1: // HOP
								switch(board[i][j]->direction)
								{
									case EAST:
										std::cout << "east" << endl;
										if(j < width-1 && board[i][j+1] == 0)
										{
											std::cout << "east1" << endl;
											board[i][j+1] = board[i][j];
											board[i][j] = 0;

											board[i][j+1]->turnFlag = !board[i][j+1]->turnFlag;
										}
									break;
									
									case NORTH:
										
										std::cout << "north >> : " << board[i-1][j] << endl;
										if(i > 0 && board[i-1][j] == 0)
										{
											std::cout << "north1" << endl;
											board[i-1][j] = board[i][j];
											board[i][j] = 0;
											cout << "north turnFlag: " << board[i-1][j]->turnFlag << endl;
											board[i-1][j]->turnFlag = !board[i-1][j]->turnFlag;
											cout << "north turnFlag2: " << board[i-1][j]->turnFlag << endl;
										}
									break;

									case WEST:
										
										std::cout << "west" << endl;
										if(j > 0 && board[i][j-1] == 0)
										{
											std::cout << "west1" << endl;
											board[i][j-1] = board[i][j];
											board[i][j] = 0;
											board[i][j-1]->turnFlag = !board[i][j-1]->turnFlag;
										}
									break;

									case SOUTH:
										
										std::cout << "south" << endl;
										if(i < height-1 && board[i+1][j] == 0)
										{
											std::cout << "south1" << endl;
											board[i+1][j] = board[i][j];
											board[i][j] = 0;
											board[i+1][j]->turnFlag = !board[i+1][j]->turnFlag;
										}
									break;

										
								}	
								break;
							case 2: // left
								board[i][j]->direction = (board[i[j]->direction+1) % 4;
							break;
							case 3: // right
								if (board[i][j]->direction == EAST)
									board[i][j]->direction == SOUTH;
								else {
									board[i][j]->direction--;
								}
							break;
							case 4: // infect
								switch(board[i][j]->direction)
								{
									case EAST:
										std::cout << "east" << endl;
										if(j < width-1 && board[i][j+1] != 0)
										{
											std::cout << "east1" << endl;
											board[i][j+1] = board[i][j];
											board[i][j] = 0;

											board[i][j+1]->turnFlag = !board[i][j+1]->turnFlag;
										}
									break;
									
									case NORTH:
										
										std::cout << "north >> : " << board[i-1][j] << endl;
										if(i > 0 && board[i-1][j] == 0)
										{
											std::cout << "north1" << endl;
											board[i-1][j] = board[i][j];
											board[i][j] = 0;
											cout << "north turnFlag: " << board[i-1][j]->turnFlag << endl;
											board[i-1][j]->turnFlag = !board[i-1][j]->turnFlag;
											cout << "north turnFlag2: " << board[i-1][j]->turnFlag << endl;
										}
									break;

									case WEST:
										
										std::cout << "west" << endl;
										if(j > 0 && board[i][j-1] == 0)
										{
											std::cout << "west1" << endl;
											board[i][j-1] = board[i][j];
											board[i][j] = 0;
											board[i][j-1]->turnFlag = !board[i][j-1]->turnFlag;
										}
									break;

									case SOUTH:
										
										std::cout << "south" << endl;
										if(i < height-1 && board[i+1][j] == 0)
										{
											std::cout << "south1" << endl;
											board[i+1][j] = board[i][j];
											board[i][j] = 0;
											board[i+1][j]->turnFlag = !board[i+1][j]->turnFlag;
										}
									break;






						}

					}
					
				}
			}
		}

		
		
		
};

int main() {

	// Darwin d(8, 8);
	// Species s1('f');
	// Species s2('h');
	// Creature c1(&s1);
	// Creature c2(&s2);
	// vector<Creature> cr;
	// for (int i = 0; i < 4; ++i) {
	// 	cr.push_back(c1);
	// }
	// cr.push_back(c2);
	// cr.push_back(c2);
	// for (int i = 0; i < cr.size(); ++i) {
	// 	cout << "Size: " << cr.size() << endl;
	// 	d.addCreature(cr[i], NORTH, 3, 3);
	// 	d.addCreature(cr[i], EAST, 3, 4);
	// 	d.addCreature(cr[i], SOUTH, 4, 4);
	// 	d.addCreature(cr[i], WEST, 4, 3);
	// 	d.addCreature(cr[i], EAST, 0, 0);
	// 	d.addCreature(cr[i], NORTH, 7, 7);
	// }

	// d.darwin_print(cout);


	Darwin d(10, 10);
	Species hopper('h');
	Species food('f');

	cout << "hopper:  " << hopper.symbol << endl;


	hopper.addInstruction(1);

	cout << "hopper2:  " << hopper.symbol << endl;
	Creature h1(&hopper, SOUTH);
	cout << "Direction at addCreature0:" << h1.direction << endl;
	Creature h2(&food, NORTH);
	cout << "Direction at addCreature0.1:" << h1.direction << endl;

	cout << "hopper3:  " << hopper.symbol << endl;


	d.addCreature(h1, SOUTH, 1, 1);
	cout << "Direction at addCreature:" << d.board[1][1]->direction << endl;
	cout << "hopper4:  " << hopper.symbol << endl;
	d.addCreature(h2, NORTH, 9, 2);
	cout << "Direction at addCreature2: " << d.board[1][1]->direction << endl;
	cout << "hopper5:  " << hopper.symbol << endl;

	
	
	// d.addCreature(monster, NORTH, 0, 0);
	// d.addCreature(monster, SOUTH, 9, 8);
	// d.addCreature(monster, EAST, 9, 9);

	//d.addCreature(monster, NORTH, 1, 2);

	d.darwin_run(9, std::cout);






	
	return 0;
};



