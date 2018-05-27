#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED
#include<vector>
#include "math.h"
#define PI 3.14159265

using namespace std;


/**
 * Klasa piłki
 */
class Ball {
public:
    float ball_position_x;
    float ball_position_y;
    float damage;
    int vector_index;
    bool life;
    float time = 1;
    float step = 0.1;


};



#endif // BALL_HPP_INCLUDED
