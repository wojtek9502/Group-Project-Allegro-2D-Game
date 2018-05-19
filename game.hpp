#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "player.hpp"
#include "math.h"
#include "Turn.hpp"
#include "Ball.hpp"
#include "wind.hpp"
#include <sstream>
#include <time.h>
#include <sys/time.h>
#define PI 3.14159265
#define wind_rectangle_width 10
#define max_throw_strenght 300

using namespace std;
bool dog_strenght_rise = true;
bool cat_strenght_rise = true;
Ball moveBallDog(Ball ball, float Vo, float angle, float wind)
{
    float constant_wind = 10;
    float g = 9.80665;
    float e = 2.718281828459;
    float x = (Vo * cos(angle*PI/180) / constant_wind) * (1 - pow(e, -constant_wind*ball.time));
    float y = ((Vo * sin(angle*PI/180) / wind) + (g/wind) ) * (1 - pow(e, -wind*ball.time)) - (g*ball.time/wind);

        ball.ball_position_x -= x*ball.step;
        ball.ball_position_y -= y*ball.step;
        ball.time +=ball.step;
        if(ball.ball_position_y>450){
            ball.time=1;
            ball.step=0.1;}
    return ball;
}
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

Player check_dog_move(ALLEGRO_KEYBOARD_STATE keyboard, Player &dog, int screen_width, int dog_width, Turn turn){

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

        // siła rzutu pies
        if(al_key_down(&keyboard, ALLEGRO_KEY_R))
        {

                if(dog_strenght_rise == true)
                {
                    dog.Vo = dog.Vo + 1.0;
                    if(dog.Vo >= max_throw_strenght) // max_throw_strange is #define
                        dog_strenght_rise = false;
                }
                else
                {
                    dog.Vo = dog.Vo - 1.0;
                    if(dog.Vo == 0)
                        dog_strenght_rise = true;
                }
                cout << "Pies sila rzutu (Vo):" << dog.Vo << endl;
        }

    }
     return dog;
}

Player check_cat_move(ALLEGRO_KEYBOARD_STATE keyboard, Player &cat, int screen_width, int cat_width, Turn turn)
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

        // siła rzutu kot
        if(al_key_down(&keyboard, ALLEGRO_KEY_RSHIFT))
        {

                if(cat_strenght_rise == true)
                {
                    cat.Vo = cat.Vo + 1.0;
                    if(cat.Vo >= max_throw_strenght) // max_throw_strange is #define
                        cat_strenght_rise = false;
                }
                else
                {
                    cat.Vo = cat.Vo - 1.0;
                    if(cat.Vo == 0)
                        cat_strenght_rise = true;
                }
                cout << "Kot sila rzutu (Vo):" << cat.Vo << endl;
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

string prepate_wind_text(float wind)
{
    ostringstream output;
    output << "Siła: " << wind ;
    return output.str();
}

string prepate_throw_strengtht_text(float throw_strength)
{
    ostringstream output;
    output << "Siła rzutu: " << throw_strength ;
    return output.str();
}

void draw_wind_icons(Wind wind, ALLEGRO_BITMAP *wind_left_bitmap, ALLEGRO_BITMAP *wind_right_bitmap){

    if(wind.strength<10){
        al_draw_bitmap(wind_left_bitmap, (800/2-20), 35, 0);
        al_draw_bitmap(wind_left_bitmap, (800/2-50), 35, 0);
        al_draw_bitmap(wind_left_bitmap, (800/2-80), 35, 0);
    }
    if(wind.strength<15){
        al_draw_bitmap(wind_left_bitmap, (800/2-20), 35, 0);
        al_draw_bitmap(wind_left_bitmap, (800/2-50), 35, 0);
    }
    if(wind.strength<20){
        al_draw_bitmap(wind_left_bitmap, (800/2-20), 35, 0);
    }

    if(wind.strength>20)
    {
        al_draw_bitmap(wind_right_bitmap, (800/2), 35, 0);
    }
    if(wind.strength>25)
    {
        al_draw_bitmap(wind_right_bitmap, (800/2), 35, 0);
        al_draw_bitmap(wind_right_bitmap, (800/2)+30, 35, 0);
    }
    if(wind.strength>28)
    {
        al_draw_bitmap(wind_right_bitmap, (800/2), 35, 0);
        al_draw_bitmap(wind_right_bitmap, (800/2)+30, 35, 0);
        al_draw_bitmap(wind_right_bitmap, (800/2)+60, 35, 0);
    }
    /* wiatr jako pasek
    if(wind.direction == LEFT)
        al_draw_filled_rectangle(800/2, 40, (800/2)+wind.strength*-wind_rectangle_width, 50, al_map_rgb(0,0,200));
    else
        al_draw_filled_rectangle(800/2, 40, (800/2)+wind.strength*wind_rectangle_width, 50, al_map_rgb(0,0,200));
    */

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

void check_wind_change(Wind &wind, ALLEGRO_KEYBOARD_STATE keyboard){
     if(al_key_down(&keyboard, ALLEGRO_KEY_Z))
        {
            if(wind.strength>=10)
                wind.strength -=0.1;
        }
     if(al_key_down(&keyboard, ALLEGRO_KEY_X))
        {
            if(wind.strength<=30)
                wind.strength +=0.1;
        }


}

#endif // GAME_HPP_INCLUDED
