#include "Gestures.h"

Gestures::Gestures()
{
    my_hand=new finger [6];
    for(int i=0;i<6;i++)
    {
        my_hand[i].numberFinger=i+1;
        my_hand[i].intValueFingerAngle=0;
        my_hand[i].intValueFingerSpeed=0;
        my_hand[i].NUMBER_CELL=i;
    }
}

void Gestures::set_one_gesture(finger value)
{
    my_hand[value.numberFinger]=value;
}

void Gestures::set_one_gesture(short numberFinger, short intValueFingerSpeed, short intValueFingerAngle,short int NUMBER_CELL)
{
    my_hand[numberFinger].intValueFingerAngle=intValueFingerAngle;
    my_hand[numberFinger].intValueFingerSpeed=intValueFingerSpeed;
    my_hand[numberFinger].NUMBER_CELL=NUMBER_CELL;
    my_hand[numberFinger].numberFinger=numberFinger;
}

void Gestures::set_all_gestures(finger *vec_value)
{
    my_hand=vec_value;
}

finger Gestures::get_one_gesture(short numberFinger)
{
    return my_hand[numberFinger];
}

short int Gestures::get_one_gesture_angle(short numberFinger)
{
    return my_hand[numberFinger].intValueFingerAngle;
}

short int Gestures::get_one_gesture_speed(short numberFinger)
{
    return my_hand[numberFinger].intValueFingerSpeed;
}

short int Gestures::get_one_gesture_NUMBER_CELL(short numberFinger)
{
    return my_hand[numberFinger].NUMBER_CELL;
}

finger* Gestures::get_all_gestures()
{
    return my_hand;
}


Gestures::~Gestures()
{

}
