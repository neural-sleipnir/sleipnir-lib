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

#include <stdlib.h>
#include <stdio.h>

#include "sleipnir_list.h"

struct MyData {
    int value;
};

struct MyData *myDataCreate(int value) {
    struct MyData *pData = (struct MyData *) malloc(sizeof(struct MyData));
    pData->value = value;

    return pData;
}

void destroyUserData(void *userData) {
    free(userData);
}

bool compareNodes(struct SpListNode *pCurrentNode,
                  struct SpListNode *pOtherNode) {
    struct MyData *pCurrentData = (struct MyData *) pCurrentNode->data;
    struct MyData *pOtherData = (struct MyData *) pOtherNode->data;

    return pCurrentData->value == pOtherData->value;
}

int main() {
    struct SpAllocationCallbacks allocationCallbacks = {
            .pfnAllocation = malloc,
            .pfnFree = free,
            .pfnReallocation = realloc,
    };
    struct SpList *pList = spListCreate(&allocationCallbacks);

    struct MyData *pData1 = myDataCreate(1);
    struct MyData *pData2 = myDataCreate(2);
    struct MyData *pData3 = myDataCreate(3);
    struct MyData *pData4 = myDataCreate(4);

    spListAdd(pList, (void *) pData1);
    spListAdd(pList, (void *) pData2);
    spListAdd(pList, (void *) pData3);
    spListAdd(pList, (void *) pData4);

    struct MyData otherData = {
            .value = 3,
    };
    struct SpListNode node;
    node.data = &otherData;
    node.next = NULL;
    spListRemoveNodeIf(pList, compareNodes, &node);

    struct SpListNode *pos = NULL;
    SP_LIST_FOREACH(pos, pList) {
        struct MyData *data = (struct MyData *) pos->data;
        printf("%d\n", data->value);
    }

    spListDestroy(pList, destroyUserData);

    return 0;
}