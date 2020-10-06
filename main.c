#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "defines.h"
#include "update.h"

int main (void) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    unsigned char *a = calloc((w.ws_col-2)*((w.ws_row-2)*2), 1);
    unsigned char *b = calloc((w.ws_col-2)*((w.ws_row-2)*2), 1);
    unsigned char *current = a;

    if (!b || !a) {
        perror("calloc");
        return -1;
    }

    for (size_t i = 0; i < (w.ws_col-2)*((w.ws_row-2)*2); i++)
        a[i] = (rand()%10 == 0);

    while (1) {
        termclear();
        for (size_t y = 0; y < w.ws_row; y++) {
            for (size_t x = 0; x < w.ws_col; x++) {
                if (y == 0 || x == 0 || y == w.ws_row-1 || x == w.ws_col-1)
                    fwrite("\033[100m ", 7, 1, stdout);
                else {
                    size_t y_tmp = (y-1)*2;
                    size_t x_tmp = (x-1)*2;

                    if (current[x+(y*(w.ws_col-2))])
                        fwrite("\033[107m", 6, 1, stdout);
                    else
                        fwrite("\033[40m", 5, 1, stdout);

                    if (current[x+((y+1)*(w.ws_col-2))])
                        fwrite("\033[97m", 5, 1, stdout);
                    else
                        fwrite("\033[30m", 5, 1, stdout);
                    fwrite("▄", 3, 1, stdout);
                }
            }
        }

        update(current, (current==a) ? b : a, (w.ws_row-2)*2, w.ws_col-2);
        current = (current==a) ? b : a;
        usleep(UPDATE_INTERVAL);
    }

    return 0;
}