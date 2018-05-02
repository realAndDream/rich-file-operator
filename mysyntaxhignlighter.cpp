#include "mysyntaxhignlighter.h"

Mysyntaxhignlighter::Mysyntaxhignlighter(QTextDocument *parent):
    QSyntaxHighlighter(parent)
{

}

void Mysyntaxhignlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myformat;
    myformat.setFontWeight(QFont::Bold);
    myformat.setForeground(Qt::green);
    QString pattern = "\\bchar\\b";
    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index,length,myformat);
        index = text.indexOf(expression,index + length);
    }
}
