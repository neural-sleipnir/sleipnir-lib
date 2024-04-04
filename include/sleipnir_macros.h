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

#ifndef SLEIPNIRLIB_SLEIPNIR_MACROS_H
#define SLEIPNIRLIB_SLEIPNIR_MACROS_H

////////////////////////////////////////////////////////////////////////////////
// Cpp
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
#define SLEIPNIR_START_CPP_NAMESPACE \
  namespace sleipnir {               \
  extern "C" {
#define SLEIPNIR_END_CPP_NAMESPACE \
  }                                \
  }
#else
#define SLEIPNIR_START_CPP_NAMESPACE
#define SLEIPNIR_END_CPP_NAMESPACE
#endif

////////////////////////////////////////////////////////////////////////////////
// Architectures
////////////////////////////////////////////////////////////////////////////////

#if (defined(_M_IX86) || defined(__i386__)) && !defined(CPU_FEATURES_ARCH_VM)
#define SLEIPNIR_ARCH_X86_32
#endif

#if (defined(_M_X64) || defined(__x86_64__)) && !defined(CPU_FEATURES_ARCH_VM)
#define SLEIPNIR_ARCH_X86_64
#endif

#if defined(CPU_FEATURES_ARCH_X86_32) || defined(CPU_FEATURES_ARCH_X86_64)
#define SLEIPNIR_ARCH_X86
#endif

#if (defined(__aarch64__) || defined(_M_ARM64))
#define SLEIPNIR_ARCH_AARCH64
#endif

////////////////////////////////////////////////////////////////////////////////
// Os
////////////////////////////////////////////////////////////////////////////////

#if (defined(__freebsd__) || defined(__FreeBSD__))
#define SLEIPNIR_OS_FREEBSD
#endif

#if defined(__ANDROID__)
#define SLEIPNIR_OS_ANDROID
#endif

#if defined(__linux__) && !defined(SLEIPNIR_OS_FREEBSD) && \
    !defined(SLEIPNIR_OS_ANDROID)
#define SLEIPNIR_OS_LINUX
#endif

#if (defined(_WIN64) || defined(_WIN32))
#define SLEIPNIR_OS_WINDOWS
#endif

////////////////////////////////////////////////////////////////////////////////
// Compilers
////////////////////////////////////////////////////////////////////////////////

#if defined(__clang__)
#define CPU_FEATURES_COMPILER_CLANG
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define SLEIPNIR_COMPILER_GCC
#endif

#if defined(_MSC_VER)
#define SLEIPNIR_COMPILER_MSC
#endif

////////////////////////////////////////////////////////////////////////////////
// DllImport
////////////////////////////////////////////////////////////////////////////////

#if defined(SLEIPNIR_OS_WINDOWS)
#ifdef SLEIPNIR_DLL
#define SLEIPNIR_DLL_EXPORT __declspec(dllexport)
#else
#define SLEIPNIR_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define SLEIPNIR_DLL_EXPORT
#endif  // SLEIPNIR_OS_WINDOWS

#endif  // SLEIPNIRLIB_SLEIPNIR_MACROS_H
