#ifndef __GET_XY_H_
#define __GET_XY_H_
#include <stdio.h>
#include <linux/input.h>//触摸
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "lcdjpg.h"

extern int ts_fd;//变量声明
extern int lcd_fd;
extern int *lcd_ptr;

int get_xy(int *x, int *y);//函数声明

#endif