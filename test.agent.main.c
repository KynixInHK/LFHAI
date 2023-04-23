#include "board.h"
#include "KynixAI.h"

#include <stdio.h>
#include <unistd.h>

#define AGENT_ERROR 1
#define AGENT_NORMAL 0


Point human_agent(int your_color,Point last_step){
//    Point p = {0,0};
//    printf("Please input x and y:");
//    scanf("%d %d", &p.x, &p.y );
    Point p = generate();
    return p;
}

Point your_agent(int your_color,Point last_step){
  int board[N][N];
  int i,j;
  Point p;

  for(i=0;i<N;i++)
      for(j=0;j<N;j++)
          board[i][j] = get_color_at(i,j);

          //Here, I just implement a naive agent
          for(i=0;i<N;i++)
              for(j=0;j<N;j++){
                  if(EMPTY == board[i][j]) {
                      p.x =i;
                      p.y =j;
                      return p;
                  }
             }
}





int main(){
    Point p={-1,-1};
    int   color = BLACK;
    int   game_flag;
    int   exit_loop_flag = AGENT_NORMAL;


    while(1) {
        printf("Your agent is thinking...\n");sleep(1);
        p = your_agent(color,p);
        if(EMPTY == get_color_at(p.x,p.y)) {
            set_color_at(p.x,p.y,color);
            color = - color;
        } else {
            printf("Your agent gets an error,game over!\n");
            exit_loop_flag = AGENT_ERROR;
            break;
        }
        draw_board();

        game_flag = judge_board();
        if(game_flag != GAME_GO_AHEAD) break;


	      printf("Human is thinking...\n");sleep(5);
        p = human_agent(color,p);
        if(EMPTY == get_color_at(p.x,p.y)) {
            set_color_at(p.x,p.y,color);
            color = - color;
        } else {
            printf("Human agent gets an error,game over!\n");
            exit_loop_flag = AGENT_ERROR;
            break;
        }
        draw_board();
        game_flag = judge_board();
        if(game_flag != GAME_GO_AHEAD) break;
    }

    if(exit_loop_flag == AGENT_ERROR){
        printf("Game is over due to agent's error\n");
    } else {
        switch (game_flag) {
          case GAME_BLACK_WIN:printf("(BLACK) wins!\n"); break;
          case GAME_WHITE_WIN:printf("(WHITE) wins!\n"); break;
          case GAME_DRAW:     printf("You are good friends now\n");break;
        }
    }
}
