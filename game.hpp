#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "player.hpp"
#include "math.h"
#include "Turn.hpp"
#include "Ball.hpp"
#include <sstream>
#define PI 3.14159265
using namespace std;

bool run_menu_start(ALLEGRO_MOUSE_STATE mouse, ALLEGRO_DISPLAY* display, ALLEGRO_MOUSE_CURSOR* cursor, bool end_menu_start)
{
     if((mouse.x >=278 && mouse.x <=500) && (mouse.y >= 190 && mouse.y <=215))
        {

            printf("one player: (%d, %d)\n", mouse.x, mouse.y);
            al_set_mouse_cursor(display, cursor);
            al_rest(0.1);
            if(mouse.buttons & 1){
                cout<<"clicked one player: x:"<<mouse.x<<"y: "<<mouse.y<<endl;
                end_menu_start = true;
            }
        }

        if((mouse.x >=275 && mouse.x <=510) && (mouse.y >=240 && mouse.y <=281))
        {
            printf("two player: (%d, %d)\n", mouse.x, mouse.y);
            al_set_mouse_cursor(display, cursor);
            al_rest(0.1);
            if(mouse.buttons & 1){
                cout<<"clicked one player: x:"<<mouse.x<<"y: "<<mouse.y<<endl;
                end_menu_start = true;
            }
        }

    return end_menu_start;
}

Player check_dog_move(ALLEGRO_KEYBOARD_STATE keyboard, Player dog, int screen_width, int dog_width, Turn turn){

    if(turn.whose_turn == DOG_TURN)
    {
        if(al_key_down(&keyboard, ALLEGRO_KEY_A))
        {
          if(dog.x_position>0+5)
                dog.move_left();
                dog.move_arrow(0, dog);
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_D))
        {
            if( dog.x_position < (screen_width/2-dog_width-20))
                dog.move_right();
                dog.move_arrow(0, dog);
        }

         //arrow move
        if(al_key_down(&keyboard, ALLEGRO_KEY_W))
        {
                dog.move_arrow(1, dog);
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_S))
        {
                dog.move_arrow(-1, dog);
        }

    }
     return dog;
}

Player check_cat_move(ALLEGRO_KEYBOARD_STATE keyboard, Player cat, int screen_width, int cat_width, Turn turn)
{
    if(turn.whose_turn == CAT_TURN)
    {
        if(al_key_down(&keyboard, ALLEGRO_KEY_LEFT))
        {
            if((cat.x_position > screen_width/2+30))
                cat.move_left();
                cat.move_arrow(0, cat);
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))
        {
            if( cat.x_position < (screen_width-cat_width-5) )
                cat.move_right();
                cat.move_arrow(0, cat);
        }

        //arrow move
        if(al_key_down(&keyboard, ALLEGRO_KEY_UP))
        {
                cat.move_arrow(-1, cat);
        }

        if(al_key_down(&keyboard, ALLEGRO_KEY_DOWN))
        {
                cat.move_arrow(1, cat);
        }
    }
    return cat;
}
Player check_hp_dog(Player dog, int x, int y, int dWidth, int dHeight)
{

    if((dog.x_position + dWidth) > x && dog.x_position < x &&  (dog.y_position + dHeight) > y && dog.y_position < y)
    {
        dog.hp=dog.hp - 10;
        if(dog.hp<0)
        {
            dog.hp=0;
        }
        cout<<"dog hp: " << dog.hp<<endl;
    }
    return dog;
}
Player check_hp_cat(Player cat, int x, int y, int cWidth, int cHeight)
{

    if((cat.x_position + cWidth) > x && cat.x_position < x &&  (cat.y_position + cHeight) > y && cat.y_position < y)
    {
        cat.hp=cat.hp - 10;
        if(cat.hp<0)
        {
            cat.hp=0;
        }
        cout<<"cat hp: " << cat.hp<<endl;

    }
    return cat;
}

string prepate_hp_text(int hp)
{
    ostringstream output;
    output << "HP " << hp ;
    return output.str();
}

void check_end_game(Player dog, Player cat, ALLEGRO_FONT font_title_size_obj[])
{
    //wygrana psa
    if(cat.hp <= 0){
        al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), 800/2, 80, ALLEGRO_ALIGN_CENTRE, "Wygrał Pies");
    }

    if(dog.hp <= 0){
        al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), 800/2, 80, ALLEGRO_ALIGN_CENTRE, "Wygrał Kot");
    }
}



#endif // GAME_HPP_INCLUDED
