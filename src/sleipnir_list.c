// Copyright 2024 Mykola Hohsadze
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "sleipnir_list.h"

#include <stddef.h>

struct SpList {
    struct SpAllocationCallbacks *pAllocationCallbacks;
    struct SpListNode *head;
    struct SpListNode *tail;
    size_t count;
};

struct SpList *spListCreate(struct SpAllocationCallbacks *pAllocationCallbacks) {
    if (pAllocationCallbacks == NULL)
        return NULL;

    struct SpList *pList = pAllocationCallbacks->pfnAllocation(sizeof(struct SpList));
    pList->head = NULL;
    pList->tail = NULL;
    pList->count = 0;
    pList->pAllocationCallbacks = pAllocationCallbacks;

    return pList;
}

void spListDestroy(struct SpList *pList,
                   PFN_spListDestroyFreeUserDataFunction pfnUserDataDestroy) {
    if (pList == NULL)
        return;

    struct SpListNode *pCurrent = pList->head;
    struct SpListNode *pTemp = NULL;

    while (pCurrent != NULL) {
        pTemp = pCurrent;
        pCurrent = pCurrent->next;

        pfnUserDataDestroy(pTemp->data);
        pList->pAllocationCallbacks->pfnFree(pTemp);
    }
    pList->head = NULL;
    pList->tail = NULL;
    pList->count = 0;
    pList->pAllocationCallbacks->pfnFree(pList);
}

void spListAdd(struct SpList *pList, void *data) {
    struct SpListNode *pNode = pList->pAllocationCallbacks->pfnAllocation(sizeof(struct SpListNode));
    pNode->data = data;
    pNode->next = NULL;

    if (pList->head == NULL)
        pList->head = pNode;
    else
        pList->tail->next = pNode;

    pList->tail = pNode;
    pList->count++;
}

bool spListRemoveNodeIf(struct SpList *pList,
                        PFN_spListEqualityComparerFunction comparer,
                        struct SpListNode *pOtherNode) {
    struct SpListNode *pCurrent = pList->head;
    struct SpListNode *pPrevious = NULL;
    struct SpListNode *pTemp = NULL;

    while (pCurrent != NULL) {
        if (!comparer(pCurrent, pOtherNode)) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
            continue;
        }
        pTemp = pCurrent;
        if (pPrevious != NULL) {
            pPrevious->next = pCurrent->next;
            if (spListIsLastNode(pList, pCurrent))
                pList->tail = pPrevious;
        } else {
            pList->head = pList->head->next;
            if (pList->head == NULL)
                pList->tail = NULL;
        }
        pList->pAllocationCallbacks->pfnFree(pTemp);
        pList->count--;
        return true;
    }

    return false;
}

bool spListIsLastNode(struct SpList *pList, struct SpListNode *pNode) {
    return pList->tail == pNode;
}
