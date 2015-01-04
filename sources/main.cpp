#include "mainwindow.hpp"
#include <QApplication>

/**
 * @mainpage Project documentation
 *
 * \section intro_sec Introduction
 *
 * This is the documentation of our Matrix Calculator.
 *
 * This project has been made by Axel Mousset and Aurelien Labate
 * when they were following the NF05 course (Introduction to C)
 * at the University of Technology of Troyes.
 *
*/

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
