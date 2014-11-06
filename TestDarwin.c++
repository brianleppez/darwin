#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include "Darwin.c++"

#include "gtest/gtest.h"


TEST(Darwin, print) {
	std::ostringstream w;
	Darwin d(8,8);
	d.darwin_print(w);
	ASSERT_EQ("Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n", w.str());
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
}