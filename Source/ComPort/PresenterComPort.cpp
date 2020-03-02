#include "PresenterComPort.h"
#include <QDebug>

PresenterComPort::PresenterComPort(QObject *parent) :
    QObject(parent),
    m_model(new ModelComPort)
{
    thread = ComPortThread::getInstance();

    connect(thread, SIGNAL(responseMsg(const QByteArray&)), this, SLOT(response(const QByteArray&)));
    connect(thread, SIGNAL(error(QString)), this, SLOT(error(QString)));
    connect(thread, SIGNAL(timeout(QString)), this, SLOT(timeout(QString)));
}

PresenterComPort::~PresenterComPort()
{
    qDebug("~PresenterComPort()");
    if (m_model)
    {
        delete m_model;
        m_model = 0;
    }

    if (thread)
    {
        thread->free();
        thread = 0;
    }
}

void PresenterComPort::appendView(IViewComPort *view)
{
    // Проверяем наличие данного вида в списке
    if (m_viewList.contains(view))
    {
        return;
    }

    m_viewList.append(view);

    QObject *view_obj = dynamic_cast<QObject*>(view);
    // Подключение к COM-порту
    QObject::connect(view_obj, SIGNAL(processConnect()), this, SLOT(processConnect()));
    // Изменение имени COM-порта
    QObject::connect(view_obj, SIGNAL(processNameComPortChanged(QString)), this, SLOT(processNameComPortChanged(QString)));
    // Изменение скорости подключения
    QObject::connect(view_obj, SIGNAL(processBaudratePortChanged(int)), this, SLOT(processBaudratePortChanged(int)));
    // Отправка команды в COM-порт
    QObject::connect(view_obj, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    // Отправка значения открытия в COM-порт
    QObject::connect(view_obj, SIGNAL(change_open_rate(int)), this, SLOT(change_open_rate(int)));
    // Отправка значения закрытия в COM-порт
    QObject::connect(view_obj, SIGNAL(change_close_rate(int)), this, SLOT(change_close_rate(int)));

    QObject::connect(view_obj,SIGNAL(set_gesture_for_1_hand_1_finger(finger)),this,SLOT(set_gesture_for_1_hand_1_finger(finger)));

    QObject::connect(view_obj,SIGNAL(processProgramParamsChanged(controler_data)),this,SLOT(processProgramParamsChanged(controler_data)));
    //QObject::connect(view_obj,SIGNAL(setProgramParams(long long int)),this,SLOT(getProgramParams()));
    refreshView(view);
    setPortInfo(view);
}
// Подключение к Com-порту
void PresenterComPort::processConnect()
{
    IViewComPort *view = dynamic_cast<IViewComPort*>(sender());
    m_model->setPortName(view->getPortName());
    m_model->setBaudrate(view->getBaudrate());
    m_model->setProgramParams(view->getProgramParams());

    m_model->connectToComPort();

    refreshView();
}

// Изменение имени COM-порта
void PresenterComPort::processNameComPortChanged(QString portName)
{
    if (portName != m_model->getPortName())
    {
        m_model->setPortName(portName);
        refreshView();
    }
}

// Изменение скорости COM-порта
void PresenterComPort::processBaudratePortChanged(int baudrate)
{
    if (baudrate != m_model->getBaudrate())
    {
        m_model->setBaudrate(baudrate);
        refreshView();
    }
}

void PresenterComPort::processProgramParamsChanged(controler_data value)
{
    static controler_data temp;
//    value.msgCurrent!=temp.msgCurrent||
//                value.msgLevelCH1!=temp.msgLevelCH1||
//                value.msgLevelCH2!=temp.msgLevelCH2||
//                value.msgBatteryTension!=temp.msgBatteryTension||
//                value.msgBlockIndication!=temp.msgBlockIndication||
//                value.msgRoughnessOfSensors!=temp.msgRoughnessOfSensors
    if (memcmp(&value,&temp,sizeof (controler_data))!=0)
    {
        temp=value;
    }
    else
    {
        refreshView();
        return;
    }
    //qDebug()<<"PresenterComPort::processProgramParamsChanged";
    //qDebug()<<m_model->getProgramParams();
    m_model->setProgramParams(value);
    refreshView();
}

void PresenterComPort::onCommand(QString command)
{
    m_model->onCommand(command);
}

void PresenterComPort::change_open_rate(int value)
{
    m_model->change_open_rate(value);
}

void PresenterComPort::set_gesture_for_1_hand_1_finger(finger value)
{
    m_model->set_gesture_for_1_hand_1_finger(value);
}


void PresenterComPort::change_close_rate(int value)
{
    m_model->change_close_rate(value);
}
void PresenterComPort::response(const QByteArray& msg)
{
    m_model->response(msg);
}


void PresenterComPort::error(QString errorMsg)
{
    // Отправляем на форму сообщение об ошибке
}

void PresenterComPort::timeout(QString timeoutMsg)
{
    // Отправляем на форму сообщение, что время ответа истекло
}

void PresenterComPort::refreshView() const
{
    // Пробегаем по списку и обновляем каждый вид
    for (QList<IViewComPort*>::const_iterator it = m_viewList.constBegin(); it != m_viewList.constEnd(); ++it)
    {
        refreshView(*it);
    }
}


void PresenterComPort::refreshView(IViewComPort *view) const
{
    view->setPortName(m_model->getPortName());
    view->setBaudrate(m_model->getBaudrate());
    view->ledOn(m_model->isConnect());
    m_model->readCommand();
    view->setProgramParams(m_model->getProgramParams());
    // Если подключены, блокируем возможность изменить настройки
    // и надпись на кнопке
    if (m_model->isConnect())
    {
        view->setEnablePortNameBox(false);
        view->setEnableBaudrateBox(false);
        view->setTitleButton("Disconnect");
    }
    else
    {
        view->setEnablePortNameBox(true);
        view->setEnableBaudrateBox(true);
        view->setTitleButton("Connect");
    }
}

void PresenterComPort::setPortInfo() const
{
    // Пробегаем по списку и в каждый вид добавляем информацию о портах
    for (QList<IViewComPort*>::const_iterator it = m_viewList.constBegin(); it != m_viewList.constEnd(); ++it)
    {
        setPortInfo(*it);
    }
}

void PresenterComPort::setPortInfo(IViewComPort *view) const
{
    // Список всех COM-портов в системе
    QList<QString> tempList = m_model->getListNamePorts();

    // Заносим на вид все COM-порты в системе
    for (int i = 0; i < tempList.count(); i++)
    {
        view->addPortName(tempList.at(i));
    }

    // Заносим на вид возможные скорости подключения
    view->addBaudrate(9600);
    view->addBaudrate(34800);
    view->addBaudrate(115200);
}
