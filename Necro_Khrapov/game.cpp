#include "game.h"

Game::Game(QWidged * parent) : QWidget(parent)
{
	setStyleSheet("background-color:black;");
	resize(1600, 1200);
	loadImages();


}
