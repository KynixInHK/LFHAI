//
// Created by kynix on 4/23/23.
// 本算法采用博弈树算法，辅以Alpha-Beta剪枝
// 请根据实际情况修改evaluate评估函数的内容
//
#include "board.h"
#include "KynixAI.h"
#include <stdio.h>
int evaluate(int board[N][N], int player);
int count = 0;
int max(int num_1, int num_2);
int min(int num_1, int num_2);
int calc(int depth, int alpha, int beta, int isMaxPlayer, int board[N][N]);
Evaluations evaluations;
Point generate() {
    int board[N][N];
    count = 0;
    int i, j;
    for(i = 0;i < N*N;i ++) {
        Evaluation e = {0, 0, -10000000};
        evaluations[i] = e;
    }
    // 获取当前棋局
    for(i = 0;i < N;i ++) {
        for(j = 0;j < N; j ++) {
            board[i][j] = get_color_at(i, j);
        }
    }

    // 执行计算
    int max_score = calc(3, -1000000, 1000000, TRUE, board);
    Evaluation result_score = {0,0,-10000000};
    for(i = 0;i < count;i ++) {
//        result_score.score = evaluations[i].score > result_score.score ? evaluations[i].score : result_score.score;
//        result_score.x = evaluations[i].score > result_score.score ? evaluations[i].x : result_score.x;
//        result_score.y = evaluations[i].score > result_score.score ? evaluations[i].y : result_score.y;
        if(evaluations[i].score > result_score.score) {
            result_score.score = evaluations[i].score;
            result_score.x = evaluations[i].x;
            result_score.y = evaluations[i].y;
        }
    }
    Point point = {result_score.x, result_score.y};
    return point;
}


/*
 * 引数说明：
 * 1. depth：搜索深度
 * 2. alpha：当前搜索到的极大值
 * 3. beta：当前搜索到的极小值
 * 4. isMaxPlayer：是否是机器人，是为1（TRUE），否为0（FALSE）
 * 5. board：当前棋局
 * */
int calc(int depth, int alpha, int beta, int isMaxPlayer, int board[N][N]) {
    int i,j;
    int k = 0;
    if(depth == 0) {
        return evaluate(board, isMaxPlayer);
    }

    // 机器人算法：执行博弈树
    if(isMaxPlayer == TRUE) {
        int max_eval = -1000000; // 初始极大值为近似-inf
        // 遍历每一个可能的落子位置
        for(i = 0;i < N;i ++) {
            for(j = 0;j < N;j ++) {
                if(board[i][j] == EMPTY) {
                    board[i][j] = WHITE; // 模拟执行落子
                    int eval = calc(depth - 1, alpha, beta, FALSE, board); // 递归，直到game over或者达到最大的depth
                    board[i][j] = EMPTY; // 模拟撤销落子，因为递归已经完成，需要对下一个可能的落子点进行推演和评估
                    max_eval = max(max_eval,eval); // 获取当前节点之子节点的最高分值
                    alpha = max(alpha, eval); // 更新alpha值，永远保持当前搜索层级的极大值
                    if(beta <= alpha) break; // 执行alpha-beta剪枝-1
                    if(depth == 3) {
                        Evaluation eva = { i,j, max_eval };
                        evaluations[k] = eva;
                        count ++;
                        k ++;
                    }
                }
            }
            if(j < N) break; // 执行alpha-beta剪枝-2
        }
        return max_eval;
    }
    // 对手算法：执行最劣解
    else {
        int min_eval = 1000000; //初始极小值近似为+inf
        // 遍历每一个可能的落子位置
        for(i = 0;i < N;i ++) {
            for(j = 0;j < N;j ++) {
                if(board[i][j] == EMPTY) {
                    board[i][j] = BLACK; // 模拟执行落子
                    int eval = calc(depth - 1, alpha, beta, TRUE, board); // 递归，直到game over或者达到最大的depth
                    board[i][j] = EMPTY; // 模拟撤销落子，因为递归已经完成，需要对下一个可能的落子点进行推演和评估
                    min_eval = min(min_eval,eval); // 获取当前节点之子节点的最高分值
                    beta = min(beta, eval); // 更新alpha值，永远保持当前搜索层级的极大值
                    if(beta <= alpha) break; // 执行alpha-beta剪枝-1
                }
            }
            if(j < N) break; // 执行alpha-beta剪枝-2
        }
        return min_eval;
    }
}

int max(int num_1, int num_2) {
    if(num_1 >= num_2) return num_1;
    else return num_2;
}

int min(int num_1, int num_2) {
    if(num_1 <= num_2) return num_1;
    else return num_2;
}

/*
 * 引数说明：
 * 1. board: 当前棋局
 * 2. player：当前执棋的玩家
 * 函式说明：评估函数，用于评估当前棋局的score，评估指标如下：
 * 1. 空位评估
 * 2. 连续线
 * 3. 威胁线
 * 备注：评估函式是从ChatGPT那里抄来的，叔叔不是很精通五子棋，故评估函式可以替换掉。
 * */
int evaluate(int board[N][N], int player) {
    // 分数
    int score = 0;
    int i,j;
    // 空位评估
    for(i = 0;i < N;i ++) {
        for(j = 0;j < N;j ++) {
            if(board[i][j] == EMPTY) {
                int pos_score = 0;
                // 己方局or对方局，己方局给正分数，对方局给负分数
                if(player == 1) {
                    pos_score += 10;
                } else {
                    pos_score -= 10;
                }

                // 中心位置得分较高
                if (i == 7 && j == 7) {
                    pos_score += 5;
                }

                // 如果当前位置周围有己方棋子，增加得分
                if (i > 0 && board[i-1][j] == 1) {
                    pos_score += 2;
                }
                if (i < 14 && board[i+1][j] == 1) {
                    pos_score += 2;
                }
                if (j > 0 && board[i][j-1] == 1) {
                    pos_score += 2;
                }
                if (j < 14 && board[i][j+1] == 1) {
                    pos_score += 2;
                }

                // 如果当前位置周围有对方棋子，减少得分
                if (i > 0 && board[i-1][j] == -1) {
                    pos_score -= 1;
                }
                if (i < 14 && board[i+1][j] == -1) {
                    pos_score -= 1;
                }
                if (j > 0 && board[i][j-1] == -1) {
                    pos_score -= 1;
                }
                if (j < 14 && board[i][j+1] == -1) {
                    pos_score -= 1;
                }

                // 当前位置连续线
                int k;
                int line_score = 0;
                // 水平线
                int horizontal_score = 0;
                for (k = j - 1; k >= 0; k --) { // 向左搜索
                    if (board[i][k] == 1) {
                        horizontal_score += 3;
                    } else {
                        break;
                    }
                }

                for (k = j + 1; k < N; k ++) { // 向右搜索
                    if (board[i][k] == 1) {
                        horizontal_score += 3;
                    } else {
                        break;
                    }
                }

                // 竖直线
                int vertical_score = 0;
                for(k = i - 1;k >= 0;k --) { // 向上搜索
                    if (board[k][j] == 1) {
                        vertical_score += 3;
                    } else {
                        break;
                    }
                }

                for(k = i + 1;k < N;k ++) { // 向下搜索
                    if (board[k][j] == 1) {
                        vertical_score += 3;
                    } else {
                        break;
                    }
                }

                // 左斜线
                int left_slash_score = 0;
                for(k = i - 1; k >= 0; k --) {
                    if(j - 1 < 0) {
                        break;
                    } else {
                        if(board[k][j - 1] == 1) {
                            left_slash_score += 3;
                        } else {
                            break;
                        }
                    }
                }

                for(k = i + 1; k < N; k ++) {
                    if(j + 1 >= N) {
                        break;
                    } else {
                        if(board[k][j + 1] == 1) {
                            left_slash_score += 3;
                        } else {
                            break;
                        }
                    }
                }

                // 右斜线
                int right_slash_score = 0;
                for(k = i + 1; k < N; k ++) {
                    if(j - 1 < 0) {
                        break;
                    } else {
                        if(board[k][j - 1] == 1) {
                            right_slash_score += 3;
                        } else {
                            break;
                        }
                    }
                }

                for(k = i - 1; k >= 0; k ++) {
                    if(j + 1 >= N) {
                        break;
                    } else {
                        if(board[k][j + 1] == 1) {
                            right_slash_score += 3;
                        } else {
                            break;
                        }
                    }
                }
                // 最高分为连续线最终得分
                line_score = max(max(max(horizontal_score, vertical_score), left_slash_score), right_slash_score);

                // 当前位置威胁线
                int danger_score = 0;
                if ((j - 1 >= 0 && board[i][j - 1] == 1) && (j + 1 < N && board[i][j + 1] == 1)) {
                    // 左侧空位可以形成连续五子
                    if (j - 2 >= 0 && board[i][j - 2] == 0) {
                        danger_score += 3;
                    }
                    // 右侧空位可以形成连续五子
                    if (j + 2 < N && board[i][j + 2] == 0) {
                        danger_score += 3;
                    }
                }

                score += (pos_score + line_score + danger_score);
            }
        }
    }
    return score;
}