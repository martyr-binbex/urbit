#include "urcrypt.h"
#include "util.h"
#include <string.h>
#include <libec.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  prj_pt p0;
  prj_pt p1;
  prj_pt p2;
  prj_pt p3;
  prj_pt p4;
} constant_points;

static constant_points *cp = NULL;
static ec_params *curve_params = NULL;

int
get_curve_params(ec_params *curve_params) {
  int ret;
  printf("inside get_curve_params\r\n");
  u8 curve_name[MAX_CURVE_NAME_LEN] = "USER_DEFINED_STARK";
  u32 len = strnlen((const char *)curve_name, MAX_CURVE_NAME_LEN);
  len += 1;
  const ec_str_params *curve_string_params;
  ret = ec_get_curve_params_by_name(curve_name, (u8)len, &curve_string_params);
  if (curve_string_params == NULL || ret != 0) {
    return -1;
  }
  ret = import_params(curve_params, curve_string_params);
  return ret;
}

int
get_constant_points(ec_params *curve_params, constant_points* cp) {
  int ret = 0;
  ec_shortw_crv_src_t crv = &(curve_params->ec_curve);

  printf("inside get_constant_points\r\n");
  const u8 p0_buf[] = {
    // x coordinate
    0x04, 0x9e, 0xe3, 0xeb, 0xa8, 0xc1, 0x60, 0x07,
    0x00, 0xee, 0x1b, 0x87, 0xeb, 0x59, 0x9f, 0x16,
    0x71, 0x6b, 0x0b, 0x10, 0x22, 0x94, 0x77, 0x33,
    0x55, 0x1f, 0xde, 0x40, 0x50, 0xca, 0x68, 0x04,

    // y coordinate
    0x03, 0xca, 0x0c, 0xfe, 0x4b, 0x3b, 0xc6, 0xdd,
    0xf3, 0x46, 0xd4, 0x9d, 0x06, 0xea, 0x0e, 0xd3,
    0x4e, 0x62, 0x10, 0x62, 0xc0, 0xe0, 0x56, 0xc1,
    0xd0, 0x40, 0x5d, 0x26, 0x6e, 0x10, 0x26, 0x8a
  };

  const u8 p1_buf[] = {
    // x coordinate
    0x02, 0x34, 0x28, 0x7d, 0xcb, 0xaf, 0xfe, 0x7f,
    0x96, 0x9c, 0x74, 0x86, 0x55, 0xfc, 0xa9, 0xe5,
    0x8f, 0xa8, 0x12, 0x0b, 0x6d, 0x56, 0xeb, 0x0c,
    0x10, 0x80, 0xd1, 0x79, 0x57, 0xeb, 0xe4, 0x7b,

    // y coordinate
    0x03, 0xb0, 0x56, 0xf1, 0x00, 0xf9, 0x6f, 0xb2,
    0x1e, 0x88, 0x95, 0x27, 0xd4, 0x1f, 0x4e, 0x39,
    0x94, 0x01, 0x35, 0xdd, 0x7a, 0x6c, 0x94, 0xcc,
    0x6e, 0xd0, 0x26, 0x8e, 0xe8, 0x9e, 0x56, 0x15
  };

  const u8 p2_buf[] = {
    // x coordinate
    0x04, 0xfa, 0x56, 0xf3, 0x76, 0xc8, 0x3d, 0xb3,
    0x3f, 0x9d, 0xab, 0x26, 0x56, 0x55, 0x8f, 0x33,
    0x99, 0x09, 0x9e, 0xc1, 0xde, 0x5e, 0x30, 0x18,
    0xb7, 0xa6, 0x93, 0x2d, 0xba, 0x8a, 0xa3, 0x78,

    // y coordinate
    0x03, 0xfa, 0x09, 0x84, 0xc9, 0x31, 0xc9, 0xe3,
    0x81, 0x13, 0xe0, 0xc0, 0xe4, 0x7e, 0x44, 0x01,
    0x56, 0x27, 0x61, 0xf9, 0x2a, 0x7a, 0x23, 0xb4,
    0x51, 0x68, 0xf4, 0xe8, 0x0f, 0xf5, 0xb5, 0x4d
  };

  const u8 p3_buf[] = {
    // x coordinate
    0x04, 0xba, 0x4c, 0xc1, 0x66, 0xbe, 0x8d, 0xec,
    0x76, 0x49, 0x10, 0xf7, 0x5b, 0x45, 0xf7, 0x4b,
    0x40, 0xc6, 0x90, 0xc7, 0x47, 0x09, 0xe9, 0x0f,
    0x3a, 0xa3, 0x72, 0xf0, 0xbd, 0x2d, 0x69, 0x97,

    // y coordinate
    0x00, 0x40, 0x30, 0x1c, 0xf5, 0xc1, 0x75, 0x1f,
    0x4b, 0x97, 0x1e, 0x46, 0xc4, 0xed, 0xe8, 0x5f,
    0xca, 0xc5, 0xc5, 0x9a, 0x5c, 0xe5, 0xae, 0x7c,
    0x48, 0x15, 0x1f, 0x27, 0xb2, 0x4b, 0x21, 0x9c
  };

  const u8 p4_buf[] = {
    // x coordinate
    0x05, 0x43, 0x02, 0xdc, 0xb0, 0xe6, 0xcc, 0x1c,
    0x6e, 0x44, 0xcc, 0xa8, 0xf6, 0x1a, 0x63, 0xbb,
    0x2c, 0xa6, 0x50, 0x48, 0xd5, 0x3f, 0xb3, 0x25,
    0xd3, 0x6f, 0xf1, 0x2c, 0x49, 0xa5, 0x82, 0x02,

    // y coordinate
    0x01, 0xb7, 0x7b, 0x3e, 0x37, 0xd1, 0x35, 0x04,
    0xb3, 0x48, 0x04, 0x62, 0x68, 0xd8, 0xae, 0x25,
    0xce, 0x98, 0xad, 0x78, 0x3c, 0x25, 0x56, 0x1a,
    0x87, 0x9d, 0xcc, 0x77, 0xe9, 0x9c, 0x24, 0x26
  };

  ret = prj_pt_import_from_aff_buf(&(cp->p0), p0_buf, 64, crv);
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_import_from_aff_buf(&(cp->p1), p1_buf, 64, crv);
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_import_from_aff_buf(&(cp->p2), p2_buf, 64, crv);
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_import_from_aff_buf(&(cp->p3), p3_buf, 64, crv);
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_import_from_aff_buf(&(cp->p4), p4_buf, 64, crv);
  return ret;
}

void
print_buf(uint8_t *buf, u16 len) {
  int i;
  for(i = 0; i < len; i++) {
    printf("%x ", buf[i]);
  }
  printf("\r\n");
}

int
urcrypt_pedersen(uint8_t a[32], uint8_t b[32], uint8_t out[32])
{
  int ret = 0;

  printf("a= ");
  print_buf(a, 32);
  printf("b= ");
  print_buf(b, 32);

  urcrypt__reverse(32, a);
  urcrypt__reverse(32, b);

  printf("a= ");
  print_buf(a, 32);
  printf("b= ");
  print_buf(b, 32);

  if (curve_params == NULL) {
    printf("initializing curve_params\r\n");
    curve_params = (ec_params *)malloc(sizeof(ec_params));
    ret = get_curve_params(curve_params);
    if (ret != 0) {
      return ret;
    }
  } else {
    printf("curve_params already initialized\r\n");
  }

  if (cp == NULL) {
    printf("initializing constant points\r\n");
    cp = (constant_points *)malloc(sizeof(constant_points));
    ret = get_constant_points(curve_params, cp);
    if (ret != 0) {
      return ret;
    }    
  } else {
    printf("constant points already initialized\r\n");
  }

  nn alow, ahig, blow, bhig;
  ret = nn_init_from_buf(&alow, a+1, 31);
  if (ret != 0) {
    return ret;
  }
  ret = nn_init_from_buf(&ahig, a, 1);
  if (ret != 0) {
    return ret;
  }
  ret = nn_init_from_buf(&blow, b+1, 31);
  if (ret != 0) {
    return ret;
  }
  ret = nn_init_from_buf(&bhig, b, 1);
  if (ret != 0) {
    return ret;
  }

  uint8_t alow_buf[32], ahig_buf[32], blow_buf[32], bhig_buf[32];
  nn_export_to_buf(alow_buf, 32, &alow);
  nn_export_to_buf(ahig_buf, 32, &ahig);
  nn_export_to_buf(blow_buf, 32, &blow);
  nn_export_to_buf(bhig_buf, 32, &bhig);
  printf("alow= ");
  print_buf(alow_buf, 32);
  printf("ahig= ");
  print_buf(ahig_buf, 32);
  printf("blow= ");
  print_buf(blow_buf, 32);
  printf("bhig= ");
  print_buf(bhig_buf, 32);


  prj_pt p1_alow, p2_ahig, p3_blow, p4_bhig;
  ret = prj_pt_mul(&p1_alow, &alow, &(cp->p1));
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_mul(&p2_ahig, &ahig, &(cp->p2));
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_mul(&p3_blow, &blow, &(cp->p3));
  if (ret != 0) {
    return ret;
  }

  ret = prj_pt_mul(&p4_bhig, &bhig, &(cp->p4));
  if (ret != 0) {
    return ret;
  }

  prj_pt sum;
  ret = prj_pt_add(&sum, &(cp->p0), &p1_alow);
  if (ret != 0) {
    return ret;
  }
  ret = prj_pt_add(&sum, &sum, &p2_ahig);
  if (ret != 0) {
    return ret;
  }
  ret = prj_pt_add(&sum, &sum, &p3_blow);
  if (ret != 0) {
    return ret;
  }
  ret = prj_pt_add(&sum, &sum, &p4_bhig);
  if (ret != 0) {
    return ret;
  }

  prj_pt aff;
  ret = prj_pt_unique(&aff, &sum);
  if (ret != 0) {
    return ret;
  }

  ret = fp_export_to_buf(out, 32, &(aff.X));

  printf("out= ");
  print_buf(out, 32);
  urcrypt__reverse(32, out);
  printf("out= ");
  print_buf(out, 32);
  return ret;
}
