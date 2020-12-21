#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

#include "lights.h"
#include "bouncing_balls.h"
#include "light_effects.h"

volatile bool running = true;
static void ctrl_c_handler(int signum)
{
        (void)(signum);
    running = false;
}

static void setup_handlers(void)
{
    struct sigaction sa =
    {
        .sa_handler = ctrl_c_handler
    };
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main()
{
    init_lights();
    setup_handlers();
    uint8_t mode = 0;
    uint32_t color;
    while (running)
    {
        switch (mode)
        {
        case 0:
            BouncingBalls(255, 0, 0, 3);
            break;
        case 1:
            color = get_random_color();
            NewKITT(color >> 16, (color >> 8) & 0xFF, color & 0xFF, 8, 10, 50);
            break;

        case 2:
            rainbowCycle(20);
        default:
            TwinkleRandom(20, 100, false);
            break;
        }
    }   
    
    free_lights();
    printf("Exiting \r\n");
    return 0;
}