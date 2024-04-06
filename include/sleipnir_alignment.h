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

#ifndef SLEIPNIRLIB_SLEIPNIR_ALIGNMENT_H
#define SLEIPNIRLIB_SLEIPNIR_ALIGNMENT_H

#include <stdalign.h>

#define SLEIPNIR_ALIGN_SIZE (alignof(long double))
#define SLEIPNIR_ALIGN_UP(s) (((s) + (SLEIPNIR_ALIGN_SIZE - 1)) & ~(SLEIPNIR_ALIGN_SIZE - 1))

#endif // SLEIPNIRLIB_SLEIPNIR_ALIGNMENT_H
