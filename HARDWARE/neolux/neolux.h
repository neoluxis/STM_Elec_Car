/**
 * @file neolux.h
 * @author Neolux Lee (neolux.lee@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __NEOLUX_H__
#define __NEOLUX_H__

#include "main.h"
#include "stdio.h"

#define __NEOLUX_DEBUG

#define NOBUG "                                  \n\
                    _oo0oo_                       \n\
                   088888880                      \n\
                   88\" . \"88                    \n\
                   (| -_- |)                      \n\
                    0\ = /0                       \n\
                 ___/'---'\___                    \n\
               .' \\\\\\\\|     |// '.            \n\
              / \\\\\\\\|||  :  |||// \\\\        \n\
             /_ ||||| -:- |||||- \\\\             \n\
            |   | \\\\\\\\\\\\  -  /// |   |      \n\
            | \\_|  ''\\---/''  |_/ |             \n\
            \  .-\\__  '-'  __/-.  /              \n\
          ___'. .'  /--.--\\  '. .'___            \n\
       .\"\" '<  '.___\\_<|>_/___.' >'  \"\".     \n\
      | | : '-  \\'.;'\\ _ /';.'/ - ' : | |       \n\
      \\  \\ '_.   \\_ __\\ /__ _/   .-' /  /     \n\
  ====='-.____'.___ \\_____/___.-'____.-'=====    \n\
                    '=---='                       \n\
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \n\
|         佛祖保佑    iii    永无BUG             |  \n\
|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|  \n\
|----------------------------------------------|  \n\
" // NO BUG BUDHA

// #pragma diag_suppress 77,550,1294,1295
#pragma diag_suppress 870

#define NEOLUXLEE_SHADOW "\r\n\
███╗   ██╗███████╗ ██████╗ ██╗     ██╗   ██╗██╗  ██╗    ██╗     ███████╗███████╗\r\n\
████╗  ██║██╔════╝██╔═══██╗██║     ██║   ██║╚██╗██╔╝    ██║     ██╔════╝██╔════╝\r\n\
██╔██╗ ██║█████╗  ██║   ██║██║     ██║   ██║ ╚███╔╝     ██║     █████╗  █████╗  \r\n\
██║╚██╗██║██╔══╝  ██║   ██║██║     ██║   ██║ ██╔██╗     ██║     ██╔══╝  ██╔══╝  \r\n\
██║ ╚████║███████╗╚██████╔╝███████╗╚██████╔╝██╔╝ ██╗    ███████╗███████╗███████╗\r\n\
╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═╝    ╚══════╝╚══════╝╚══════╝\r\n\
"

#ifdef __NEOLUX_DEBUG

#define neolux_info(format, ...) printf("[neolux.c] info:  " format "\r\n", ##__VA_ARGS__)
#define neolux_debug(format, ...) printf("[neolux.c] debug: " format "\r\n", ##__VA_ARGS__)
#define neolux_error(format, ...) printf("[neolux.c] error: " format "\r\n", ##__VA_ARGS__)
#else

#define neolux_info(format, ...)
#define neolux_debug(format, ...)
#define neolux_error(format, ...)
#endif

#endif // __NEOLUX_H__
