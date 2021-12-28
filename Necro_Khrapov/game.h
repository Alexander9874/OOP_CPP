#ifndef GAME_HEADER
#define GAME_HEADER

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QLabel>
#include <iostream>

#include "Dungeon_and_Creature.h"
#include "User.h"
#include "Golem.h"

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

		QLabel * label_user_stat;
/*
		QLabel * label_health;
		QLabel * label_mana;
		QLabel * label_damage;
		QLabel * label_experience;
*/
		static const int WIGHT = 1200;
		static const int HIGHT = 950;
		static const int CELL_SIZE = 30;
		static const int DELAY = 150;

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
