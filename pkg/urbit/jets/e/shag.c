/* j/e/shag.c
**
*/
#include "all.h"
#include <stdio.h>

u3_noun
u3qe_shag(u3_noun n)
{
  if ( c3y == u3ud(n) ) {
    return _cqe_phash(n, u3_nul);
  } 
  else {
    return _cqe_phash(u3qe_shag(u3h(n)), u3qe_shag(u3t(n)));
  }
}

u3_noun
u3we_shag(u3_noun cor)
{
  printf("running shag jet\r\n");
  u3_noun n;
  if ( c3n == u3r_mean(cor, u3x_sam, &n, 0) )
  {
      return u3m_bail(c3__exit);
  }
  else {
    return u3qe_shag(n);
  }
}