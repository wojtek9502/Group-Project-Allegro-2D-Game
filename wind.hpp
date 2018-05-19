#ifndef WIND_HPP_INCLUDED
#define WIND_HPP_INCLUDED
#include <cstdlib>
#include <ctime>


using namespace std;
enum Wind_direction
{
    LEFT = 0,
    RIGHT = 1
};

class Wind{

public:
    float strength;
    Wind_direction direction;



void rand_wind(){
    float range_start = 10.0;
    float range_end = 30.0;
    float new_strenght = range_start + (rand() / ( RAND_MAX / (range_end-range_start) ) ) ;
    this->strength = new_strenght;
}



};

#endif // WIND_HPP_INCLUDED
