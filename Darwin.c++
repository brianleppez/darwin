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

enum Direction {EAST = 0, NORTH = 1, WEST = 2, SOUTH = 3};


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
		std::vector<Instruction> InstructionSet;

		Species() {}

		Species (char s) : symbol(s) {}
		
		
};

class Creature {
	public:
		Species* species;
		Direction direction;
		bool turnFlag;
		bool isCreature;
		int PC;

		Creature () {}

		Creature(Species* s) :
		species(s), turnFlag(true), isCreature(true), PC(0)
		{}

		void infect(Creature& c) {
			species = c.species;
			PC = 0; 
		}

		void receiveInstruction () {
			return species.InstructionSet.[PC];
		}




};

class Darwin {
	public:
		int turn;
		int height;
		int width;
		bool turnFlag;

		std::vector<std::vector<Creature*>> board;


		Darwin (int height, int width) :
		turn(0), height(height), width(width), turnFlag(true), board(height, std::vector<Creature*>(width)) {}

		void darwin_print (ostream& w) {
			w << "Turn = " << turn << "." << endl;
			w << "  ";
			for (int i = 0; i < width; i++) {
				w  << i % 9;
			} 
			w << endl;
			for (int i = 0; i < height; i++) {
				w << i % 9 << " ";
				for (int j = 0; j < width; j++) {
					if((board[i][j]) == 0)
						w << '.';
					else
						w << board[i][j]->species->symbol; 
				}
				w << endl;
			}
			w << endl;
		}
		
		void addCreature(Creature& c, Direction direction, int row, int column) {
			board[row][column] = &c;
			board[row][column]->direction = direction;
		}

		void darwin_run(int moves, ostream& o) {
			for (int i = 1; i <= moves; ++i) {
				darwin_turn();
			}
		}
		void darwin_turn() {
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; j++) {
					while (board[i][j].isCreature && board[i][j].turnFlag) {
						const Instruction& instruction = board[i[j].species.InstructionSet

					}
				}
			}
		}
		
		
};

int main() {

	Darwin d(8, 8);
	Species s1('f');
	Species s2('h');
	Creature c1(&s1);
	Creature c2(&s2);
	vector<Creature> cr;
	for (int i = 0; i < 4; ++i) {
		cr.push_back(c1);
	}
	cr.push_back(c2);
	cr.push_back(c2);
	for (int i = 0; i < cr.size(); ++i) {
		cout << "Size: " << cr.size() << endl;
		d.addCreature(cr[i], NORTH, 3, 3);
		d.addCreature(cr[i], EAST, 3, 4);
		d.addCreature(cr[i], SOUTH, 4, 4);
		d.addCreature(cr[i], WEST, 4, 3);
		d.addCreature(cr[i], EAST, 0, 0);
		d.addCreature(cr[i], NORTH, 7, 7);
	}

	d.darwin_print(cout);
	
	return 0;
};



