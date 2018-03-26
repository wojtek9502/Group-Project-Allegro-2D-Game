#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "player.hpp"
#include <math.h>
using namespace std;

bool run_menu_start(ALLEGRO_MOUSE_STATE mouse, ALLEGRO_DISPLAY* display, ALLEGRO_MOUSE_CURSOR* cursor, bool end_menu_start)
{

     if((mouse.x >=300 && mouse.x <=500) && (mouse.y >= 150 && mouse.y <=201))
        {

            printf("one player: (%d, %d)\n", mouse.x, mouse.y);
            al_set_mouse_cursor(display, cursor);
            al_rest(0.1);
            if(mouse.buttons & 1){
                cout<<"clicked one player: x:"<<mouse.x<<"y: "<<mouse.y<<endl;
                end_menu_start = true;
            }
        }

        if((mouse.x >=300 && mouse.x <=500) && (mouse.y >=230 && mouse.y <=281))
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

Player check_dog_move(ALLEGRO_KEYBOARD_STATE keyboard, Player dog, int screen_width, int dog_width){

    if(al_key_down(&keyboard, ALLEGRO_KEY_A))
    {
      if(dog.x_position>0+5)
            dog.move_left();
    }

    if(al_key_down(&keyboard, ALLEGRO_KEY_D))
    {
        if( dog.x_position < (screen_width/2-dog_width-20))
            dog.move_right();
    }

    return dog;
}

Player check_cat_move(ALLEGRO_KEYBOARD_STATE keyboard, Player cat, int screen_width, int cat_width)
{
 if(al_key_down(&keyboard, ALLEGRO_KEY_J))
    {
        if((cat.x_position > screen_width/2+30))
            cat.move_left();
    }

    if(al_key_down(&keyboard, ALLEGRO_KEY_L))
    {
        if( cat.x_position < (screen_width-cat_width-5) )
            cat.move_right();
    }
    return cat;
}
Player check_hp_dog(Player dog, int x, int y, int dWidth, int dHeight)
{

    if((dog.x_position + dWidth) > x && dog.x_position < x &&  (dog.y_position + dHeight) > y && dog.y_position < y)
    {
        if(dog.hp!=10){
        dog.hp=dog.hp - 10;
        cout<<"dodano"<<endl;
    }
    }
    return dog;
}
Player check_hp_cat(Player cat, int x, int y, int cWidth, int cHeight)
{

    if((cat.x_position + cWidth) > x && cat.x_position < x &&  (cat.y_position + cHeight) > y && cat.y_position < y)
    {
        if(cat.hp!=0){
        cat.hp=cat.hp - 10;
        cout<<"dodano"<<endl;
    }
    }
    return cat;
}
bool dog_allowed_x_position(Player dog)
{

}

void ball_move(float wind_strength, float star_x, float start_y, float start_V){
    ///wind_strength   ------ 0 ++++++

    const float sin_angle = 0.86602;
    const float g = 9.8;
    float H_max = 0;
    ///if(DOG_ROUND){
        if(wind_strength >= 0)
            H_max = ( (pow(start_V, 2) ) * (pow(sin_angle, 2)) ) / ((2*g) + wind_strength);
        else
            H_max = ( (pow(start_V, 2) ) * (pow(sin_angle, 2)) ) / ((2*g) - wind_strength);
    ///}
    ///if(CAT_ROUND){
        if(wind_strength <= 0)
            H_max = ( (pow(start_V, 2) ) * (pow(sin_angle, 2)) ) / ((2*g) + wind_strength);
        else
            H_max = ( (pow(start_V, 2) ) * (pow(sin_angle, 2)) ) / ((2*g) - wind_strength);
    ///}


}

#endif // GAME_HPP_INCLUDED
