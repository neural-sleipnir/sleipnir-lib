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

#include "sleipnir_bumpalloc.h"

#include <assert.h>

#include "sleipnir_alignment.h"

#define SLEIPNIR_BUMP_ALLOC_SIZE (4096 * 1024 * 24)

struct SpBumpAlloc {
    char *ptr;
    size_t size;
};

static char buffer[SLEIPNIR_BUMP_ALLOC_SIZE];

static struct SpBumpAlloc bumpAllocator = {
        .ptr = buffer,
        .size = sizeof(struct SpBumpAlloc)
};

void *spBumpAlloc(size_t size) {
    assert(size != 0 || size < SLEIPNIR_BUMP_ALLOC_SIZE);
    size = SLEIPNIR_ALIGN_UP(size);
    assert(bumpAllocator.size >= size);
    void *ptr = bumpAllocator.ptr;
    bumpAllocator.size -= size;
    bumpAllocator.ptr += size;
    return ptr;
}
