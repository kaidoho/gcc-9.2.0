/* Copyright (C) 2018-2019 Free Software Foundation, Inc.
   Contributed by Jakub Jelinek <jakub@redhat.com>.

   This file is part of the GNU Offloading and Multi Processing Library
   (libgomp).

   Libgomp is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   Libgomp is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* This file handles the host TEAMS construct.  */

#include "libgomp.h"
#include <limits.h>

static unsigned gomp_num_teams = 1, gomp_team_num = 0;

void
GOMP_teams_reg (void (*fn) (void *), void *data, unsigned int num_teams,
		unsigned int thread_limit, unsigned int flags)
{
  (void) flags;
  (void) num_teams;
  unsigned old_thread_limit_var = 0;
  if (thread_limit)
    {
      struct gomp_task_icv *icv = gomp_icv (true);
      old_thread_limit_var = icv->thread_limit_var;
      icv->thread_limit_var
	= thread_limit > INT_MAX ? UINT_MAX : thread_limit;
    }
  if (num_teams == 0)
    num_teams = 3;
  gomp_num_teams = num_teams;
  for (gomp_team_num = 0; gomp_team_num < num_teams; gomp_team_num++)
    fn (data);
  gomp_num_teams = 1;
  gomp_team_num = 0;
  if (thread_limit)
    {
      struct gomp_task_icv *icv = gomp_icv (true);
      icv->thread_limit_var = old_thread_limit_var;
    }
}

int
omp_get_num_teams (void)
{
  return gomp_num_teams;
}

int
omp_get_team_num (void)
{
  return gomp_team_num;
}

ialias (omp_get_num_teams)
ialias (omp_get_team_num)
