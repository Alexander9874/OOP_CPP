#include <QApplication>
#include "game.h"

#include "Dungeon_and_Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"
#include "Summoner.h"
#include "Golem.h"
#include "User.h"
#include "Cell.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	Game window;
	window.setWindowTitle("Game");
	window.show();
	return app.exec();
}
