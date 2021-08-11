#include <gorlot.h>

/**
 * This component system will work through callbacks.
 * For example:
 *
 * struct component *light_component = component_create (callbacks);
 * element_add_component (el, light_component);
 *
 * When the component is added to an element, it will initialised, and the
 * variable "owner" will be set to point to the element the component was added
 * to.
 *
 * Now, when the element is updated and free'd, the respective callbacks will
 * be called for each component.
 *
 * There's also a void pointer called "data", in which the programmer can store
 * the data that is required for that component to work properly.
 *
 * And also, there's a variable called "type" which will be used for loading
 * and saving projects, depending on this variable's value, some callbacks will
 * be set by default, that is, initialising the component from a file (as we
 * cannot do "component->init = fgets("%s", file)" to set a function to a
 * component.
 *
 * This system might need some refactoring in the way it will work, that's why
 * I haven't started coding it yet, instead, I will wait some time, I will try
 * to think of a new way of doing this and then I will start working on some
 * components.
 *
 * Some components I've thought of are:
 *
 * Light component (emits light - based on owner's properties.)
 * Sound component (emits a sound.)
 * Collider component (checks if another element in the scene has collided with
 * owner's properties.)
 * Physics components (basically... Physics?)
 */
