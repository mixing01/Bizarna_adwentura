#include "draw_handle.h"
#include "init.h"
void draw_title()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(title, (window_width - al_get_bitmap_width(title)) / 2, 100, 0);
    al_draw_bitmap(jotaro, 900, 300, 0);
    if (onButton1_hover)
    {
        al_draw_filled_rectangle(window_width / 2 - 100, 380, window_width / 2 + 100, 480, al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, 420, ALLEGRO_ALIGN_CENTRE, "New Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 500, window_width / 2 + 100, 600, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 540, ALLEGRO_ALIGN_CENTRE, "Load Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 620, window_width / 2 + 100, 720, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 660, ALLEGRO_ALIGN_CENTRE, "Quit");
    }
    else if (onButton2_hover)
    {
        al_draw_filled_rectangle(window_width / 2 - 100, 380, window_width / 2 + 100, 480, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 420, ALLEGRO_ALIGN_CENTRE, "New Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 500, window_width / 2 + 100, 600, al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, 540, ALLEGRO_ALIGN_CENTRE, "Load Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 620, window_width / 2 + 100, 720, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 660, ALLEGRO_ALIGN_CENTRE, "Quit");
    }
    else if (onButton3_hover)
    {
        al_draw_filled_rectangle(window_width / 2 - 100, 380, window_width / 2 + 100, 480, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 420, ALLEGRO_ALIGN_CENTRE, "New Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 500, window_width / 2 + 100, 600, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 540, ALLEGRO_ALIGN_CENTRE, "Load Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 620, window_width / 2 + 100, 720, al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, 660, ALLEGRO_ALIGN_CENTRE, "Quit");
    }
    else
    {
        al_draw_filled_rectangle(window_width / 2 - 100, 380, window_width / 2 + 100, 480, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 420, ALLEGRO_ALIGN_CENTRE, "New Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 500, window_width / 2 + 100, 600, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 540, ALLEGRO_ALIGN_CENTRE, "Load Game");
        al_draw_filled_rectangle(window_width / 2 - 100, 620, window_width / 2 + 100, 720, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, 660, ALLEGRO_ALIGN_CENTRE, "Quit");
    }
    al_draw_bitmap(kakyoin, 0, 300, 0);
    al_flip_display();
}

void draw_game()
{
    char wynik[30] = "Points: ";
    char punkty[20];
    sprintf(punkty, "%ld", points);
    strcat(wynik, punkty);
    char ruchy[15] = "Moves left: ";
    char movesText[4];
    sprintf(movesText, "%ld", moves);
    strcat(ruchy, movesText);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), window_width - 50, 100, ALLEGRO_ALIGN_RIGHT, wynik);
    al_draw_text(font, al_map_rgb(255, 255, 255), 50, 100, ALLEGRO_ALIGN_LEFT, ruchy);
    for (int i = 0; i <= 10; i++)
    {
        al_draw_line(400, 100 + i * 60, window_width - 400, 100 + i * 60, al_map_rgb(255, 255, 255), 2);
        al_draw_line(400 + i * 60, 100, 400 + i * 60, window_height - 100, al_map_rgb(255, 255, 255), 2);
    }
    if (onButton4_hover)
    {
        al_draw_filled_rectangle(100, window_height - 200, 300, window_height - 100, al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 200, window_height - 180, ALLEGRO_ALIGN_CENTRE, "Save and");
        al_draw_text(font, al_map_rgb(0, 0, 0), 200, window_height - 130, ALLEGRO_ALIGN_CENTRE, "Quit");
    }    
    else
    {
        al_draw_filled_rectangle(100, window_height - 200, 300, window_height - 100, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 180, ALLEGRO_ALIGN_CENTRE, "Save and");
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 130, ALLEGRO_ALIGN_CENTRE, "Quit");
    }
    if (itemClick1_i > -1 && itemClick1_j > -1)
    {
        al_draw_filled_rectangle(100, window_height - 200, 300, window_height - 100, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 180, ALLEGRO_ALIGN_CENTRE, "Save and");
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 130, ALLEGRO_ALIGN_CENTRE, "Quit");
        al_draw_filled_rectangle(grid[itemClick1_j][itemClick1_i].x1, grid[itemClick1_j][itemClick1_i].y1, grid[itemClick1_j][itemClick1_i].x2, grid[itemClick1_j][itemClick1_i].y2, al_map_rgb(255, 255, 0));
    }
    if (itemHover_i > -1 && itemHover_j > -1)
    {
        al_draw_filled_rectangle(100, window_height - 200, 300, window_height - 100, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 180, ALLEGRO_ALIGN_CENTRE, "Save and");
        al_draw_text(font, al_map_rgb(234, 51, 254), 200, window_height - 130, ALLEGRO_ALIGN_CENTRE, "Quit");
        al_draw_filled_rectangle(grid[itemHover_i][itemHover_j].x1, grid[itemHover_i][itemHover_j].y1, grid[itemHover_i][itemHover_j].x2, grid[itemHover_i][itemHover_j].y2, al_map_rgb(255, 255, 255));
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j].itemHeld == 1)
            {
                al_draw_bitmap(tile1, grid[i][j].x1, grid[i][j].y1, 0);
            }
            else if (grid[i][j].itemHeld == 2)
            {
                al_draw_bitmap(tile2, grid[i][j].x1, grid[i][j].y1, 0);
            }
            else if (grid[i][j].itemHeld == 3)
            {
                al_draw_bitmap(tile3, grid[i][j].x1, grid[i][j].y1, 0);
            }
            else if (grid[i][j].itemHeld == 4)
            {
                al_draw_bitmap(tile4, grid[i][j].x1, grid[i][j].y1, 0);
            }
        }
    }
    al_flip_display();
    if (wasMatch)
        Sleep(500);
}

void draw_credits()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    char wynik[30] = "Points: ";
    char punkty[20];
    sprintf(punkty, "%ld", points);
    strcat(wynik, punkty);
    al_draw_text(font, al_map_rgb(255, 255, 255), window_width / 2, window_height / 2, ALLEGRO_ALIGN_CENTRE, wynik);
    if (onButton5_hover)
    {
        al_draw_filled_rectangle(window_width / 2 - 100, window_height-200, window_width / 2 + 100, window_height - 100, al_map_rgb(255, 255, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), window_width / 2, window_height - 160, ALLEGRO_ALIGN_CENTRE, "Main Menu");
    }
    else
    {
        al_draw_filled_rectangle(window_width / 2 - 100, window_height - 200, window_width / 2 + 100, window_height - 100, al_map_rgb(143, 237, 255));
        al_draw_text(font, al_map_rgb(234, 51, 254), window_width / 2, window_height - 160, ALLEGRO_ALIGN_CENTRE, "Main Menu");
    }
    al_flip_display();
}

void draw_easterEgg()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(polpo, 0, 0, 0);
    al_flip_display();
}