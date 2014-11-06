#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include "Darwin.h"

#include "gtest/gtest.h"


TEST(Darwin, print) {
	std::ostringstream w;
	Darwin d(8,8);
	d.darwin_print(w);
	ASSERT_EQ("Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n", w.str());
}

TEST(Darwin, print2) {
    std::ostringstream w;
    Darwin d(1,1);
    d.darwin_print(w);
    ASSERT_EQ("Turn = 0.\n  0\n0 .\n\n", w.str());
}

TEST(Darwin, print3) {
    std::ostringstream w;
    Darwin d(2,2);
    d.darwin_print(w);
    ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 ..\n\n", w.str());
}

TEST(Darwin, species)
{
	Species food('h');
	food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    ASSERT_EQ(food.InstructionSet.size(), 2);
}

TEST(Darwin, species2)
{
	Species food('h');
    ASSERT_EQ(food.symbol, 'h');
}

TEST(Darwin, species4) {
    Species best('b');
    ASSERT_EQ(best.symbol, 'b');
}

TEST(Darwin, species_rover)
{
	Species rover('r');
        rover.addInstruction(IF_ENEMY, 9);  //0
        rover.addInstruction(IF_EMPTY, 7);  //1
        rover.addInstruction(IF_RANDOM, 5); //2
        rover.addInstruction(LEFT);         //3
        rover.addInstruction(GO, 0);        //4
        rover.addInstruction(RIGHT);        //5
        rover.addInstruction(GO, 0);         //6
        rover.addInstruction(HOP);          //7
        rover.addInstruction(GO, 0);        //8
        rover.addInstruction(INFECT);       //9
        rover.addInstruction(GO, 0);        //10
    ASSERT_EQ(rover.symbol, 'r');
    ASSERT_EQ(rover.InstructionSet.size(), 11);
    ASSERT_EQ(rover.InstructionSet[0].first, IF_ENEMY);
    ASSERT_EQ(rover.InstructionSet[1].first, IF_EMPTY);
    ASSERT_EQ(rover.InstructionSet[2].first, IF_RANDOM);
    ASSERT_EQ(rover.InstructionSet[3].first, LEFT);
    ASSERT_EQ(rover.InstructionSet[4].first, GO);
    ASSERT_EQ(rover.InstructionSet[5].first, RIGHT);
    ASSERT_EQ(rover.InstructionSet[6].first, GO);
    ASSERT_EQ(rover.InstructionSet[7].first, HOP);
    ASSERT_EQ(rover.InstructionSet[8].first, GO);
    ASSERT_EQ(rover.InstructionSet[9].first, INFECT);
    ASSERT_EQ(rover.InstructionSet[10].first, GO);
    ASSERT_EQ(rover.InstructionSet[0].second, 9);
    ASSERT_EQ(rover.InstructionSet[1].second, 7);
    ASSERT_EQ(rover.InstructionSet[2].second, 5);
    ASSERT_EQ(rover.InstructionSet[3].second, -1);
    ASSERT_EQ(rover.InstructionSet[4].second, 0);
    ASSERT_EQ(rover.InstructionSet[5].second, -1);
    ASSERT_EQ(rover.InstructionSet[6].second, 0);
    ASSERT_EQ(rover.InstructionSet[7].second, -1);
    ASSERT_EQ(rover.InstructionSet[8].second, 0);
    ASSERT_EQ(rover.InstructionSet[9].second, -1);
    ASSERT_EQ(rover.InstructionSet[10].second, 0);

}

TEST(Darwin, species3)
{
	Species food('h');
	food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    ASSERT_EQ(food.InstructionSet[0].first, LEFT);
    ASSERT_EQ(food.InstructionSet[1].first, GO);
    ASSERT_EQ(food.InstructionSet[1].second, 0);
}

TEST(Darwin, direction) {
    Species best('b');
    Creature c1(&best);
    ASSERT_EQ(c1.direction, 0);
}

TEST(Darwin, turnFlag) {
    Species best('b');
    Creature c1(&best);
    ASSERT_EQ(c1.turnFlag, false);
}

TEST(Darwin, PC) {
    Species best('b');
    Creature c1(&best);
    ASSERT_EQ(c1.PC, 0);

}

TEST(Darwin, creatures)
{
	Species food('h');
	food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature c1(&food);
    ASSERT_EQ(c1.PC, 0);
    ASSERT_EQ(c1.turnFlag, false);
    ASSERT_EQ(c1.direction, 0);
    ASSERT_EQ(c1.species->symbol, 'h');
}

TEST(Darwin, creatures2)
{
	Species rover('r');
        rover.addInstruction(IF_ENEMY, 9);  //0
        rover.addInstruction(IF_EMPTY, 7);  //1
        rover.addInstruction(IF_RANDOM, 5); //2
        rover.addInstruction(LEFT);         //3
        rover.addInstruction(GO, 0);        //4
        rover.addInstruction(RIGHT);        //5
        rover.addInstruction(GO, 0);         //6
        rover.addInstruction(HOP);          //7
        rover.addInstruction(GO, 0);        //8
        rover.addInstruction(INFECT);       //9
        rover.addInstruction(GO, 0);        //10
    Creature c1(&rover);
    ASSERT_EQ(c1.PC, 0);
    ASSERT_EQ(c1.turnFlag, false);
    ASSERT_EQ(c1.direction, 0);
    ASSERT_EQ(c1.species->symbol, 'r');
    for(int i = 1; i < 30; i++)
    {
    	
    	c1.incrementPC();
    	ASSERT_EQ(i%11, c1.PC);

    }
    
}

TEST(Darwin, creatures3)
{
    Species rover('r');
    rover.addInstruction(IF_ENEMY, 9);  //0
    rover.addInstruction(IF_EMPTY, 7);  //1
    rover.addInstruction(IF_RANDOM, 5); //2
    rover.addInstruction(LEFT);         //3
    rover.addInstruction(GO, 0);        //4
    rover.addInstruction(RIGHT);        //5
    rover.addInstruction(GO, 0);         //6
    rover.addInstruction(HOP);          //7
    rover.addInstruction(GO, 0);        //8
    rover.addInstruction(INFECT);       //9
    rover.addInstruction(GO, 0);        //10
    Creature c1(&rover);

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature c2(&food);

    c1.infect(&c2);
    ASSERT_EQ(c1.species->symbol, 'r');
    ASSERT_EQ(c1.species->symbol, c2.species->symbol);
    ASSERT_EQ(c1.species->InstructionSet.size(), c2.species->InstructionSet.size());
    ASSERT_EQ(c1.species->InstructionSet[0].first, IF_ENEMY);
    ASSERT_EQ(c1.species->InstructionSet[1].first, IF_EMPTY);
    ASSERT_EQ(c1.species->InstructionSet[2].first, IF_RANDOM);
    ASSERT_EQ(c1.species->InstructionSet[3].first, LEFT);
    ASSERT_EQ(c1.species->InstructionSet[4].first, GO);
    ASSERT_EQ(c1.species->InstructionSet[5].first, RIGHT);
    ASSERT_EQ(c1.species->InstructionSet[6].first, GO);
    ASSERT_EQ(c1.species->InstructionSet[7].first, HOP);
    ASSERT_EQ(c1.species->InstructionSet[8].first, GO);
    ASSERT_EQ(c1.species->InstructionSet[9].first, INFECT);
    ASSERT_EQ(c1.species->InstructionSet[10].first, GO);
    ASSERT_EQ(c1.species->InstructionSet[0].second, 9);
    ASSERT_EQ(c1.species->InstructionSet[1].second, 7);
    ASSERT_EQ(c1.species->InstructionSet[2].second, 5);
    ASSERT_EQ(c1.species->InstructionSet[3].second, -1);
    ASSERT_EQ(c1.species->InstructionSet[4].second, 0);
    ASSERT_EQ(c1.species->InstructionSet[5].second, -1);
    ASSERT_EQ(c1.species->InstructionSet[6].second, 0);
    ASSERT_EQ(c1.species->InstructionSet[7].second, -1);
    ASSERT_EQ(c1.species->InstructionSet[8].second, 0);
    ASSERT_EQ(c1.species->InstructionSet[9].second, -1);
    ASSERT_EQ(c1.species->InstructionSet[10].second, 0);
    ASSERT_EQ(c2.species->InstructionSet[0].first, IF_ENEMY);
    ASSERT_EQ(c2.species->InstructionSet[1].first, IF_EMPTY);
    ASSERT_EQ(c2.species->InstructionSet[2].first, IF_RANDOM);
    ASSERT_EQ(c2.species->InstructionSet[3].first, LEFT);
    ASSERT_EQ(c2.species->InstructionSet[4].first, GO);
    ASSERT_EQ(c2.species->InstructionSet[5].first, RIGHT);
    ASSERT_EQ(c2.species->InstructionSet[6].first, GO);
    ASSERT_EQ(c2.species->InstructionSet[7].first, HOP);
    ASSERT_EQ(c2.species->InstructionSet[8].first, GO);
    ASSERT_EQ(c2.species->InstructionSet[9].first, INFECT);
    ASSERT_EQ(c2.species->InstructionSet[10].first, GO);
    ASSERT_EQ(c2.species->InstructionSet[0].second, 9);
    ASSERT_EQ(c2.species->InstructionSet[1].second, 7);
    ASSERT_EQ(c2.species->InstructionSet[2].second, 5);
    ASSERT_EQ(c2.species->InstructionSet[3].second, -1);
    ASSERT_EQ(c2.species->InstructionSet[4].second, 0);
    ASSERT_EQ(c2.species->InstructionSet[5].second, -1);
    ASSERT_EQ(c2.species->InstructionSet[6].second, 0);
    ASSERT_EQ(c2.species->InstructionSet[7].second, -1);
    ASSERT_EQ(c2.species->InstructionSet[8].second, 0);
    ASSERT_EQ(c2.species->InstructionSet[9].second, -1);
    ASSERT_EQ(c2.species->InstructionSet[10].second, 0);

}

TEST(Darwin, darwin_turn) {
    Darwin d(2, 2);
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature c(&food);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[1][1]->species->symbol, 'f');
}

TEST(Darwin, darwin_turn2) {
    Darwin d(2, 2);
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature c(&food);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[1][1]->direction, WEST);
}

TEST(Darwin, darwin_turn3) {
    Darwin d(2, 2);
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature c(&food);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[1][1]->PC, 1);
}

TEST(Darwin, darwin_turn4) {
    Darwin d(2, 2);
    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
    Creature c(&hopper);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[0][1]->species->symbol, 'h');
}

TEST(Darwin, darwin_turn5) {
    Darwin d(2, 2);
    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
    Creature c(&hopper);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[0][1]->direction, NORTH);
}


TEST(Darwin, darwin_turn6) {
    Darwin d(2, 2);
    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
    Creature c(&hopper);
    d.addCreature(c, NORTH, 1, 1);
    d.darwin_turn();
    ASSERT_EQ(d.board[0][1]->PC, 1);
}