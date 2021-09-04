#include <iostream>
#include "header.h"
using namespace std;

vegetables::vegetables(int x)
{
	number = x;
}

void vegetables::count()
{
	cout << "We have" << number << "vegetables.\n";
}

vegetables::~vegetables()
{
	cout << "Oh no! Nobody did not eat them. They have become rotten.\n ";
}

int main()
{
	vegetables carrots(142);
	carrots.count();
	vegetables *Cptr = &carrots;
	cout << "Whatever..." << Cptr->number << endl;
	return 0;
}
