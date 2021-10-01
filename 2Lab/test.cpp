#include "Lem_Bouta.h"

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

TEST(Lem_BoutaMethods, Setters)
{
	Lem_Bouta Obj;
	Obj.SetCoeff(1, 0);
	ASSERT_EQ(1, Obj.GetM());
	ASSERT_EQ(0, Obj.GetC());
	Obj.SetCoeff(0, 5);
	ASSERT_EQ(0, Obj.GetM());
	ASSERT_EQ(5, Obj.GetC());
	Obj.SetCoeff(-12, 0.43);
	ASSERT_EQ(-12, Obj.GetM());
	ASSERT_EQ(0.43, Obj.GetC());
}

TEST(Lem_BoutaMwthods, Parameters)
{
	Lem_Bouta Obj(2, 9);
	double AS, BS;
	ASSERT_EQ("Elliptical Lemniscate Bouta", Obj.WhatType());
	ASSERT_NEAR(28.27, Obj.FindSquare(), 0.01);
	Obj.PolarCoeff(AS, BS);
	ASSERT_NEAR(17, AS, 0.02);
	ASSERT_NEAR(1, BS, 0.02);
	ASSERT_NEAR(4.12, Obj.FindRadius(0), 0.02);
	ASSERT_NEAR(4.12, Obj.FindRadius(3.14159), 0.02);
	ASSERT_STREQ("r^2=17.00*cos(f)^2+1.00*sin(f)^2", Obj.TextPolarEquation());
	
	Obj.SetCoeff(2, 7);
	ASSERT_EQ("Hyperbolic Lemniscate Bouta", Obj.WhatType());
	ASSERT_NEAR(11.16, Obj.FindSquare(), 0.01);
	Obj.PolarCoeff(AS, BS);
	ASSERT_NEAR(15, AS, 0.02);
	ASSERT_NEAR(-1, BS, 0.02);
	ASSERT_NEAR(3.87, Obj.FindRadius(0), 0.02);
	ASSERT_NEAR(3.87, Obj.FindRadius(3.14159), 0.02);
	ASSERT_STREQ("r^2=15.00*cos(f)^2-1.00*sin(f)^2", Obj.TextPolarEquation());

	Obj.SetCoeff(2, 8);
	ASSERT_EQ("Double Circle", Obj.WhatType());
	ASSERT_NEAR(25.13, Obj.FindSquare(), 0.01);
	Obj.PolarCoeff(AS, BS);
	ASSERT_NEAR(16, AS, 0.02);
	ASSERT_NEAR(0, BS, 0.02);
	ASSERT_NEAR(4, Obj.FindRadius(0), 0.02);
	ASSERT_NEAR(4, Obj.FindRadius(3.14159), 0.02);
	ASSERT_STREQ("r^2=16.00*cos(f)^2", Obj.TextPolarEquation());
	
	Obj.SetCoeff(2, -8);
	ASSERT_EQ("Point", Obj.WhatType());
	ASSERT_NEAR(0, Obj.FindSquare(), 0.01);
	Obj.PolarCoeff(AS, BS);
	ASSERT_NEAR(0, AS, 0.02);
	ASSERT_NEAR(-16, BS, 0.02);
	ASSERT_NEAR(0, Obj.FindRadius(0), 0.02);
	ASSERT_NEAR(0, Obj.FindRadius(3.14159), 0.02);
	ASSERT_STREQ("r^2=-16.00*sin(f)^2", Obj.TextPolarEquation());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
