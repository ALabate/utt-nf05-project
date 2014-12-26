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
            QString varValue = currentVar->getValue()->getValue();

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
    if(this->history.isEmpty() || this->history.last() != expression)
        this->history.append(expression);
    this->currentPos = this->history.length();
    Calculable *value;
    Parser parser(expression, this->registry);

    ui->textBrowser->append("<span style=\"color:#858282;text-decoration:underline;font-size:5px;\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>");
    ui->textBrowser->append("<span style=\"color:#A3A3A3;\">" + expression + " = </span>");

    try
    {
        value = parser.run();
        memorySync();
        if (value != NULL)
        {
            ui->textBrowser->append(value->getValue());
            ui->lineEdit->setText("");
        }
        else
        {
            throw std::runtime_error("Unknown error");
        }
    }
    catch (std::runtime_error &e)
    {
        ui->textBrowser->append("<span style=\"color:red\">[Error] " + QString::fromStdString(e.what()) + "</span>");
    }
    catch (...) {
        ui->textBrowser->append("<span style=\"color:red\">[Error] Caught an unknown exception</span>");
    }
}
