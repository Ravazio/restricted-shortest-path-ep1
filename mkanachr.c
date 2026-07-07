#include <stdio.h>
#include <stdlib.h>

#define CMAX 100
#define TMAX 100
#define TLIM 6000

#define rnd(x) (1 + (int) ((double)x*rand()/(RAND_MAX+1.0)))

int main (int argc, char* argv[])
{
  int i, j, k, m, n, s, x, y;
  int E[100][100];

  if (argc < 4) {
    fprintf (stderr, "Usage: mkanachr n m k [s]\n");
    exit (1);
  }

  n = atoi (argv[1]);
  m = atoi (argv[2]);
  k = atoi (argv[3]);
  if (argc > 4)
    s = atoi (argv[4]);
  else 
    s = 1;

  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      E[i][j] = 0;

  fprintf (stdout, "%d %d\n", n, m);
  srand ((n+m)*s);

  for (i = 0; i < m; ++i) {
    do {
      x = rnd(n), y = rnd(n);
    } while (E[x][y]);
    E[x][y] = 1;

    fprintf (stdout, "%d %d %d %d\n", x, y, rnd(CMAX), rnd(TMAX));
  }

  fprintf (stdout, "%d\n", k);
  for (i = 0; i < k; ++i)
    fprintf (stdout, "%d %d %d\n", rnd(n), rnd(n), rnd(TLIM));

  return 0;
}
