/**
 * @file macro.h
 * @brief 常用宏的封装
 * @author sylar.yin
 * @email 564628276@qq.com
 * @date 2019-06-01
 * @copyright Copyright (c) 2019年 sylar.yin All rights reserved (www.sylar.top)
 */
#ifndef __SYLAR_MACRO_H__
#define __SYLAR_MACRO_H__

#include <string.h>
#include <assert.h>
#include "log.h"
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#define SYLAR_LIKELY(x) __builtin_expect(!!(x), 1) //和汇编结合起来进行理解，因为cpu是流水线模式工作，汇编中如果有跳转语句，就得flush然后拿取新指令，那之前预读
//的指令就浪费了，因此这里告诉一个概率，从而影响汇编里跳转语句的生成，从而减少跳转提升程序运行的效率
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#define SYLAR_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define SYLAR_LIKELY(x) (x)
#define SYLAR_UNLIKELY(x) (x)
#endif

/// 断言宏封装
#define SYLAR_ASSERT(x)                                                                \
    if (SYLAR_UNLIKELY(!(x))) {                                                        \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x                          \
                                          << "\nbacktrace:\n"                          \
                                          << sylar::BacktraceToString(100, 2, "    "); \
        assert(x);                                                                     \
    }

/// 断言宏封装
#define SYLAR_ASSERT2(x, w)                                                            \
    if (SYLAR_UNLIKELY(!(x))) {                                                        \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x                          \
                                          << "\n"                                      \
                                          << w                                         \
                                          << "\nbacktrace:\n"                          \
                                          << sylar::BacktraceToString(100, 2, "    "); \
        assert(x);                                                                     \
    }

#endif
