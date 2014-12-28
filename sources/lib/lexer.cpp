#include "lexer.h"


Lexer::Lexer(QString source)
{
    this->source = source;
}


Lexer::~Lexer() {}


QList<Token> Lexer::run()
{
    QList<Token> tokens;
    int offset = 0;

    while (offset <= this->source.length()-1)
    {
        Token result = this->match(this->source, offset);

        if (result.getValue() == "")
        {
            throw std::runtime_error("Unable to parse the character " + QString::number(offset+1).toStdString());
            qWarning() << "Unable to parse the element, offset: " << offset;
            emit lexerError(this->source, offset);
            return tokens;
        }

        if (result.getKind() != T_WHITESPACE && result.getKind() != T_NULL)
        {
            tokens.append(result);
        }

        offset += result.getValue().length();
    }

    return tokens;
}


QMap<TokenKind, QRegExp> Lexer::initializeTokens()
{
    QMap<TokenKind, QRegExp> map;

    map.insert(T_ASSIGNMENT, QRegExp("^(:=)"));
    map.insert(T_WHITESPACE, QRegExp("^(\\s+)"));
    map.insert(T_SOLVE, QRegExp("^(=)"));
    map.insert(T_MULTIPLY, QRegExp("^(\\*)"));
    map.insert(T_DIVIDE, QRegExp("^(/)"));
    map.insert(T_SUM, QRegExp("^(\\+)"));
    map.insert(T_SUB, QRegExp("^(-)"));
    map.insert(T_MODULO, QRegExp("^(%)"));
    map.insert(T_POW, QRegExp("^(\\^)"));
    map.insert(T_SCALAR, QRegExp("^([0-9][\\.0-9]*)"));
    map.insert(T_MATRIX, QRegExp("^(\[.+\])"));
    map.insert(T_PARENTHESIS_LEFT, QRegExp("^(\\()"));
    map.insert(T_PARENTHESIS_RIGHT, QRegExp("^(\\))"));
    map.insert(T_STRING, QRegExp("^([A-z][A-z0-9_]*)"));
    map.insert(T_COMMA, QRegExp("^(,)"));

    return map;
}


QMap<TokenKind, QRegExp> Lexer::tokens = Lexer::initializeTokens();


Token Lexer::match(QString line, int offset)
{
    QString string = line.right(line.length() - offset);

    foreach (TokenKind kind, Lexer::tokens.keys())
    {
        QRegExp value = Lexer::tokens.value(kind);
        int pos = value.indexIn(string);
        if (pos > -1)
        {
            QString match = value.cap(1);
            return Token(kind, match);
        }

    }

    return Token(T_NULL, NULL);
}
