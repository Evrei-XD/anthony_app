#ifndef GESTURES_H
#define GESTURES_H

#include "UsedStructs.h"
#include <QVector>

class Gestures
{
public:
    Gestures();
    ~Gestures();
    void set_all_gestures(finger *vec_value);

    void set_one_gesture(finger value);
    void set_one_gesture(short int numberFinger, short int intValueFingerSpeed, short int intValueFingerAngle,short int NUMBER_CELL);

    finger* get_all_gestures();

    short int get_one_gesture_speed(short int numberFinger);
    short int get_one_gesture_angle(short int numberFinger);
    short int get_one_gesture_NUMBER_CELL(short int numberFinger);
    finger get_one_gesture(short int numberFinger);

private:
    finger *my_hand;

};

#endif // GESTURES_H
