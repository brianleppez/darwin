#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

TEST(Darwin, print) {
	std::ostringstream w;
	darwin_print();
	ASSERT("........\n........\n........\n........\n........\n........\n........\n........\n", w.str());
}
