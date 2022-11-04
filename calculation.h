#ifndef CALCULATION_H
#define CALCULATION_H
#include <string>
#include <QString>
#include <sstream>

class unit {
  public:
  char kind;
  int value;

};

//input stream for holding unused values
class unit_stream
{

    bool full = false;
    unit holder;
    QString data = "";


public:
    std::stringstream ss;
    unit parse();
    void buffer(unit u);
    void init(QString q);
};



#endif // CALCULATION_H
