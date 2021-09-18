#include "source_header.h"

#include <gtest/gtest.h>

TEST(Lem_BoutaConstructor, DefaultConstructor)
{
	Lem_Bouta Obj;
	ASSERT_EQ(0, Obj.GetM());
	ASSERT_EQ(0, Obj.GetC());
	ASSERT_EQ(0, Obj.GetDMS());
	ASSERT_EQ(0, Obj.GetAS());
	ASSERT_EQ(0, Obj.GetBS());
}

TEST(Lem_BoutaConstructor, InitConstructors)
{
	Lem_Bouta Obj(23.98, -32.04);
	ASSERT_EQ(23.98, Obj.GetM());
	ASSERT_EQ(-32.04, Obj.GetC());
	ASSERT_NEAR(1150.08, Obj.GetDMS(), 0.01);
	ASSERT_NEAR(-1182.11, Obj.GetBS(), 0.02);
	ASSERT_NEAR(1118.03, Obj.GetAS(), 0.02);
}
/*
TEST()
{
	
}
*/
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
