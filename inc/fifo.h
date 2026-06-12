/***************************************************************************//**
 * Copyright (c) 2020 South China University of Technology. All rights reserved.
 *
 * \file        fifo.h
 * \brief
 * \author      Leon
 * \version     1.0
 * \date        2020-02-28
 * \note
 ******************************************************************************/

/* History:
 *  Version 1.0
 *    Initial release
 *
 *  Version 1.1.0, 2024-07-05
 *    Add fifo_pop()
 *    Add fifo_push()
 *  
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIFO_H__
#define __FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#define FIFO_VERSION_STRING         "1.1.0"

/* Exported types ------------------------------------------------------------*/
/**
 * \struct  fifo_structure
 * \brief   This structure holds the data that defines a fifo buffer, and
 *          pointers to access data on the buffer
 */
struct fifo_structure {
    uint8_t *           items;         /*!< Start address on memory for item space. */
    uint16_t            item_size;     /*!< Size in bytes for each element in the buffer. */
    uint16_t            capacity;      /*!< Size in bytes of the whole buffer. */
    volatile uint16_t   front;         /*!< Memory offset where data will be written. */
    volatile uint16_t   rear;          /*!< Memory offset from which we will read data. */
    volatile uint16_t   stored_bytes;  /*!< Number of bytes used currently by stored items.*/
};

typedef struct fifo_structure * fifo_t;

/* Exported constants --------------------------------------------------------*/
#define FIFO_OK                      0  /*!< NO ERROR         */
#define FIFO_PARAM_ERR              -1  /*!< Parameters ERROR */
#define FIFO_EMPTY_ERR              -2  /*!< Empty ERROR      */
#define FIFO_OVERFLOW_ERR           -3  /*!< Overflow ERROR   */

/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define fifo_push(fifo, pItem)  fifo_append(fifo, pItem)
#define fifo_pop(fifo, pItem)   fifo_detach(fifo, pItem)

/**
 * \def     FIFO_CREATE(Name, Type, Size)
 * \brief   Macro for FIFO construction
 */
#define FIFO_CREATE(Name, Type, Size)\
    Type Name##_items[Size] = {0}; \
    struct fifo_structure Name##_structure\
                = { Name##_items, \
                    sizeof(Type), \
                    (Size) * sizeof(Type),\
                    0, \
                    0, \
                    0 };\
    fifo_t Name = &Name##_structure


/* Exported functions --------------------------------------------------------*/						
int32_t     fifo_initialize   (fifo_t fifo,
                               void * items,
                               uint16_t item_num,
                               uint16_t item_size);  /*!< 初始化FIFO结构 */
int32_t     fifo_flush        (fifo_t fifo);         /*!< 清空FIFO所有数据 */
int32_t     fifo_append       (fifo_t fifo,
                               const void * item);   /*!< 向FIFO追加数据 */
int32_t     fifo_detach       (fifo_t fifo,
                               void * item);         /*!< 从FIFO分离数据 */
int32_t     fifo_peek         (fifo_t fifo,
                               void * item);         /*!< 查看FIFO当前读指针所指内容而不分离数据 */
int32_t     fifo_get_count    (fifo_t fifo);         /*!< 获取FIFO当前所存储数据个数 */
bool        fifo_is_full      (fifo_t fifo);         /*!< 查看FIFO是否已满 */
bool        fifo_is_half_full (fifo_t fifo);         /*!< 查看FIFO是否半满 */
bool        fifo_is_empty     (fifo_t fifo);         /*!< 查看FIFO是否已空 */

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /* __FIFO_H__ */
/*************************************************** End of file: fifo.h ******/
