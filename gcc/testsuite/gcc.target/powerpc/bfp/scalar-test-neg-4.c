/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-require-effective-target lp64 } */
/* { dg-require-effective-target powerpc_p9vector_ok } */
/* { dg-options "-mdejagnu-cpu=power9" } */

#include <altivec.h>
#include <stdbool.h>

bool
test_neg (__ieee128 *p)
{
  __ieee128 source = *p;

  /* IEEE 128-bit floating point operations are only supported
     on 64-bit targets.  */
  return scalar_test_neg (source);
}

/* { dg-final { scan-assembler "xststdcqp" } } */
