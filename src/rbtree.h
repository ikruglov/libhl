/**
 * @file rbtree.h
 *
 * @brief Red/Black Tree
 *
 * Red/Black Tree implementation to store/access arbitrary data
 *
 * @todo extend the api to allow walking from/to a specific node
 *       (instead of only allowing to walk the entire tree)
 *
 */

#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <stdint.h>
#include "comparators.h"

/**
 * @brief Opaque structure representing the tree
 */
typedef struct __rbt_s rbt_t;

/**
 * @brief Callback that, if provided, will be called to release the value
 *        resources when an item is being overwritten or when removed from
 *        the tree
 * @param v the pointer to free
 */
typedef void (*rbt_free_value_callback_t)(void *v);

/**
 * @brief Create a new red/black tree
 * @param cmp_keys_cb   The comparator callback to use when comparing
 *                      keys (defaults to memcmp())
 * @param free_value_cb The callback used to release values when a node
 *                      is removed or overwritten
 * @return              A valid and initialized red/black tree (empty)
 */
rbt_t *rbt_create(libhl_cmp_callback_t cmp_keys_cb,
                        rbt_free_value_callback_t free_value_cb);

/**
 * @brief Release all the resources used by a red/black tree
 * @param rbt A valid pointer to an initialized rbt_t structure
 */
void rbt_destroy(rbt_t *rbt);

/**
 * @brief Add a new value into the tree
 * @param rbt   A valid pointer to an initialized rbt_t structure
 * @param key   The key of the node where to store the new value
 * @param klen  The size of the key
 * @param value The new value to store
 * @param vsize The size of the value
 * @return 0 if a new node has been created successfully;
 *         1 if an existing node has been found and the value has been updated;
 *         -1 otherwise
 */
int rbt_add(rbt_t *rbt, void *key, size_t klen, void *value, size_t vsize);


/**
 * @brief Remove a node from the tree
 * @param rbt   A valid pointer to an initialized rbt_t structure
 * @param key  The key of the node to remove
 * @param klen The size of the key
 * @param value If not NULL the address of the value hold by the removed node
 *              will be stored at the memory pointed by the 'value' argument.
 *              If NULL and a free_value_callback is set, the value hold by
 *              the removed node will be released using the free_value_callback
 * @param vlen  If not NULL the size of the value hold by the removed node
 *              will be stored at the memory pointed by the 'vlen' argument
 * @return 0 on success; -1 otherwise
 */
int rbt_remove(rbt_t *rbt, void *key, size_t klen, void **value, size_t *vlen);

/**
 * @brief Find the value stored in the node node matching a specific key
 *        (if any)
 * @param rbt   A valid pointer to an initialized rbt_t structure
 * @param key   The key of the node where to store the new value
 * @param klen The size of the key
 * @param value A reference to the pointer which will set to point to the
 *              actual value if found
 * @param vsize A pointer to the memory where to store the size of the value
 * @return 0 on success and both *value and *vsize are set to point to the stored
 *         value and its size;\n-1 if not found
 */
int rbt_find(rbt_t *rbt, void *key, size_t klen, void **value, size_t *vsize);

/**
 * @brief Callback called for each node when walking the tree
 * @param rbt   A valid pointer to an initialized rbt_t structure
 * @param key  The key of the node where to store the new value
 * @param klen The size of the key
 * @param value The new value to store
 * @param vsize The size of the value
 * @param priv  The private pointer passed to either rbt_walk() or rbt_walk_sorted()
 * @return 1 If the walker can go ahead visiting the next node,
 *         0 if the walker should stop and return
 *        -1 if the current node should be removed and the walker can go ahead
 *        -2 if the current node should be removed and the walker should stop
 */
typedef int (*rbt_walk_callback)(rbt_t *rbt,
                                    void *key,
                                    size_t klen,
                                    void *value,
                                    size_t vsize,
                                    void *priv);

/**
 * @brief Walk the entire tree and call the callback for each visited node
 * @param rbt  A valid pointer to an initialized rbt_t structure
 * @param cb   The callback to call for each visited node
 * @param priv A pointer to private data provided passed as argument to the
 *             callback when invoked.
 * @return The number of visited nodes
 */
int rbt_walk(rbt_t *rbt, rbt_walk_callback cb, void *priv);

/**
 * @brief Walk the entire tree visiting nodes in ascending order and call the callback
 *        for each visited node
 * @param rbt  A valid pointer to an initialized rbt_t structure
 * @param cb   The callback to call for each visited node
 * @param priv A pointer to private data provided passed as argument to the
 *             callback when invoked.
 * @return The number of visited nodes
 */
int rbt_walk_sorted(rbt_t *rbt, rbt_walk_callback cb, void *priv);

#ifdef DEBUG_RBTREE
/**
 * @brief Print out the whole tree on stdout (for debugging purposes only)
 */
void rbtree_print(rbtree_t *rbt);
#endif

#endif
