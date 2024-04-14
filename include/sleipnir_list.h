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

#ifndef SLEIPNIR_LIB_SLEIPNIR_LIST_H
#define SLEIPNIR_LIB_SLEIPNIR_LIST_H

#include "sleipnir_common.h"

#include <stdbool.h>

struct SpListNode {
    void *data;
    struct SpListNode *next;
};

struct SpList;

typedef bool (*PFN_spListEqualityComparerFunction)(struct SpListNode *pCurrentNode,
                                                   struct SpListNode *pOtherNode);

typedef void (*PFN_spListDestroyFreeUserDataFunction)(void *pUserData);

struct SpList *spListCreate(struct SpAllocationCallbacks *pAllocationCallbacks);

void spListDestroy(struct SpList *pList,
                   PFN_spListDestroyFreeUserDataFunction pfnUserDataDestroy);

struct SpListNode *spListBegin(struct SpList *pList);

bool spListIsFirstNode(struct SpList *pList, struct SpListNode *pNode);

void spListAdd(struct SpList *pList, void *data);

bool spListRemoveNodeIf(struct SpList *pList,
                        PFN_spListEqualityComparerFunction comparer,
                        struct SpListNode *pOtherNode);

bool spListIsLastNode(struct SpList *pList, struct SpListNode *pNode);

size_t spListGetLength(struct SpList *pList);

void spListIteratorReset(struct SpList *pList);

struct SpListNode *spListIteratorNext(struct SpList *pList);

bool spListIteratorEnd(struct SpList *pList);

#define SP_LIST_FOREACH(pos, list) \
    for (pos = spListBegin((list)); pos != NULL; pos = spListIteratorNext((list)))

#endif // SLEIPNIR_LIB_SLEIPNIR_LIST_H
