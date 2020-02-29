/* Zephyr threads compatibility routines for libgcc2 and libobjc.
   by: M.B.Moessner (based on gthr-rtems.h) */
/* Compile this one with gcc.  */
/* Copyright (C) 1997-2019 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_GTHR_ZEPHYR_H
#define GCC_GTHR_ZEPHYR_H

#include <sys/lock.h>
#include <pthread.h>
#include <sched.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __GTHREADS 1
#define __GTHREADS_CXX0X 1
#define __GTHREAD_HAS_COND 1


typedef struct _z_gthread_sem_t  __gthread_mutex_t;
typedef struct _z_gthread_mutex_t __gthread_recursive_mutex_t;
typedef struct _z_gthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;

typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;


#define __GTHREAD_ONCE_INIT 0
#define __GTHREAD_MUTEX_INIT _z_gthread_sem_initializer
#define __GTHREAD_MUTEX_INIT_FUNCTION _z_gthread_sem_initialize
#define __GTHREAD_RECURSIVE_MUTEX_INIT _z_gthread_mutex_initializer
#define __GTHREAD_RECURSIVE_MUTEX_INIT_FUNCTION _z_gthread_mutex_initialize
#define __GTHREAD_COND_INIT _z_gthread_cond_initializer
#define __GTHREAD_COND_INIT_FUNCTION _z_gthread_cond_initialize
#define __GTHREAD_TIME_INIT {0, 0}

static inline int
__gthread_active_p (void)
{
  return 1;
}

static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void *),
		  void *__args)
{
  return pthread_create (__threadid, NULL, __func, __args);
}

static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return pthread_join (__threadid, __value_ptr);
}

static inline int
__gthread_detach (__gthread_t __threadid)
{
  return pthread_detach (__threadid);
}

static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return pthread_equal (__t1, __t2);
}

static inline __gthread_t
__gthread_self (void)
{
  return pthread_self ();
}

static inline int
__gthread_yield (void)
{
  return _z_gthread_yield ();
}

static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
   return pthread_once (__once, __func);
}

static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return pthread_key_create (__key, __dtor);
}

static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return pthread_key_delete (__key);
}

static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return pthread_getspecific (__key);
}

static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return pthread_setspecific (__key, __ptr);
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  return _z_gthread_sem_lock (__mutex);
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  return _z_gthread_sem_trylock (__mutex);
}

static inline int
__gthread_mutex_timedlock (__gthread_mutex_t *__mutex,
			   const __gthread_time_t *__abs_timeout)
{
  return _z_gthread_sem_timedlock (__mutex, __abs_timeout);
}

static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  return _z_gthread_sem_unlock (__mutex);
}

static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  return _z_gthread_sem_destroy (__mutex);
}

static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return _z_gthread_mutex_lock (__mutex);
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return _z_gthread_mutex_trylock (__mutex);
}

static inline int
__gthread_recursive_mutex_timedlock (__gthread_recursive_mutex_t *__mutex,
				     const __gthread_time_t *__abs_timeout)
{
  return _z_gthread_mutex_timedlock (__mutex, __abs_timeout);
}

static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return _z_gthread_mutex_unlock (__mutex);
}

static inline int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
  return  _z_gthread_mutex_destroy (__mutex);
}

static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return _z_gthread_cond_broadcast (__cond);
}

static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return _z_gthread_cond_signal (__cond);
}

static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return _z_gthread_cond_wait (__cond, __mutex);
}

static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
			  const __gthread_time_t *__abs_timeout)
{
  return _z_gthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}

static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
			       __gthread_recursive_mutex_t *__mutex)
{
  return _z_gthread_cond_wait_recursive (__cond, __mutex);
}

static inline int
__gthread_cond_destroy (__gthread_cond_t *__cond)
{
  return _z_gthread_cond_destroy (__cond);
}

#ifdef __cplusplus
}
#endif

#endif /* ! GCC_GTHR_ZEPHYR_H */
