#include <QApplication>
#include "game.h"

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	Game window;
	window.setWindowTitle("Game");
	window.show();
	return app.exec();
}
