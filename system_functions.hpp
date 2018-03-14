#ifndef SYSTEM_FUNCTIONS_HPP_INCLUDED
#define SYSTEM_FUNCTIONS_HPP_INCLUDED


//example:  ALLEGRO_BITMAP *start_background = load_bitmap("start_background.png");
ALLEGRO_BITMAP* load_bitmap(char *bitmap_path)
{
    ALLEGRO_BITMAP *tmp_bitmap_array =  al_load_bitmap(bitmap_path);
    if(!tmp_bitmap_array){
            std::cout<<"failed to load bitmap: " + std::string(bitmap_path);
        }
    else
        return tmp_bitmap_array;
}

/*
ALLEGRO_FONT* load_font(char *font_path, int font_size=12)
{
    ALLEGRO_FONT *tmp_font_array =  al_load_ttf_font(font_path,font_size,0);
    if(!tmp_font_array){
            std::cout<<"failed to load font: " + std::string(font_path);
        }
    else
        return tmp_font_array;
}
*/


#endif // SYSTEM_FUNCTIONS_HPP_INCLUDED
