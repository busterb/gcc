/* { dg-do assemble } */
/* { dg-options "-O -march=armv8-a+sve -msve-vector-bits=256 --save-temps" } */

#include <stdint.h>

typedef int64_t v4di __attribute__((vector_size (32)));
typedef int32_t v8si __attribute__((vector_size (32)));
typedef int16_t v16hi __attribute__((vector_size (32)));
typedef int8_t v32qi __attribute__((vector_size (32)));
typedef double v4df __attribute__((vector_size (32)));
typedef float v8sf __attribute__((vector_size (32)));
typedef _Float16 v16hf __attribute__((vector_size (32)));

#define EXTRACT(ELT_TYPE, TYPE, INDEX)		\
  ELT_TYPE permute_##TYPE##_##INDEX (void)	\
  {						\
    TYPE values;				\
    asm ("" : "=w" (values));			\
    return values[INDEX];			\
  }

#define TEST_ALL(T)				\
  T (int64_t, v4di, 0)				\
  T (int64_t, v4di, 1)				\
  T (int64_t, v4di, 2)				\
  T (int64_t, v4di, 3)				\
  T (int32_t, v8si, 0)				\
  T (int32_t, v8si, 1)				\
  T (int32_t, v8si, 3)				\
  T (int32_t, v8si, 4)				\
  T (int32_t, v8si, 7)				\
  T (int16_t, v16hi, 0)				\
  T (int16_t, v16hi, 1)				\
  T (int16_t, v16hi, 7)				\
  T (int16_t, v16hi, 8)				\
  T (int16_t, v16hi, 15)			\
  T (int8_t, v32qi, 0)				\
  T (int8_t, v32qi, 1)				\
  T (int8_t, v32qi, 15)				\
  T (int8_t, v32qi, 16)				\
  T (int8_t, v32qi, 31)				\
  T (double, v4df, 0)				\
  T (double, v4df, 1)				\
  T (double, v4df, 2)				\
  T (double, v4df, 3)				\
  T (float, v8sf, 0)				\
  T (float, v8sf, 1)				\
  T (float, v8sf, 3)				\
  T (float, v8sf, 4)				\
  T (float, v8sf, 7)				\
  T (_Float16, v16hf, 0)			\
  T (_Float16, v16hf, 1)			\
  T (_Float16, v16hf, 7)			\
  T (_Float16, v16hf, 8)			\
  T (_Float16, v16hf, 15)

TEST_ALL (EXTRACT)

/* { dg-final { scan-assembler-times {\tumov\tx[0-9]+, v[0-9]+\.d\[0\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tumov\tx[0-9]+, v[0-9]+\.d\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-not {\tdup\td[0-9]+, v[0-9]+\.d\[0\]\n} } } */
/* { dg-final { scan-assembler-times {\tdup\td[0-9]+, v[0-9]+\.d\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\tz[0-9]+\.d, z[0-9]+\.d\[2\]\n} 2 } } */
/* { dg-final { scan-assembler-times {\tlastb\tx[0-9]+, p[0-7], z[0-9]+\.d\n} 1 } } */
/* { dg-final { scan-assembler-times {\tlastb\td[0-9]+, p[0-7], z[0-9]+\.d\n} 1 } } */

/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.s\[0\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.s\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.s\[3\]\n} 1 } } */
/* { dg-final { scan-assembler-not {\tdup\ts[0-9]+, v[0-9]+\.s\[0\]\n} } } */
/* { dg-final { scan-assembler-times {\tdup\ts[0-9]+, v[0-9]+\.s\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\ts[0-9]+, v[0-9]+\.s\[3\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\tz[0-9]+\.s, z[0-9]+\.s\[4\]\n} 2 } } */
/* { dg-final { scan-assembler-times {\tlastb\tw[0-9]+, p[0-7], z[0-9]+\.s\n} 1 } } */
/* { dg-final { scan-assembler-times {\tlastb\ts[0-9]+, p[0-7], z[0-9]+\.s\n} 1 } } */

/* Also used to move the result of a non-Advanced SIMD extract.  */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.h\[0\]\n} 2 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.h\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.h\[7\]\n} 1 } } */
/* { dg-final { scan-assembler-not {\tdup\th[0-9]+, v[0-9]+\.h\[0\]\n} } } */
/* { dg-final { scan-assembler-times {\tdup\th[0-9]+, v[0-9]+\.h\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\th[0-9]+, v[0-9]+\.h\[7\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\tz[0-9]+\.h, z[0-9]+\.h\[8\]\n} 2 } } */
/* { dg-final { scan-assembler-times {\tlastb\tw[0-9]+, p[0-7], z[0-9]+\.h\n} 1 } } */
/* { dg-final { scan-assembler-times {\tlastb\th[0-9]+, p[0-7], z[0-9]+\.h\n} 1 } } */

/* Also used to move the result of a non-Advanced SIMD extract.  */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.b\[0\]\n} 2 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.b\[1\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tumov\tw[0-9]+, v[0-9]+\.b\[15\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tdup\tz[0-9]+\.b, z[0-9]+\.b\[16\]\n} 1 } } */
/* { dg-final { scan-assembler-times {\tlastb\tw[0-9]+, p[0-7], z[0-9]+\.b\n} 1 } } */
