#include <stdio.h>
#include "board.h"
static int board[N][N];
int get_color_at(int x,int y){
	if(x<0||x>N||y<0||y>N){
		return ERROR;
	}else
		return board[x][y];
}
void set_color_at(int x,int y,int color){
	board[x][y] = color;	
}
int judge_board(){
        int x, y;
        for (x = 0; x < N; x++){
                for (y = 0; y < N; y++){
                        if (board[x][y] == EMPTY)
                                continue;
                        if (y < N-4)
                                if (board[x][y] == board[x][y + 1] && board[x][y] == board[x][y + 2]&& board[x][y] == board[x][y + 3] && board[x][y] == board[x][y + 4]){
                                        if(board[x][y] == BLACK)
						return GAME_BLACK_WIN;
					else
						return GAME_WHITE_WIN;
				}
                        if (x < N-4)
                                if (board[x][y] == board[x + 1][y] && board[x][y] == board[x + 2][y]&& board[x][y] == board[x + 3][y] && board[x][y] == board[x + 4][y]){
                                        if(board[x][y] == BLACK)
                                                return GAME_BLACK_WIN;
                                        else
                                                return GAME_WHITE_WIN;
                                }
                        if (x < N-4&& y < N-4)
                                if (board[x][y] == board[x + 1][y + 1] && board[x][y] == board[x + 2][y + 2]&& board[x][y] == board[x + 3][y + 3] && board[x][y] == board[x + 4][y + 4]){
                                        if(board[x][y] == BLACK)
                                                return GAME_BLACK_WIN;
                                        else
                                                return GAME_WHITE_WIN;
                                }
                        if (x < N-4&&y>3)
                                if (board[x][y] == board[x + 1][y - 1] && board[x][y] == board[x + 2][y - 2]&& board[x][y] == board[x + 3][y - 3] && board[x][y] == board[x + 4][y - 4]){
                                        if(board[x][y] == BLACK)
                                                return GAME_BLACK_WIN;
                                        else
                                                return GAME_WHITE_WIN;
                                }
                }
        }
	return GAME_GO_AHEAD;
}
void draw_board(){
	int x = 0,y = 0;
	printf(" ");
	for(x = 0;x < N;x++){
		printf("%d ",x%10);
		if(x==N-1)
			printf("\n");
	}
	for (x = 0; x < N ; x++){

                printf("%d",x%10);
                        for (y = 0; y < N; y++){
				if (board[x][y] == WHITE)
					printf("● ");
				if (board[x][y] == BLACK)
					printf("○ ");
				if (board[x][y] == EMPTY)
					printf("+ ");
                        }
                        printf("\n");
        }
}
