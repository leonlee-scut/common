/***************************************************************************//**
 * Copyright (c) 2020 South China University of Technology. All rights reserved.
 *
 * \file        fifo.c
 * \brief
 * \author      Leon
 * \version     1.0
 * \date        2020-02-28
 * \note
 ******************************************************************************/

/* History:
 *  Version 1.0
 *    Initial release
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "critical_section.h"
#include "atomic.h"
#include "fifo.h"

/* Public variables ----------------------------------------------------------*/
/* Private typedefs ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/***************************************************************************//**
 * \fn          int32_t fifo_initialize  (fifo_t fifo, void * items, uint16_t item_num, uint16_t item_size)
 * \brief		初始化FIFO结构
 * \param[in]	fifo        指向被操作FIFO数据结构指针
 * \param[in]   items       指向FIFO中存放元素的数组指针
 * \param[in]   item_num    FIFO中存放的元素个数
 * \param[in]   item_size   单个元素存放空间大小，以Byte为单位
 * \return		 0          - 操作成功
 *              -1          - 操作失败
 ******************************************************************************/
int32_t fifo_initialize(fifo_t fifo,
                        void *items,
                        uint16_t item_num,
                        uint16_t item_size)
{
    ASSERT(fifo != NULL && items != NULL && item_num != 0 && item_size != 0);
    // if (fifo == NULL || items == NULL || item_num == 0 || item_size == 0)
    // {
    //     return (FIFO_PARAM_ERR);
    // }

    fifo->items = items;
    fifo->item_size = item_size;
    fifo->capacity = item_num * item_size;
    fifo->front = 0;
    fifo->rear = 0;
    fifo->stored_bytes = 0;

    return (FIFO_OK);
}


/***************************************************************************//**
 * \fn          int32_t fifo_flush(fifo_t fifo)
 * \brief       清空FIFO所有数据
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \return       0          - 操作成功
 *              -1          - 操作失败
 ******************************************************************************/
int32_t fifo_flush(fifo_t fifo)
{
    ASSERT(fifo != NULL);
    // if (fifo == NULL)
    // {
    //     return (FIFO_PARAM_ERR);
    // }

    fifo->front = 0;
    fifo->rear = 0;
    fifo->stored_bytes = 0;

    return (FIFO_OK);
}


/***************************************************************************//**
 * \fn          int32_t fifo_append(fifo_t fifo, const void *item)
 * \brief       向FIFO追加数据
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \param[in]   item        指向新增元素的指针
 * \return       0          - 操作成功
 *              -1          - 操作失败
 ******************************************************************************/
int32_t fifo_append(fifo_t fifo, const void *item)
{
    ASSERT(fifo != NULL && item != NULL);
    // if (fifo == NULL || item == NULL)
    // {
    //     return (FIFO_PARAM_ERR);
    // }

    if (fifo_is_full(fifo))
    {
        return (FIFO_OVERFLOW_ERR);
    }

    CRITICAL_SECTION_BEGIN();

    memcpy((fifo->items + fifo->front), item, fifo->item_size);
    fifo->front += fifo->item_size;
    if (fifo->front >= fifo->capacity)
    {
        fifo->front = 0;
    }
    fifo->stored_bytes += fifo->item_size;

    CRITICAL_SECTION_END();

    return (FIFO_OK);
}


/***************************************************************************//**
 * \fn          int32_t fifo_detach(fifo_t fifo, void *item)
 * \brief       从FIFO分离数据
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \param[out]  item        指向被分离出来的元素指针
 * \return       0          - 操作成功
 *              -1          - 操作失败
 ******************************************************************************/
int32_t fifo_detach(fifo_t fifo, void *item)
{
    ASSERT(fifo != NULL && item != NULL);
    // if (fifo == NULL || item == NULL)
    // {
    //     return (FIFO_PARAM_ERR);
    // }

    if (fifo_is_empty(fifo))
    {
        return (FIFO_EMPTY_ERR);
    }

    CRITICAL_SECTION_BEGIN();

    memcpy(item, (fifo->items + fifo->rear), fifo->item_size);
    fifo->rear += fifo->item_size;
    if (fifo->rear >=  fifo->capacity)
    {
        fifo->rear = 0;
    }
    fifo->stored_bytes -= fifo->item_size;

    CRITICAL_SECTION_END();

    return (FIFO_OK);
}


/***************************************************************************//**
 * \fn          int32_t fifo_peek(fifo_t fifo, void *item)
 * \brief       查看FIFO当前读指针所指内容而不分离数据
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \param[out]  item        指向结果元素指针
 * \return       0          - 操作成功
 *              -1          - 操作失败
 ******************************************************************************/
int32_t fifo_peek(fifo_t fifo, void *item)
{
    ASSERT(fifo != NULL && item != NULL);
    // if (fifo == NULL || item == NULL)
    // {
    //     return (FIFO_PARAM_ERR);
    // }

    if (fifo_is_empty(fifo))
    {
        return (FIFO_EMPTY_ERR);
    }

    CRITICAL_SECTION_BEGIN();

    memcpy(item, (fifo->items + fifo->rear), fifo->item_size);

    CRITICAL_SECTION_END();

    return (FIFO_OK);
}


/***************************************************************************//**
 * \fn          int32_t fifo_get_count(fifo_t fifo)
 * \brief       获取FIFO当前所存储元素个数
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \return      操作成功，返回FIFO当前存储元素个数，-1 -- 操作失败
 ******************************************************************************/
int32_t fifo_get_count(fifo_t fifo)
{
    ASSERT(fifo != NULL);
    // if (fifo == NULL)
    // {
    //     return (FIFO_PARAM_ERR);
    // }
    // else
    {
        uint16_t cnt;

        CRITICAL_SECTION_BEGIN();
        cnt = fifo->stored_bytes / fifo->item_size;
        CRITICAL_SECTION_END();

        return (cnt);
    }
}


/***************************************************************************//**
 * \fn          bool fifo_is_full(fifo_t fifo)
 * \brief       查看FIFO是否已满
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \return      true        FIFO已满或出错
 *              false       FIFO未满
 ******************************************************************************/
bool fifo_is_full(fifo_t fifo)
{
    ASSERT(fifo != NULL);
    // if (fifo == NULL)
    // {
    //     return true;
    // }
    // else
    {
        bool ret_val;

        CRITICAL_SECTION_BEGIN();
        ret_val = (fifo->stored_bytes >= fifo->capacity) ? true : false;
        CRITICAL_SECTION_END();

        return ret_val;
    }
}


/***************************************************************************//**
 * \fn          bool fifo_is_half_full(fifo_t fifo)
 * \brief       查看FIFO是否半满
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \return      true        FIFO半满或出错
 *              false       FIFO未满
 ******************************************************************************/
bool fifo_is_half_full(fifo_t fifo)
{
    ASSERT(fifo != NULL);
    // if (fifo == NULL)
    // {
    //     return true;
    // }
    // else
    {
        bool ret_val;

        CRITICAL_SECTION_BEGIN();
        ret_val = (fifo->stored_bytes >= fifo->capacity / 2) ? true : false;
        CRITICAL_SECTION_END();

        return ret_val;
    }
}


/***************************************************************************//**
 * \fn          bool fifo_is_empty(fifo_t fifo)
 * \brief       查看FIFO是否已空
 * \param[in]   fifo        指向被操作FIFO数据结构指针
 * \return      true        FIFO空或出错
 *              false       FIFO非空
 ******************************************************************************/
bool fifo_is_empty(fifo_t fifo)
{
    ASSERT(fifo != NULL);
    // if (fifo == NULL)
    // {
    //     return true;
    // }
    // else
    {
        bool ret_val;

        CRITICAL_SECTION_BEGIN();
        ret_val = (fifo->stored_bytes == 0) ? true : false;
        CRITICAL_SECTION_END();

        return ret_val;
    }
}

/**************************************************** End of file: fifo.c *****/
