#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

using namespace std;
class Player{

public:
    string name;
    float x_position;
    float y_position;
    int hp;


    Player(string name, int x_position, int y_position, int hp=100)
    {
        this->name=name;
        this->x_position=x_position;
        this->y_position=y_position;
        this->hp=hp;
    }

    void move_left(float pixels=0.05)
    {
        x_position = x_position-pixels;
    }

    void move_right(float pixels=0.05)
    {
        x_position = x_position+pixels;
    }



};


#endif // PLAYER_HPP_INCLUDED
