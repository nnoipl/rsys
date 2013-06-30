#ifndef ATOMIC_H
#define ATOMIC_H

#include "rsys.h"

/*******************************************************************************
 * GCC implementation
 ******************************************************************************/ 
#ifdef COMPILER_GCC

typedef int atomic_int_T;
typedef size_t atomic_size_T;

#define ATOMIC_INCR(Atom) __sync_add_and_fetch((Atom), 1)
#define ATOMIC_DECR(Atom) __sync_sub_and_fetch((Atom), 1)
#define ATOMIC_ADD(Atom, Val) __sync_add_and_fetch((Atom), (Val))
#define ATOMIC_SUB(Atom, Val) __sync_sub_and_fetch((Atom), (Val))
#define ATOMIC_FETCH_AND_INCR(Atom) __sync_fetch_and_add((Atom), 1)
#define ATOMIC_FETCH_AND_DECR(Atom) __sync_fetch_and_sub((Atom), 1)
#define ATOMIC_FETCH_AND_ADD(Atom, Val) __sync_fetch_and_add((Atom), (Val))
#define ATOMIC_FETCH_AND_SUB(Atom, Val) __sync_fetch_and_sub((Atom), (Val))

/*******************************************************************************
 * Other implementation
 ******************************************************************************/ 
#else
typedef int atomic_int_T;
typedef size_t atomic_size_T;

#define ATOMIC_INCR(Atom) ASSERT(0), 0
#define ATOMIC_DECR(Atom) ASSERT(0), 0
#define ATOMIC_ADD(Atom, Val) ASSERT(0), 0
#define ATOMIC_SUB(Atom, Val) ASSERT(0), 0
#define ATOMIC_FETCH_AND_INCR(Atom) ASSERT(0), 0
#define ATOMIC_FETCH_AND_DECR(Atom) ASSERT(0), 0
#define ATOMIC_FETCH_AND_ADD(Atom, Val) ASSERT(0), 0
#define ATOMIC_FETCH_AND_SUB(Atom, Val) ASSERT(0), 0

#endif /* COMPILER_XXX */

#endif /* ATOMIC_H */
