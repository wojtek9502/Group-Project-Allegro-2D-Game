#include <iostream>
#include<stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "system_functions.hpp"
#include "game.hpp"
#define width 800
#define height 537

using namespace std;

int main(){
    bool end_menu_start = false;
    bool clear_display = false;

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_MOUSE_STATE mouse;

    ALLEGRO_DISPLAY *display = al_create_display( width, height );
    if(!display)
        cout<<"failed to load display";


    ALLEGRO_BITMAP *start_background = load_bitmap("img//start_background.png");
    ALLEGRO_BITMAP *background = load_bitmap("img//background.png");
    ALLEGRO_BITMAP *dog = load_bitmap("img//dog.png");
    ALLEGRO_BITMAP *cat = load_bitmap("img//cat.png");
    ALLEGRO_BITMAP *one_player = load_bitmap("img//1 player.png");
    ALLEGRO_BITMAP *two_player = load_bitmap("img//2 player.png");
    ALLEGRO_BITMAP *cursor_bitmap = load_bitmap("img//cursor.png");
    ALLEGRO_MOUSE_CURSOR *cursor = al_create_mouse_cursor(cursor_bitmap, 0, 0);


    al_clear_to_color(al_map_rgb(0,0,0));

    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {
        al_get_keyboard_state(&keyboard);
        al_get_mouse_state(&mouse);
        al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

        if(end_menu_start==false)
        {
            end_menu_start = run_menu_start(mouse, display, cursor, end_menu_start);
            al_draw_bitmap(start_background,0,0,0);
            al_draw_bitmap(dog,130,390,0);
            al_draw_bitmap(cat,500,380,0);
            al_draw_bitmap(one_player, 320, 150, 0);
            al_draw_bitmap(two_player, 300, 230, 0);
            al_flip_display();
        }

        if(end_menu_start==true)
        {
            //game functions here
            check_move(keyboard);
            cout << endl << "Game start" << endl;
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(dog,130,390,0);
            al_draw_bitmap(cat,500,380,0);
            al_flip_display();
        }



    }//END GAME LOOP

    al_destroy_bitmap(cursor_bitmap);
    al_destroy_bitmap(two_player);
    al_destroy_bitmap(one_player);
    al_destroy_bitmap(dog);
    al_destroy_bitmap(cat);
    al_destroy_bitmap(start_background);
    al_destroy_bitmap(background);
    al_destroy_display( display );
    return 0;
}
