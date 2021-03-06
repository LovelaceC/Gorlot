#ifndef __GORLOT_H
#define __GORLOT_H

#include <cglm/cglm.h>

#define SUPPORT_CAMERA_SYSTEM
#include <raylib.h>

#include <raymath.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// utils/vector.h
struct vector
{
  void **child;
  int children;
};

struct vector vector_create ();
void vector_add_child (struct vector *vector, void *element);
void vector_delete_child (struct vector *vector, void *element);
void vector_free (struct vector *vector);

// core/element.h
struct element
{
  Mesh mesh;
  Model model;

  Matrix matrix;

  Vector3 position;
  Vector3 scale;
  Vector3 rotation;

  struct vector children;

  Color color;

  struct element *parent;

  // Util info?
  int selected;
  int visible;
  int is_static;
};

enum primitive_type
{
  PRIMITIVE_CUBE,
  PRIMITIVE_CYLINDER,
  PRIMITIVE_CONE,
  PRIMITIVE_PLANE,
  PRIMITIVE_SPHERE,
  PRIMITIVE_TORUS,
  PRIMITIVE_KNOT
};

struct element element_create ();
struct element element_create_primitive (enum primitive_type type);
void element_add_child (struct element *parent, struct element *child);
_Bool element_has_children (struct element *el);
void element_update (struct element *el);
void element_draw (struct element *el);
void element_free (struct element *el);
void element_set_static (struct element *el, int is_static);
Vector3 element_get_final_position (struct element *element);

// core/scene.h
struct scene
{
  struct vector elements;
};

struct scene scene_create ();
void scene_add_element (struct scene *scene, struct element *element);
void scene_update (struct scene *scene);
void scene_free (struct scene *scene);

// core/camera.h
struct camera
{
  Camera3D cam;

  Vector3 position;
  Vector3 rotation;
};

struct camera camera_create ();
void camera_set_position (struct camera *camera, Vector3 position);
void camera_update (struct camera *camera);

// core/component.h
struct component
{
  // Owner is the element that owns this component
  void (*init) (struct element *owner);
  void (*update) (struct element *owner);
  void (*free) (struct element *owner, struct component *this);

  int type; // For loading/saving projects (basically, set the init, update and
            // free functions)
  void *data; // Just in case some data is required.
  struct element *owner;
};

// math/matrix.h
void matrix_mat4_scale_from_vec3 (mat4 mat, vec3 vec);
void matrix_mat4_rotate_from_vec3 (mat4 mat, vec3 vec);
void matrix_mat4_translate (mat4 mat, vec3 vec);
Matrix matrix_mat4_to_matrix (mat4 mat);

// math/vector.h
float *vector_vector3_to_vec3 (Vector3 vector);
Vector3 vector_vector3_add_vector3 (Vector3 v1, Vector3 v2);

#endif
