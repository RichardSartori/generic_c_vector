/**
 * Generic dynamically sized array in C
 *
 * The core of this file are the macros DECLARE_VEC and IMPLEMENT_VEC.
 * These macros take two parameters, `prefix` and `type`, and generate
 * respectively the declarations and implementations of all the functions
 * of `prefix`vec, a container able to hold a dynamic number of `type` elements.
 */

#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdlib.h>
#include <stdint.h>

/**
 * Error code of faillible operations
 */
typedef enum {
	SUCCESS = 0,        /* no error */
	OUT_OF_MEMORY = -1, /* failed to allocate memory */
	OUT_OF_BOUNDS = -2, /* index out of bounds */
} vec_result;

/**
 * Type declaration of `prefix`vec
 * @warning do not modify fields manually
 */
#define STRUCT(type, prefix) \
typedef struct {             \
	size_t size, capacity;   \
	type* data;              \
} prefix##vec;               \

/**
 * Constructor for `prefix`vec
 * @return an empty `prefix`vec
 */
#define CREATE_SIGNATURE(type, prefix) \
prefix##vec prefix##vec_create(void)   \

#define IMPLEMENT_CREATE(type, prefix) \
CREATE_SIGNATURE(type, prefix) {       \
	prefix##vec retval = {             \
		.size = 0,                     \
		.capacity = 0,                 \
		.data = NULL,                  \
	};                                 \
	return retval;                     \
}                                      \

/**
 * Destructor for `prefix`vec
 * @param vec pointer to the `prefix`vec
 */
#define DESTROY_SIGNATURE(type, prefix)    \
void prefix##vec_destroy(prefix##vec* vec) \

#define IMPLEMENT_DESTROY(type, prefix) \
DESTROY_SIGNATURE(type, prefix) {       \
	vec->size = vec->capacity = 0;      \
	free(vec->data);                    \
}                                       \

/**
 * Get the size of a `prefix`vec
 * @param vec pointer to the `prefix`vec
 * @return the size of the `prefix`vec
 */
#define SIZE_SIGNATURE(type, prefix)            \
size_t prefix##vec_size(prefix##vec const* vec) \

#define IMPLEMENT_SIZE(type, prefix) \
SIZE_SIGNATURE(type, prefix) {       \
	return vec->size;                \
}                                    \

/**
 * Check if a `prefix`vec is empty
 * @param vec pointer to the `prefix`vec
 * @return 1 if the `prefix`vec is empty, 0 otherwise
 */
#define IS_EMPTY_SIGNATURE(type, prefix)         \
int prefix##vec_is_empty(prefix##vec const* vec) \

#define IMPLEMENT_IS_EMPTY(type, prefix) \
IS_EMPTY_SIGNATURE(type, prefix) {       \
	return prefix##vec_size(vec) == 0;   \
}                                        \

/**
 * Reserve memory for at least `additional` more elements
 * (preserving the growth factor)
 * @param vec pointer to the `prefix`vec
 * @param additional lower bound of capacity increase
 * @return a vec_result
 */
#define RESERVE_SIGNATURE(type, prefix)                             \
vec_result prefix##vec_reserve(prefix##vec* vec, size_t additional) \

#define IMPLEMENT_RESERVE(type, prefix)                               \
RESERVE_SIGNATURE(type, prefix) {                                     \
	if (additional == 0) return SUCCESS;                              \
	if (vec->size > SIZE_MAX - additional) return OUT_OF_MEMORY;      \
	if (vec->capacity > vec->size + additional) return SUCCESS;       \
	size_t min_increment = vec->capacity / 2;                         \
	if (additional < min_increment) additional = min_increment;       \
	if (vec->capacity > SIZE_MAX - additional) return OUT_OF_MEMORY;  \
	size_t new_capacity = vec->capacity + additional;                 \
	if (new_capacity > SIZE_MAX / sizeof(type)) return OUT_OF_MEMORY; \
	size_t byte_size = new_capacity * sizeof(type);                   \
	type* new_data = realloc(vec->data, byte_size);                   \
	if (new_data == NULL) return OUT_OF_MEMORY;                       \
	vec->data = new_data;                                             \
	vec->capacity = new_capacity;                                     \
	return SUCCESS;                                                   \
}                                                                     \

/**
 * Remove all elements from a `prefix`vec
 * @param vec pointer to the `prefix`vec
 */
#define CLEAR_SIGNATURE(type, prefix)    \
void prefix##vec_clear(prefix##vec* vec) \

#define IMPLEMENT_CLEAR(type, prefix) \
CLEAR_SIGNATURE(type, prefix) {       \
	vec->size = 0;                    \
}                                     \

/**
 * Append an element at the end of a `prefix`vec
 * @param vec pointer to the `prefix`vec
 * @param value value to push
 * @return a vec_result
 */
#define PUSH_SIGNATURE(type, prefix)                      \
vec_result prefix##vec_push(prefix##vec* vec, type value) \

#define IMPLEMENT_PUSH(type, prefix)              \
PUSH_SIGNATURE(type, prefix) {                    \
	vec_result res = prefix##vec_reserve(vec, 1); \
	if (res != SUCCESS) return res;               \
	*prefix##vec_end(vec) = value;                \
	++(vec->size);                                \
	return SUCCESS;                               \
}

/**
 * Remove the last element from a `prefix`vec
 * @param vec pointer to the `prefix`vec
 * @return a vec_result
 */
#define POP_SIGNATURE(type, prefix)          \
vec_result prefix##vec_pop(prefix##vec* vec) \

#define IMPLEMENT_POP(type, prefix)                      \
POP_SIGNATURE(type, prefix) {                            \
	if (prefix##vec_is_empty(vec)) return OUT_OF_BOUNDS; \
	--(vec->size);                                       \
	return SUCCESS;                                      \
}                                                        \

/**
 * Set the value of an element from a `prefix`vec
 * @param vec pointer to the `prefix`vec
 * @param index index of the element to set
 * @param value value of the element to set
 * @return a vec_result
 */
#define SET_SIGNATURE(type, prefix)                                          \
vec_result prefix##vec_set(prefix##vec* vec, size_t index, type const value) \

#define IMPLEMENT_SET(type, prefix)               \
SET_SIGNATURE(type, prefix) {                     \
	if (index >= vec->size) return OUT_OF_BOUNDS; \
	vec->data[index] = value;                     \
	return SUCCESS;                               \
}                                                 \

/**
 * Get the value of an element from a `prefix`vec
 * @param vec pointer to the `prefix`vec
 * @param index index of the element to get
 * @param[out] ptr pointer to store the value of the element
 * @return a vec_result
 */
#define GET_SIGNATURE(type, prefix)                                         \
vec_result prefix##vec_get(prefix##vec const* vec, size_t index, type* ptr) \

#define IMPLEMENT_GET(type, prefix)               \
GET_SIGNATURE(type, prefix) {                     \
	if (index >= vec->size) return OUT_OF_BOUNDS; \
	*ptr = vec->data[index];                      \
	return SUCCESS;                               \
}                                                 \

/**
 * Iterator to the beginning of a `prefix`vec
 * (may be invalidated by `prefix`vec_push and `prefix`vec_pop)
 * @param vec pointer to the `prefix`vec
 * @return a pointer to the first element
 */
#define BEGIN_SIGNATURE(type, prefix)           \
type* prefix##vec_begin(prefix##vec const* vec) \

#define IMPLEMENT_BEGIN(type, prefix) \
BEGIN_SIGNATURE(type, prefix) {       \
	return vec->data;                 \
}                                     \

/**
 * Iterator to the end of a `prefix`vec
 * (may be invalidated by `prefix`vec_push and `prefix`vec_pop)
 * @param vec pointer to the `prefix`vec
 * @return a pointer to one past the last element
 */
#define END_SIGNATURE(type, prefix)           \
type* prefix##vec_end(prefix##vec const* vec) \

#define IMPLEMENT_END(type, prefix) \
END_SIGNATURE(type, prefix) {       \
	return vec->data+vec->size;     \
}                                   \

/**
 * Generate the declaration of `prefix`vec and its associated functions
 * @param type type of the elements to hold
 * @param prefix prefix added to all declarations
 */
#define DECLARE_VEC(type, prefix) \
STRUCT(type, prefix)              \
CREATE_SIGNATURE(type, prefix);   \
DESTROY_SIGNATURE(type, prefix);  \
SIZE_SIGNATURE(type, prefix);     \
IS_EMPTY_SIGNATURE(type, prefix); \
RESERVE_SIGNATURE(type, prefix);  \
CLEAR_SIGNATURE(type, prefix);    \
PUSH_SIGNATURE(type, prefix);     \
POP_SIGNATURE(type, prefix);      \
SET_SIGNATURE(type, prefix);      \
GET_SIGNATURE(type, prefix);      \
BEGIN_SIGNATURE(type, prefix);    \
END_SIGNATURE(type, prefix);      \

/**
 * Generate the implementation of `prefix`vec and its associated functions
 * @param type type of the elements to hold
 * @param prefix prefix added to all declarations
 */
#define IMPLEMENT_VEC(type, prefix) \
IMPLEMENT_CREATE(type, prefix)      \
IMPLEMENT_DESTROY(type, prefix)     \
IMPLEMENT_SIZE(type, prefix)        \
IMPLEMENT_IS_EMPTY(type, prefix)    \
IMPLEMENT_RESERVE(type, prefix)     \
IMPLEMENT_CLEAR(type, prefix)       \
IMPLEMENT_PUSH(type, prefix)        \
IMPLEMENT_POP(type, prefix)         \
IMPLEMENT_SET(type, prefix)         \
IMPLEMENT_GET(type, prefix)         \
IMPLEMENT_BEGIN(type, prefix)       \
IMPLEMENT_END(type, prefix)         \

/**
 * Generate both declaration and implementation of `prefix`vec
 * @param type type of the elements to hold
 * @param prefix prefix added to all declarations
 */
#define VEC(type, prefix)   \
DECLARE_VEC(type, prefix)   \
IMPLEMENT_VEC(type, prefix) \

#endif // _VECTOR_H
