#ifndef TOKEN_H
#define TOKEN_H

#include <QDebug>
#include <QString>


enum TokenKind
{
    T_NULL,
    T_ASSIGNMENT,
    T_WHITESPACE,
    T_SOLVE,
    T_MULTIPLY,
    T_DIVIDE,
    T_SUM,
    T_SUB,
    T_DOUBLE,
    T_PARENTHESIS_LEFT,
    T_PARENTHESIS_RIGHT,
    T_STRING,
    T_MODULO,
    T_POW,
    T_COMMA
};


class Token
{
    public:

        /**
         * @brief constructor
         *
         * @param kind kind of token
         * @param value value of token
         */
        Token(TokenKind kind, QString value="");

        /**
         * @brief destructor
         */
        ~Token();

        /**
         * @brief kind accessor
         * @return kind of token
         */
        TokenKind getKind() const;

        /**
         * @brief value accessor
         * @return value of token
         */
        QString getValue() const;

        /**
         * @brief setValue value setter
         * @param value value to set
         */
        void setValue(QString value);

        /**
         * @brief setKind kind setter
         * @param kind kind to set
         */
        void setKind(TokenKind kind);


    protected:
        TokenKind kind;
        QString value;
};

#endif // TOKEN_H
