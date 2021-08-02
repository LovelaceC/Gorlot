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

void
vector_delete_child (struct vector *vector, void *element)
{
  int index = 0;

  for (int i = 0; i < vector->children; i++)
    {
      if (vector->child[i] == element)
        {
          index = i;
          break;
        }
    }

  vector->child[index] = NULL;

  for (int i = index; i < vector->children - 1; i++)
    {
      vector->child[i] = vector->child[i + 1];
      vector->child[i + 1] = NULL;
    }

  vector->children -= 1;
  vector->child = realloc (vector->child, sizeof (void *) * vector->children);
}

void
vector_free (struct vector *vector)
{
  // Freeing a vector contents is the programmer's responsibility
  free (vector->child);
  vector->child = NULL;

  vector->children = 0;
}
