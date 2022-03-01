#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>

double firstNum;
bool userIsTypingSecondNum = false; // 判断是否输入第二个数字
bool equalsTyping = false; //判断是否点击过等号
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // 数字键绑定信号和槽(按下时调用digit_pressed()函数)
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusMinus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    // 设置按键可check
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::digit_pressed
 *
 * 点击数字按键，并将数字显示在label上，精度为15位
 */

void MainWindow::digit_pressed()
{
    // 接收按键发送信号
    QPushButton * button = (QPushButton*) sender();

    double labelNumber; // 获取当前按键数字
    QString newLabel;   // 组合按键数字

    if (!equalsTyping)
    {
    // 判断是否为第二个num
        if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
                ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNum))
        {
            labelNumber = button->text().toDouble();
            userIsTypingSecondNum = true;
            newLabel = QString::number(labelNumber,'g',15);
        }
        else
        {
            // 判断小数点后有0的情况
            if (ui->label->text().contains('.') && button->text() == "0")
            {
                newLabel = ui->label->text() + button->text();
            }
            else
            {
                labelNumber = (ui->label->text() + button->text()).toDouble();
                newLabel = QString::number(labelNumber,'g',15);
            }
        }
        ui->label->setText(newLabel);
    }
    else
    {
        ui->label->clear();
        equalsTyping = false;

        // 判断是否为第二个num
            if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
                    ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNum))
            {
                labelNumber = button->text().toDouble();
                userIsTypingSecondNum = true;
                newLabel = QString::number(labelNumber,'g',15);
            }
            else
            {
                // 判断小数点后有0的情况
                if (ui->label->text().contains('.') && button->text() == "0")
                {
                    newLabel = ui->label->text() + button->text();
                }
                else
                {
                    labelNumber = (ui->label->text() + button->text()).toDouble();
                    newLabel = QString::number(labelNumber,'g',15);
                }
            }
            ui->label->setText(newLabel);
    }


}

/**
 * @brief MainWindow::on_pushButton_decimal_released
 *
 * 添加小数
 */
void MainWindow::on_pushButton_decimal_released()
{
    // 只能存在一个小数点
    if(ui->label->text().contains('.'))
    {
        ui->label->setText(ui->label->text());
    }
    else
    {
        ui->label->setText(ui->label->text() + ".");
    }


}

/**
 * @brief MainWindow::unary_operation_pressed
 *
 * 一元操作运算
 */

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    // 负号
    if (button->text()=="+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

    // 百分比
    if (button->text()=="%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
    }

}

/**
 * @brief MainWindow::on_pushButton_clear_released
 *
 * 清除
 */
void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userIsTypingSecondNum = false;

    ui->label->setText("0");
}

/**
 * @brief MainWindow::on_pushButton_eauals_released
 *
 * 等于
 */
void MainWindow::on_pushButton_eauals_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if (ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }
    else if (ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_subtract->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber,'f',8);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }

    userIsTypingSecondNum = false;
    equalsTyping = true;
}

/**
 * @brief MainWindow::binary_operation_pressed
 *
 * 二元操作运算
 */
void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);

}
