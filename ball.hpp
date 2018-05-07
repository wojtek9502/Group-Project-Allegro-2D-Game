#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED
#include<vector>
#include "math.h"
#define PI 3.14159265

using namespace std;


class Ball {
public:
    float ball_position_x;
    float ball_position_y;
    float damage;
    vector<float> ball_position_vector;
    int vector_index;
    float time = 1;
    float step = 0.1;
    Ball() { }

vector<float> calculate_ball_position(float Vo, float angle, float wind, float start_x, float start_y){
    float x;
    float y;
    float constant_wind = 10;
    float g = 9.80665;
    float e = 2.718281828459;
    float time = 1;
    float step = 0.1;
    float ball_x = start_x;
    float ball_y = start_y;
    vector<float> x_y_position;
    float position[200][2];
    int i=0;

    while(ball_y < 500){
        x = (Vo * cos(angle*PI/180) / constant_wind) * (1 - pow(e, -constant_wind*time));
        y = ((Vo * sin(angle*PI/180) / wind) + (g/wind) ) * (1 - pow(e, -wind*time)) - (g*time/wind);

        ball_x -= x*step;
        ball_y -= y*step;
        x_y_position.push_back(ball_x);
        x_y_position.push_back(ball_y);
        i++;
        time +=step;
    }

    return x_y_position;
}


void print_position_vector()
{
    for (std::vector<float>::const_iterator i = ball_position_vector.begin(); i != ball_position_vector.end(); ++i)
    std::cout << *i << endl;
}

};



#endif // BALL_HPP_INCLUDED
