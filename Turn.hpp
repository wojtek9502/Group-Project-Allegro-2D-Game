#ifndef TURN_HPP_INCLUDED
#define TURN_HPP_INCLUDED

using namespace std;

enum Turn_enum
{
    DOG_TURN = 0,
    CAT_TURN = 1
};

class Turn {
public:
     Turn_enum whose_turn;

public:
    Turn()
    {
        whose_turn = DOG_TURN;
    }

    void check_change_turn(ALLEGRO_KEYBOARD_STATE keyboard) // zmiana turny jesli byla tura psa to zmien na ture kota itd
    {
        if(al_key_down(&keyboard, ALLEGRO_KEY_SPACE))
        {
             switch(whose_turn)
            {
                case DOG_TURN:
                    {
                        whose_turn = CAT_TURN;
                        break;
                    }
                case CAT_TURN:
                    {
                        whose_turn = DOG_TURN;
                        break;
                    }
            }
           cout << "Zmiana tury, teraz tura: " << whose_turn << endl;
        }


    }

};


#endif // TURN_HPP_INCLUDED
