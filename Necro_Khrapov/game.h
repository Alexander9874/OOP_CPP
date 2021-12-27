#ifndef GAME_HEADER
#define GAME_HEADER

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <iostream>

#include "Dungeon_and_Creature.h"
#include "User.h"

enum directions
{
	NO_DIRECTION,
	LEFT,
	DOWN,
	UP,
	RIGHT
};

enum actions_
{
	NO_ACTION,
	WITHER_,
	CURSE_,
	NECROMANCY_,
	MORPHISM_
};

class Game : public QWidget, public Dungeon
{
	public:
		Game(QWidget * parent = 0);
	protected:
		void paintEvent(QPaintEvent *);
		void timerEvent(QTimerEvent *);
		void keyPressEvent(QKeyEvent *);
	private:
		QImage Player;
		QImage Enemy;
		QImage Wall;
		QImage Lava;
		QImage DoorOpened;
		QImage DoorClosed;
		QImage Ladder;
		QImage Essence;
		// And so on...

		static const int WIGHT = 1600;
		static const int HIGHT = 1200;
		static const int CELL_SIZE = 40;
		static const int DELAY = 200;

		int timerId;
		bool inGame;

		directions direction;
		actions_ action;

		void loadImages();
		void startGame();
		void move();
		void doDrawing();
		void gameOver(QPainter &);
};

#endif
