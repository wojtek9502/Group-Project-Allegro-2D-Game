#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "player.hpp"
#include "math.h"
#include <list>
#define PI 3.14159265
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

    return dog;
}

Player check_cat_move(ALLEGRO_KEYBOARD_STATE keyboard, Player cat, int screen_width, int cat_width)
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

list<float> ball_position(float Vo, float angle, float wind, float start_x, float start_y){
    float x;
    float y;
    float constant_wind = 10;
    float g = 9.80665;
    float e = 2.718281828459;
    float time = 1;
    float step = 0.1;
    float ball_x = start_x;
    float ball_y = start_y;
    list<float> x_y_position;

    while(ball_y > 0){
        x = (Vo * cos(angle*PI/180) / constant_wind) * (1 - pow(e, -constant_wind*time));
        y = ((Vo * sin(angle*PI/180) / wind) + (g/wind) ) * (1 - pow(e, -wind*time)) - (g*time/wind);

        ball_x += x*step;
        ball_y += y*step;

        x_y_position.push_back(ball_x);
        x_y_position.push_back(ball_y);
        time +=step;
    }

    return x_y_position;
}

#endif // GAME_HPP_INCLUDED
