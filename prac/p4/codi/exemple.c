#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i;
  int *p;

  p = malloc(10 * sizeof(int));

  for(i = 0; i < 10; i++)
    p[i] = i;

  for(i = 0; i < 10; i++)
    printf("%d\n", p[i]);

  void *tmp = realloc(NULL, 1);
  p = realloc(p, 5 * sizeof(int));
  p = realloc(p, 15 * sizeof(int));

  p = calloc(5, sizeof(int));

  free(p);


  p = calloc(10, sizeof(int));
  free(p);

  return 0;
}
