#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>

#include "lib/parser.h"
#include "lib/calculable.h"
#include "lib/varNode.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

    private:
        void memorySync();
        QList<VarNode *> *registry;
		Ui::MainWindow *ui;

    private slots:
        void deleteVar(QString varName);
        void eval();
};

#endif // MAINWINDOW_HPP
