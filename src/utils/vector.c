#include <gorlot.h>

struct vector
vector_create ()
{
  struct vector vector = { 0 };
  vector.child = NULL;
  vector.children = 0;
  return vector;
}

void
vector_add_child (struct vector *vector, void *element)
{
  vector->child
      = realloc (vector->child, sizeof (void *) * vector->children + 1);

  if (!vector->child)
    {
      printf (
          "vector_add_child: Error allocating memory for `vector->child'.\n");
      return;
    }

  vector->child[vector->children] = element;
  vector->children += 1;
}
