#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <cassert>


// Global variables
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

// Classes

class Species {
public:
	// A symbol to indicate what species the creature is
	char symbol;

	// A vector of pairs, indicating the action and the line target.
	std::vector<std::pair<int, int>> InstructionSet;

	// One parameter constructor which takes a char.
	Species (char);

	// method called in RunDarwin. Adds instructions to each Species
	void addInstruction (const int, int = -1);

	// Overloads != operator. Checks whether two species are of the same kind. Useful in infect.
	bool operator != (const Species&) const;
};

class Creature {
public:
	// Pointer to a Species to have many Creature belonging to one species.
	Species* species;

	// Direction in which the creature is facing.
	int direction;

	// turnFlag for each creature. Indicates whether it's a creature's turn.
	bool turnFlag;

	// Program Counter for the specie. It tells the creature which instruction to perform.
	int PC;

	// One parameter construction. Creates the creature based on a specie.
	Creature(Species*);

	// Infect. It tells the creature to infect another if they're not the same species.
	void infect(Creature*);

	// Increments the PC and prevents from overflowing.
	void incrementPC();
};

class Darwin {
public:
	// It represents the amount of turns the game is going to perform.
	int turn;

	// Height of the board
	int height;

	// Width of the board
	int width;

	// turnFlag used by Creature to perform instructions if it matches
	bool darwinTurnFlag;

	// The board itself. It is of type Creature* to prevent creating N*N Creatures
	std::vector<std::vector<Creature*>> board;

	// Two parameter constructor that establishes the board's dimensions.
	Darwin(int, int);

	// Prints the board
	void darwin_print(std::ostream&);

	// Adds Creatures to the board. 
	void addCreature(Creature&, int, int, int);

	// Runs the program itself
	void darwin_run(int, std::ostream&);

	// Performs each turn
	void darwin_turn();
};

