#ifndef __SPD_PRAGMA__
#define __SPD_PRAGMA__

#include <stdbool.h>

extern void __spd_begin(unsigned int region_number);
extern void __spd_loop(unsigned int region_number,
                       unsigned int vector_length,
                       unsigned int unroll_count,
                       bool switch_in_out);
extern void __spd_end(unsigned int region_number);

#endif // __SPD_PRAGMA__
