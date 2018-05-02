#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *rootframe = document->rootFrame();

    QTextFrameFormat format;
    format.setBorderBrush(Qt::red);
    format.setBorder(2);
    format.setMargin(2);
//    format.setBackground(Qt::blue);
    rootframe->setFrameFormat(format);

    QTextFrameFormat cursorformat;
    cursorformat.setBackground(Qt::gray);
    cursorformat.setBorder(2);
    cursorformat.setMargin(3);
    cursorformat.setPadding(4);
    cursorformat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertFrame(cursorformat);

    QAction *action_textFrame = new QAction("框架",this);
    connect(action_textFrame,&QAction::triggered,this,&MainWindow::showTextFrame);
    ui->mainToolBar->addAction(action_textFrame);

    QAction *action_out = new QAction("打印",this);
    connect(action_out,&QAction::triggered,this,&MainWindow::output);
    ui->mainToolBar->addAction(action_out);

    QAction *action_font = new QAction("字体",this);
    action_font->setCheckable(true);
    connect(action_font,&QAction::toggled,this,&MainWindow::setTextFont);
    ui->mainToolBar->addAction(action_font);

    QAction *action_textTable = new QAction("表格",this);
    QAction *action_textList = new QAction("列表",this);
    QAction *action_textImage = new QAction("图片",this);
    connect(action_textTable,&QAction::triggered,this,&MainWindow::insertTable);
    connect(action_textImage,&QAction::triggered,this,&MainWindow::insertImage);
    connect(action_textList,&QAction::triggered,this,&MainWindow::insertList);
    ui->mainToolBar->addAction(action_textImage);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textTable);

    finddialog = new QDialog(this);
    lineedit = new QLineEdit(finddialog);
    QPushButton *btn_next = new QPushButton(finddialog);
    btn_next->setText("下一个");
    connect(btn_next,&QPushButton::clicked,this,&MainWindow::findNext);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineedit);
    layout->addWidget(btn_next);
    finddialog->setLayout(layout);

    QAction *action_find = new QAction("寻找",this);
    connect(action_find,&QAction::triggered,this,&MainWindow::textFind);
    ui->mainToolBar->addAction(action_find);

    highlighter = new Mysyntaxhignlighter(ui->textEdit->document());

    ui->textEdit_2->append(tr("<html><font color = red>使用html</font></html>"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *frame = document->rootFrame();
    QTextFrame::iterator iterator;
    for(iterator = frame->begin(); !(iterator.atEnd()); iterator++)
    {
        QTextFrame *childFrame = iterator.currentFrame();
        QTextBlock childBlock = iterator.currentBlock();
        if(childFrame)
            qDebug()<<"frame:";
        else if (childBlock.isValid()) {
            qDebug()<<"block:"<<childBlock.text();
        }
    }
}

void MainWindow::output()
{
    qDebug()<<ui->textEdit->toPlainText();
}

void MainWindow::setTextFont(bool checked)
{
    if(checked)
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockformat;
        blockformat.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(blockformat);

        QTextCharFormat charformat;
        charformat.setFont(QFont("宋体,10,-1,5,75,0,0,0,0,0"));
        charformat.setBackground(Qt::red);
        charformat.setForeground(Qt::blue);
        charformat.setFontUnderline(true);
        cursor.setCharFormat(charformat);
        cursor.insertText("字体");
    }
}

void MainWindow::insertImage()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat format;
    format.setName("../untitled/images/6.png");
    cursor.insertImage(format);
}

void MainWindow::insertList()
{
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellSpacing(2);
    format.setCellSpacing(10);
    cursor.insertTable(2,2,format);
}

void MainWindow::textFind()
{
    finddialog->show();
}

void MainWindow::findNext()
{
    QString string = lineedit->text();
    bool isfind = ui->textEdit->find(string,QTextDocument::FindCaseSensitively);
    if(isfind)
    {
        qDebug()<<tr("行号：%1   列号：%2").arg(ui->textEdit->textCursor().blockNumber()).arg(ui->textEdit->textCursor().columnNumber());
    }
}
