#include "init.h"

int moves = 25;
Item grid[10][10];
int matchMatrix[sizeMatrix][sizeMatrix];
int points = 0;
char pointsText[30] = "Punkty:";
int** matrix, ** vertical;
int mouse_x, mouse_y;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;
ALLEGRO_BITMAP* jotaro;
ALLEGRO_BITMAP* kakyoin;
ALLEGRO_BITMAP* title;
ALLEGRO_BITMAP* polpo;
ALLEGRO_BITMAP* tile1, *tile2, *tile3, *tile4;
ALLEGRO_MOUSE_STATE state;
int screen = 1;
int itemHover_i = -1;
int itemHover_j = -1;
int itemClick1_i = -1;
int itemClick1_j = -1;
int itemClick2_i = -1;
int itemClick2_j = -1;
const int window_width = 1400;
const int window_height = 800;
bool isFirst = true;
bool done = false;
bool redraw = true;
bool wasMatch = false;
bool onButton1_hover = false;
bool onButton2_hover = false;
bool onButton3_hover = false;
bool onButton4_hover = false;
bool onButton5_hover = false;
ALLEGRO_EVENT event;
int title_number = 0;

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void init_all()
{   
    srand(time(NULL));
    matrix = malloc(sizeMatrix * sizeof * matrix);
    vertical = malloc(sizeMatrix * sizeof * vertical);
    for (int z = 0; z < sizeMatrix; z++) {
        matrix[z] = malloc(sizeMatrix * sizeof * matrix[z]);
        vertical[z] = malloc(sizeMatrix * sizeof * vertical[z]);
    }
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_font_addon(), "fonts");
    must_init(al_init_ttf_addon(), "ttf");

    timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(window_width, window_height);
    must_init(disp, "display");

    font = al_load_font("Fonts/Font_menu.ttf", 20, 0);
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    kakyoin = al_load_bitmap("Graphics/Kakyoin.png");
    jotaro = al_load_bitmap("Graphics/Jotaro.png");
    title = al_load_bitmap("Graphics/Title.png");
    polpo = al_load_bitmap("Graphics/Polpo.jpg");
    must_init(jotaro, "jotaro");
    must_init(kakyoin, "kakyoin");
    must_init(title, "title");
    must_init(polpo, "polpo");

    tile1 = al_load_bitmap("Graphics/tile1.png");
    must_init(tile1, "tile1");
    tile2 = al_load_bitmap("Graphics/tile2.png");
    must_init(tile2, "tile2");
    tile3 = al_load_bitmap("Graphics/tile3.png");
    must_init(tile3, "tile3");
    tile4 = al_load_bitmap("Graphics/tile4.png");
    must_init(tile4, "tile4");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j].x1 = 400 + j * 60;
            grid[i][j].x2 = 400 + (j + 1) * 60;
            grid[i][j].y1 = 100 + i * 60;
            grid[i][j].y2 = 100 + (i + 1) * 60;
            matchMatrix[i][j] = 0;
        }
    }
}

void generator(int** matrix)
{
    int i, j, num;
    for (i = 0; i < sizeMatrix; i++) 
    {
        for (j = 0; j < sizeMatrix; j++) 
        {
            num = (rand() % 4) + 1;
            if (j >= 2) 
            {
                while (num == matrix[i][j - 2]) 
                {
                    num = (rand() % 4) + 1;
                }
            }
            if (i >= 2)
            {
                while (num == matrix[i-2][j])
                {
                    num = (rand() % 4) + 1;
                }
            }
            if (j >= 2 && i>= 2) 
            {
                while (num == matrix[i][j - 2] || num == matrix[i - 2][j]) 
                {
                    num = (rand() % 4) + 1;
                }

            }

            matrix[i][j] = num;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j].itemHeld = matrix[i][j];
        }
    }
}

void printer(int** matrix)
{
    int i, j;
    printf("\n");
    for (i = 0; i < sizeMatrix; i++) {
        for (j = 0; j < sizeMatrix; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void rotate(int** vertical, int** matrix)
{
    int i, j;
    for (i = 0; i < sizeMatrix; i++) {
        for (j = 0; j < sizeMatrix; j++) {
            vertical[i][j] = matrix[j][i];
        }
    }
}

void saveGame()
{
    FILE* plikZapisu;
    plikZapisu = fopen("save.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(plikZapisu, "%d ", matrix[i][j]);
        }
        fprintf(plikZapisu, "\n");
    }
    fprintf(plikZapisu, "%ld", points);
    fprintf(plikZapisu, "d");
    fprintf(plikZapisu, "%ld", moves);
    fprintf(plikZapisu, "d");
    fclose(plikZapisu);

}

int loadGame()
{
    int macierzTemp[10][10];
    int punktyTemp = 0, ruchyTemp = 0;
    FILE* plikZapisu;
    plikZapisu = fopen("save.txt", "r");
    printf("1\n");
    if (feof(plikZapisu))
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                macierzTemp[i][j] = getc(plikZapisu) - 48;
                getc(plikZapisu);
            }
            getc(plikZapisu);
        }
        printf("2\n");
        char znak = getc(plikZapisu);
        while (znak != 'd')
        {
            punktyTemp = punktyTemp * 10 + (((int) znak) - 48);
            znak = getc(plikZapisu);
        }
        znak = getc(plikZapisu);
        while (znak != 'd')
        {
            ruchyTemp = ruchyTemp * 10 + (((int)znak) - 48);
            znak = getc(plikZapisu);
        }
        printf("3\n");
        fclose(plikZapisu);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                matrix[i][j] = macierzTemp[i][j];
            }
        }
        points = punktyTemp;
        moves = ruchyTemp;
        printf("4\n");
        return 0;
    }
    
}

void checkMatches(int** matrix)
{
    wasMatch = false;
    int beginning_i, beginning_j, end_i, end_j;
    for (int i = 0; i < sizeMatrix; i++)
    {
        beginning_j = 0;
        for (int j = 1; j < sizeMatrix; j++)
        {
            if (matrix[i][j] != matrix[i][beginning_j])
            {
                if (j - beginning_j >= 3)
                {
                    wasMatch = true;
                    for (int k = beginning_j; k < j; k++)
                    {
                        matchMatrix[i][k] = matrix[i][k];
                    }
                }
                beginning_j = j;
            }
        }
        if (10 - beginning_j >= 3)
        {
            wasMatch = true;
            for (int k = beginning_j; k < 10; k++)
            {
                matchMatrix[i][k] = matrix[i][k];
            }
        }

    }
    for (int j = 0; j < sizeMatrix; j++)
    {
        beginning_i = 0;
        for (int i = 1; i < sizeMatrix; i++)
        {
            if (matrix[i][j] != matrix[beginning_i][j])
            {
                if (i - beginning_i >= 3)
                {
                    wasMatch = true;
                    for (int k = beginning_i; k < i; k++)
                    {
                        matchMatrix[k][j] = matrix[k][j];
                    }
                }
                beginning_i = i;
            }
        }
        if (10 - beginning_i >= 3)
        {
            wasMatch = true;
            for (int k = beginning_i; k < 10; k++)
            {
                matchMatrix[k][j] = matrix[k][j];
            }
        }

    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", matchMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int countMatches(int **matrix, int i, int j)
{
    int counter = 1, figure = matchMatrix[i][j];
    if (figure == 0)
    {
        return 0;
    }
    matchMatrix[i][j] = 0;
    matrix[i][j] = (rand() % 4) + 1;
    for (int k = i-1; k > 0; k--)
    {
        if (matchMatrix[k][j] != figure || matchMatrix[k][j] == 0)
        {
            break;
        }
        else
        {
            counter++;
            matchMatrix[k][j] = 0;
            matrix[k][j] = (rand() % 4) + 1;
            grid[k][j].itemHeld = matrix[k][j];

        }
    }
    for (int k = i + 1; k < 10; k++)
    {
        if (matchMatrix[k][j] != figure || matchMatrix[k][j] == 0)
        {
            break;
        }
        else
        {
            counter++;
            matchMatrix[k][j] = 0;
            matrix[k][j] = (rand() % 4) + 1;
            grid[k][j].itemHeld = matrix[k][j];
        }
    }
    for (int k = j - 1; k > 0; k--)
    {
        if (matchMatrix[i][k] != figure || matchMatrix[i][k] == 0)
        {
            break;
        }
        else
        {
            counter++;
            matchMatrix[i][k] = 0;
            matrix[i][k] = (rand() % 4) + 1;
            grid[i][k].itemHeld = matrix[i][k];
        }
    }
    for (int k = j + 1; k < 10; k++)
    {
        if (matchMatrix[i][k] != figure || matchMatrix[i][k] == 0)
        {
            break;
        }
        else
        {
            counter++;
            matchMatrix[i][k] = 0;
            matrix[i][k] = (rand() % 4) + 1;
            grid[i][k].itemHeld = matrix[i][k];
        }
    }
    return obliczPunkty(counter);
}

int obliczPunkty(int counter)
{
    int wynik = 0;
    for (int i = counter; i >= 3; i--)
    {
        wynik += i * 100;
    }
    return wynik;

}

void swap(int** matrix, int** vertical, int i, int j, int x, int y)
{
    int temp = matrix[i][j];
    matrix[i][j] = matrix[x][y];
    vertical[j][i] = vertical[y][x];
    vertical[y][x] = temp;
    matrix[x][y] = temp;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j].itemHeld = matrix[i][j];
        }
    }
    moves--;
}