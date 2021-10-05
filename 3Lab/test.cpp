#include "PCB.h"
#include <gtest/gtest.h>

using namespace Printed_Circuit_Board;

TEST(Contact_Constructor, Default_Constructor)
{
	Contact x;
	ASSERT_EQ(x.type, false);
	ASSERT_EQ(x.x, 0);
	ASSERT_EQ(x.y, 0);
	ASSERT_EQ(x.connection, false);
}

TEST(Contact_Constructor, Init_Constructor)
{
	Contact x(true, 98.3431, -0.1);
	ASSERT_EQ(x.type, true);
	ASSERT_NEAR(x.x, 98.34, 0.01);
	ASSERT_NEAR(x.y, -0.1, 0.01);
	ASSERT_EQ(x.connection, false);
}



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
