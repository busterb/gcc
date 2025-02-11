/* { dg-do compile } */
/* { dg-options "-mcmse -mfloat-abi=softfp" } */
/* { dg-require-effective-target arm_arch_v8m_base_ok } */
/* { dg-add-options arm_arch_v8m_base } */

double __attribute__ ((cmse_nonsecure_call)) (*bar) (float, double);

double
foo (double a)
{
  return bar (1.0f, 2.0) + a;
}

float __attribute__ ((cmse_nonsecure_entry))
baz (float a, double b)
{
  return (float) bar (a, b);
}

/* Make sure we are not using FP instructions, since ARMv8-M Baseline does not
   support such instructions.  */
/* { dg-final { scan-assembler-not "vmov" } } */
/* { dg-final { scan-assembler-not "vmsr" } } */
/* { dg-final { scan-assembler-not "vmrs" } } */

/* Just double checking that we are still doing cmse though.  */
/* { dg-final { scan-assembler-not "vmrs" } } */
/* { dg-final { scan-assembler "bl\t__gnu_cmse_nonsecure_call" } } */

