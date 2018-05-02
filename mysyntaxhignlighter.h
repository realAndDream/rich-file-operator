#ifndef MYSYNTAXHIGNLIGHTER_H
#define MYSYNTAXHIGNLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>

class Mysyntaxhignlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit Mysyntaxhignlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);
};

#endif // MYSYNTAXHIGNLIGHTER_H
