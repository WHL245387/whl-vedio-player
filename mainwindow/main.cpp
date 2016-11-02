#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);
	MainWindow * testWindow = new MainWindow;
	testWindow->show();
	return app.exec();
	
	
	
}