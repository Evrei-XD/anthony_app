#include "MainWindow.h"
#include "ui_mainspace.h"
#include <QtDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // "Гасим" светодиод
    ui->led->turnOff();

    my_graphic1=new Chart;
    my_graphic1->setTitle("График открытия");
    my_graphic1->legend()->hide();
    my_graphic1->setAnimationOptions(QChart::NoAnimation);

    ui->mygraphicView1->setChart(my_graphic1);

    my_graphic2=new Chart;
    my_graphic2->setTitle("График закрытия");
    my_graphic2->legend()->hide();
    my_graphic2->setAnimationOptions(QChart::NoAnimation);
    ui->mygraphicView2->setChart(my_graphic2);
    // Смена COM-порта
    connect(ui->portNameBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkCustomPortName(int)));
    // Смена скорости COM-порта
    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkCustomBaudRatePolicy(int)));
    // Смена параметров протеза
   // connect(ui->Openrate, SIGNAL(valueChanged(int)), this, SLOT(checkCustomProgramParams()));
 //   connect(ui->Closerate,SIGNAL(valueChanged(int)),this,SLOT(checkCustomProgramParams()));
    // Нажата кнопка подключения
    connect(ui->connectBtn, SIGNAL(clicked()), this, SIGNAL(processConnect()));
    // Отправка команды через консоль
    connect(ui->console, SIGNAL(onCommand(QString)), this, SIGNAL(onCommand(QString)));
    // Отправка значения с спинера открытия
    connect(ui->Openrate,SIGNAL(valueChanged(int)),this,SIGNAL(change_open_rate(int)));
    // Отправка значения с спинера закрытия
    connect(ui->Closerate,SIGNAL(valueChanged(int)),this,SIGNAL(change_close_rate(int)));
    // Отправка значений о жестах
    connect(ui->Gest1Speed1,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle1,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Speed2,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle2,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Speed3,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle3,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Speed4,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle4,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Speed5,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle5,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Speed6,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Angle6,SIGNAL(sliderReleased()),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(set_gesture_for_1_finger()));
    connect(ui->Gest1Dial,SIGNAL(valueChanged(int)),this,SLOT(set_gesture_for_1_finger()));
    timer = new QTimer(this);
    timer->setInterval(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkCustomProgramParams()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getPortName() const
{
    return ui->portNameBox->currentText();
}

void MainWindow::setPortName(QString portName)
{
    ui->portNameBox->setCurrentText(portName);
}

void MainWindow::addPortName(QString portName)
{
    ui->portNameBox->addItem(portName);
}


int MainWindow::getBaudrate() const
{
    return ui->baudRateBox->currentText().toInt();
}

void MainWindow::setBaudrate(int baudrate)
{
    ui->baudRateBox->setCurrentText(QString::number(baudrate));
}

void MainWindow::addBaudrate(int baudrate)
{
    ui->baudRateBox->addItem(QString::number(baudrate));
}

void MainWindow::ledOn(bool on)
{
    ui->led->turnOn(on);
}

void MainWindow::setEnablePortNameBox(bool enable)
{
    ui->portNameBox->setEnabled(enable);
}

void MainWindow::setEnableBaudrateBox(bool enable)
{
    ui->baudRateBox->setEnabled(enable);
}

void MainWindow::setTitleButton(QString title)
{
    ui->connectBtn->setText(title);
}

void MainWindow::checkCustomBaudRatePolicy(int idx)
{
    Q_UNUSED(idx)
    emit processBaudratePortChanged(ui->baudRateBox->currentText().toInt());
}

controler_data MainWindow::getProgramParams()
{
    //qDebug()<<"MainWindow::getProgramParams";
    controler_data temp;
    temp.msgLevelCH1=ui->Openrate->value();
    temp.msgLevelCH2=ui->Closerate->value();
    temp.msgCurrent;
    temp.msgBatteryTension;
    temp.msgBlockIndication;
    temp.msgRoughnessOfSensors;
    return temp;
}

void MainWindow::setProgramParams(controler_data value)
{
    //qDebug()<<"MainWindow::setProgramParams";
    ui->Openrate->setValue(value.msgLevelCH1);
    ui->Closerate->setValue(value.msgLevelCH2);
    //my_graphics->ShowGraphics(value.msgLevelCH1graph);
    my_graphic1->appendPoint(ui->Openrate->value());
    my_graphic2->appendPoint(ui->Openrate->value());
    //my_graphics->ShowGraphics(ui->Openrate->value(),ui->Closerate->value());
}

void MainWindow::checkCustomProgramParams()
{
    //qDebug()<<"MainWindow::checkCustomProgramParams";
    controler_data temp;
    temp.msgLevelCH1=ui->Openrate->value();
    temp.msgLevelCH2=ui->Closerate->value();
    temp.msgCurrent;
    temp.msgBatteryTension;
    temp.msgBlockIndication;
    temp.msgRoughnessOfSensors;
    temp.msgLevelCH1graph;
    temp.msgLevelCH2graph;
    emit processProgramParamsChanged(temp);
}

void MainWindow::set_gesture_for_1_finger()
{
    finger temp;
    QSlider *temp_slider=reinterpret_cast<QSlider*>(sender());
    if(temp_slider->objectName().contains("Speed"))
    {
        temp.numberFinger=temp_slider->objectName().back().digitValue();
        temp.intValueFingerSpeed=temp_slider->value();
        for(int i=0;i<ui->Gest1->count();i++)
        {

            if(ui->Gest1->itemAt(i)->widget()->objectName().contains("Angle"+temp_slider->objectName().back()))
            {
                temp.intValueFingerAngle=findChild<QSlider*>(ui->Gest1->itemAt(i)->widget()->objectName())->value();
                break;
            }
        }
    }
    else if(temp_slider->objectName().contains("Angle"))
    {
        temp.numberFinger=temp_slider->objectName().back().digitValue();
        temp.intValueFingerAngle=temp_slider->value();
        for(int i=0;i<ui->Gest1->count();i++)
        {

            if(ui->Gest1->itemAt(i)->widget()->objectName().contains("Speed"+temp_slider->objectName().back()))
            {
                temp.intValueFingerSpeed=findChild<QSlider*>(ui->Gest1->itemAt(i)->widget()->objectName())->value();
                break;
            }
        }
    }
    else
    {
        temp.intValueFingerAngle=0;
        temp.intValueFingerSpeed=0;
        temp.numberFinger=1;
        for(int i=0;i<ui->Gest1->count();i++)
        {
            if(ui->Gest1->itemAt(i)->widget()->objectName().contains("Gest"))
            {
                findChild<QSlider*>(ui->Gest1->itemAt(i)->widget()->objectName())->setValue(0);
            }
        }
    }
    temp.NUMBER_CELL=ui->Gest1Dial->value()+ui->Gest1Combobox->currentIndex()*2;
    //qDebug()<<"SPEED"<<temp.intValueFingerSpeed;
    //qDebug()<<"ANGLE"<<temp.intValueFingerAngle;
    emit set_gesture_for_1_hand_1_finger(temp);
}

void MainWindow::checkCustomPortName(int idx)
{
    Q_UNUSED(idx)
    emit processNameComPortChanged(ui->portNameBox->currentText());
}

