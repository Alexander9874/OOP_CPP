#include "game.h"

Game::Game(QWidget * parent) : QWidget(parent), Dungeon()
{
	//setStyleSheet("background-color:black;");
	resize(1600, 1200);
	loadImages();

    label_user_stat = new QLabel("health %s / %s\tdamage %s\tmana %s / %s\texperience %s / %s", this);
	label_user_stat->setFont(QFont("Purisa", 20));
	label_user_stat->setGeometry(QRect(10, 640, 1100, 630));

/*
	label_health = new QLabel("health %s / %s", this);
	label_damage = new QLabel("damage %s", this);
	label_mana = new  QLabel("mana %s / %s", this);
	label_experience = new QLabel("experience %s / %s", this);

	label_health->setFont(QFont("Purisa", 20));
	label_damage->setFont(QFont("Purisa", 20));
	label_mana->setFont(QFont("Purisa", 20));
	label_experience->setFont(QFont("Purisa", 20));
*/	
	startGame();	
}

void Game::loadImages()
{
	Player.load("./pictures/Player.png");
	Wall.load("./pictures/Wall.png");
	Lava.load("./pictures/Lava.png");
	Enemy.load("./pictures/Enemy.png");
	Essence.load("./pictures/Essence.png");

}

void Game::startGame()
{
	//configuratioin add
	//cells add
	// creatures add

	inGame = true;
	action = NO_ACTION;
	direction = NO_DIRECTION;

	set_limits({(WIGHT) / CELL_SIZE, (HIGHT - 50) / CELL_SIZE});

std::cout << (WIGHT)/ CELL_SIZE << ' ' << HIGHT / CELL_SIZE << std::endl;

	user = new User(30, 10, 65, 10);
	user->set_dungeon(this);
	user->set_position({10, 10});
	user->set_skill_point(2);

	set_cell({8, 9}, WALL);
	set_cell({8, 10}, WALL);
	set_cell({8, 11}, WALL);
	set_cell({12, 9}, WALL);
	set_cell({12, 10}, WALL);
	set_cell({12, 11}, WALL);
	set_cell({9, 8}, WALL);
	set_cell({10, 8}, WALL);
	set_cell({11, 8}, WALL);
	set_cell({9, 12}, WALL);
	set_cell({10, 12}, WALL);
	//set_cell({11, 12}, WALL);

	set_cell({0, 0}, WALL);
	set_cell({40, 30} , WALL);

	set_cell({9, 9}, LAVA);

	for(int i = 0; i < 41; ++i)
	{
		set_cell({i, 30}, WALL);
		set_cell({i, 0}, WALL);
	}
	for(int i = 1; i < 30; i++)
	{
		set_cell({0, i}, WALL);
		set_cell({40, i}, WALL);
	}

	for(int i = 1; i < 30; i++)
	{
		set_cell({1, i}, ESSENCE);
		set_cell({2, i}, ESSENCE);
	}

	Alive_Creature * creat = new Alive_Creature(GOBLIN, 20, ENEMY, 5, 50);
	Alive_Creature * creat_1 = new Alive_Creature(GOBLIN, 10, ENEMY, 5, 0);
	Dead_Creature * creat_2 = new Dead_Creature(OGRE, 20, FRIEND, 0, 0); 

	Golem * gol_1 = new Golem(10, 0, 0, STONE, 100);
	Golem * gol_2 = new Golem(10, 0, 0, FIRE, 100);
	Golem * gol_3 = new Golem(10, 0, 0, ETHER, 100);

	gol_1->set_position({39, 29});
	gol_2->set_position({38, 28});
	gol_3->set_position({37, 27});
	

	creat->set_position({20, 20});
	creat_1->set_position({1, 1});
	creat_2->set_position({20, 25});

	set_cell({20, 23}, WALL);

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
		QString str = ("health %1 / %2\tdamage %3\tmana %4 / %5\texperience %6 / %7");
		label_user_stat->setText(str.arg(user->get_health()).arg(user->get_max_health()).arg(user->get_damage()).arg(user->get_mana()).arg(user->get_max_mana()).arg(user->get_experience()).arg(user->get_next_level_experience()));

		std::map<std::pair<int, int>, Cell>::const_iterator it_cell = cells.begin();
		std::map<std::pair<int, int>, Creature *>::const_iterator it_creat = creatures.begin();
		for(; it_cell != cells.end(); ++it_cell)
		{
			if(it_cell->second.get_cell_state() == WALL)
			{
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, Wall);
			}
			else
			if(it_cell->second.get_cell_state() == LAVA)
			{
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, Lava);
			}
			else
			if(it_cell->second.get_cell_state() == ESSENCE)
			{
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, Essence);
			}
			else
			if(it_cell->second.get_cell_state() == DOOR_CLOSED)
			{				
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, DoorClosed);
			}
			else
			if(it_cell->second.get_cell_state() == DOOR_OPENED)
			{
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, DoorOpened);
			}
			else
			if(it_cell->second.get_cell_state() == LADDER)
			{
				qp.drawImage(it_cell->first.first * CELL_SIZE, it_cell->first.second * CELL_SIZE, Ladder);
			}
		}
		for(; it_creat != creatures.end(); ++it_creat)
		{
			if(it_creat->second->get_creature_state() != USER)
			{
				qp.drawImage(it_creat->first.first * CELL_SIZE, it_creat->first.second * CELL_SIZE, Enemy);
			}
			else
			{
				qp.drawImage(it_creat->first.first * CELL_SIZE, it_creat->first.second * CELL_SIZE, Player);
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

	//direction = NO_DIRECTION;

	if(is_creature(coords))
	{
//std::cout << "BZZZ" << std::endl;
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

	//action = NO_ACTION;
}

void Game::timerEvent(QTimerEvent * e)
{

//std::cout << "IM HERE" << std::endl;

	Q_UNUSED(e);

	if(inGame)
	{
		try
		{
			turns();
			move();
//std::cout << "MEOW" << std::endl;
		}
		catch(const std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
		direction = NO_DIRECTION;
		action = NO_ACTION;
	}

	if(user->get_health() == 0)
	{
		inGame = false;
	}

	repaint();
}

void Game::keyPressEvent(QKeyEvent * e)
{
	int key = e->key();

	if(key == Qt::Key_W) direction = UP;
	else if(key == Qt::Key_A) direction = LEFT;
	else if(key == Qt::Key_S) direction = DOWN;
	else if(key == Qt::Key_D) direction = RIGHT;

	if(key == Qt::Key_H) action = WITHER_;
	else if(key == Qt::Key_J) action = CURSE_;
	else if(key == Qt::Key_K) action = NECROMANCY_;
	else if(key == Qt::Key_L) action = MORPHISM_;
	try
	{
		if(key == Qt::Key_Y) user->skill_increase(WITHER);
		else if(key == Qt::Key_U) user->skill_increase(CURSE);
		else if(key == Qt::Key_I) user->skill_increase(NECROMANCY);
		else if(key == Qt::Key_O) user->skill_increase(MORPHISM);
		else if(key == Qt::Key_Q) user->collect_essence();
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	QWidget::keyPressEvent(e);
}
