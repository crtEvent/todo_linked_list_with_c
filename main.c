#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TODODATA {
    char task[256];
    char due[256];
    struct TODODATA *pNext;
} TODODATA;

TODODATA *g_pHeadNode = NULL;

void AddFirst(const char *pszTask, const char *pszDue) {
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

void AddLast(const char *pszTask, const char *pszDue) {
    TODODATA *pNewNode = (TODODATA *)malloc(sizeof(TODODATA));
    strcpy(pNewNode->task, pszTask);
    strcpy(pNewNode->due, pszDue);
    pNewNode->pNext = NULL;

    if (g_pHeadNode == NULL) {
        g_pHeadNode = pNewNode;
    } else {
         TODODATA *pTail = g_pHeadNode;
         while (pTail->pNext != NULL) {
            pTail = pTail->pNext;
         }
         pTail->pNext = pNewNode;
    }
}

void PrintList() {
    printf("List:\n");
    TODODATA *pTmp = g_pHeadNode;
    
    if (pTmp == NULL) {
        printf("\tList is empty\n");
        return;
    }

    int count = 0;
    while (pTmp != NULL) {
        count++;
        printf("\t[%p] %s, %s [%p]\n", 
            pTmp, pTmp->task, pTmp->due, pTmp->pNext);
        pTmp = pTmp->pNext;
    }
    printf("\t%d Tasks\n", count);
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

void RemoveByTask(const char *pszTask) {
    TODODATA *pCurrent = g_pHeadNode;
    TODODATA *pPrev = NULL;
    while (pCurrent != NULL) {
        if (strcmp(pszTask, pCurrent->task) == 0) {
            if (pPrev == NULL) {
                g_pHeadNode = pCurrent->pNext;
            } else {
                pPrev->pNext = pCurrent->pNext;
            }
            printf("Delete: [%p] %s, %s [%p]\n", 
                pCurrent, pCurrent->task, pCurrent->due, pCurrent->pNext);
            free(pCurrent);
            return;
        }
        pPrev = pCurrent;
        pCurrent = pCurrent->pNext;
    }
}

TODODATA* SearchByTask(const char* pszTask) {
    TODODATA *pTmp = g_pHeadNode;
    while (pTmp != NULL) {
        if (strcmp(pszTask, pTmp->task) == 0) {
            printf("Found: [%p] %s, %s [%p]\n",
                pTmp, pTmp->task, pTmp->due, pTmp->pNext);
            return pTmp;
        }
        pTmp = pTmp->pNext;
    }
    return NULL;
}

int main() {
    AddLast("Task 4", "2024-09-04");
    AddLast("Task 5", "2024-09-05");
    AddLast("Task 6", "2024-09-06");
    AddFirst("Task 3", "2024-09-03");
    AddFirst("Task 2", "2024-09-02");
    AddFirst("Task 1", "2024-09-01");

    PrintList();

    SearchByTask("Task 6");
    SearchByTask("Task 5");
    SearchByTask("Task 4");
    SearchByTask("Task 3");
    SearchByTask("Task 2");
    SearchByTask("Task 1");

    RemoveByTask("Task 5");
    RemoveByTask("Task 1");
    RemoveByTask("Task 3");

    PrintList();

    ReleaseList();

    PrintList();

    printf("Done\n");
    return 0;
}