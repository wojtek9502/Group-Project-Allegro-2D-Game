#include <iostream>
#include<stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

#include "system_functions.hpp"
#include "game.hpp"
#include "player.hpp"
#include "Turn.hpp"
#include "ball.hpp"
#include "wind.hpp"

#define screen_width 800
#define screen_height 537

//wielkosci fontow
#define font_normal_size 40
#define font_small_size 20
#define font_very_small_size 18
#define font_title_size 65




bool end_game = false;
const float FPS = 180;
using namespace std;
Player dog = Player("dog",130,390,300);
Player cat = Player("cat",500,380,300);


int main(){
    srand(time(NULL));
    bool end_menu_start = false;

    Turn game_turn = Turn(); // obiekt tury, zaczyna pies
    Wind wind = Wind(); // wiatr = 0, losowanie wiatru gdy nowa tura (nacisnij spacje)
    wind.rand_wind();
    Ball ball;

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    ball.print_position_vector();

    // fonts init
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font_title_size_obj = al_load_font("fonts//font1.ttf", font_title_size, 0);
    ALLEGRO_FONT *font_normal_size_obj = al_load_font("fonts//font1.ttf", font_normal_size, 0);
    ALLEGRO_FONT *font_small_size_obj = al_load_font("fonts//font1.ttf", font_small_size, 0);
    ALLEGRO_FONT *font_very_small_size_obj = al_load_font("fonts//font1.ttf", font_very_small_size, 0);
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_DISPLAY *display = al_create_display( screen_width, screen_height );
    if(!display)
        cout<<"failed to load display";


    ALLEGRO_BITMAP *background = load_bitmap("img//background.png");
    ALLEGRO_BITMAP *dog_bitmap = load_bitmap("img//dog.png");
    ALLEGRO_BITMAP *cat_bitmap = load_bitmap("img//cat.png");
    ALLEGRO_BITMAP *cursor_bitmap = load_bitmap("img//cursor.png");
    ALLEGRO_BITMAP *wall_bitmap = load_bitmap("img//wall.png");
    ALLEGRO_BITMAP *ball_bitmap = load_bitmap("img//ball.png");
    ALLEGRO_BITMAP *wind_right_bitmap = load_bitmap("img//wind_right.png");
    ALLEGRO_BITMAP *wind_left_bitmap = load_bitmap("img//wind_left.png");
    int cat_width = al_get_bitmap_width(cat_bitmap);
    int dog_width = al_get_bitmap_width(dog_bitmap);
    int cat_height = al_get_bitmap_height(cat_bitmap);
    int dog_height = al_get_bitmap_height(dog_bitmap);
    int wall_width = al_get_bitmap_width(wall_bitmap);
    int wall_height = al_get_bitmap_height(wall_bitmap);
    ALLEGRO_MOUSE_CURSOR *cursor = al_create_mouse_cursor(cursor_bitmap, 0, 0);

    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    if (!eventQueue){
    cout<<"failed to load";
    }
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    al_start_timer(timer);

    //GAME LOOP
    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {

        al_get_keyboard_state(&keyboard);
        al_get_mouse_state(&mouse);
        al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);
     // if(ev.type == ALLEGRO_EVENT_TIMER)
     //   {


        if(end_menu_start==false)
        {
            end_menu_start = run_menu_start(mouse, display, cursor, end_menu_start);
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0);
            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0);
            al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 80, ALLEGRO_ALIGN_CENTRE, "Pies i Kot");
            al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 180, ALLEGRO_ALIGN_CENTRE, "PLAY");
            //al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 240, ALLEGRO_ALIGN_CENTRE, "Two Players");

        }

        if(end_menu_start==true)
        {

            //game functions here
            if(end_game == false)
            {
                if(ev.type == ALLEGRO_EVENT_TIMER)
                {
                check_wind_change(wind, keyboard);
                dog = check_dog_move(keyboard, dog, screen_width, dog_width, game_turn);
                cat = check_cat_move(keyboard, cat, screen_width, cat_width, game_turn);
                CollisionDetection(dog,cat,ball,game_turn,cat_width,cat_height,dog_width,dog_height,wall_height,wall_width);
                //CollisionDetection(dog,cat,ball,game_turn,cat_width,cat_height,dog_width,dog_height)

                if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                {
                   dog = check_hp_dog(dog, ev.mouse.x, ev.mouse.y, dog_width, dog_height);
               //    cat = check_hp_cat(cat, ev.mouse.x, ev.mouse.y, cat_width, cat_height);
                }
                if(al_key_down(&keyboard, ALLEGRO_KEY_SPACE))
                {
                    if(game_turn.whose_turn==DOG_TURN){
                     ball.ball_position_x=dog.x_position+dog_width+10;
                     ball.ball_position_y=dog.y_position+10;
                     ball.life=true;
                     throww=true;
                    }
                    if(game_turn.whose_turn==CAT_TURN){
                     ball.ball_position_x=cat.x_position-30;
                     ball.ball_position_y=cat.y_position;
                     ball.life=true;
                     throww=true;
                    }
                }
                if(throww==true&&ball.life==true&&game_turn.whose_turn==CAT_TURN)
                ball = moveBallDog(ball,dog.Vo,180-dog.arrow_angle,wind.strength,dog,dog_width);
                if(throww==true&&ball.life==true&&game_turn.whose_turn==DOG_TURN)
                ball = moveBallCat(ball,cat.Vo,180-cat.arrow_angle,wind.strength,cat,cat_width);
            //    ball = moveBallCat(ball,180,135,10,dog,cat_width);
                }
                //check turn change and change wind!! (in Turn.hpp)
                game_turn.check_change_turn(keyboard, ev, wind);
            }

            // draw elements here
            // draw players elements
           // cout<<dog.arrow_angle<<endl;
          //  cout<<cat.arrow_angle<<endl;
            al_draw_bitmap(background,0,0,0);
            al_draw_pixel(dog.x_position,dog.y_position,al_map_rgb(226, 82, 222));
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0); //pies postac
            al_draw_line( dog.x_position+dog_width, dog.y_position,  dog.x_arrow_point+dog_width, dog.y_arrow_point, al_map_rgb(0,0,255), 3); //pies strzalka
            al_draw_text(font_very_small_size_obj, al_map_rgb(206, 82, 0), 10, screen_height-25, ALLEGRO_ALIGN_LEFT, prepate_throw_strengtht_text(dog.Vo).c_str()); //pies sila rzutu napis
            al_draw_filled_rectangle(150, screen_height-20, (150+dog.Vo/2), screen_height-10, al_map_rgb(206, 82, 0)); //sila rzutu pasek pies

            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0); // kot postac
            al_draw_line( cat.x_position, cat.y_position,  cat.x_arrow_point, cat.y_arrow_point, al_map_rgb(255,0,0), 3); // strzalka kot
            al_draw_text(font_very_small_size_obj, al_map_rgb(206, 82, 0), 660, screen_height-25, ALLEGRO_ALIGN_LEFT, prepate_throw_strengtht_text(cat.Vo).c_str()); //pies sila rzutu napis
            al_draw_filled_rectangle( (650-cat.Vo/2), screen_height-20, 650, screen_height-10, al_map_rgb(206, 82, 0)); //sila rzutu pasek kot


           //draw hp and hp texts
            al_draw_filled_rectangle(10, 10, 10+dog.hp, 25, al_map_rgb(255, 0, 0));
            al_draw_filled_rectangle(790-cat.hp, 10, 790, 25, al_map_rgb(255, 0, 0));
            al_draw_text(font_small_size_obj, al_map_rgb(255, 0, 0), 50, 40, ALLEGRO_ALIGN_CENTRE, prepate_hp_text(dog.hp).c_str());
            al_draw_text(font_small_size_obj, al_map_rgb(255, 0, 0), 750, 40, ALLEGRO_ALIGN_CENTRE, prepate_hp_text(cat.hp).c_str());

            //draw wind
            al_draw_text(font_small_size_obj, al_map_rgb(0, 0, 200), screen_width/2, 10, ALLEGRO_ALIGN_CENTRE, "Wiatr");
            draw_wind_icons(wind, wind_left_bitmap, wind_right_bitmap);
            //al_draw_text(font_small_size_obj, al_map_rgb(0, 0, 200), screen_width/2, 60, ALLEGRO_ALIGN_CENTRE, prepate_wind_text(wind.strength).c_str());

            //draw wall and turn text
            al_draw_bitmap(wall_bitmap, screen_width/2, 370, 0);
            al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 80, ALLEGRO_ALIGN_CENTRE, game_turn.whose_turn_text.c_str());
            if(throww==true&&ball.life==true){
           // al_draw_filled_circle(ball.ball_position_x,ball.ball_position_y,15,al_map_rgb(255, 180, 80));
           al_draw_bitmap(ball_bitmap, ball.ball_position_x, ball.ball_position_y, 0);
            }
           //  cat = CollisionDetection(dog,cat,ball,game_turn,cat_width,cat_height,dog_width,dog_height);
          //  al_draw_bitmap(ball_bitmap, ball.ball_position_x, ball.ball_position_y, 0);



            // end game check
            if(cat.hp <= 0){
                al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 200, ALLEGRO_ALIGN_CENTRE, "Wygrał Pies");
                end_game = true;
            }
            if(dog.hp <= 0){
                al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 200, ALLEGRO_ALIGN_CENTRE, "Wygrał Kot");
                end_game = true;
            }

        }
       // }
        al_flip_display();



    }//END GAME LOOP
    ball.print_position_vector();
    al_destroy_bitmap(wall_bitmap);
    al_destroy_bitmap(ball_bitmap);
    al_destroy_bitmap(wind_right_bitmap);
    al_destroy_bitmap(wind_left_bitmap);
    al_destroy_bitmap(cursor_bitmap);
    al_destroy_bitmap(dog_bitmap);
    al_destroy_bitmap(cat_bitmap);
    al_destroy_bitmap(background);
    al_destroy_display( display );
    return 0;
}
