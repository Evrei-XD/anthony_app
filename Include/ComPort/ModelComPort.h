#ifndef MODEL_H
#define MODEL_H

#include <QtCore/qglobal.h>
#include <QThread>
#include <QIcon>
#include <QString>
#include <QStringList>
#include <QSerialPort>
#include <QByteArray>

#include "ComPortThread.h"
#include "Gestures.h"

class ModelComPort
{
public:
    ModelComPort();
    ~ModelComPort();

    // Соединение с COM-портом
    void connectToComPort();

    // Наименование порта
    void setPortName(QString portName);
    QString getPortName() const;

    // Скорость порта
    void setBaudrate(int baudrate);
    int getBaudrate() const;

    //Работа с параметрами протеза
    controler_data getProgramParams();
    void setProgramParams(controler_data value);

    // Получение списка COM-портов
    QList<QString> getListNamePorts() const;

    // Получение состояния порта
    bool isConnect() const;

    // Запись в COM-порт
    void onCommand(QString command);

    // Изменение значения открытия
    void change_open_rate(int value);

    // Изменение значения закрытия
    void change_close_rate(int value);

    // Получить значения для жестов из граф.интерфейса
    void set_gesture_for_1_hand_1_finger(finger value);

    // Прием ответа из COM-порта
    void response(QByteArray msg);
    void readCommand();

private:
    // Поиск существующих COM-портов в системе
    void searchComPorts();
    // Отправка команды на контроллер
    void sendCommand(QByteArray command);
    //Приведение к бинарной системе счисления десятичного числа
    QByteArray changing_the_number_system(long long int command, int system_begin,int system_end);
    //Контрольна сумма
    char crc (char *pcBlock, int len);
    // Разбор принятой команды
    void evaluateCommand(quint8 cmd);

private:
    bool m_connected;               // Есть ли соединение с COM-портом
    QString m_portName;             // Имя COM-порта
    QList<QString> m_listPorts;     // Список COM-портов в системе
    int m_baudrate;
    int m_dataBits;
    int m_parity;
    int m_stopBits;
    int m_flowControl;

    int open_rate;
    int close_rate;
    short int last_finger;
    bool flag_changed;

    QByteArray m_inBuf;

    ComPortThread* thread;

    Gestures *m_usedGest;
    controler_data controler_input;
};

#endif // MODEL_H
