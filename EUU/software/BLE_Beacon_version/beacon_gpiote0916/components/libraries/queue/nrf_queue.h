/* Copyright (c) 2016 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */


/**
* @defgroup nrf_queue Queue module
* @{
* @ingroup app_common
* @brief Functions that handle the queue instances.
*/

#ifndef NRF_QUEUE_H__
#define NRF_QUEUE_H__

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "nrf_assert.h"
#include "sdk_errors.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Queue control block. */
typedef struct
{
    size_t front;                   //!< Queue front index.
    size_t back;                    //!< Queue back index.
    size_t max_utilization;         //!< Maximum utilization of the queue.
} nrf_queue_cb_t;

/**@brief Supported queue modes. */
typedef enum
{
    NRF_QUEUE_MODE_OVERFLOW,        //!< If the queue is full, new element will not be accepted.
    NRF_QUEUE_MODE_NO_OVERFLOW,     //!< If the queue is full, new element will overwrite the oldest.
} nrf_queue_mode_t;

/**@brief Instance of the queue. */
typedef struct
{
    nrf_queue_cb_t * p_cb;          //!< Pointer to the instance control block.
    void           * p_buffer;      //!< Pointer to the memory that is used as storage.
    size_t           size;          //!< Size of the queue.
    size_t           element_size;  //!< Size of one element.
    nrf_queue_mode_t mode;          //!< Mode of the queue.
} nrf_queue_t;

/**@brief Create a queue instance.
 *
 * @note  This macro reserves memory for the given queue instance.
 *
 * @param[in]   _type       Type which is stored.
 * @param[in]   _name       Name of the queue.
 * @param[in]   _size       Size of the queue.
 * @param[in]   _mode       Mode of the queue.
 */
#define NRF_QUEUE_DEF(_type, _name, _size, _mode)                   \
    static _type             _name##_nrf_queue_buffer[(_size) + 1]; \
    static nrf_queue_cb_t    _name##_nrf_queue_cb;                  \
    static const nrf_queue_t _name =                                \
        {                                                           \
            .p_cb           = &_name##_nrf_queue_cb,                \
            .p_buffer       = _name##_nrf_queue_buffer,             \
            .size           = (_size),                              \
            .element_size   = sizeof(_type),                        \
            .mode           = _mode,                                \
        }

/**@brief Declare a queue interface.
 *
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 */
#define NRF_QUEUE_INTERFACE_DEC(_type, _name)               \
    ret_code_t  _name##_push(_type const * p_element);      \
    ret_code_t  _name##_pop(_type * p_element);             \
    ret_code_t  _name##_peek(_type * p_element);            \
    ret_code_t  _name##_write(_type const * p_data,         \
                              size_t        element_count); \
    ret_code_t  _name##_read(_type * p_data,                \
                             size_t  element_count);        \
    size_t      _name##_out(_type * p_data,                 \
                            size_t  element_count);         \
    size_t      _name##_in(_type * p_data,                  \
                            size_t element_count);          \
    bool        _name##_is_full(void);                      \
    bool        _name##_is_empty(void);                     \
    size_t      _name##_utilization_get(void);              \
    size_t      _name##_available_get(void);                \
    size_t      _name##_max_utilization_get(void);          \
    void        _name##_reset(void)

/**@brief Define a custom queue interface.
 *
 * @param[in]   _attr    Function attribute that will be added to the queue function definition.
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 * @param[in]   _p_queue Queue instance.
 */
#define NRF_QUEUE_INTERFACE_CUSTOM_DEF(_attr, _type, _name, _p_queue)   \
    _attr ret_code_t _name##_push(_type const * p_element)              \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_push((_p_queue), p_element);                   \
    }                                                                   \
    _attr ret_code_t _name##_pop(_type * p_element)                     \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_pop((_p_queue), p_element);                    \
    }                                                                   \
    _attr ret_code_t _name##_peek(_type * p_element)                    \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_peek((_p_queue), p_element);                   \
    }                                                                   \
    ret_code_t _name##_write(_type const * p_data,                      \
                             size_t        element_count)               \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_write((_p_queue), p_data, element_count);      \
    }                                                                   \
    ret_code_t _name##_read(_type * p_data,                             \
                            size_t  element_count)                      \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_read((_p_queue), p_data, element_count);       \
    }                                                                   \
    size_t _name##_in(_type * p_data,                                   \
                      size_t  element_count)                            \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_in((_p_queue), p_data, element_count);         \
    }                                                                   \
    size_t _name##_out(_type * p_data,                                  \
                       size_t  element_count)                           \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        return nrf_queue_out((_p_queue), p_data, element_count);        \
    }                                                                   \
    bool _name##_is_full(void)                                          \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_is_full(_p_queue);                             \
    }                                                                   \
    bool _name##_is_empty(void)                                         \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_is_empty(_p_queue);                            \
    }                                                                   \
    size_t _name##_utilization_get(void)                                \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_utilization_get(_p_queue);                     \
    }                                                                   \
    size_t _name##_available_get(void)                                  \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_available_get(_p_queue);                       \
    }                                                                   \
    size_t _name##_max_utilization_get(void)                            \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_max_utilization_get(_p_queue);                 \
    }                                                                   \
    void _name##_reset(void)                                            \
    {                                                                   \
        ASSERT((_p_queue) != NULL);                                     \
        nrf_queue_reset(_p_queue);                                      \
    }

/**@brief Define a queue interface.
 *
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 * @param[in]   _p_queue Queue instance.
 */
#define NRF_QUEUE_INTERFACE_DEF(_type, _name, _p_queue)                 \
        NRF_QUEUE_INTERFACE_CUSTOM_DEF(/* empty */, _type, _name, _p_queue)

/**@brief Define a local queue interface.
 *
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 * @param[in]   _p_queue Queue instance.
 */
#define NRF_QUEUE_INTERFACE_LOCAL_DEF(_type, _name, _p_queue)           \
        NRF_QUEUE_INTERFACE_CUSTOM_DEF(static, _type, _name, _p_queue)

/**@brief Function for pushing an element to the end of queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_element           Pointer to the element that will be stored in the queue.
 *
 * @return      NRF_SUCCESS         If an element has been successfully added.
 * @return      NRF_ERROR_NO_MEM    If the queue is full (only in @ref NRF_QUEUE_MODE_NO_OVERFLOW).
 */
ret_code_t nrf_queue_push(nrf_queue_t const * p_queue, void const * p_element);

/**@brief Generic pop implementation.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_element           Pointer where the element will be copied.
 * @param[out]  just_peek           If true, the returned element will not be removed from queue.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
ret_code_t nrf_queue_generic_pop(nrf_queue_t const * p_queue,
                                 void              * p_element,
                                 bool                just_peek);

/**@brief Pop element from the front of the queue.
 *
 * @param[in]   _p_queue            Pointer to the nrf_queue_t instance.
 * @param[out]  _p_element          Pointer where the element will be copied.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
#define nrf_queue_pop(_p_queue, _p_element) nrf_queue_generic_pop((_p_queue), (_p_element), false)

/**@brief Peek element from the front of the queue.
 *
 * @param[in]   _p_queue            Pointer to the nrf_queue_t instance.
 * @param[out]  _p_element          Pointer where the element will be copied.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
#define nrf_queue_peek(_p_queue, _p_element) nrf_queue_generic_pop((_p_queue), (_p_element), true)

/**@brief Function for writing elements to the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_data              Pointer to the buffer with elements to write.
 * @param[in]   element_count       Number of elements to write.
 *
 * @return      NRF_SUCCESS         If an element was written.
 * @return      NRF_ERROR_NO_MEM    There is not enough space in the queue. No element was written.
 */
ret_code_t nrf_queue_write(nrf_queue_t const * p_queue,
                           void const        * p_data,
                           size_t              element_count);

/**@brief Function for writing a portion of elements to the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_data              Pointer to the buffer with elements to write.
 * @param[in]   element_count       Number of elements to write.
 *
 * @return      The number of added elements.
 */
size_t nrf_queue_in(nrf_queue_t const * p_queue,
                    void              * p_data,
                    size_t              element_count);

/**@brief Function for reading elements from the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_data              Pointer to the buffer where elements will be copied.
 * @param[in]   element_count       Number of elements to read.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND There is not enough elements in the queue.
 */
ret_code_t nrf_queue_read(nrf_queue_t const * p_queue,
                          void              * p_data,
                          size_t              element_count);

/**@brief Function for reading a portion of elements from the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_data              Pointer to the buffer where elements will be copied.
 * @param[in]   element_count       Number of elements to read.
 *
 * @return      The number of read elements.
 */
size_t nrf_queue_out(nrf_queue_t const * p_queue,
                    void               * p_data,
                    size_t               element_count);

/**@brief Function for checking if the queue is full. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      True if the queue is full.
 */
bool nrf_queue_is_full(nrf_queue_t const * p_queue);

/**@brief Function for checking if the queue is empty. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      True if the queue is empty.
 */
__STATIC_INLINE bool nrf_queue_is_empty(nrf_queue_t const * p_queue);

/**@brief Function for getting the current queue utilization. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Current queue utilization.
 */
size_t nrf_queue_utilization_get(nrf_queue_t const * p_queue);

/**@brief Function for getting the size of available space. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Size of available space.
 */
__STATIC_INLINE size_t nrf_queue_available_get(nrf_queue_t const * p_queue);

/**@brief Function for getting the maximal queue utilization. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Maximal queue utilization.
 */
__STATIC_INLINE size_t nrf_queue_max_utilization_get(nrf_queue_t const * p_queue);

/**@brief Function for resetting the queue state. 
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 */
void nrf_queue_reset(nrf_queue_t const * p_queue);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE bool nrf_queue_is_empty(nrf_queue_t const * p_queue)
{
    ASSERT(p_queue != NULL);
    return (p_queue->p_cb->front == p_queue->p_cb->back);
}

__STATIC_INLINE size_t nrf_queue_available_get(nrf_queue_t const * p_queue)
{
    ASSERT(p_queue != NULL);
    return p_queue->size - nrf_queue_utilization_get(p_queue);
}

__STATIC_INLINE size_t nrf_queue_max_utilization_get(nrf_queue_t const * p_queue)
{
    ASSERT(p_queue != NULL);
    return p_queue->p_cb->max_utilization;
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // NRF_QUEUE_H__
/** @} */
