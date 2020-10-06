#ifndef __GOL_DEFINES_H__
#define __GOL_DEFINES_H__

#include <stdlib.h>

#define termclear() fwrite("\033[H\033[J\033[0m", 1, 10, stdout)
#define UPDATE_INTERVAL 100000

#endif