#include "token.h"


/**
 * @brief Constructor
 * 
 * @param kind kind of token   
 * @param value value of token
 */

Token::Token(TokenKind kind, QString value)
{
    this->kind = kind;
    this->value = value;
}


/**
 * @brief kind accessor
 * @return kind of token
 */

TokenKind Token::getKind() const
{
    return this->kind;
}


/**
 * @brief value accessor
 * @return value of token
 */

QString Token::getValue() const
{
    return this->value;
}