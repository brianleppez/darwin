#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cassert>

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

				}
			}
		}
		
		
};

int main() {

	
	Darwin d(8, 8);
	Species s('f');
	//Species s1('h');
	Creature c(&s);
	Creature c1(&s);
	//cout<< c.isCreature << endl;
	d.addCreature(c, EAST, 0, 0);
	d.addCreature(c, EAST, 7, 7);
	d.addCreature(c1	, WEST, 4, 4);
	d.darwin_print(cout);
	
	return 0;
};



