#include"calculation.h"
#include"mainwindow.h"


void unit_stream::init(QString q)
{
    ss.clear();
    std::string f = q.toStdString();
    ss<<f;
}

void unit_stream::buffer(unit u)
{
    if(full == true)throw error("buffer already full");
    else
    {
       holder = u;
       full = true;

    }
}
unit unit_stream::parse()
{
    if(full == true)
    {
        full = false;
        return holder;
    }

    char ch;
    ss>>ch;
    if(isdigit(ch))
    {
        ss.putback(ch);
        int i;
        ss >> i;
        return unit{'0', i};
    }
    if(ch == '+'|| ch == '-'|| ch == '*'||ch == '/'|| ch == '(' || ch == ')')
    {
        return unit{ch};
    }
    if(ss.eof()) return unit{'g'};

}
