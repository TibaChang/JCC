#ifndef __DEBUG_H_
#define __DEBUG_H_
#include <stdio.h>


#if defined(JCC_DEBUG)
    #define DBG_printf(...)  printf(__VA_ARGS__)
#else
    #define DBG_printf(...)
    /*
     * #warning "If you would like to open DEBUG function in JCC,please check the Makefile!"
     */
#endif



#endif
