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

    currentPos = 0;
}

MainWindow::~MainWindow()
{
	delete ui;
}


bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Up)
        {
            if (this->currentPos > 0)
            {
                this->currentPos--;
                this->ui->lineEdit->setText(this->history[this->currentPos]);
            }
        }
        else if (ke->key() == Qt::Key_Down)
        {
            if (this->currentPos < this->history.length()-1)
            {
                this->currentPos++;
                this->ui->lineEdit->setText(this->history[this->currentPos]);
            }
        }
    }

    return QWidget::event(event);
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
    this->history.append(expression);
    this->currentPos = this->history.length();
    Parser parser(expression, this->registry);
    Calculable *value = parser.run();

    memorySync();
    if (value != NULL)
    {
        ui->textBrowser->append(QString::number(value->getValue()));
    }

    ui->lineEdit->setText("");
}
