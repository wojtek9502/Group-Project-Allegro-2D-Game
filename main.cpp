#include <iostream>
#include<stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<vector>

#include "system_functions.hpp"
#include "game.hpp"
#include "player.hpp"

#define screen_width 800
#define screen_height 537

using namespace std;

int main(){
    bool end_menu_start = false;
    Player dog = Player("dog",130,390,100);
    Player cat = Player("cat",500,380,100);


    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_MOUSE_STATE mouse;

    ALLEGRO_DISPLAY *display = al_create_display( screen_width, screen_height );
    if(!display)
        cout<<"failed to load display";


    ALLEGRO_BITMAP *start_background = load_bitmap("img//start_background.png");
    ALLEGRO_BITMAP *background = load_bitmap("img//background.png");

    ALLEGRO_BITMAP *dog_bitmap = load_bitmap("img//dog.png");
    ALLEGRO_BITMAP *cat_bitmap = load_bitmap("img//cat.png");
    int cat_width = al_get_bitmap_width(cat_bitmap);
    int dog_width = al_get_bitmap_width(dog_bitmap);

    ALLEGRO_BITMAP *one_player = load_bitmap("img//1 player.png");
    ALLEGRO_BITMAP *two_player = load_bitmap("img//2 player.png");
    ALLEGRO_BITMAP *cursor_bitmap = load_bitmap("img//cursor.png");
    ALLEGRO_MOUSE_CURSOR *cursor = al_create_mouse_cursor(cursor_bitmap, 0, 0);


    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
    {
        al_get_keyboard_state(&keyboard);
        al_get_mouse_state(&mouse);
        al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

        if(end_menu_start==false)
        {
            end_menu_start = run_menu_start(mouse, display, cursor, end_menu_start);
            al_draw_bitmap(start_background,0,0,0);
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0);
            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0);
            al_draw_bitmap(one_player, 320, 150, 0);
            al_draw_bitmap(two_player, 300, 230, 0);

        }

        if(end_menu_start==true)
        {
            //game functions here
            dog = check_dog_move(keyboard, dog, screen_width, dog_width);
            cat = check_cat_move(keyboard, cat, screen_width, cat_width);
            //cout << dog.x_position << endl << cat.x_position;
            al_draw_bitmap(background,0,0,0);
            al_draw_bitmap(dog_bitmap, dog.x_position, dog.y_position, 0);
            al_draw_bitmap(cat_bitmap, cat.x_position, cat.y_position,0);

        }

        al_flip_display();



    }//END GAME LOOP

    al_destroy_bitmap(cursor_bitmap);
    al_destroy_bitmap(two_player);
    al_destroy_bitmap(one_player);
    al_destroy_bitmap(dog_bitmap);
    al_destroy_bitmap(cat_bitmap);
    al_destroy_bitmap(start_background);
    al_destroy_bitmap(background);
    al_destroy_display( display );
    return 0;
}
