#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TODODATA {
    char task[256];
    char due[256];
    struct TODODATA *pNext;
} TODODATA;

TODODATA *g_pHeadNode = NULL;

int main() {
    TODODATA *pTmp = g_pHeadNode;
    while (pTmp != NULL) {
        printf("[%p] %s, %s [%p]\n", 
            pTmp, pTmp->task, pTmp->due, pTmp->pNext);
        pTmp = pTmp->pNext;
    }
    return 0;
}
