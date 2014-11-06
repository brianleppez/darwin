#include "Darwin.h"


Species::Species (char s) : symbol(s) {}

void Species::addInstruction (const int i, int n)
{
	std::pair<int, int> instruction(i, n);
	InstructionSet.push_back(instruction);
}

bool Species::operator != (const Species& other) const {
	return (this->symbol != other.symbol);
}

Creature::Creature(Species* s) :
species(s), direction(0), turnFlag(false), PC(0) {}

void Creature::infect(Creature* other) {
	if(species->symbol != other->species->symbol) {
		other->species = species;
		other->PC = 0; 
	}
}

void Creature:: incrementPC() 
{
	PC = (PC+1) % (species->InstructionSet.size());
}


Darwin::Darwin (int height, int width) :
turn(0), height(height), width(width), darwinTurnFlag(false), board(height, std::vector<Creature*>(width)) {}

void Darwin::darwin_print (std::ostream& w) {
	w << "Turn = " << turn << "." << std::endl;
	w << "  ";
	for (int i = 0; i < width; i++) {
		w  << i % 10;
	} 
	w << std::endl;
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
		w << std::endl;
	}
	w << std::endl;
}
		
void Darwin::addCreature(Creature& c, int direction, int row, int column) {
	board[row][column] = &c;
	board[row][column]->direction = direction;
}

void Darwin::darwin_run(int moves, std::ostream& o) {
	darwin_print(o);
	while(turn < moves) {
		darwin_turn();
		darwinTurnFlag = !darwinTurnFlag;
		turn++;
		darwin_print(o);
	}
}
void Darwin::darwin_turn() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; j++) {
			while (board[i][j] != 0 && board[i][j]->turnFlag == darwinTurnFlag) {
				int instruction = board[i][j]->species->InstructionSet[board[i][j]->PC].first;
				switch(instruction) {
					case 1: // HOP
						switch(board[i][j]->direction)
						{
							case EAST:
								
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
								if(i > 0 && board[i-1][j] == 0)
								{
									
									board[i-1][j] = board[i][j];
									board[i][j] = 0;
									board[i-1][j]->incrementPC();
									board[i-1][j]->turnFlag = !board[i-1][j]->turnFlag;
								}
								else {
									board[i][j]->incrementPC();
									board[i][j]->turnFlag = !board[i][j]->turnFlag;
								}
							break;

							case WEST:
								if(j > 0 && board[i][j-1] == 0)
								{
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
								if(i < height-1 && board[i+1][j] == 0)
								{
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
						board[i][j]->direction = ((board[i][j]->direction) +1) % 4;
						board[i][j]->turnFlag = !board[i][j]->turnFlag;
						board[i][j]->incrementPC();

					break;
					
					case 3: // right
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
						switch(board[i][j]->direction)
						{
							case EAST:
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
						board[i][j]->PC = board[i][j]->species->InstructionSet[board[i][j]->PC].second;
				break;
				}
			}
		}
	}
}
