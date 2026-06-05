/*
 * Copyright (c) 2026 Tan Wah Ken
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef LSERZ_H
#define LSERZ_H

#ifndef SZC_ULTRALITE
#include <stdint.h>
#include <string.h>
#endif // SZC_ULTRALITE
#if !defined(SZCMALLOC) && !defined(SZCREALLOC) && !defined(SZCFREE)
#include <stdlib.h>
#endif

#ifndef SZC_DST_NAME
#define SZC_DST_NAME szc_dst__
#endif // SZC_DST_NAME
#ifndef SZF_NAME_PREFIX
#define SZF_NAME_PREFIX __szcf
#endif // SZF_NAME_PREFIX

#ifndef SZCMALLOC
#define SZCMALLOC malloc
#endif // SZCMALLOC
#ifndef SZCREALLOC
#define SZCREALLOC realloc
#endif // SZCREALLOC
#ifndef SZCFREE
#define SZCFREE free
#endif // SZCFREE

#define SZCMIN(a, b) (((a) < (b)) ? (a) : (b))
#define SZCMAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAZ_SZ (~(size_t)0)
#define zz8(x) ((x) == 0 ? 8 : (x))
#define zy8(x) ((x) % 8)

#define SZC_PASTER(x, y) x##_##y
#define SZC_CONCAT(x, y) SZC_PASTER(x, y)

#define SZC_FLAG_NOMLC 1

typedef enum {
  szcmode_read,
  szcmode_write,
} szcmode_t;

typedef enum {
  szc_dtyp_o,
  szc_dtyp_o2,
  szc_dtyp_o3,
  szc_dtyp_b,
  szc_dtyp_b2,
  szc_dtyp_b3,
  szc_dtyp_b4,
  _szc_dtyp_max,
} szc_dtyp_t;

struct szc_dst_s {
  szcmode_t omode;
  uint8_t flag;
  unsigned long long int bitlen;
  size_t maxlen;
  uint8_t *val;
};

static inline void *_szcmemset(uint8_t *s, int c, size_t n) {
  for (; n > 0; n--)
    s[n - 1] = c;
  return s;
}

static inline int _szcmemcmp(uint8_t *a, uint8_t *b, size_t sz) {
  for (size_t i = 0; i < sz; i++)
    if (a[i] != b[i])
      return a[i] - b[i];
  return 0;
}

static inline int szc_typ_is_octal(szc_dtyp_t typ) {
  switch (typ) {
  case szc_dtyp_o:
  case szc_dtyp_o2:
  case szc_dtyp_o3:
    return 1;
  case szc_dtyp_b:
  case szc_dtyp_b2:
  case szc_dtyp_b3:
  case szc_dtyp_b4:
    return 0;
  default:
    return -1;
  }
}

#define szc_count_oct(typ, count)                                              \
  ((size_t)(szc_typ_is_octal(typ)                                              \
                ? (count)                                                      \
                : ((count) >> 3) + ((count) % 8 == 0 ? 0 : 1)))
#define szc_count_bit(typ, count)                                              \
  ((unsigned long long int)(szc_typ_is_octal(typ)                              \
                                ? ((unsigned long long int)(count) << 3)       \
                                : (count)))
#define szc_conv_1(typ, count)                                                 \
  ((unsigned long long int)(szc_typ_is_octal(typ)                              \
                                ? (count)                                      \
                                : ((unsigned long long int)(count) << 3)))

static inline uint8_t szc_get_msb32(register unsigned int val) {
  return 32 - __builtin_clz(val);
}

static inline uint8_t szc_get_msb64(register unsigned long long val) {
  return 64 - __builtin_clzll(val);
}

static inline uint8_t szc_get_ctnsz(register unsigned long long val) {
  uint8_t a = szc_get_msb64(val);
  return (a / 8) + (a % 8 > 0 ? 1 : 0);
}

#ifndef SZC_ULTRALITE
// clang-format off
static const uint8_t byte_rev_table[256] = {
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};
// clang-format on
#else  // SZC_ULTRALITE
extern const uint8_t byte_rev_table[256];
#endif // SZC_ULTRALITE

static inline uint8_t bb_rev8(uint8_t byte) { return byte_rev_table[byte]; }

static inline uint8_t bb_mask(uint8_t target, char p1, char p2, char off1) {
  if (off1 >= 8)
    return (uint8_t)0;
  if (p1 < 0 || p2 < 0 || p1 >= p2)
    return (uint8_t)0;
  uint16_t a = (1 << (8 - p1)) - (1 << (8 - p2));
  return off1 > 0 ? (target & a) >> off1 : (target & a) << (-off1);
}

static inline uint8_t bb_mask2(uint8_t target, char p1, char p2, char off1) {
  if (off1 >= 8)
    return (uint8_t)0;
  if (p1 < 0 || p2 < 0 || p1 >= p2)
    return (uint8_t)0;
  uint16_t a = (1 << p2) - (1 << p1);
  return off1 > 0 ? (target & a) << off1 : (target & a) >> (-off1);
}

static inline void _szcpy_w(szc_dtyp_t typ, uint8_t *dst, const uint8_t *src,
                            unsigned long long int count, uint8_t pos_bb) {
  uint8_t pos_ba = count % 8;
  uint8_t ba_left = 8 - pos_ba, bb_left = 8 - pos_bb;
  uint8_t x1 = SZCMIN(bb_left, pos_ba), x2 = pos_ba - x1;
  size_t i, cnt2 = count >> 3;
  if (count == 0)
    return;
  switch (typ) {
  case szc_dtyp_o:
    for (i = 0; i < count; i++)
      dst[i] = src[i];
    break;
  case szc_dtyp_o2:
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[i];
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[count - i - 1];
#else
#error byte order not defined
#endif
    break;
  case szc_dtyp_o3:
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[i];
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[count - i - 1];
#else
#error byte order not defined
#endif
    break;
  case szc_dtyp_b:
    for (i = 0; i < cnt2; i++) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(src[i], 0, bb_left, pos_bb);
      if (bb_left < 8) {
        dst[i + 1] = 0;
        dst[i + 1] |= bb_mask(src[i], bb_left, 8, -bb_left);
      }
    }
    if (pos_bb > 0 || pos_ba > 0) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(src[i], 0, x1, pos_bb);
    }

    if (x2 > 0) {
      dst[i + 1] = 0;
      dst[i + 1] |= bb_mask(src[i], x1, x1 + x2, -bb_left);
    }
    break;
  case szc_dtyp_b2:
    for (i = 0; i < cnt2; i++) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(bb_rev8(src[i]), 0, bb_left, pos_bb);
      if (bb_left < 8) {
        dst[i + 1] = 0;
        dst[i + 1] |= bb_mask(bb_rev8(src[i]), bb_left, 8, -bb_left);
      }
    }
    if (pos_bb > 0) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(bb_rev8(src[i]), 0, x1, pos_bb);
    }

    if (x2 > 0) {
      dst[i + 1] = 0;
      dst[i + 1] |= bb_mask(bb_rev8(src[i]), x1, x1 + x2, -bb_left);
    }
    break;
  case szc_dtyp_b3:
    cnt2 -= (pos_ba == 0 ? 1 : 0);
    dst[0] &= bb_mask2(255, bb_left, 8, 0);
    for (i = 0; i <= cnt2; i++) {
      dst[i] |= bb_mask2(bb_rev8(src[cnt2 - i]), 0, zz8(pos_ba),
                         zy8(ba_left) - pos_bb);
      if (i == cnt2 && pos_ba - bb_left < 0)
        break;
      dst[i + 1] = 0;
      dst[i + 1] |=
          bb_mask2(bb_rev8(src[cnt2 - i]), 0, zz8(pos_ba) - zz8(bb_left),
                   8 - (zz8(pos_ba) - zz8(bb_left))); // spillover
      if (i == cnt2)
        break;
      dst[i + 1] |= bb_mask(bb_rev8(src[cnt2 - i - 1]), 0,
                            8 - (zz8(pos_ba) - zz8(bb_left)),
                            zz8(pos_ba) - zz8(bb_left)); // spillover
      dst[i] |=
          bb_mask(bb_rev8(src[cnt2 - i - 1]), 0, zz8(bb_left) - zz8(pos_ba),
                  8 - (zz8(bb_left) - zz8(pos_ba))); // not enough
      dst[i + 1] |=
          bb_mask(bb_rev8(src[cnt2 - i - 1]), zz8(bb_left) - zz8(pos_ba), 8,
                  zz8(pos_ba) - zz8(bb_left)); // not enough
    }
    break;
  case szc_dtyp_b4:
    for (i = 0; i < cnt2; i++) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(src[i], 0, bb_left, pos_bb);
      if (bb_left < 8) {
        dst[i + 1] = 0;
        dst[i + 1] |= bb_mask(src[i], bb_left, 8, -bb_left);
      }
    }
    if (pos_bb > 0 || pos_ba > 0) {
      dst[i] &= bb_mask(255, 0, pos_bb, 0);
      dst[i] |= bb_mask(src[i], ba_left, ba_left + x1, pos_bb - ba_left);
    }

    if (x2 > 0) {
      dst[i + 1] = 0;
      dst[i + 1] |= bb_mask2(src[i], 0, x2, 8 - x2);
    }
    break;
  default:
    break;
  }
}

static inline void _szcpy_r(szc_dtyp_t typ, uint8_t *dst, const uint8_t *src,
                            unsigned long long int count, uint8_t pos_bb) {
  uint8_t pos_ba = count % 8, pos_bc = (pos_bb + pos_ba) % 8;
  uint8_t bb_left = 8 - pos_bb, bc_left = 8 - pos_bc;
  uint8_t x1 = SZCMIN(bb_left, pos_ba);
  size_t i, cnt = (count + pos_bb) >> 3, cnt2 = count >> 3;
  size_t cnt3 = cnt - (pos_bb == 0 ? 0 : 1);
  if (count == 0)
    return;
  switch (typ) {
  case szc_dtyp_o:
    for (i = 0; i < count; i++)
      dst[i] = src[i];
    break;
  case szc_dtyp_o2:
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[i];
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[count - i - 1];
#else
#error byte order not defined
#endif
    break;
  case szc_dtyp_o3:
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[i];
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    for (i = 0; i < count; i++)
      dst[i] = src[count - i - 1];
#else
#error byte order not defined
#endif
    break;
  case szc_dtyp_b:
    for (i = 0; i < cnt2; i++) {
      dst[i] = 0;
      dst[i] |= bb_mask(src[i], pos_bb, 8, -pos_bb);
      dst[i] |= bb_mask(src[i + 1], 0, pos_bb, bb_left);
    }
    dst[i] = 0;
    dst[i] |= bb_mask(src[i], pos_bb, pos_bb + x1, -pos_bb);
    if (pos_ba > bb_left)
      dst[i] |= bb_mask(src[i + 1], 0, pos_ba - bb_left, pos_ba);
    break;
  case szc_dtyp_b2:
    for (i = 0; i < cnt2; i++) {
      dst[i] = 0;
      dst[i] |= bb_rev8(bb_mask(src[i], pos_bb, 8, -pos_bb));
      dst[i] |= bb_rev8(bb_mask(src[i + 1], 0, pos_bb, bb_left));
    }
    dst[i] = 0;
    dst[i] |= bb_rev8(bb_mask(src[i], pos_bb, pos_bb + x1, -pos_bb));
    if (pos_ba > bb_left)
      dst[i] |= bb_rev8(bb_mask(src[i + 1], 0, pos_ba - bb_left, pos_ba));
    break;
  case szc_dtyp_b3:
    if (pos_bb + count < 8) {
      dst[0] = 0;
      dst[0] |= bb_mask2(bb_rev8(src[0]), pos_bb, pos_bc, bc_left);
      break;
    }
    dst[0] = 0;
    if (pos_bc > 0)
      dst[0] |= bb_mask2(bb_rev8(src[cnt]), 0, pos_bc, bc_left);
    for (i = 0; i < cnt3; i++) {
      dst[i] |= bb_mask(bb_rev8(src[cnt - i - 1]), 0, bc_left, pos_bc);
      dst[i + 1] = 0;
      dst[i + 1] |= bb_mask2(bb_rev8(src[cnt - i - 1]), 0, pos_bc, bc_left);
    }
    dst[i] |=
        bb_mask(bb_rev8(src[0]), 0, SZCMIN(bb_left, zz8(bc_left)), pos_bc);
    if (bc_left < bb_left) {
      dst[i + 1] = 0;
      dst[i + 1] |= bb_mask2(bb_rev8(src[0]), bb_left, pos_bc, bc_left);
    }
    break;
  case szc_dtyp_b4:
    for (i = 0; i < cnt2; i++) {
      dst[i] = 0;
      dst[i] |= bb_mask(src[i], pos_bb, 8, -pos_bb);
      dst[i] |= bb_mask(src[i + 1], 0, pos_bb, bb_left);
    }
    dst[i] = 0;
    if (bc_left <= bb_left) {
      dst[i] |= bb_mask(src[i], pos_bb, zz8(pos_bc), bc_left);
    } else {
      dst[i] |= bb_mask(src[i + 1], 0, pos_bc, bc_left);
      dst[i] |= bb_mask(src[i], pos_bb, 8, -pos_bc);
    }
    break;
  default:
    break;
  }
}

static inline void _szcmask(uint8_t *dst, size_t count,
                            unsigned long long int mask) {
  uint8_t pos_bb;
  size_t cnt2;
  size_t i;
  pos_bb = mask % 8;
  cnt2 = count - (mask >> 3) - (pos_bb == 0 ? 0 : 1);
  for (i = 0; i < cnt2; i++) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst[count - i - 1] = 0;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    dst[i] = 0;
#else
#error byte order not defined
#endif
  }
  if (pos_bb > 0)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    dst[count - i - 1] &= (1 << pos_bb) - 1;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    dst[i] &= (1 << pos_bb) - 1;
#else
#error byte order not defined
#endif
}

#define _SZC_ROUNDUP(x) ((x) % 8 == 0 ? (x) : (((x) >> 3) << 3) + 8)

static inline int _szc_r(szc_dtyp_t typ, unsigned long long int count,
                         uint8_t *target, struct szc_dst_s *dd) {
  if (count == 0) {
    return 0;
  }
  if (typ >= _szc_dtyp_max) {
    return 1;
  }
  if (szc_typ_is_octal(typ))
    dd->bitlen = _SZC_ROUNDUP(dd->bitlen);
  size_t start = dd->bitlen >> 3;
  size_t end;
  if (szc_typ_is_octal(typ))
    end = start + count;
  else
    end = _SZC_ROUNDUP(dd->bitlen + count) >> 3;
  if (end > (dd->maxlen >> 3)) {
    return 1;
  }
  _szcpy_r(typ, target, dd->val + start, count,
           szc_typ_is_octal(typ) ? 0 : dd->bitlen % 8);
  dd->bitlen += szc_count_bit(typ, count);
  return 0;
}

static inline int _szc_w(szc_dtyp_t typ, unsigned long long int count,
                         uint8_t *target, struct szc_dst_s *dd) {
  if (count == 0) {
    return 0;
  }
  if (typ >= _szc_dtyp_max) {
    return 1;
  }
  if (szc_typ_is_octal(typ))
    dd->bitlen = _SZC_ROUNDUP(dd->bitlen);
  size_t start = dd->bitlen >> 3;
  size_t end;
  if (szc_typ_is_octal(typ))
    end = start + count;
  else
    end = _SZC_ROUNDUP(dd->bitlen + count) >> 3;
  if (end > (dd->maxlen >> 3))
    return 1;
#ifndef SZC_ULTRALITE
  uint8_t *val_p;
  if (!(dd->flag & SZC_FLAG_NOMLC)) {
    val_p = SZCREALLOC(dd->val, end);
    if (val_p == NULL) {
      return 1;
    }
    dd->val = val_p;
  }
#endif // SZC_ULTRALITE
  _szcpy_w(typ, dd->val + start, target, count,
           szc_typ_is_octal(typ) ? 0 : dd->bitlen % 8);
  dd->bitlen += szc_count_bit(typ, count);
  return 0;
}

static inline int szcyz_r(szc_dtyp_t typ, unsigned long long int count,
                          uint8_t *target, struct szc_dst_s *dd) {
  return _szc_r(typ, count, target, dd);
}

static inline int szcyz_w(szc_dtyp_t typ, unsigned long long int count,
                          uint8_t *target, struct szc_dst_s *dd) {
  return _szc_w(typ, count, target, dd);
}

#define szc_getmode() (SZC_DST_NAME->omode)
#define szc_foreach(idx, len) for (size_t idx = 0; idx < (len); idx++)

#define _szcexec(f1, ...)                                                      \
  do {                                                                         \
    int ans__;                                                                 \
    ans__ = f1(__VA_ARGS__);                                                   \
    if (ans__)                                                                 \
      return ans__;                                                            \
  } while (0)
#define szcy(typ, count, target)                                               \
  do {                                                                         \
    uint8_t data__[szc_count_oct(typ, count)];                                 \
    _szcmemset(data__, 0, szc_count_oct(typ, count));                          \
    if (SZC_DST_NAME->omode == szcmode_write) {                                \
      _szcexec(szcyz_w, typ, count, (uint8_t *)(target), SZC_DST_NAME);        \
    } else {                                                                   \
      _szcexec(szcyz_r, typ, count, data__, SZC_DST_NAME);                     \
      if (_szcmemcmp((uint8_t *)(target), data__,                              \
                     szc_count_oct(typ, count)) != 0)                          \
        return 1;                                                              \
    }                                                                          \
  } while (0);
#define szcset(typ, count, c)                                                  \
  do {                                                                         \
    uint8_t data__[szc_count_oct(typ, count)];                                 \
    _szcmemset(data__, c, szc_count_oct(typ, count));                          \
    szcy(typ, count, data__);                                                  \
  } while (0)
#define szcyy(typ, count, target)                                              \
  do {                                                                         \
    if (SZC_DST_NAME->omode == szcmode_write) {                                \
      _szcexec(szcyz_w, typ, count, (uint8_t *)(target), SZC_DST_NAME);        \
    } else {                                                                   \
      _szcexec(szcyz_r, typ, count, (uint8_t *)(target), SZC_DST_NAME);        \
    }                                                                          \
  } while (0)
#define szcmlcl(target_p, sz)                                                  \
  do {                                                                         \
    if (SZC_DST_NAME->omode == szcmode_read) {                                 \
      *(target_p) = SZCMALLOC(sz);                                             \
      if (*(target_p) == NULL)                                                 \
        return 1;                                                              \
      _szcmemset((uint8_t *)*(target_p), 0, sz);                               \
    }                                                                          \
  } while (0)
#define szcrealcl(target_p, sz)                                                \
  do {                                                                         \
    void *target2__;                                                           \
    if (SZC_DST_NAME->omode == szcmode_read) {                                 \
      target2__ = SZCREALLOC(*(target_p), sz);                                 \
      if (target2__ == NULL)                                                   \
        return 1;                                                              \
      *(target_p) = target2__;                                                 \
    }                                                                          \
  } while (0)
#define szcmemset(s, c, sz)                                                    \
  do {                                                                         \
    if (SZC_DST_NAME->omode == szcmode_read) {                                 \
      _szcmemset(s, c, sz);                                                    \
    }                                                                          \
  } while (0)
#define szcdelete(pt) SZCFREE(pt)

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define szcyyx(typ, count, bbcnt, target)                                      \
  szcyy(typ, count, (target) + ((bbcnt) - szc_count_oct(typ, count)))
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define szcyyx(typ, count, bbcnt, target) szcyy(typ, count, target)
#else
#error byte order not defined
#endif

#define szcv(typ, target)                                                      \
  szcyy(typ, szc_typ_is_octal(typ) ? sizeof(target) : (sizeof(target) << 3),   \
        &(target))
#define szcmlcv(typ, ptr)                                                      \
  do {                                                                         \
    szcmlcl(&(ptr), sizeof(*ptr));                                             \
    szcyy(typ, sizeof(*ptr), (uint8_t *)(ptr));                                \
  } while (0)
#define szcmlcyy(typ, len, ptr)                                                \
  do {                                                                         \
    szcmlcl(&(ptr), len);                                                      \
    szcyy(typ, len, (uint8_t *)(ptr));                                         \
  } while (0)
#define szclvp(typ, len, maxlen, ptr)                                          \
  do {                                                                         \
    szcyyx(typ, szc_conv_1(typ, szc_get_ctnsz(szc_count_oct(typ, maxlen))),    \
           szc_conv_1(typ, sizeof(len)), (uint8_t *)&(len));                   \
    if ((len) > (maxlen))                                                      \
      return 1;                                                                \
    szcmlcyy(szc_dtyp_o, szc_conv_1(typ, (len) * sizeof(*(ptr))), ptr);        \
  } while (0)
#define szclvstr2(typ, len, maxlen, ptr)                                       \
  do {                                                                         \
    szcyyx(typ, szc_conv_1(typ, szc_get_ctnsz(szc_count_oct(typ, maxlen))),    \
           szc_conv_1(typ, sizeof(len)), (uint8_t *)&(len));                   \
    if ((len) > (maxlen))                                                      \
      return 1;                                                                \
    szcmlcl(&(ptr), (len) + 1);                                                \
    szcyy(szc_dtyp_o, len, (uint8_t *)(ptr));                                  \
  } while (0)
#define szclvstr(typ, maxlen, ptr)                                             \
  do {                                                                         \
    size_t len__ =                                                             \
        (ptr) == NULL ? 0 : strnlen(ptr, szc_count_oct(typ, maxlen));          \
    szclvstr2(typ, len__, maxlen, ptr);                                        \
  } while (0)

typedef int (*szc_ff_t)(void *, struct szc_dst_s *);
#define SZFNAME(struname) SZC_CONCAT(SZF_NAME_PREFIX, struname)
#define SZFFUNCP(struname) ((szc_ff_t)SZFNAME(struname))
#define SZFDECL(t__, struname, p)                                              \
  int SZFNAME(struname)(t__ struname * p, struct szc_dst_s * SZC_DST_NAME)
#define SZFDECL_STATIC(t__, struname, p)                                       \
  static int SZFNAME(struname)(t__ struname * p,                               \
                               struct szc_dst_s * SZC_DST_NAME)

#define szcf(ff, p) _szcexec(ff, p, SZC_DST_NAME)
#define szcfn(struname, p) szcf(SZFNAME(struname), p)
#define szclvrcrse(typ, tlv_len_t, ff, target)                                 \
  do {                                                                         \
    tlv_len_t tlvv__ = 0;                                                      \
    unsigned long long int bitlen2__, bitlen3__;                               \
    if (SZC_DST_NAME->omode == szcmode_read) {                                 \
      szcv(typ, tlvv__);                                                       \
      bitlen2__ = szc_typ_is_octal(typ) ? (tlvv__ << 3) : tlvv__;              \
      if (SZC_DST_NAME->bitlen + bitlen2__ > SZC_DST_NAME->maxlen)             \
        return 1;                                                              \
      bitlen3__ = SZC_DST_NAME->maxlen;                                        \
      SZC_DST_NAME->maxlen = SZC_DST_NAME->bitlen + bitlen2__;                 \
      szcf(ff, target);                                                        \
      SZC_DST_NAME->maxlen = bitlen3__;                                        \
    } else {                                                                   \
      if (szc_typ_is_octal(typ))                                               \
        SZC_DST_NAME->bitlen = _SZC_ROUNDUP(SZC_DST_NAME->bitlen);             \
      SZC_DST_NAME->bitlen += (sizeof(tlv_len_t) << 3);                        \
      bitlen2__ = SZC_DST_NAME->bitlen;                                        \
      szcf(ff, target);                                                        \
      bitlen3__ = SZC_DST_NAME->bitlen - bitlen2__;                            \
      SZC_DST_NAME->bitlen = bitlen2__ - (sizeof(tlv_len_t) << 3);             \
      tlvv__ = szc_typ_is_octal(typ) ? (bitlen3__ >> 3) : bitlen3__;           \
      szcv(typ, tlvv__);                                                       \
      SZC_DST_NAME->bitlen += bitlen3__;                                       \
    }                                                                          \
  } while (0)

#define SZFREAD(struname, ll, p, data, datasz)                                 \
  do {                                                                         \
    struct szc_dst_s d__ = (struct szc_dst_s){                                 \
        .omode = szcmode_read,                                                 \
        .maxlen = (datasz) << 3,                                               \
        .val = data,                                                           \
    };                                                                         \
    if (SZFNAME(struname)(p, &d__)) {                                          \
      return -1;                                                               \
    }                                                                          \
    (ll) = (size_t)(d__.bitlen >> 3);                                          \
  } while (0)
#define SZFWRITE(struname, ll, p, buf, bufsz)                                  \
  do {                                                                         \
    struct szc_dst_s d__ = (struct szc_dst_s){                                 \
        .omode = szcmode_write,                                                \
        .flag = SZC_FLAG_NOMLC,                                                \
        .maxlen = (bufsz) << 3,                                                \
        .val = buf,                                                            \
    };                                                                         \
    if (SZFNAME(struname)(p, &d__)) {                                          \
      return -1;                                                               \
    }                                                                          \
    (ll) = (size_t)(d__.bitlen >> 3);                                          \
  } while (0)
#ifndef SZC_ULTRALITE
#define SZFOUTEXEC(struname, p, f, ctx1)                                       \
  do {                                                                         \
    size_t ll__;                                                               \
    struct szc_dst_s d__ = (struct szc_dst_s){                                 \
        .omode = szcmode_write,                                                \
        .maxlen = MAZ_SZ << 3,                                                 \
    };                                                                         \
    if (SZFNAME(struname)(p, &d__)) {                                          \
      return -1;                                                               \
    }                                                                          \
    ll__ = (size_t)(d__.bitlen >> 3);                                          \
    f(ctx1, d__.val, ll__);                                                    \
    SZCFREE(d__.val);                                                          \
  } while (0)
#endif // SZC_ULTRALITE

#endif // LSERZ_H
