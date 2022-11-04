#include "calculation.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Parameters = new QLineEdit;
    Parameters->setReadOnly(true);
    mainWidget = new QWidget;
    Result = new QLabel;
    oneButton = new QPushButton("1");
    twoButton = new QPushButton("2");
    threeButton = new QPushButton("3");
    fourButton = new QPushButton("4");
    fiveButton = new QPushButton("5");
    sixButton = new QPushButton("6");
    sevenButton = new QPushButton("7");
    eightButton = new QPushButton("8");
    nineButton = new QPushButton("9");
    multiplication = new QPushButton("*");
    division = new QPushButton("/");
    addition = new QPushButton("+");
    subtraction = new QPushButton("-");
    evaluateButton = new QPushButton("=");
    clear = new QPushButton("C");
    std::vector<QPushButton*> vec{oneButton, twoButton, threeButton, fourButton, fiveButton, sixButton, sevenButton, eightButton, nineButton, multiplication, division, addition, subtraction};
    Grid = new QGridLayout;
    Grid->addWidget(Parameters, 0, 0, 1,4);
    Grid->addWidget(oneButton, 1,0);
    Grid->addWidget(twoButton, 1, 1);
    Grid ->addWidget(threeButton, 1, 2);
    Grid ->addWidget(addition, 1, 3);
    Grid->addWidget(fourButton, 2,0);
    Grid->addWidget(fiveButton, 2,1);
    Grid->addWidget(sixButton, 2,2);
    Grid ->addWidget(subtraction,2,3);
    Grid->addWidget(sevenButton, 3,0);
    Grid->addWidget(eightButton,3,1);
    Grid->addWidget(nineButton,3,2);
    Grid ->addWidget(multiplication,3,3);
    Grid->addWidget(evaluateButton,4,0);
    Grid->addWidget(clear,4,2);
    Grid ->addWidget(division,4,3);
    Grid->addWidget(Result,5,0);
    mainWidget->setLayout(Grid);
    setCentralWidget(mainWidget);
    mainWidget->show();
    setUpButtonConnections(vec);

}
 unit_stream* us = new unit_stream;

void MainWindow::setUpButtonConnections(std::vector<QPushButton*> vec)
{
    //Pointers to class local members because lambda can't capture out of scope variables
    QString* j = &hold;
    QLineEdit* Line = Parameters;
    unit_stream* fs = us;
    QLabel* res = Result;
    for(int i = 0; i < vec.size(); ++i)
    {
        QPushButton* h = vec[i];

        connect(h, &QPushButton::clicked, this, [this, h, j, Line]{Line->insert(PassNum(h, j));});
    }
    connect(evaluateButton, &QPushButton::clicked, this, [this,fs,j,res]{evaluate(fs,j,res);});
    connect(clear, &QPushButton::clicked, this, [this,Line,j]{Line->clear(); *j = "";});
}



int MainWindow::lowestGM()
{
    unit left = us->parse();
    switch(left.kind){
    case '(':
    {
        int d = highestGM();
        left = us->parse();
        if(left.kind != ')')
        {
            throw error("missing closing parentheses");
        }
        return d;
    }
    case '0':
    {
        return left.value;
    }
    default:
    if(us->ss.eof()){};

}
}
int MainWindow::mediumGM()
{

    int left = lowestGM();
    unit u = us->parse();
    while(true)
    {
    if(us->ss.eof()) return left;
    switch(u.kind)
    {
    case '*':
    left *= lowestGM();
    u = us->parse();
    break;
    case '/':
    {
        int h = lowestGM();
        if (h == 0) throw error("cannot divide by zero");
        left /= h;
        u = us->parse();
        break;
    }
    default:
        us->buffer(u);
        return left;
    }
    }
}

int MainWindow::highestGM()
{
    int left;
    left = mediumGM();
    unit u = us->parse();
    while(true)
    {

        switch(u.kind)
        {
        case '+':
        left += mediumGM();
        u = us->parse();
        break;
        case '-':
        left -= mediumGM();
        u = us->parse();
        break;
        default:
        if(us->ss.eof()) return left;
        us->buffer(u);
        return left;
        }
    }

}

QString MainWindow::PassNum(QPushButton* num, QString* str)
{
    QString F = num->text();
    *str += F;
    return F;
}

void MainWindow::evaluate(unit_stream* ps, QString* str, QLabel* res)
{
    ps->init(*str);
    int g = highestGM();
    QString display = QString::number(g);
    res->setText(display);


}

QString MainWindow::Clear(QString* str)
{
    *str ="";
    return *str;
}

