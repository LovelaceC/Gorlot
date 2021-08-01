#include <gorlot.h>

struct scene
scene_create ()
{
  struct scene scene = { 0 };

  scene.elements = vector_create ();

  return scene;
}

void
scene_add_element (struct scene *scene, struct element *element)
{
  vector_add_child (&scene->elements, element);
}

void
scene_update (struct scene *scene)
{
  for (int i = 0; i < scene->elements.children; i++)
    {
      element_update (scene->elements.child[i]);
    }
}
