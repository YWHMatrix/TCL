#ifndef __GAME_2048_H_
#define __GAME_2048_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "lcdjpg.h"
#include<time.h>
#include "get_xy.h"

extern int ts_fd, lcd_fd;
extern int* lcd_ptr;

int get_piece_index(int x);
int get_zeros_count();
int get_finger_direction();

void draw_matrix();
void init_matrix();
void rand_matrix();
int change_matrix();

void fin_left();
void fin_right();
void fin_up();
void fin_down();

int move_judge();

int set_matrix_value(int x, int value);

int lcd_draw_dect(int x, int y, int w, int h, int color);

int game2048();


#endif