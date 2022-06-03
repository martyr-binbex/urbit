
/* j/5/pedersen.c
**
*/
#include "all.h"
#include <urcrypt.h>


c3_y*
u3r_bytes_all_works(c3_w* len_w, u3_atom a)
{
  c3_w met_w;
  if (a == u3_nul) {
    met_w = *len_w = 1;
  } else {
    met_w = *len_w = u3r_met(3, a);
  }
  return u3r_bytes_alloc(0, met_w, a);
}

static u3_noun
_cqe_phash(u3_atom x, u3_atom y)
{
  c3_y dat_x[32], dat_y[32], out_y[32];
  if ( (0 != u3r_bytes_fit(32, dat_x, x)) ||
       (0 != u3r_bytes_fit(32, dat_y, y)) ) {
    return u3m_bail(c3__exit);
  }

  printf("dat_x = %d\r\n", *dat_x);
  printf("dat_y = %d\r\n", *dat_y);
  urcrypt_pedersen(dat_x, dat_y, out_y);

  return u3i_bytes(32, out_y);


  /*  c3_w len_x, len_y;
    c3_y *dat_x = u3r_bytes_all_works(&len_x, x);
    c3_y *dat_y = u3r_bytes_all_works(&len_y, y);
    c3_y out_y[32];

    if (y == u3_nul) {
        printf("y == u3_nul\r\n");
    }
    printf("dat_y = %d\r\n", *dat_y);
    printf("len_y = %d\r\n", len_y);

    urcrypt_pedersen(dat_x, len_x, dat_y, len_y, out_y);

    u3a_free(dat_x);
    u3a_free(dat_y);

    return u3i_bytes(32, out_y);*/
}

u3_noun
u3we_phash(u3_noun cor)
{
    printf("running phash jet\r\n");
    u3l_log("running u3we_phash\r\n");

    u3_noun x, y;
    if ( (c3n == u3r_mean(cor,
                          u3x_sam_2,  &x,
                          u3x_sam_3,  &y,
                          0)) ||
         (c3n == u3ud(x)) ||
         (c3n == u3ud(y)) ) 
    {
        return u3m_bail(c3__exit);
    }
    else {
        return _cqe_phash(x, y);
    }
}
