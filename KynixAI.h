//
// Created by kynix on 4/23/23.
//

#ifndef AGENT_KYNIXAI_H
#define AGENT_KYNIXAI_H
#define TRUE 1
#define FALSE -1

#include "board.h"

typedef struct {
    int x;
    int y;
    int score;
} Evaluation,Evaluations[N*N];

Point generate();

#endif //AGENT_KYNIXAI_H
