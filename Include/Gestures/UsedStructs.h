#ifndef USEDSTRUCTS_H
#define USEDSTRUCTS_H

struct finger
{
    short int NUMBER_CELL;
    short int numberFinger;
    short int intValueFingerSpeed;
    short int intValueFingerAngle;
};


struct controler_data{
        long int msgRoughnessOfSensors;
        long long int msgCurrent;
        long long int msgLevelCH1;
        long long int msgLevelCH2;
        long long int msgLevelCH1graph;
        long long int msgLevelCH2graph;
        long int msgBatteryTension;
        int msgBlockIndication;
};
#endif // USEDSTRUCTS_H
