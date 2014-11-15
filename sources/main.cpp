#include "mainwindow.hpp"
#include <QApplication>

/**
 * @mainpage Project documentation
 *
 * \section intro_sec Introduction
 *
 * This our project documentation. But this project doesn't have any name currently.
*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
