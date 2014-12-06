#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    registry(new QList<VarNode *>),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(eval()));
    connect(ui->detailedList, SIGNAL(elementDeleted(QString)), this, SLOT(deleteVar(QString)));
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::memorySync()
{
    QMultiMap<QString, QListWidgetItem*>* list = ui->detailedList->getList();

    foreach (VarNode* currentVar, *(this->registry))
    {
        QString varName = currentVar->getName();

        if (currentVar->getValue() != NULL) {
            QString varValue = QString::number(currentVar->getValue()->getValue());

            bool found = false;

            foreach (QListWidgetItem* currentItem, list->values(varName))
            {
                QLabel* currentLabel = (QLabel*) ui->detailedList->itemWidget(currentItem);

                if (currentLabel->text() != varValue)
                {
                    currentLabel->setText(varValue);
                }

                found = true;
                break;
            }

            if (!found)
            {
                ui->detailedList->addElement(varName, varValue);
            }
        }
    }
}


void MainWindow::deleteVar(QString varName)
{
    for (int i = 0; i < this->registry->length(); i++)
    {
        VarNode* currentNode = this->registry->at(i);

        if (currentNode->getName() == varName)
        {
            this->registry->removeAt(i);
            return;
        }
    }
}

void MainWindow::eval()
{
    QString expression = ui->lineEdit->text();
    Parser parser(expression, this->registry);
    Calculable *value = parser.run();

    memorySync();
    if (value != NULL)
    {
        ui->textBrowser->append(QString::number(value->getValue()));
    }
}
