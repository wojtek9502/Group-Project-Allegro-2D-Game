#ifndef SYSTEM_FUNCTIONS_HPP_INCLUDED
#define SYSTEM_FUNCTIONS_HPP_INCLUDED


ALLEGRO_BITMAP* load_bitmap(char *bitmap_path)
{
    ALLEGRO_BITMAP *tmp_bitmap_array =  al_load_bitmap(bitmap_path);
    if(!tmp_bitmap_array){
            std::cout<<"failed to load bitmap: " + std::string(bitmap_path);
        }
    else
        return tmp_bitmap_array;
}


#endif // SYSTEM_FUNCTIONS_HPP_INCLUDED
