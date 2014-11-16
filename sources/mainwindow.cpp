#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//connect(ui->expressionEdit->document()->documentLayout(),SIGNAL(documentSizeChanged(QSizeF)), ui->expressionEdit, SLOT())

	ui->detailedList->addElement("Test1","Hello\ntest");
	ui->detailedList->addElement("Test0","Hello2\ntest",true);
	ui->detailedList->addElement("Test3","Hello3\ntest",false);
	ui->detailedList->addElement("Test1","HelloNOPE\ntest",false);
	ui->detailedList->addElement("Test2","Hello");

	ui->detailedList->expandElement("Test0", false);
	ui->detailedList->deleteElement("Test2");
	ui->detailedList->UpdateElement("Test0","Updated :)");

}

MainWindow::~MainWindow()
{
	delete ui;
}
