#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QAction>
#include <QLabel>
#include <Qt>
#include <QtGui>
#include <QMoveEvent>
#include <sstream>
#include <QLineEdit>
#include <QObject>
#include<iostream>
#include<vector>
#include "calculation.h"
class error{
    std::string mess;
public:
    error(std::string M):mess{M}{}
    void show() {std::cout<<mess<<std::endl;}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString PassNum(QPushButton* num, QString* str);
    int highestGM();
    int mediumGM();
    int lowestGM();
    QString Clear(QString* str);
    void evaluate(unit_stream* ps, QString* str, QLabel* res);
    QString hold = "";
    void setUpButtonConnections(std::vector<QPushButton*> vec);


private:
    QGridLayout* Grid;
    QWidget* mainWidget;
    
    QPushButton* clear;
    QPushButton* oneButton;
    QPushButton* twoButton;
    QPushButton* threeButton;
    QPushButton* fourButton;
    QPushButton* fiveButton;
    QPushButton* sixButton;
    QPushButton* sevenButton;
    QPushButton* eightButton;
    QPushButton* nineButton;
    QPushButton* addition;
    QPushButton* subtraction;
    QPushButton* division;
    QPushButton* multiplication;
    QLabel* Result;

    QPushButton* evaluateButton;
    QLineEdit* Parameters;

};

#endif // MAINWINDOW_H
