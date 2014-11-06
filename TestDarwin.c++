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