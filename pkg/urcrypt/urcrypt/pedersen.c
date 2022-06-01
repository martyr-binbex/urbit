#include "urcrypt.h"
#include "util.h"
#include <string.h>
#include <libec.h>
#include <stdio.h>

int
get_curve_params(ec_params *curve_params) {
  int ret;
  printf("0\r\n");
  u8 curve_name[MAX_CURVE_NAME_LEN] = "STARK";
  printf("1\r\n");
  u32 len = strnlen((const char *)curve_name, MAX_CURVE_NAME_LEN);
  printf("2\r\n");
  len += 1;
  const ec_str_params *curve_string_params;
  printf("3\r\n");
  ret = ec_get_curve_params_by_name(curve_name, (u8)len, &curve_string_params);
  printf("4\r\n");
  if (curve_string_params == NULL) {
    printf("5\r\n");
    return -1;
  }
  printf("6\r\n");
  ret = import_params(curve_params, curve_string_params);
  printf("7\r\n");
  return ret;
}

int
urcrypt_pedersen(uint8_t x[32], uint8_t y[32], uint8_t out[32])
{
  int ret = 0;
  fp x1, y1;
  fp_ctx_src_t ctx;
  printf("10\r\n");
  fp_init(&x1, ctx);
  printf("11\r\n");
  //ctx = &(curve_params->ec_fp);

  printf("x = %d\r\n", *x);
  printf("y = %d\r\n", *y);

  urcrypt__reverse(32, x);
  urcrypt__reverse(32, y);


  ec_params curve_params;
  ret = get_curve_params(&curve_params);
  printf("got curve params\r\n");
  if (ret != 0) {
    return ret;
  }
  fp_ctx c = curve_params.ec_fp;
  const char *name = (const char *)curve_params.curve_name;
  printf("curve name = %s\r\n", name);;

  *out = 5;

  urcrypt__reverse(32, out);
  return ret;
}
