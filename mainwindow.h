#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextFrame>
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "mysyntaxhignlighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *lineedit;
    QDialog *finddialog;
    Mysyntaxhignlighter *highlighter;

private slots:
    void showTextFrame();

    void output();

    void setTextFont(bool checked);

    void insertTable();
    void insertList();
    void insertImage();

    void textFind();
    void findNext();
};

#endif // MAINWINDOW_H
