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
bool throww = false;

/**
 * Sprawdzenie czy przycisk start został kliknięty, jesli tak zostaje włączona główna rozgrywka
 * @param mouse
 * @param display
 * @param cursor
 * @param end_menu_start
 * @return
 */
bool run_menu_start(ALLEGRO_MOUSE_STATE mouse, ALLEGRO_DISPLAY* display, ALLEGRO_MOUSE_CURSOR* cursor, bool end_menu_start)
{
     if((mouse.x >=278 && mouse.x <=500) && (mouse.y >= 190 && mouse.y <=215))
        {

            printf("one player: (%d, %d)\n", mouse.x, mouse.y);
            al_set_mouse_cursor(display, cursor);
            al_rest(0.1);
            if(mouse.buttons & 1)
            {
                //cout<<"clicked one player: x:"<<mouse.x<<"y: "<<mouse.y<<endl;
                end_menu_start = true;
            }
        }
    return end_menu_start;
}

/**
 * Tura psa
 * @param keyboard
 * @param dog
 * @param screen_width
 * @param dog_width
 * @param turn
 * @return
 */
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
        if(al_key_down(&keyboard, ALLEGRO_KEY_LSHIFT))
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
                //cout << "Pies sila rzutu (Vo):" << dog.Vo << endl;
        }

    }
     return dog;
}

/**
 * Tura kota
 * @param keyboard
 * @param cat
 * @param screen_width
 * @param cat_width
 * @param turn
 * @return
 */
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
                //cout << "Kot sila rzutu (Vo):" << cat.Vo << endl;
        }

    }
    return cat;
}

/**
 * Sprawdzenie ilości życia psa
 * @param dog
 * @param x
 * @param y
 * @param dWidth
 * @param dHeight
 * @return
 */
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

/**
 * Sprawdzenie ilości życia kota
 * @param cat
 * @param x
 * @param y
 * @param cWidth
 * @param cHeight
 * @return
 */
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

/**
 * Wyświetlenie napisu PZ
 * @param hp
 * @return
 */
string prepate_hp_text(int hp)
{
    ostringstream output;
    output << "PZ " << hp ;
    return output.str();
}

/**
 * Wyświetlenie napisu Siła
 * @param wind
 * @return
 */
string prepate_wind_text(float wind)
{
    ostringstream output;
    output << "Siła: " << wind ;
    return output.str();
}

/**
 * Wyświetlenie napisu Siła rzutu
 * @param throw_strength
 * @return
 */
string prepate_throw_strengtht_text(float throw_strength)
{
    ostringstream output;
    output << "Siła rzutu: " << throw_strength ;
    return output.str();
}

/**
 * Wyświetlenie ikonek wiatru w zależności od jego siły
 * @param wind
 * @param wind_left_bitmap
 * @param wind_right_bitmap
 * @param turn
 */
void draw_wind_icons(Wind wind, ALLEGRO_BITMAP *wind_left_bitmap, ALLEGRO_BITMAP *wind_right_bitmap, Turn turn){

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
    if(wind.strength>30)
    {
        al_draw_bitmap(wind_right_bitmap, (800/2), 35, 0);
        al_draw_bitmap(wind_right_bitmap, (800/2)+30, 35, 0);
        al_draw_bitmap(wind_right_bitmap, (800/2)+60, 35, 0);
    }


}

/**
 * Sprawdzenie kto wygrał grę i wyświetlenie odpowiedniego napisu
 * @param dog
 * @param cat
 * @param font_title_size_obj
 */
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

/**
 * Zmiana wiatru
 * @param wind
 * @param keyboard
 */
void check_wind_change(Wind &wind, ALLEGRO_KEYBOARD_STATE keyboard){
     if(al_key_down(&keyboard, ALLEGRO_KEY_Z))
        {
            if(wind.strength>=10)
                wind.strength -=0.5;
        }
     if(al_key_down(&keyboard, ALLEGRO_KEY_X))
        {
            if(wind.strength<=40)
                wind.strength +=0.5;
        }
}

/**
 * Rzut piłką przez psa
 * @param ball
 * @param Vo
 * @param angle
 * @param wind
 * @param dog
 * @param width
 * @return
 */
Ball moveBallDog(Ball ball, float Vo, float angle, float wind, Player dog, int width)
{
    if(ball.life==true){
    float constant_wind = 10;
    float windreverse = 50 - wind;
    float g = 9.80665;
    float e = 2.718281828459;
    float x = (Vo * cos(angle*PI/180) / windreverse) * (1 - pow(e, -windreverse*ball.time));
    float y = ((Vo * sin(angle*PI/180) / constant_wind) + (g/constant_wind) ) * (1 - pow(e, -constant_wind*ball.time)) - (g*ball.time/constant_wind);

        ball.ball_position_x -= x*ball.step;
        ball.ball_position_y -= y*ball.step;
        ball.time +=ball.step;

       // cout << angle <<endl;
    }
        if(ball.ball_position_y>500){
            ball.life=false;
            ball.ball_position_x= dog.x_position+width;
            ball.ball_position_y= dog.y_position;
            ball.time=1;
            ball.step=0.1;}
    return ball;
}

/**
 * Rzut piłką przez kota
 * @param ball
 * @param Vo
 * @param angle
 * @param wind
 * @param cat
 * @param width
 * @return
 */
Ball moveBallCat(Ball ball, float Vo, float angle, float wind, Player cat, int width)
{
    if(ball.life==true){
    float constant_wind = 10;
    float g = 9.80665;
    float e = 2.718281828459;
   float x = (Vo * cos(angle*PI/180) / wind) * (1 - pow(e, -wind*ball.time));
   float y = ((Vo * sin(angle*PI/180) / constant_wind) + (g/constant_wind) ) * (1 - pow(e, -constant_wind*ball.time)) - (g*ball.time/constant_wind);

        ball.ball_position_x -= x*ball.step;
        ball.ball_position_y -= y*ball.step;
        ball.time +=ball.step;
       // cout << angle <<endl;
    }
        if(ball.ball_position_y>475){
            ball.life=false;
            throww=false;
            ball.ball_position_x= cat.x_position+width;
            ball.ball_position_y= cat.y_position;
            ball.time=1;
            ball.step=0.1;}
    return ball;
}

/**
 * Wykrywanie kolizji piłki z psem, kotem lub murem
 * @param dog
 * @param cat
 * @param ball
 * @param turn
 * @param cat_w
 * @param cat_h
 * @param dog_w
 * @param dog_h
 * @param wall_h
 * @param wall_w
 */
void CollisionDetection(Player &dog, Player &cat, Ball &ball, Turn turn, int cat_w, int cat_h, int dog_w, int dog_h, int wall_h, int wall_w)
{
      if((turn.whose_turn==DOG_TURN)&&(throww==true))
    {
        if((ball.ball_position_x>=dog.x_position)&&(ball.ball_position_x<=dog.x_position+dog_w)&&(ball.ball_position_y>=dog.y_position)&&(ball.ball_position_y<=dog.y_position+dog_h)&&ball.life==true){
            ball.life=false;
            throww=false;
            dog.hp=dog.hp - 30;;
            cout<<"Wykryto"<<endl;
            cout<<dog.hp<<endl;
            ball.ball_position_x= dog.x_position+dog_w;
            ball.ball_position_y= dog.y_position;
            ball.time=1;
            ball.step=0.1;
        }
    }
    if((turn.whose_turn==CAT_TURN)&&(throww==true))
    {
        if((ball.ball_position_x>=cat.x_position)&&(ball.ball_position_x<=cat.x_position+cat_w)&&(ball.ball_position_y>=cat.y_position)&&(ball.ball_position_y<=cat.x_position+cat_h)&&ball.life==true){
            ball.life=false;
            throww=false;
            cat.hp=cat.hp - 30;;
           // cout<<"Wykryto"<<endl;
           // cout<<cat.hp<<endl;
            ball.ball_position_x= cat.x_position+cat_w;
            ball.ball_position_y= cat.y_position;
            ball.time=1;
            ball.step=0.1;
        }
    }
        if(throww==true)
    {
        if((ball.ball_position_x>=380)&&(ball.ball_position_x<=380+wall_w)&&(ball.ball_position_y>=360)&&(ball.ball_position_y<=360+wall_h)&&ball.life==true){
            ball.life=false;
            throww=false;
           // cout<<"Wykryto"<<endl;
           // cout<<cat.hp<<endl;
            ball.time=1;
            ball.step=0.1;
        }
    }
        if(throww==true)
    {
        if((ball.ball_position_x>=810)||(ball.ball_position_x<=0)&&ball.life==true){
            ball.life=false;
            throww=false;
           // cout<<"Wykryto"<<endl;
           // cout<<cat.hp<<endl;
            ball.time=1;
            ball.step=0.1;
        }

    }

}

#endif // GAME_HPP_INCLUDED
