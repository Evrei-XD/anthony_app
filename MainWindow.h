#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif
*/

#include <QMainWindow>

#include "IViewComPort.h"
#include "Graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IViewComPort
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Имя текущего COM-порта
    virtual QString getPortName() const;
    virtual void setPortName(QString portName);
    virtual void addPortName(QString portName);
    // Текущая скорость
    virtual int getBaudrate() const;
    virtual void setBaudrate(int baudrate);
    virtual void addBaudrate(int baudrate);

    //Текущие параметры
    virtual controler_data getProgramParams();
    virtual void setProgramParams(controler_data value);

    // Включение/выключение светодиода
    virtual void ledOn(bool on);

    // Блокировка comboBox
    virtual void setEnablePortNameBox(bool enable);
    virtual void setEnableBaudrateBox(bool enable);

    // Изменение надписи на кнопке
    virtual void setTitleButton(QString title);

private slots:
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomPortName(int idx);
    void set_gesture_for_1_finger();
    void checkCustomProgramParams();

signals:
    // Подключение к Com-порту
    void processConnect();
    // Изменение имени Com-порта
    void processNameComPortChanged(QString portName);
    // Изменение скорости Com-порта
    void processBaudratePortChanged(int baudrate);
    // Изменение параметров протеза
    void processProgramParamsChanged(controler_data value);
    // Отправка команды в COM-порт
    void onCommand(QString cmd);
    // Отправка значения открытия со спинера в COM-порт
    void change_open_rate(int value);
    // Отправка значения закрытия со спинера в COM-порт
    void change_close_rate(int value);
    // Отправка значений в UI
    void set_gesture_for_1_hand_1_finger(finger value);

private:
    Ui::MainWindow *ui;

    Chart *my_graphic1;
    Chart *my_graphic2;
    QTimer *timer;

};

#endif // MAINWINDOW_H
