#include "event_handler.h"
#include "draw_handle.h"
#include "init.h"
void handle_events()
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
        if (screen == 2)
        {
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    matrix[i][j] = grid[i][j].itemHeld;

                }
            }
            checkMatches(matrix);

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    points += countMatches(matrix, i, j);  
                }
            }
            if (moves <= 0)
            {
                screen = 3;
            }

        }
        redraw = true;
        break;
    case ALLEGRO_EVENT_MOUSE_AXES:
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        //printf("Coords: %d, %d\n", mouse_x, mouse_y);
        if (screen == 1)
        {
            if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 380 && mouse_y <= 480)
            {
                onButton1_hover = true;
                printf("UGA BUGA PRZYCISK NOWEJ GRY\n");
            }
            else if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 500 && mouse_y <= 600)
            {
                onButton2_hover = true;
                printf("UGA BUGA PRZYCISK £ADOWANIA GRY\n");
            }
            else if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 620 && mouse_y <= 720)
            {
                onButton3_hover = true;
                printf("UGA BUGA PRZYCISK WYJŒCIA Z GRY\n");
            }
            else
            {
                onButton1_hover = false;
                onButton2_hover = false;
                onButton3_hover = false;
            }
        }
        else if (screen == 2)
        {
            if (mouse_x >= 400 && mouse_x <= window_width - 400 && mouse_y >= 100 && mouse_y <= window_height - 100)
            {
                onButton4_hover = false;
                itemHover_j = (mouse_x - 400) / 60;
                itemHover_i = (mouse_y - 100) / 60;
                //printf("Wspolrzedne: %d, %d\n", itemHover_i, itemHover_j);
            }
            else if (mouse_x >= 100 && mouse_x <= 300 && mouse_y >= window_height - 200 && mouse_y <= window_height - 100)
            {
                itemHover_i = -1;
                itemHover_j = -1;
                onButton4_hover = true;
            }
            else
            {
                itemHover_i = -1;
                itemHover_j = -1;
                onButton4_hover = false;
            }
        }
        else if (screen == 3)
        {
            if (mouse_x >= window_width / 2 - 100 && mouse_y >= window_height - 200 && mouse_x <= window_width / 2 + 100 && mouse_y <= window_height - 100)
            {
                onButton5_hover = true;
            }
            else
            {
                onButton5_hover = false;
            }
        }
        break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        al_get_mouse_state(&state);
        //printf("CLIKED!!!: %d, %d\n", state.x, state.y);
        if (screen == 1)
        {
            if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 380 && mouse_y <= 480)
            {
                onButton1_hover = false;
                generator(matrix);
                rotate(vertical, matrix);
                printer(matrix);
                printf("JOJO REFERENCE STARTED, OMG\n");
                points = 0;
                moves = 25;
                screen = 2;
            }
            else if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 500 && mouse_y <= 600)
            {
                int kodWyjscia = loadGame();
                printer(matrix);
                printf("JOJO REFERENCE STARTED, OMG - LOAD\n");
                printf("Punkty: %ld\n", points);
                if (kodWyjscia == 0)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            grid[i][j].itemHeld = matrix[i][j];
                        }
                    }
                    rotate(vertical, matrix);
                    screen = 2;
                }
            }
            else if (mouse_x >= window_width / 2 - 100 && mouse_x <= window_width / 2 + 100 && mouse_y >= 620 && mouse_y <= 720)
            {
                done = true;
                printf("JOJO REFERENCE STARTED, OMG - CLOSE\n");
            }
        }
        else if (screen == 2)
        {
            if (mouse_x >= 100 && mouse_x <= 300 && mouse_y >= window_height - 200 && mouse_y <= window_height - 100)
            {
                onButton4_hover = false;
                printf("Back to the Main Menu!!!\n");
                saveGame();
                screen = 1;
            }
            else if (mouse_x >= 400 && mouse_x <= window_width - 400 && mouse_y >= 100 && mouse_y <= window_height - 100)
            {
                if (isFirst)
                {
                    itemClick1_i = (mouse_x - 400) / 60;
                    itemClick1_j = (mouse_y - 100) / 60;
                    isFirst = false;
                }
                else
                {
                    itemClick2_i = (mouse_x - 400) / 60;
                    itemClick2_j = (mouse_y - 100) / 60;
                    if ((abs(itemClick1_i - itemClick2_i) == 1 && abs(itemClick1_j - itemClick2_j) == 0) || (abs(itemClick1_i - itemClick2_i) == 0 && abs(itemClick1_j - itemClick2_j) == 1))
                    {
                        swap(matrix, vertical, itemClick1_j, itemClick1_i, itemClick2_j, itemClick2_i);
                        checkMatches(matrix);
                        itemClick1_i = -1;
                        itemClick1_j = -1;
                        itemClick2_i = -1;
                        itemClick2_j = -1;
                        isFirst = true;
                    }
                    else
                    {
                        itemClick1_i = -1;
                        itemClick1_j = -1;
                        itemClick2_i = -1;
                        itemClick2_j = -1;
                        isFirst = true;
                    }

                }

            }
        }
        else if (screen == 3)
        {
            if (mouse_x >= window_width / 2 - 100 && mouse_y >= window_height - 200 && mouse_x <= window_width / 2 + 100 && mouse_y <= window_height - 100)
            {
                onButton5_hover = false;
                screen = 1;
            }
        }
        break;
    case ALLEGRO_EVENT_KEY_DOWN:
        break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }
}