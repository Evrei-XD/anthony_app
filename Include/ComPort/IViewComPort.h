#ifndef IVIEW
#define IVIEW

#include "ModelComPort.h"

class IViewComPort
{
public:
    // Имя текущего COM-порта
    virtual QString getPortName() const = 0;
    virtual void setPortName(QString portName) = 0;
    virtual void addPortName(QString portName) = 0;
    // Текущая скорость
    virtual int getBaudrate() const = 0;
    virtual void setBaudrate(int baudrate) = 0;
    virtual void addBaudrate(int baudrate) = 0;

    //Работа с параметрами протеза
    virtual void setProgramParams(controler_data value) = 0;
    virtual controler_data getProgramParams() = 0;

    // Включение/выключение светодиода
    virtual void ledOn(bool on) = 0;

    // Блокировка comboBox
    virtual void setEnablePortNameBox(bool enable) = 0;
    virtual void setEnableBaudrateBox(bool enable) = 0;

    // Изменение надписи на кнопке
    virtual void setTitleButton(QString) = 0;

    // signals
public:
    // Подключение к Com-порту
    virtual void processConnect() = 0;
    // Изменение имени Com-порта
    virtual void processNameComPortChanged(QString portName) = 0;
    // Изменение скорости Com-порта
    virtual void processBaudratePortChanged(int baudrate) = 0;
    //Работа с параметрами протеза
    virtual void processProgramParamsChanged(controler_data value) = 0;
    // Отправка данных в COM-порт
    virtual void onCommand(QString command) = 0;
    // Изменение значения открытия
    virtual void change_open_rate(int value) = 0;
    // Изменение значения закрытия
    virtual void change_close_rate(int value) = 0;
    //Измение значений для жеста
    virtual void set_gesture_for_1_hand_1_finger(finger value) = 0;

};

#endif // IVIEW
