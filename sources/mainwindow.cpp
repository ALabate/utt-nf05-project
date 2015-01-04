#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(eval()));
    connect(ui->detailedList, SIGNAL(elementDeleted(QString)), this, SLOT(deleteVar(QString)));
    connect(ui->actionClearVars, SIGNAL(triggered()), ui->detailedList, SLOT(deleteAll()));
    connect(ui->actionClearAll, SIGNAL(triggered()), ui->detailedList, SLOT(deleteAll()));
    connect(ui->actionClearHist, SIGNAL(triggered()), this, SLOT(clearHist()));
    connect(ui->actionClearAll, SIGNAL(triggered()), this, SLOT(clearHist()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));

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

    foreach (VarNode* currentVar, *(VarNode::getRegistry()))
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
                    ui->detailedList->UpdateElement(varName, varValue);
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
    for (int i = 0; i < VarNode::getRegistry()->length(); i++)
    {
        VarNode* currentNode = VarNode::getRegistry()->at(i);

        if (currentNode->getName() == varName)
        {
            VarNode::getRegistry()->removeAt(i);
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
    Parser parser(expression);

    ui->textBrowser->append("<span style=\"color:#858282;text-decoration:underline;font-size:5px;\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>");
    ui->textBrowser->append("<span style=\"color:#A3A3A3;\">" + expression + "</span>");

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
    //Scroll to the bottom of the ouput
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::clearHist()
{
    ui->textBrowser->clear();
    this->history.clear();
    currentPos = 0;
}

void MainWindow::about()
{
    About* ab = new About();
    ab->show();
}

void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save session file", "session.maf", "Matrix calculator file (*.maf);;All files (*)");
    if(filename.isEmpty())
        return;

    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    // stores vars, one per line
    foreach(VarNode* var, *(VarNode::getRegistry()))
    {
        if(var != NULL && var->getValue() != NULL)
        {
            QString varName = var->getName();
            QString varStr = var->getValue()->getValue();

            //Remove \n and/or \r that are used to make variables text more human-readable
            varStr = varStr.replace('\n',"").replace('\r', "");
            varName = varName.replace('\n',"").replace('\r', "");

            //Write variable to the file
            if(!varStr.toUtf8().isEmpty() && !varName.toUtf8().isEmpty())
            {
                f.write(varName.toUtf8());
                f.write("=");
                f.write(varStr.toUtf8());
                f.write("\n");
            }
        }
    }

    //Jump another line to signal end of variable list
    f.write("\n");

    //History list
    foreach(QString str, this->history)
    {

        //Remove \n and/or \r even if they're not supposed to be there
        str = str.replace('\n',"").replace('\r', "");

        //Write variable to the file
        if(!str.toUtf8().isEmpty())
        {
            f.write(str.toUtf8());
            f.write("\n");
        }
    }

    //Jump another line to signal end of history list
    f.write("\n");

    //Calculs output
    f.write(QByteArray(this->ui->textBrowser->toHtml().toUtf8()));

    f.close();
}


void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open session file", "session.maf", "Matrix calculator files (*.maf);;All files (*)");
    if(filename.isEmpty())
        return;

    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //Reset current vars and hist
    clearHist();
    ui->detailedList->deleteAll();

    int state = 0;
    QString html;
    //Reload all data
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        //Remove all endline chars
        line = line.replace('\n',"").replace('\r', "");

        if(line.isEmpty() && state < 2)
        {
            state++;
        }
        else
        {
            switch(state)
            {
                case 0: //Reading vars
                {
                    Parser parser(line);
                    try
                    {
                        parser.run();
                        memorySync();
                    }
                    catch (...) {
                        ui->textBrowser->append("<span style=\"color:red\">[Error] Could not restore one of the variables from the file : <br/>" + line + "</span>");
                        return;
                    }
                }
                break;

                case 1: //Reading hist
                {
                    this->history.append(line);
                    break;
                }
                case 2: //Reading hist
                {
                    html.append(line);
                    break;
                }
            }
        }

    }
    this->currentPos = this->history.length();

    //Write html content to the output
    ui->textBrowser->setHtml(html);

    //Scroll to the bottom of the ouput
    ui->textBrowser->moveCursor(QTextCursor::End);
}
