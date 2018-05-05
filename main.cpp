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

#define screen_width 800
#define screen_height 537

//wielkosci fontow
#define font_normal_size 40
#define font_small_size 20
#define font_title_size 65



bool end_game = false;
const float FPS = 60;
using namespace std;

int main(){
    bool end_menu_start = false;
    Player dog = Player("dog",130,390,300);
    Player cat = Player("cat",500,380,300);
    Turn game_turn = Turn(); // obiekt tury, zaczyna pies

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();

    // fonts init
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font_title_size_obj = al_load_font("fonts//font1.ttf", font_title_size, 0);
    ALLEGRO_FONT *font_normal_size_obj = al_load_font("fonts//font1.ttf", font_normal_size, 0);
    ALLEGRO_FONT *font_small_size_obj = al_load_font("fonts//font1.ttf", font_small_size, 0);

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    timer = al_create_timer(1.0 / FPS);
    ALLEGRO_DISPLAY *display = al_create_display( screen_width, screen_height );
    if(!display)
        cout<<"failed to load display";


    ALLEGRO_BITMAP *background = load_bitmap("img//background.png");
    ALLEGRO_BITMAP *dog_bitmap = load_bitmap("img//dog.png");
    ALLEGRO_BITMAP *cat_bitmap = load_bitmap("img//cat.png");
    ALLEGRO_BITMAP *cursor_bitmap = load_bitmap("img//cursor.png");
    ALLEGRO_BITMAP *wall_bitmap = load_bitmap("img//wall.png");
    ALLEGRO_BITMAP *ball_bitmap = load_bitmap("img//ball.png");
    int cat_width = al_get_bitmap_width(cat_bitmap);
    int dog_width = al_get_bitmap_width(dog_bitmap);
    int cat_height = al_get_bitmap_height(cat_bitmap);
    int dog_height = al_get_bitmap_height(dog_bitmap);
    ALLEGRO_MOUSE_CURSOR *cursor = al_create_mouse_cursor(cursor_bitmap, 0, 0);
    eventQueue = al_create_event_queue();
    if (!eventQueue){
    cout<<"failed to load";
    }
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    al_start_timer(timer);
    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {

        al_get_keyboard_state(&keyboard);
        al_get_mouse_state(&mouse);
        al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);

        if(end_menu_start==false)
        {
            end_menu_start = run_menu_start(mouse, display, cursor, end_menu_start);
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0);
            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0);
            al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 80, ALLEGRO_ALIGN_CENTRE, "Pies i Kot");
            al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 180, ALLEGRO_ALIGN_CENTRE, "One Player");
            al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 240, ALLEGRO_ALIGN_CENTRE, "Two Players");

        }

        if(end_menu_start==true)
        {
            //game functions here
            if(end_game == false)
            {
                dog = check_dog_move(keyboard, dog, screen_width, dog_width, game_turn);
                cat = check_cat_move(keyboard, cat, screen_width, cat_width, game_turn);


                if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                {
                   dog = check_hp_dog(dog, ev.mouse.x, ev.mouse.y, dog_width, dog_height);
                   cat = check_hp_cat(cat, ev.mouse.x, ev.mouse.y, cat_width, cat_height);
                }
                //check turn change
                game_turn.check_change_turn(keyboard, ev);
            }


            // draw elements here
            // draw players elements
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0);
            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0);
            al_draw_line( cat.x_position, cat.y_position,  cat.x_arrow_point, cat.y_arrow_point, al_map_rgb(255,0,0), 3);
            al_draw_line( dog.x_position+dog_width, dog.y_position,  dog.x_arrow_point+dog_width, dog.y_arrow_point, al_map_rgb(0,0,255), 3);

           //draw hp and hp texts
            al_draw_filled_rectangle(10, 10, 10+dog.hp, 25, al_map_rgb(255, 0, 0));
            al_draw_filled_rectangle(790-cat.hp, 10, 790, 25, al_map_rgb(255, 0, 0));
            al_draw_text(font_small_size_obj, al_map_rgb(255, 0, 0), 50, 40, ALLEGRO_ALIGN_CENTRE, prepate_hp_text(dog.hp).c_str());
            al_draw_text(font_small_size_obj, al_map_rgb(255, 0, 0), 750, 40, ALLEGRO_ALIGN_CENTRE, prepate_hp_text(cat.hp).c_str());

            //draw wall and turn text
            al_draw_bitmap(wall_bitmap, screen_width/2, 370, 0);
            al_draw_text(font_normal_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 40, ALLEGRO_ALIGN_CENTRE, game_turn.whose_turn_text.c_str());

            //al_draw_bitmap(ball_bitmap, ball.ball_position_x, ball.ball_position_y, 0);



            // end game check
            if(cat.hp <= 0){
                al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 100, ALLEGRO_ALIGN_CENTRE, "Wygrał Pies");
                end_game = true;
            }
            if(dog.hp <= 0){
                al_draw_text(font_title_size_obj, al_map_rgb(255, 177, 10), screen_width/2, 80, ALLEGRO_ALIGN_CENTRE, "Wygrał Kot");
                end_game = true;
            }

        }

        al_flip_display();



    }//END GAME LOOP

    al_destroy_bitmap(wall_bitmap);
    al_destroy_bitmap(ball_bitmap);
    al_destroy_bitmap(cursor_bitmap);
    al_destroy_bitmap(dog_bitmap);
    al_destroy_bitmap(cat_bitmap);
    al_destroy_bitmap(background);
    al_destroy_display( display );
    return 0;
}
