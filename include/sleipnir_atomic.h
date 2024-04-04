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

#ifndef SLEIPNIRLIB_SLEIPNIR_ATOMIC_H
#define SLEIPNIRLIB_SLEIPNIR_ATOMIC_H

#include <stdatomic.h>

#define sp_atomic_add_relaxed(p, x) \
  atomic_fetch_add_explicit(p, x, memory_order_relaxed)
#define sp_atomic_sub_relaxed(p, x) \
  atomic_fetch_sub_explicit(p, x, memory_order_relaxed)
#define sp_atomic_add_acq_rel(p, x) \
  atomic_fetch_add_explicit(p, x, memory_order_acq_rel)
#define sp_atomic_sub_acq_rel(p, x) \
  atomic_fetch_sub_explicit(p, x, memory_order_acq_rel)
#define sp_atomic_and_acq_rel(p, x) \
  atomic_fetch_and_explicit(p, x, memory_order_acq_rel)
#define sp_atomic_orr_acq_rel(p, x) \
  atomic_fetch_or_explicit(p, x, memory_order_acq_rel)

#define sp_atomic_inc_relaxed(p) sp_atomic_add_relaxed(p, (uintptr_t)1)
#define sp_atomic_dec_relaxed(p) sp_atomic_sub_relaxed(p, (uintptr_t)1)
#define sp_atomic_inc_acq_rel(p) sp_atomic_add_acq_rel(p, (uintptr_t)1)
#define sp_atomic_dec_acq_rel(p) sp_atomic_sub_acq_rel(p, (uintptr_t)1)

#endif //SLEIPNIRLIB_SLEIPNIR_ATOMIC_H
