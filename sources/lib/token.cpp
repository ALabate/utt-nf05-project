#include "token.h"


Token::Token(TokenKind kind, QString value)
{
    this->kind = kind;
    this->value = value;
}


Token::~Token() {}


TokenKind Token::getKind() const
{
    return this->kind;
}


QString Token::getValue() const
{
    return this->value;
}