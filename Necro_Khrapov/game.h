#ifndef GAME_HEADER
#define GAME_HEADER

#include <QWidget>
#include <QKeyEvent>
#include "Dungeon_and_Creatures.h"

class Game : public QWidget, public Dungeon
{
	public:
		Game(QWidget * parent = 0);
	protected:
		
	private:
		QImage Player;
		QImage Enemy;
		QImage Wall;
		QImage Lava;
		QImage DoorOpen;
		QImage Ladder;
		QIMage Essence
		// And so on...
		
}

#endif
