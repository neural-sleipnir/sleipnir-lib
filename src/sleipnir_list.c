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

struct SpListIterator {
    struct SpListNode *pCurrentNode;
    size_t currentIndex;
};

struct SpList {
    struct SpAllocationCallbacks *pAllocationCallbacks;
    struct SpListNode *pHead;
    struct SpListNode *pTail;
    size_t count;
    struct SpListIterator *pIterator;
};

struct SpList *spListCreate(struct SpAllocationCallbacks *pAllocationCallbacks) {
    if (pAllocationCallbacks == NULL)
        return NULL;

    struct SpList *pList = pAllocationCallbacks->pfnAllocation(sizeof(struct SpList));
    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->count = 0;
    pList->pAllocationCallbacks = pAllocationCallbacks;

    struct SpListIterator *pIterator = pAllocationCallbacks->pfnAllocation(sizeof(struct SpListIterator));
    pIterator->pCurrentNode = NULL;
    pIterator->currentIndex = -1;
    pList->pIterator = pIterator;

    return pList;
}

void spListDestroy(struct SpList *pList,
                   PFN_spListDestroyFreeUserDataFunction pfnUserDataDestroy) {
    if (pList == NULL)
        return;

    struct SpListNode *pCurrent = pList->pHead;
    struct SpListNode *pTemp = NULL;

    while (pCurrent != NULL) {
        pTemp = pCurrent;
        pCurrent = pCurrent->next;

        pfnUserDataDestroy(pTemp->data);
        pList->pAllocationCallbacks->pfnFree(pTemp);
    }
    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->count = 0;
    pList->pIterator->pCurrentNode = NULL;
    pList->pIterator->currentIndex = -1;
    pList->pAllocationCallbacks->pfnFree(pList->pIterator);
    pList->pAllocationCallbacks->pfnFree(pList);
}

void spListAdd(struct SpList *pList, void *data) {
    struct SpListNode *pNode = pList->pAllocationCallbacks->pfnAllocation(sizeof(struct SpListNode));
    pNode->data = data;
    pNode->next = NULL;

    if (pList->pHead == NULL)
        pList->pHead = pNode;
    else
        pList->pTail->next = pNode;

    pList->pTail = pNode;
    pList->count++;
}

bool spListRemoveNodeIf(struct SpList *pList,
                        PFN_spListEqualityComparerFunction comparer,
                        struct SpListNode *pOtherNode) {
    struct SpListNode *pCurrent = pList->pHead;
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
                pList->pTail = pPrevious;
        } else {
            pList->pHead = pList->pHead->next;
            if (pList->pHead == NULL)
                pList->pTail = NULL;
        }
        pList->pAllocationCallbacks->pfnFree(pTemp);
        pList->count--;
        return true;
    }

    return false;
}

bool spListIsFirstNode(struct SpList *pList, struct SpListNode *pNode) {
    return pList->pHead == pNode;
}

bool spListIsLastNode(struct SpList *pList, struct SpListNode *pNode) {
    return pList->pTail == pNode;
}

size_t spListGetLength(struct SpList *pList) {
    return pList->count;
}

struct SpListNode *spListIteratorNext(struct SpList *pList) {
    pList->pIterator->currentIndex++;

    struct SpListNode *pCurrentNode = pList->pIterator->pCurrentNode;
    if (pCurrentNode == NULL)
        pList->pIterator->pCurrentNode = pList->pHead;
    else
        pList->pIterator->pCurrentNode = pCurrentNode->next;

    return pList->pIterator->pCurrentNode;
}

void spListIteratorReset(struct SpList *pList) {
    pList->pIterator->currentIndex = -1;
    pList->pIterator->pCurrentNode = NULL;
}

struct SpListNode *spListBegin(struct SpList *pList) {
    pList->pIterator->currentIndex = 0;
    pList->pIterator->pCurrentNode = pList->pHead;
    return pList->pHead;
}
