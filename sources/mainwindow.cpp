#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    registry(new QList<VarNode *>),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//connect(ui->expressionEdit->document()->documentLayout(),SIGNAL(documentSizeChanged(QSizeF)), ui->expressionEdit, SLOT())
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(eval()));

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

void MainWindow::eval()
{
    QString expression = ui->lineEdit->text();
    Parser parser(expression, this->registry);
    Calculable *value = parser.run();

    if (value != NULL)
    {
        ui->textBrowser->append(QString::number(value->getValue()));
    }
}
