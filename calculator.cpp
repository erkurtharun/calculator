#include "calculator.h"
#include "./ui_calculator.h"
#include <sstream>
#include <string>

// keeps the previous value before +,-
int result = 0;
// To understand the addition operation
bool addTrigger = false;
// To understand the sub operation
bool subTrigger = false;

using namespace std;
// main method
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->display->setText(QString::number(result));
// saves all numbers in an array
    QPushButton *numButtons[16];
// pulls all the numbers in order and makes the connection settings. If a number is presses, NumPressed function runs
    for(int i=0; i<16; i++){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *> (butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
// pulls the other buttons and makes the connection settings. If a math operation is pressed then MathButtonPressed operation runs
    // if equals sign is pressed, EqualButton function runs.
    connect(ui->plus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->minus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->clear, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->equals, SIGNAL(released()), this, SLOT(EqualButton()));
}

Calculator::~Calculator()
{
    delete ui;
}

// for number
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *) sender();
    // get the button Value
    QString buttonVal = button->text();
    // get the text from screen
    QString screenText = ui->display->text();
    string newVal = button->text().toUtf8().constData();
    // check for if clr is pressed or not. If clr is clear the screen.
    if(screenText.toInt()==0 && (buttonVal < 'A' || buttonVal > 'F') && (buttonVal < '0' || buttonVal > '9')){
        ui->display->setText(buttonVal);
    }
    else{
        // if other things is pressed, then displays the current + new value as a string
        if(ui->display->text() == "0"){
            ui->display->setText(QString::fromStdString(newVal));
        }else{
            ui->display->setText(ui->display->text() + QString::fromStdString(newVal));
        }

    }
}


// for math operation
void Calculator::MathButtonPressed(){
    addTrigger = false;
    subTrigger = false;

    string screenText = ui->display->text().toUtf8().constData();
    // converting base 10 numbers to hexadecimal
    stringstream ss;
    ss<< hex << screenText << endl;
    ss >> result;
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    // if + is pressed than makes addtrigger true for understanding the operation
    if(QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    // if - is pressed than makes addtrigger true for understanding the operation
    else if(QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }
    ui->display->setText("");
}

// for calculation(equals)
void Calculator::EqualButton(){
    int solution = 0;
    int value;
    string screenText = ui->display->text().toUtf8().constData();
// converting base 10 numbers to hexadecimal
    stringstream ss;
    ss<< hex << screenText << endl;
    ss >> value;
// makes calculation and displays
    if(addTrigger){
        solution = result + value;
    }else if(subTrigger){
        solution = result - value;
    }
    ui->display->setText(QString::number(solution,16));
}
