#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void update(unsigned char *in, unsigned char *out, size_t row, size_t col) {
    uint8_t counter = 0;

    memcpy(out, in, row*col);

    for (size_t y = 0; y <= row; y++) 
    for (size_t x = 0; x <= col; x++) {
        counter = 0;
        for (int8_t offset_x = -1; offset_x < 2; offset_x++)
        for (int8_t offset_y = -1; offset_y < 2; offset_y++) {
            if (offset_y == 0 && offset_x == 0) continue;
            
            if (x+offset_x < 0)
                continue;
            if (x+offset_x >= col)
                continue;
            if (y+offset_y < 0)
                continue;
            if (y+offset_y >= row)
                continue;
            
            if (in[(x+offset_x)+((y+offset_y)*col)])
                counter += 1;
        }
        
        if (!in[x+(y*col)] && counter == 3)
            out[x+(y*col)] = 1;
        if (in[x+(y*col)] && (counter != 2 && counter != 3))
            out[x+(y*col)] = 0;
    }

}