//
// Created by user1 on 2017/06/23.
//

#ifndef NIBBLER_FEATURED_RENDERER_H
#define NIBBLER_FEATURED_RENDERER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <dirent.h>
#include <cstring>
#include <stdlib.h>

class featured_renderer
{
    private:
    sf::RenderWindow *window;

    char            **backgrounds;
    char            **snake_skins;
    char            **snake_heads;
    char            **snake_foods;

    int              food;//tells which food
    int              snake;//tells which snake
    int              snake_head;//tells which snake head
    int              background;//tells which background

    int              bodyswivel;
    int              swivel_intensity;
    int              background_movement_direction;//forward or backwards

    sf::Texture      *bg_textures;
    sf::Texture      *food_textures;//[3];
    sf::Texture      *snake_textures;//[3];//body
    sf::Texture      *snake_head_textures;

    public:
    featured_renderer(void);
    ~featured_renderer(void);
    int                 error_message(std::string message);
    sf::RenderWindow    *&getwindow(void);
    void                setwindow(sf::RenderWindow *window_data);
    int                 getbodyswivel(void);
    void                setbodyswivel(int bs_data);
    int                 getbackground_movement_direction(void);
    void                setbackground_movement_direction(int direction);
    int                 getswivelintensity(void);
    void                setswivelintensity(int bs_data);
    int                 getbackground(void);
    void                setbackground(int bg_data);
    int                 getsnake(void);
    void                setsnake(int snake_data);
    int                 getsnake_head(void);
    void                setsnake_head(int sh_data);
    int                 getfood(void);
    void                setfood(int food_data);
    sf::Texture         *&getsnake_textures(void);
    void                setsnake_textures(sf::Texture *s_data);
    sf::Texture         *&getbg_textures(void);
    void                setbg_textures(sf::Texture *bg_data);
    sf::Texture         *&getfood_textures(void);
    void                setfood_textures(sf::Texture *food_data);
    sf::Texture         *&getsnake_head_textures(void);
    void                setsnake_head_textures(sf::Texture *sh_data);
};
#endif //NIBBLER_FEATURED_RENDERER_H
