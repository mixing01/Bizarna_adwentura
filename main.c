#include "main.h"



int main()
{
    init_all();

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        handle_events();

        if (done)
            break;

        if ((screen == 1) && redraw && al_is_event_queue_empty(queue))
        {
            draw_title();
            redraw = false;
        }        
        else if ((screen == 2) && redraw && al_is_event_queue_empty(queue))
        {
            draw_game();
            redraw = false;
        }
        else if ((screen == 3) && redraw && al_is_event_queue_empty(queue))
        {
            draw_credits();
            redraw = false;
        }
        else if ((screen == 4) && redraw && al_is_event_queue_empty(queue))
        {
            draw_easterEgg();
            redraw = false;
        }

    }

    al_destroy_bitmap(jotaro);
    al_destroy_bitmap(title);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}