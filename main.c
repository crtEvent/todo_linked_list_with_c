#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TODODATA {
    char task[256];
    char due[256];
    struct TODODATA *pNext;
} TODODATA;

TODODATA *g_pHeadNode = NULL;

void AddNewNode(const char *pszTask, const char *pszDue) {
    TODODATA *pNewNode = (TODODATA *)malloc(sizeof(TODODATA));
    strcpy(pNewNode->task, pszTask);
    strcpy(pNewNode->due, pszDue);
    pNewNode->pNext = NULL;

    if (g_pHeadNode == NULL) {
        g_pHeadNode = pNewNode;
    } else {
        pNewNode->pNext = g_pHeadNode;
        g_pHeadNode = pNewNode;
    }
}

void ReleaseList(void) {
    TODODATA *pTmp = g_pHeadNode;
    TODODATA *pDelete;
    while (pTmp != NULL) {
        pDelete = pTmp;
        pTmp = pTmp->pNext;

        printf("Delete: [%p] %s, %s [%p]\n", 
            pDelete, pDelete->task, pDelete->due, pDelete->pNext);

        free(pDelete);
    }

    g_pHeadNode = NULL;
}

int main() {
    AddNewNode("Task 1", "2024-09-01");
    AddNewNode("Task 2", "2024-09-02");
    AddNewNode("Task 3", "2024-09-03");

    TODODATA *pTmp = g_pHeadNode;
    while (pTmp != NULL) {
        printf("[%p] %s, %s [%p]\n", 
            pTmp, pTmp->task, pTmp->due, pTmp->pNext);
        pTmp = pTmp->pNext;
    }

    ReleaseList();

    return 0;
}