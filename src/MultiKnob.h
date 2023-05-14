/*
Copyright (c) 2016 Zibin Zheng znbin@qq.com
All rights reserved.
*/

/*
Copyright (c) 2023 john_tito zyb_china@outlook.com
All rights reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _MULTI_KNOB_H_
#define _MULTI_KNOB_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Macros */
/* Define macros here */

#ifndef GPIO_LOW
#define GPIO_LOW (0U)
#endif

#ifndef GPIO_HIGH
#define GPIO_HIGH (1U)
#endif

#ifndef GPIO_INPUT
#define GPIO_INPUT (0U)
#endif

#ifndef GPIO_OUTPUT
#define GPIO_OUTPUT (1U)
#endif

typedef enum knobTurnEvent_t
{
    TURN_START = 0,
    TURN_STOP,

    TURN_CLOCKWISE,
    TURN_CLOCKWISE_START,
    TURN_CLOCKWISE_STOP,

    TURN_COUNTERCLOCKWISE,
    TURN_COUNTERCLOCKWISE_START,
    TURN_COUNTERCLOCKWISE_STOP,

    KNOB_TURN_EVENT_NUMBER,
    TURN_NONE,
} knobTurnEvent_t;

typedef void (*knobCallback)(void *);

/* Structures */
/* Define structures here */
typedef struct knob_btn_t
{
    uint8_t id;           // 按钮 ID，标识不同功能的按钮
    uint8_t aio_pin;      // AIO 引脚编号
    uint8_t bio_pin;      // BIO 引脚编号
    uint8_t active_level; // 是否是高电平有效

    uint16_t ticks;
    uint16_t pos;
    uint16_t event;

    uint8_t is_trigger;      // 是否已经被触发
    uint8_t bio_init_state;  // 旋钮初始状态，用于记录旋钮转动方向
    uint8_t bio_final_state; // 旋钮终止状态，用于记录旋钮转动方向
    uint8_t aio_pin_val;     // AIO 引脚输入状态
    uint8_t bio_pin_val;     // BIO 引脚输入状态

    uint8_t state;
    uint8_t (*get_pin_level)(uint8_t id);
    knobCallback cb[KNOB_TURN_EVENT_NUMBER];
    struct knob_btn_t *next;
} knob_btn_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /* Function declarations */
    /* Declare functions here */
    extern void knob_init(knob_btn_t *handle, uint8_t (*get_pin_level)(uint8_t), uint8_t aio_pin, uint8_t bio_pin, uint8_t active_level, uint8_t knob_id);
    extern void knob_evennt_attach(knob_btn_t *handle, knobTurnEvent_t event, knobCallback cb);
    extern void knob_evennt_detach(knob_btn_t *handle, knobTurnEvent_t event);
    extern knobTurnEvent_t get_knob_event(knob_btn_t *handle);
    extern int knob_start(knob_btn_t *handle);
    extern void knob_stop(knob_btn_t *handle);
    extern void knob_ticks(void);

#ifdef __cplusplus
}
#endif

#endif /* defined(_MULTI_KNOB_H_) */