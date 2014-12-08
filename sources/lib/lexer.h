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

        /**
         * @brief constructor
         *
         * @param source String going to be tokenized
         */
        Lexer(QString source);

        /**
         * @brief destructor
         */
        ~Lexer();

        /**
         * @brief tokenize the source
         * @return List of tokens
         */
        QList<Token> run();


    protected:

        /**
         * @brief Initialize Lexer::tokens static map
         * @return Map of TokenKind and it's associated regex
         */
        static QMap<TokenKind, QRegExp> initializeTokens();
        static QMap<TokenKind, QRegExp> tokens;


    protected:

        /**
         * @brief try to find a token on a string, begenning on given offset
         *
         * @param line QString source
         * @param offset index where to begin the search
         *
         * @return Token
         */
        Token match(QString line, int offset);

        QString source;


    signals:
        void lexerError(QString line, int offset);
};

#endif // LEXER_H