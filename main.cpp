#include <iostream>
#include<stdio.h>
#include <allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include "system_functions.hpp"
#define width 800
#define height 537

using namespace std;

int main(){

    al_init();
    al_install_keyboard();
    al_init_image_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;

    ALLEGRO_DISPLAY *display = al_create_display( width, height );
    if(!display)
        cout<<"failed to load display";

    ALLEGRO_BITMAP *start_background = load_bitmap("start_background.png");
    ALLEGRO_BITMAP *dog = load_bitmap("dog.png");
    ALLEGRO_BITMAP *cat = load_bitmap("cat.png");
    ALLEGRO_BITMAP *one_player = load_bitmap("1 player.png");
    ALLEGRO_BITMAP *two_player = load_bitmap("2 player.png");


    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE)){
    al_get_keyboard_state(&keyboard);

    al_draw_bitmap(start_background,0,0,0);
    al_draw_bitmap(dog,130,390,0);
    al_draw_bitmap(cat,500,380,0);
    al_draw_bitmap(one_player, 320, 150, 0);
    al_draw_bitmap(two_player, 300, 230, 0);
    al_flip_display();

    }

    al_destroy_bitmap(two_player);
    al_destroy_bitmap(one_player);
    al_destroy_bitmap(dog);
    al_destroy_bitmap(cat);
    al_destroy_bitmap(start_background);
    al_destroy_display( display );
    return 0;
}
