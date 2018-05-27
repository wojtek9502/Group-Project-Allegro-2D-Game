#ifndef TURN_HPP_INCLUDED
#define TURN_HPP_INCLUDED
#include "wind.hpp"

using namespace std;

enum Turn_enum
{
    DOG_TURN = 0,
    CAT_TURN = 1
};

class Turn {
public:
     Turn_enum whose_turn;
     string whose_turn_text;

public:
    Turn()
    {
        whose_turn = DOG_TURN;
        whose_turn_text = "Tura Psa";

    }


    /**
     * zmien ture i wylosuj wiatr
     *
     * @param keyboard
     * @param ev
     * @param wind
     */
    void check_change_turn(ALLEGRO_KEYBOARD_STATE keyboard, ALLEGRO_EVENT ev, Wind &wind) // zmiana turny jesli byla tura psa to zmien na ture kota itd
    {
        if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) // jesli nacisnie spacje
        {
                 switch(whose_turn)
                {
                    case DOG_TURN:
                        {

                            whose_turn = CAT_TURN;
                            whose_turn_text = "Tura Kota";
                            break;
                        }
                    case CAT_TURN:
                        {
                            //wind.rand_wind();
                            whose_turn = DOG_TURN;
                            whose_turn_text = "Tura Psa";
                            break;
                        }
                }

                //wylosuj nowa wartosc wiatru (funkcja jest w pliku wind.hpp)
              //  wind.rand_wind();

        }
    }

};


#endif // TURN_HPP_INCLUDED
