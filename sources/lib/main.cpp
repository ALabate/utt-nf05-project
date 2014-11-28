#include <QCoreApplication>
#include <QList>
#include <QString>
#include <QMap>

#include "lexer.h"
#include "calculable.h"
#include "parser.h"


/*
 * Entry point
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QMap<QString, Calculable *> registry;

    Parser parser("a := (((3*4)/2)+2)", registry);
    qDebug() << parser.run()->getValue();

    return a.exec();
}
