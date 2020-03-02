#ifndef PRESENTER_H
#define PRESENTER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "ModelComPort.h"
#include "IViewComPort.h"
#include "ComPortThread.h"

template <typename T> class QList;

class PresenterComPort : public QObject
{
    Q_OBJECT
public:
    explicit PresenterComPort(QObject *parent = 0);
    ~PresenterComPort();

    void appendView(IViewComPort *view);


private slots:
    // Подключение к Com-порту
    void processConnect();
    // Изменение имени Com-порта
    void processNameComPortChanged(QString portName);
    // Изменение скорости Com-порта
    void processBaudratePortChanged(int baudrate);
    // Отправка команды в COM-порт
    void onCommand(QString command);
    // Изменение значения открытия
    void change_open_rate(int value);
    // Изменение значения закрытия
    void change_close_rate(int value);
    //Преобразование значений из UI
    void set_gesture_for_1_hand_1_finger(finger value);
    // Получение ответа из COM-порта
    void response(const QByteArray& msg);
    // Ошибка отправки сообщения
    void error(QString errorMsg);
    // Истекло время ожидания ответа
    void timeout(QString timeoutMsg);
    //Работа с параметрами протеза
    void processProgramParamsChanged(controler_data value);

private:
    void refreshView() const;
    void refreshView(IViewComPort *view) const;
    void setPortInfo() const;
    void setPortInfo(IViewComPort *view) const;

private:
    ModelComPort *m_model;
    QList<IViewComPort*> m_viewList;
    ComPortThread* thread;
};

#endif // PRESENTER_H
