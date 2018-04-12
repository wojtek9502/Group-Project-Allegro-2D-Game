#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#include<math.h>

using namespace std;
class Player{

public:
    string name;
    float x_position;
    float y_position;
    int hp;
    float x_arrow_start;
    float x_arrow_end;
    float y_arrow_start;
    float y_arrow_end;
    float arrow_angle;



    Player(string name, int x_position, int y_position, int hp=100, float arrow_angle=90)
    {
        this->name=name;
        this->x_position=x_position;
        this->y_position=y_position;
        this->hp=hp;
        this->x_arrow_start=x_position;
        this->x_arrow_end=x_position+50;
        this->y_arrow_start=y_position;
        this->y_arrow_end=y_position+50;
        this->arrow_angle=0.0;


    }

    void move_left(float pixels=1)
    {
        x_position = x_position-pixels;
    }

    void move_right(float pixels=1)
    {
        x_position = x_position+pixels;
    }

    void move_arrow(double angle, Player player)
    {
         //convert degrees to radians
         double radian_angle = conv_to_radian( arrow_angle + angle);


        //caltulate new arrow_end coordinates
        float x_arrow_end_prim = ( (x_arrow_end)*cos(radian_angle) ) - ( y_arrow_end*sin(radian_angle) );
        float y_arrow_end_prim = ( x_arrow_end*sin(radian_angle) ) + ( y_arrow_end*cos(radian_angle) );

        //set arrow position
        x_arrow_start = x_position;
        y_arrow_start = y_position;
        x_arrow_end = x_arrow_end_prim;
        y_arrow_end = y_arrow_end_prim;

        cout << "arrow_start=(" << x_arrow_start << ", " << y_arrow_start << ")" << endl;
        cout << "arrow_end=(" << x_arrow_end << ", " << y_arrow_end << ")" << endl;
        cout << "radian angle:" <<  arrow_angle+angle << endl;
        cout << "sin angle: " << sin(radian_angle) << endl;
        cout << "cos angle: " << cos(radian_angle) << endl;

    }

double conv_to_radian(double degree_angle)
{
    return degree_angle * (M_PI/180);
}

};


#endif // PLAYER_HPP_INCLUDED
