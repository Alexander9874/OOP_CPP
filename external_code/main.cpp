#include "Restaurant.h"

int main()
{
	Restaurant rest;
	rest.Menu_Random();
	rest.Menu_Print();

	rest.Auto();
	rest.Report();


	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Menu_Add("FISH");
	rest.Auto();
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Manual("VASYA", "!#$");
	rest.Report();
	rest.Menu_Print();

	rest.Menu_Clear();
	rest.Clear();
	rest.Menu_Print();
	rest.Report();

	return 0;
}
