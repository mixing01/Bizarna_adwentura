#if !defined(__INIT_H)
#define __INIT_H
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#define sizeMatrix 10

typedef struct Item
{
    int x1;
    int x2;
    int y1;
    int y2;
    int itemHeld;

} Item;
extern int moves;
extern int points;
extern char pointsText[30];
extern bool isFirst;
extern int ** matrix, ** vertical;
extern int matchMatrix[sizeMatrix][sizeMatrix];
extern Item grid[sizeMatrix][sizeMatrix];
extern int mouse_x, mouse_y;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_FONT* font;
extern ALLEGRO_BITMAP* jotaro;
extern ALLEGRO_BITMAP* kakyoin;
extern ALLEGRO_BITMAP* title;
extern ALLEGRO_BITMAP* polpo;
extern ALLEGRO_MOUSE_STATE state;
extern ALLEGRO_BITMAP* tile1, * tile2, * tile3, * tile4;
extern int screen;
extern int itemHover_i;
extern int itemHover_j;
extern int itemClick1_i;
extern int itemClick1_j;
extern int itemClick2_i;
extern int itemClick2_j;
extern const int window_width;
extern const int window_height;
extern bool done;
extern bool redraw;
extern bool wasMatch;
extern bool onButton1_hover;
extern bool onButton2_hover;
extern bool onButton3_hover;
extern bool onButton4_hover;
extern bool onButton5_hover;
extern ALLEGRO_EVENT event;
extern int title_number;

void must_init(bool test, const char* description);
void init_all();
void generator(int** matrix);
void printer(int** matrix);
void rotate(int** vertical, int** matrix);
void swap(int** matrix, int** vertical, int i, int j, int x, int y);
void checkMatches(int** matrix);
int countMatches(int **matrix, int i, int j);
void saveGame();
int loadGame();
#endif