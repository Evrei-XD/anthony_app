#include "ModelComPort.h"
#include "Commands.h"

#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>

ModelComPort::ModelComPort() :
    m_portName(""),
    m_baudrate(QSerialPort::Baud9600),
    m_dataBits(QSerialPort::Data8),
    m_parity(QSerialPort::NoParity),
    m_stopBits(QSerialPort::OneStop),
    m_flowControl(QSerialPort::NoFlowControl),
    m_connected(false)
{
    thread = ComPortThread::getInstance();

    last_finger=1;
    open_rate=0;
    close_rate=0;
    flag_changed=false;

    controler_input.msgCurrent=0;
    controler_input.msgLevelCH1=1000;
    controler_input.msgLevelCH2=1000;
    controler_input.msgBatteryTension=0;
    controler_input.msgRoughnessOfSensors=0;
    m_usedGest=new Gestures;

    searchComPorts();
}

ModelComPort::~ModelComPort()
{
    qDebug("~ModelComPort()");
    if (thread)
    {
        thread->free();
        thread = 0;
    }
}

void ModelComPort::connectToComPort()
{
    if (!m_connected)
    {
        if (m_portName == "")
        {
            return;
        }

        if (!thread->isRunning())
        {
            thread->connectCom(m_portName, m_baudrate, m_dataBits, m_dataBits, m_stopBits, m_flowControl);
            thread->wait(500);

            // В случае успешного подключения
            if (thread->isConnect())
            {
                m_connected = true;
            }
        }
    }
    else
    {
        if (thread->isConnect())
        {
            thread->disconnectCom();
        }
        m_connected = false;
    }
}

void ModelComPort::setPortName(QString portName)
{
    m_portName = portName;
}

QString ModelComPort::getPortName() const
{
    return m_portName;
}

void ModelComPort::setBaudrate(int baudrate)
{
    m_baudrate = baudrate;
}

int ModelComPort::getBaudrate() const
{
    return m_baudrate;
}

controler_data ModelComPort::getProgramParams()
{
    //qDebug()<<"ModelComPort::getProgramParams";
    return controler_input;
}

void ModelComPort::setProgramParams(controler_data value)
{
    //qDebug()<<"ModelComPort::setProgramParams";
    controler_input=value;
}

bool ModelComPort::isConnect() const
{
    return m_connected;
}

void ModelComPort::onCommand(QString command)
{
    if (command == "ADDR_MIO2")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(ADDR_MIO2,2,16)));
    }
    else if (command == "READ")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(READ,2,16)));
    }
    else if (command == "WRITE")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
    }
    else if (command == "OPENING")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(OPENING,2,16)));
    }
    else if (command == "CLOSING")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(CLOSING,2,16)));
    }
    else if (command == "NOP")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(NOP,2,16)));
    }
    else if (command == "ENDPOINT_POSITION")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(ENDPOINT_POSITION,2,16)));
    }
    else if (command == "HDLC_ADDRESS_REG")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(HDLC_ADDRESS_REG,2,16)));
    }
    else if (command == "MOVE_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(MOVE_HDLC,2,16)));
    }
    else if (command == "HDLC_39")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(HDLC_39,2,16)));
    }
    else if (command == "MOTOR_REVERS")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(MOTOR_REVERS,2,16)));
    }
    else if (command == "MIO1_TRIG_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(MIO1_TRIG_HDLC,2,16)));
    }
    else if (command == "MIO2_TRIG_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(MIO2_TRIG_HDLC,2,16)));
    }
    else if (command == "CURR_LIMIT_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(CURR_LIMIT_HDLC,2,16)));
    }
    else if (command == "CURR_MAIN_DATA_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(CURR_MAIN_DATA_HDLC,2,16)));
    }
    else if (command == "TRIG_MODE_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(TRIG_MODE_HDLC,2,16)));
    }
    else if (command == "HAND_ON_OFF_REG")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(HAND_ON_OFF_REG,2,16)));
    }
    else if (command == "HAND_MOTIONS_CNT_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(HAND_MOTIONS_CNT_HDLC,2,16)));
    }
    else if (command == "ADC_BUFF_CHOISES_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(ADC_BUFF_CHOISES_HDLC,2,16)));
    }
    else if (command == "BLOCK_ON_OFF_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(BLOCK_ON_OFF_HDLC,2,16)));
    }
    else if (command == "BLOCK_PERMISSION_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(BLOCK_PERMISSION_HDLC,2,16)));
    }
    else if (command == "INVERT_INDICATION")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(INVERT_INDICATION,2,16)));
    }
    else if (command == "CURR_BAT_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(CURR_BAT_HDLC,2,16)));
    }
    else if (command == "ADC_SOURCE_HDLC")
    {
        sendCommand(QByteArray::fromHex(changing_the_number_system(ADC_SOURCE_HDLC,2,16)));
    }
    else if(command=="STOP")
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_ENDPOINT_POSITION,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(ENDPOINT_POSITION,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
    else if (command == "OPEN")
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_BRODCAST,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MOVE_HDLC,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(4,10,16)));//0 2 4
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
    else if (command == "CLOSE")
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_BRODCAST,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MOVE_HDLC,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(4,10,16)));//1 3 5
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
    else if (command == "SEND_OPEN")//ОТПРАВКА ЗНАЧЕНИЯ
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_MIO1,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MIO1_TRIG_HDLC,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(open_rate& 0xFF,10,16)));//младший байт
        temp.append(QByteArray::fromHex(changing_the_number_system(open_rate>> 8,10,16)));//старший байт
        //DANGER
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
    else if (command == "SEND_CLOSE")//ОТПРАВКА ЗНАЧЕНИЯ
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_MIO1,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(WRITE,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MIO1_TRIG_HDLC,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(close_rate& 0xFF,10,16)));//младший байт
        temp.append(QByteArray::fromHex(changing_the_number_system(close_rate>> 8,10,16)));//старший байт
        //DANGER
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
    else if (command == "SEND_FEATURES")//ОТПРАВКА ЗНАЧЕНИЙ С ПАЛЬЦЕВ
    {
        finger temp_feature=m_usedGest->get_one_gesture(last_finger);
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.numberFinger,10,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(requestType,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(GESTURE_SETTINGS,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.NUMBER_CELL,10,16)));//младший байт
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.intValueFingerSpeed& 0xFF,10,16)));//младший байт
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.intValueFingerAngle& 0xFF,10,16)));//младший байт
        temp.append(crc(temp.data(),temp.length()));
        qDebug()<<temp;
//        qDebug()<<"intValueFingerAngle"<<temp_feature.intValueFingerAngle;
//        qDebug()<<"intValueFingerSpeed"<<temp_feature.intValueFingerSpeed;
//        qDebug()<<"numberFinger"<<temp_feature.numberFinger;
//        qDebug()<<"NUMBER_CELL"<<temp_feature.NUMBER_CELL;
        sendCommand(temp);
    }
    else if (command == "SEND_MOVE")//ОТПРАВКА ЗНАЧЕНИЙ С ПАЛЬЦЕВ
    {
        finger temp_feature=m_usedGest->get_one_gesture(last_finger);
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.numberFinger,10,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(requestType,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MOVE_HDLC,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(temp_feature.NUMBER_CELL,10,16)));//младший байт
        temp.append(crc(temp.data(),temp.length()));
        qDebug()<<temp;
//        qDebug()<<"intValueFingerAngle"<<temp_feature.intValueFingerAngle;
//        qDebug()<<"intValueFingerSpeed"<<temp_feature.intValueFingerSpeed;
//        qDebug()<<"numberFinger"<<temp_feature.numberFinger;
//        qDebug()<<"NUMBER_CELL"<<temp_feature.NUMBER_CELL;
        sendCommand(temp);
    }
    else if (command == "TEST")//ОТПРАВКА ЗНАЧЕНИЙ С ПАЛЬЦЕВ
    {
        QByteArray temp;
        temp.append(QByteArray::fromHex(changing_the_number_system(ADDR_CUR_LIMIT,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(READ,2,16)));
        temp.append(QByteArray::fromHex(changing_the_number_system(MIO1_TRIG_HDLC,2,16)));
        qDebug()<<temp;
        temp.append(crc(temp.data(),temp.length()));
        sendCommand(temp);
    }
}


QByteArray ModelComPort::changing_the_number_system(long long int command,int system_begin,int system_end)
{
    bool ok;
    return(QByteArray::number(QByteArray::number(command).toLongLong(&ok, system_begin),system_end));
}

void ModelComPort::change_open_rate(int value)
{
    //qDebug()<<"Open_rate"<<value;
    open_rate=value;
}

void ModelComPort::change_close_rate(int value)
{
    //qDebug()<<"Close_rate"<<value;
    close_rate=value;
}

void ModelComPort::set_gesture_for_1_hand_1_finger(finger value)
{
    //qDebug()<<"intValueFingerAngle"<<value.intValueFingerAngle;
    //qDebug()<<"intValueFingerSpeed"<<value.intValueFingerSpeed;
    //qDebug()<<"numberFinger"<<value.numberFinger;
    //qDebug()<<"NUMBER_CELL"<<value.NUMBER_CELL;
    //qDebug()<<"ЗДАРОВА";
    last_finger=value.numberFinger;
    m_usedGest->set_one_gesture(value);
}

char ModelComPort::crc(char *pcBlock, int len)
{
    unsigned char crc = 0xFF;
    unsigned int i;
    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
    return crc;
}

void ModelComPort::response(QByteArray msg)
{
    qDebug()<<"MESSAGE ARRIVED";
    // Разбор пришедшего пакета
    QVector<int> digit;
    unsigned int i=0;
    int addressHDLCMassage=0;
    int msgRegister=0;
    int typeHDLCMassage=0;
    QByteArray byteMassCRC;
    long long int lowByte=0;
    long long int msgLevelCH1=0;
    long long int msgLevelCH2=0;
    long long int msgLevelCH1graph=0;
    long long int msgLevelCH2graph=0;
    int msgCRC=0;
    long long int msgCurrent=0;
    int msgBlockIndication=0;
    int msgRoughnessOfSensors=0;
    int msgBatteryTension=0;

    //    unsigned long long int a=11111111;
    //    qDebug()<<(a>>8);
    //    qDebug()<<(a<<8);
    //    qDebug()<<a*100000000;
    char *temp;

    for (unsigned int j=0;j<msg.length();j++)
    {
        digit.append(changing_the_number_system(QChar::fromLatin1(msg.at(j)).unicode(),10,2).toLong());
        qDebug()<<"msg="<<digit.at(j)<<"byte="<<j;
        //qDebug()<<(QByteArray::fromHex(changing_the_number_system(digit.at(j),2,16)));
    }
    /*temp=QByteArray::fromHex(changing_the_number_system(digit.at(0),2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
    qDebug()<<*temp;*/
    /* for(unsigned int j=0;j<digit.length();j++)
    {
        msg.append(QByteArray::fromHex(changing_the_number_system(digit.at(j),2,16)));
        qDebug()<<"msg="<<msg.at(j)<<"byte="<<j;
    }*/
    while(i<msg.length()){
        qDebug()<<i;
        if(i == 0){
            addressHDLCMassage = digit.at(i);
            qDebug()<<"BLUETOOTH--------------> i= "<<i<<"  msg= "<<digit.at(i);
            //                                parserCallback.setFlagReceptionExpectation(false);
            //                                startdumpingIVariableThread();
        }
        if(i == 1){
            qDebug()<<"BLUETOOTH--------------> i= "<<i<<"  msgRegister= "<<digit.at(i);
            msgRegister = digit.at(i);
        }
        if(i == 2){
            qDebug()<<"BLUETOOTH--------------> i= "<<i<<"  typeHDLCMassage= "<<digit.at(i);
            typeHDLCMassage = digit.at(i);
        }
        if(i == 3){ }
        if(i == 4){ addressHDLCMassage = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
        switch (msgRegister){
        case Commands::WRITE:
            switch (typeHDLCMassage){
            case Commands::MOVE_HDLC:
                qDebug()<<("BLUETOOTH--------------> WRITE -> MOVE_HDLC");
                i++;
                if(i == 9){
                    qDebug()<<("BLUETOOTH--------------> WRITE -> MOVE_HDLC -> resetAllVariables");
                    break;//Тут был resetAllVariables();
                }
                break;
            case Commands::HDLC_39:
                qDebug()<<("BLUETOOTH--------------> WRITE -> HDLC_39");
                i++;
                if(i == 5){
                    qDebug()<<("BLUETOOTH--------------> WRITE -> HDLC_39 -> resetAllVariables");
                    break;//Тут был resetAllVariables();
                }
                break;
            default:
                qDebug()<<("BLUETOOTH--------------> WRITE -> DEFAULT");
                i++;
                if(i == 5){
                    qDebug()<<("BLUETOOTH--------------> WRITE -> resetAllVariables");
                    break;//Тут был resetAllVariables();
                }
                break;

            }
            break;
        case Commands::READ:
            switch (typeHDLCMassage){
            case Commands::ENDPOINT_POSITION:
                qDebug()<<("BLUETOOTH--------------> READ -> ENDPOINT_POSITION");
                i++;
                if(i == 5){
                    qDebug()<<("BLUETOOTH--------------> READ -> ENDPOINT_POSITION -> resetAllVariables");
                    break;//Тут был resetAllVariables();
                }
                break;
            case Commands::MIO1_TRIG_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> MIO1_TRIG_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ lowByte = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 6){ msgLevelCH1 = lowByte*100000000 + digit.at(i);  byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 7){
                        msgCRC = digit.at(i);
                        qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                        qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<changing_the_number_system(QChar::fromLatin1(crc(byteMassCRC.data(), 3)).unicode(),10,2).toLong();
                    }//обработчик CRC
                }
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),3)){

                    //qDebug()<<"msgLevelCH1"<<msgLevelCH1;
                    qDebug()<<"msgLevelCH1"<<QByteArray::number(msgLevelCH1).toLongLong(nullptr, 2);
                    controler_input.msgLevelCH1=QByteArray::number(msgLevelCH1).toLongLong(nullptr, 2);
                    /*final Integer msgLevelCH1f = msgLevelCH1;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersTrigCH1(msgLevelCH1f);
                                         parserCallback.setStartParametersInChartActivity();
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ TRIG1 START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::MIO2_TRIG_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> MIO2_TRIG_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ lowByte = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 6){ msgLevelCH2 = lowByte*100000000 + digit.at(i);  byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 7){
                        msgCRC = digit.at(i);
                        qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                        qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<crc(byteMassCRC.data(), 3);
                    }//обработчик CRC
                }
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),3)){
                    //qDebug()<<"msgLevelCH2"<<msgLevelCH2;
                    qDebug()<<"msgLevelCH2"<<QByteArray::number(msgLevelCH2).toLongLong(nullptr, 2);
                    controler_input.msgLevelCH2=QByteArray::number(msgLevelCH2).toLongLong(nullptr, 2);
                    /*  final Integer msgLevelCH2f = msgLevelCH2;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersTrigCH2(msgLevelCH2f);
                                         parserCallback.setStartParametersInChartActivity();
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ TRIG2 START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::CURR_LIMIT_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> CURR_LIMIT_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ lowByte = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 6){ msgCurrent = lowByte*100000000 + digit.at(i);  byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 7){
                        msgCRC = digit.at(i);
                        qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                        qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<crc(byteMassCRC.data(), 3);
                    }//обработчик CRC
                }
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),3)) {
                    //qDebug()<<"msgCurrent"<<msgCurrent;
                    qDebug()<<"msgCurrent"<<QByteArray::number(msgCurrent).toLongLong(nullptr, 2);
                    controler_input.msgCurrent=QByteArray::number(msgCurrent).toLongLong(nullptr, 2);
                    /*final Integer msgCurrentf = msgCurrent;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersCurrrent(msgCurrentf);
                                         parserCallback.setStartParametersInChartActivity();
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ CURRENT START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::CURR_BAT_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> CURR_BAT_HDLC");
                if(i == 5){ msgBatteryTension = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16)));}
                if(i == 6){
                    msgCRC = digit.at(i);
                    qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                    qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<crc(byteMassCRC.data(), 2);
                }//обработчик CRC
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),2)) {
                    //qDebug()<<"msgBatteryTension"<<msgBatteryTension;
                    qDebug()<<"msgBatteryTension"<<QByteArray::number(msgBatteryTension).toLongLong(nullptr, 2);
                    controler_input.msgBatteryTension=QByteArray::number(msgBatteryTension).toLongLong(nullptr, 2);
                    /*final Integer msgBatteryTensionf = msgBatteryTension;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersBattery(msgBatteryTensionf);
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ BATTERY START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::BLOCK_PERMISSION_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> BLOCK_PERMISSION_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ msgBlockIndication = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16)));}
                    if(i == 6){
                        msgCRC = digit.at(i);
                        qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                        qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<crc(byteMassCRC.data(), 2);
                    }//обработчик CRC
                }
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),2)) {
                    //qDebug()<<"msgBlockIndication"<<msgBlockIndication;
                    qDebug()<<"msgBlockIndication"<<QByteArray::number(msgBlockIndication).toLongLong(nullptr, 2);
                    controler_input.msgBlockIndication=QByteArray::number(msgBlockIndication).toLongLong(nullptr, 2);
                    /*final Byte msgBlockIndicationf = msgBlockIndication;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersBlock(msgBlockIndicationf);
                                         parserCallback.setStartParametersInChartActivity();
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ BLOCK START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::ADC_BUFF_CHOISES_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> ADC_BUFF_CHOISES_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ msgRoughnessOfSensors = digit.at(i);}
                    if(i == 6){}//обработчик CRC
                }
                i++;
                if(i == 7) {
                    //qDebug()<<"msgRoughnessOfSensors"<<msgRoughnessOfSensors;
                    qDebug()<<"msgRoughnessOfSensors"<<QByteArray::number(msgRoughnessOfSensors).toLongLong(nullptr, 2);
                    controler_input.msgRoughnessOfSensors=QByteArray::number(msgRoughnessOfSensors).toLongLong(nullptr, 2);
                    /* final Byte msgRoughnessOfSensorsf = msgRoughnessOfSensors;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         parserCallback.givsStartParametersRoughness (msgRoughnessOfSensorsf);
                                         parserCallback.setStartParametersInChartActivity();
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ ROUGHNESS START PARAMETER ");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            case Commands::CURR_MAIN_DATA_HDLC:
                qDebug()<<("BLUETOOTH--------------> READ -> CURR_MAIN_DATA_HDLC");
                if(addressHDLCMassage == 11111010){
                    if(i == 5){ lowByte = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 6){ msgLevelCH1graph = lowByte*100000000 + digit.at(i);  byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 7){ lowByte = digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16))); }
                    if(i == 8){ msgLevelCH2graph = lowByte*100000000 + digit.at(i); byteMassCRC.append(QByteArray::fromHex(changing_the_number_system(digit.at(i),2,16)));}
                    //                                            if(i == 9){ lowByte = msg; }
                    //                                            if(i == 10){ msgCurrent = lowByte + msg; }
                    if(i == 9){
                        msgCRC = digit.at(i);
                        qDebug()<<"BLUETOOTH--------------> принятая CRC= "<<msgCRC;
                        qDebug()<<"BLUETOOTH--------------> посчитанная CRC= "<<crc(byteMassCRC.data(), 5);
                    }
                }
                i++;
                temp=QByteArray::fromHex(changing_the_number_system(msgCRC,2,16)).data();//НЕПОНЯТНАЯ ХЕРНЯ
                qDebug()<<temp;
                if(*temp == crc(byteMassCRC.data(),5)){
//                    qDebug()<<"msgRoughnessOfSensors"<<msgRoughnessOfSensors;
//                    qDebug()<<"msgCurrent"<<msgCurrent;
//                    qDebug()<<"msgLevelCH1"<<msgLevelCH1;
//                    qDebug()<<"msgLevelCH2"<<msgLevelCH2;
//                    qDebug()<<"msgBatteryTension"<<msgBatteryTension;
                    qDebug()<<"msgRoughnessOfSensors"<<QByteArray::number(msgRoughnessOfSensors).toLongLong(nullptr, 2);
                    qDebug()<<"msgCurrent"<<QByteArray::number(msgCurrent).toLongLong(nullptr, 2);
                    qDebug()<<"msgLevelCH1graph"<<QByteArray::number(msgLevelCH1).toLongLong(nullptr, 2);
                    qDebug()<<"msgLevelCH2graph"<<QByteArray::number(msgLevelCH2).toLongLong(nullptr, 2);
                    qDebug()<<"msgBatteryTension"<<QByteArray::number(msgBatteryTension).toLongLong(nullptr, 2);
                    qDebug()<<"msgBlockIndication"<<QByteArray::number(msgBlockIndication).toLongLong(nullptr, 2);

                    controler_input.msgRoughnessOfSensors=QByteArray::number(msgRoughnessOfSensors).toLongLong(nullptr, 2);
                    controler_input.msgCurrent=QByteArray::number(msgCurrent).toLongLong(nullptr, 2);
                    controler_input.msgLevelCH1graph=QByteArray::number(msgLevelCH1).toLongLong(nullptr, 2);
                    controler_input.msgLevelCH2graph=QByteArray::number(msgLevelCH2).toLongLong(nullptr, 2);
                    controler_input.msgBatteryTension=QByteArray::number(msgBatteryTension).toLongLong(nullptr, 2);
                    controler_input.msgBlockIndication=QByteArray::number(msgBlockIndication).toLongLong(nullptr, 2);
                    /*final String msgCopy = String.valueOf(msgstr);
                final Integer msgCurrentf = msgCurrent;
                final Integer msgLevelCH1f = msgLevelCH1;
                final Integer msgLevelCH2f = msgLevelCH2;
                final Byte msgIndicationStatef = msgIndicationState;
                final Integer msgBatteryTensionf = msgBatteryTension;
                ThreadHelper.run(runOnUi, activity, new Runnable() {
                                     @Override
                                     public void run() {
                                         //                                                qDebug()<<("BLUETOOTH--------------> receive");
                                         parserCallback.givsGeneralParcel(msgCurrentf, msgLevelCH1f, msgLevelCH2f, msgIndicationStatef, msgBatteryTensionf);
                                         deviceCallback.onMessage(msgCopy);
                                         if (DEBUG) {qDebug()<<("<-- сделал цикл по ветке 2:"+ msgCopy +" no_error="+no_error);}
                                         //                                                            qDebug()<<("BLUETOOTH--------------> READ -> CURR_MAIN_DATA_HDLC -> resetAllVariables");
                                         break;//Тут был resetAllVariables();
                                     }
                                 });*/
                }
                break;
            }
            break;
        default:
            qDebug()<<("BLUETOOTH--------------> DEFAULT");
            i++;
            break;
        }
    }
}

QList<QString> ModelComPort::getListNamePorts() const
{
    return m_listPorts;
}

void ModelComPort::searchComPorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        m_listPorts.append(info.portName());
    }
}

void ModelComPort::readCommand()
{
    thread->readupdate(300);
}

void ModelComPort::sendCommand(QByteArray command)
{
    //    QByteArray buffer;
    //    quint8 checkSumm = 0;

    //    buffer[0] = '#';
    //    buffer[1] = '<';
    //    buffer[2] = 0;
    //    checkSumm ^= buffer[3];
    //    QString temp;
    //    temp.setNum(command);
    //    qDebug()<<temp.toLocal8Bit();
    //    //buffer[3] = temp.toLocal8Bit();
    //    checkSumm ^= buffer[4];
    //    buffer[4] = checkSumm;

    thread->transaction(command, 300);
}

