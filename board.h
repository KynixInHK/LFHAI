#ifndef BOARD_H
#define BOARD_H

#define N 15
#define BLACK  1
#define WHITE  -1
#define EMPTY  0
#define ERROR  2

#define GAME_BLACK_WIN  1
#define GAME_WHITE_WIN  -1
#define GAME_GO_AHEAD   0
#define GAME_DRAW       2 


typedef struct {
    int x;
    int y;
} Point;

void draw_board();
int  judge_board();
void set_color_at(int x,int y, int color);
int  get_color_at(int x,int y);

#endif

