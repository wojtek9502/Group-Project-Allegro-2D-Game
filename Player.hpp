#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
class Player{

public:
    int x_position;
    int y_position;
    int hp;


    Player(int x_position, int y_position, int hp=100)
    {
        this->x_position=x_position;
        this->y_position=y_position;
        this->hp=hp;
    }

    void move_left(int pixels=1)
    {
        x_position = x_position-pixels;
    }

    void move_right(int pixels=1)
    {
        x_position = x_position+pixels;
    }

};


#endif // PLAYER_HPP_INCLUDED
