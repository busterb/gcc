/* { dg-do compile } */
/* { dg-options "-O2 -ftree-loop-distribution -ftree-loop-distribute-patterns -fdump-tree-ldist-details" } */

#define M (256)
#define N (512)
int a[M][N], b[M][N], c[M];

void
foo (void)
{
  for (int i = M - 1; i >= 0; --i)
    {
      c[i] = 0;
      for (unsigned j = N; j > 0; --j)
	a[i][j - 1] = b[i][j - 1];
    }
}

/* { dg-final { scan-tree-dump-times "Loop nest . distributed: split to 0 loops and 2 library" 1 "ldist" } } */
