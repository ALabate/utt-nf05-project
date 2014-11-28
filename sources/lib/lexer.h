#ifndef LEXER_H
#define LEXER_H

#include <QList>
#include <QString>
#include <QMap>
#include <QRegExp>
#include <QDebug>
#include <QObject>

#include "lib/token.h"


class Lexer : public QObject
{
    Q_OBJECT

    public:
        Lexer(QString source);
        QList<Token> run();

    protected:
        Token match(QString line, int offset);
        QString source;
       
        static QMap<TokenKind, QRegExp> initializeTokens();
        static QMap<TokenKind, QRegExp> tokens;

    signals:
        void lexerError(QString line, int offset);
};

#endif // LEXER_H
