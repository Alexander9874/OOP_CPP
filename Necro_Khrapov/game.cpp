#include "game.h"

Game::Game(QWidged * parent) : QWidget(parent), Dungeon()
{
	setStyleSheet("background-color:black;");
	resize(1600, 1200);
	loadImages();

	startGame();
}

void Game::loadImages()
{
	Player.load("./pictures/Player.png");
}

void Game::startGame()
{
	//configuratioin add
	//cells add
	// creatures add


	timerId = startTimer(DELAY);
}

void Game::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);

	doDrawing();
}

void Game::doDrawing()
{
	QPainter qp(this);
	if(inGame)
	{
		std::map<std::pair<int, int>, Cell>::const_iterator it_cell = cells.begin();
		std::map<std::pair<int, int>, Creature *>::const_iterator it_creat = creatures.begin();
		for(it_cell; it_cell != cells.end(); ++it_cell)
		{
			if(it_cell->second.get_cell_state() == WALL)
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Wall);
			}
			else
			if(it_cell->second.get_cell_state() == LAVA)
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Lava);
			}
			else
			if(it_cell->second.get_cell_state() == ESSENCE)
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Essence);
			}
			else
			if(it_cell->second.get_cell_state() == DOOR_CLOSED)
			{				
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, DoorClosed);
			}
			else
			if(it_cell->second.get_cell_state() == DOOR_OPENED)
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, DoorOpened);
			}
			else
			if(it_cell->second.get_cell_state() == LADDER)
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Ladder);
			}
		}
		for(it_creat; it_creat != creatures.end(); ++it_creat)
		{
			if(it_creat->second->get_creature_state() != USER)
			{
				qp.draw(it_creat->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Enemy);
			}
			else
			{
				qp.draw(it_cell->first.first * CELL_SIZE, it_cell->second * CELL_SIZE, Player);
			}
		}
	}
	else
	{
		gameOver(qp);
	}
}

void Game::gameOver(QPainter & qp)
{
	QString message = "Game Over";
	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
    int textWidth = fm.width(message);
 
    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();
 
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);  
}

void Game::move()
{
	if(direction == NO_DIRECTION && action == NO_ACTION) return;
	if(user->get_health == 0)
	{
		inGame == false;
		return;
	}
	std::pair<int, int> coords(user->get_position());
	if(direction == UP)
	{
		--coords.second;
	}
	else
	if(direction == DOWN)
	{
		++coords.second;
	}
	else
	if(direction == LEFT)
	{
		--coords.first;
	}
	else
	if(direction == RIGHT)
	{
		++coords.first;
	}

	if(is_creature(coords))
	{
		if(get_creature(coords)->get_fraction() != user->get_fraction())
		{
			user->to_damage(get_creature(coords));
		}
	}
	else
	if(get_cell_state(coords) != WALL && get_cell_state(coords) != DOOR_CLOSED && get_cell_state(coords) != LADDER)
	{
		user->set_position(coords);
	}
	if(action == NO_ACTION) return;
	if(action == WITHER_) user->wither();
	else
	if(action == CURSE_) user->curse();
	else
	if(action == NECROMANCY_) user->necromancy();
	else
	if(action == MORPHISM_) user->morphism();
}

void Game::timerEvent(QTimerEvent * e)
{
	Q_UNUSED(e);

	if(inGame)
	{
		try
		{
			turns();
			move();
		}
		catch(const std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	repaint();
}

void Game::keyPressEvent(QKeyEvent * e)
{
	int key = e->key();

	if(key == QT::Key_W) direction = UP;
	else if(key == QT::Key_A) direction = LEFT;
	else if(key == QT::Key_S) direction = DOWN;
	else if(key == QT::Key_D) direction = RIGHT;

	if(key == QT::Key_H) action = WITHER_;
	else if(key == QT::Key_J) action = CURSE_;
	else if(key == QT::Key_K) action = NECROMANCY_;
	else if(key == QT::Key_L) action = MORPHISM_;
	
	QWidget::keyPressEvent(e);
}