#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cassert>

using namespace std;

const int HOP = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int INFECT = 4;

const int IF_EMPTY = 5;
const int IF_WALL = 6;
const int IF_RANDOM = 7;
const int IF_ENEMY = 8;
const int GO = 9;

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;

/*
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
	};
	
*/
class Species {
	public:
		char letter;
		//std::vector<Instruction> InstructionSet;

		Species() {}

		Species (char l) :
		letter(l)
		{}
};

class Creature {
	public:
		Species species;
		int direction;
		bool turnFlag;
		bool isCreature;
		int PC;

		Creature () {}

		Creature(const Species& s) :
		species(s), turnFlag(true), isCreature(true), PC(0)
		{}

};

class Darwin {
	public:
		int turn;
		int height;
		int width;
		bool turnFlag;

		std::vector<std::vector<Creature> > board;


		Darwin (int height = 8, int width = 8) :
		turn(0), height(height), width(width), turnFlag(true), board(height, std::vector<Creature>(width)) {}

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
					if(!board[i][j].isCreature)
						w << '.';
					else
						w << board[i][j].species.letter; 
				}
				w << endl;
			}
			w << endl;
		}
		void addCreature(const Creature& c, int direction, int row, int column) {
			board[row][column] = c;
			board[row][column].direction = direction;
		}
};

int main() {
	Darwin d(12, 12);
	Species s('a');
	Creature c(s);
	cout<< c.isCreature << endl;
	d.addCreature(c, 0, 0, 0);
	d.addCreature(c, 3, 7, 7);
	d.darwin_print(cout);
}



