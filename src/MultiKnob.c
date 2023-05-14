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

#include "MultiKnob.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// knob handle list head.
static knob_btn_t *head_handle = NULL;

#define KNOB_EVENT_TURN_START (uint16_t)(1U << 0)
#define KNOB_EVENT_TURN_STOP (uint16_t)(1U << 1)
#define KNOB_EVENT_TURN_CLOCKWISE (uint16_t)(1U << 2)
#define KNOB_EVENT_TURN_CLOCKWISE_START (uint16_t)(1U << 3)
#define KNOB_EVENT_TURN_CLOCKWISE_STOP (uint16_t)(1U << 4)
#define KNOB_EVENT_TURN_COUNTERCLOCKWISE (uint16_t)(1U << 5)
#define KNOB_EVENT_TURN_COUNTERCLOCKWISE_START (uint16_t)(1U << 6)
#define KNOB_EVENT_TURN_COUNTERCLOCKWISE_STOP (uint16_t)(1U << 7)

typedef enum
{
    KNOB_TURN_FSM_IDLE,
    KNOB_TURN_FSM_CLOCKWISE,
    KNOB_TURN_FSM_COUNTERCLOCKWISE,
} knobTurnFSM_t;

void knob_pin_handler(knob_btn_t *handle)
{
    uint8_t aio_pin_val = handle->get_pin_level(handle->aio_pin); // 读取 AIO 引脚输入状态

    handle->state = KNOB_TURN_FSM_IDLE;

    if (!handle->is_trigger)
    {
        if (handle->aio_pin_val != aio_pin_val)
        {
            if (aio_pin_val == handle->active_level)
            {
                // 如果是上升沿则记录当前BIO引脚状态，并开始计时器
                handle->bio_pin_val = handle->get_pin_level(handle->bio_pin); // 读取 BIO 引脚输入状态
                handle->ticks = 0;
                handle->is_trigger = 1U;
            }
        }
    }
    else
    {
        if (handle->aio_pin_val != aio_pin_val)
        {
            if (aio_pin_val != handle->active_level)
            {
                printf("Knob%u:%d:%d\n", handle->id, handle->state, handle->event);
                uint8_t bio_pin_val = handle->get_pin_level(handle->bio_pin); // 读取 BIO 引脚输入状态
                handle->is_trigger = 0U;

                if (handle->bio_pin_val != bio_pin_val)
                {
                    if (bio_pin_val == handle->active_level)
                    {
                        handle->state = KNOB_TURN_FSM_CLOCKWISE;
                        handle->pos++;
                    }
                    else
                    {
                        handle->state = KNOB_TURN_FSM_COUNTERCLOCKWISE;
                        handle->pos--;
                    }
                }
            }
            else
            {
                // 如果是上升沿则重新记录当前BIO引脚状态，并开始计时器
                handle->bio_pin_val = handle->get_pin_level(handle->bio_pin); // 读取 BIO 引脚输入状态
                handle->ticks = 0;
            }
        }
        else
        {
            handle->ticks++;
        }
    }
    handle->aio_pin_val = aio_pin_val;
}

void knob_event_checker(knob_btn_t *handle)
{
    knobTurnFSM_t c_state = handle->state;
    knob_pin_handler(handle);
    knobTurnFSM_t n_state = handle->state;

    if (n_state != c_state)
    {
        if (c_state == KNOB_TURN_FSM_IDLE)
        {
            if (n_state == KNOB_TURN_FSM_CLOCKWISE)
            {
                handle->event = KNOB_EVENT_TURN_START | KNOB_EVENT_TURN_CLOCKWISE_START | KNOB_EVENT_TURN_CLOCKWISE;
            }
            else if (n_state == KNOB_TURN_FSM_COUNTERCLOCKWISE)
            {
                handle->event = KNOB_EVENT_TURN_START | KNOB_EVENT_TURN_COUNTERCLOCKWISE_START | KNOB_EVENT_TURN_COUNTERCLOCKWISE;
            }
        }
        else if (c_state == KNOB_TURN_FSM_CLOCKWISE)
        {
            if (n_state == KNOB_TURN_FSM_IDLE)
            {
                handle->event = KNOB_EVENT_TURN_STOP | KNOB_EVENT_TURN_CLOCKWISE_STOP;
            }
            else if (n_state == KNOB_TURN_FSM_COUNTERCLOCKWISE)
            {
                handle->event = KNOB_EVENT_TURN_CLOCKWISE_STOP | KNOB_EVENT_TURN_COUNTERCLOCKWISE_START | KNOB_EVENT_TURN_COUNTERCLOCKWISE;
            }
        }
        else if (c_state == KNOB_TURN_FSM_COUNTERCLOCKWISE)
        {
            if (n_state == KNOB_TURN_FSM_IDLE)
            {
                handle->event = KNOB_EVENT_TURN_STOP | KNOB_EVENT_TURN_COUNTERCLOCKWISE_STOP;
            }
            else if (n_state == KNOB_TURN_FSM_CLOCKWISE)
            {
                handle->event = KNOB_EVENT_TURN_COUNTERCLOCKWISE_STOP | KNOB_EVENT_TURN_CLOCKWISE_START | KNOB_EVENT_TURN_CLOCKWISE;
            }
        }
    }
    else
    {
        if (c_state == KNOB_TURN_FSM_IDLE)
        {
            handle->event = 0u;
        }
        else if (c_state == KNOB_TURN_FSM_CLOCKWISE)
        {
            handle->event = KNOB_EVENT_TURN_CLOCKWISE;
        }
        else if (c_state == KNOB_TURN_FSM_COUNTERCLOCKWISE)
        {
            handle->event = KNOB_EVENT_TURN_COUNTERCLOCKWISE;
        }
    }
}

void knob_event_handler(knob_btn_t *handle)
{
    for (size_t i = 0; i < KNOB_TURN_EVENT_NUMBER; i++)
    {
        if (handle->cb[i] && (handle->event & (1 << i)))
        {
            handle->cb[i]((knob_btn_t *)handle);
        }
    }
}

void knob_init(knob_btn_t *handle, uint8_t (*get_pin_level)(uint8_t), uint8_t aio_pin, uint8_t bio_pin, uint8_t active_level, uint8_t knob_id)
{
    memset(handle, 0, sizeof(knob_btn_t));
    handle->get_pin_level = get_pin_level; // function to read gpio
    handle->aio_pin = aio_pin;             // aio pin number for the knob.
    handle->bio_pin = bio_pin;             // bio pin number for the knob.
    handle->active_level = active_level;   // high or low for active high state.
    handle->id = knob_id;                  // knob id for user applecation
}

void knob_evennt_attach(knob_btn_t *handle, knobTurnEvent_t event, knobCallback cb)
{
    handle->cb[event] = cb;
}

void knob_evennt_detach(knob_btn_t *handle, knobTurnEvent_t event)
{
    handle->cb[event] = NULL;
}

knobTurnEvent_t get_knob_event(knob_btn_t *handle)
{
    return (knobTurnEvent_t)(handle->event);
}

int knob_start(knob_btn_t *handle)
{
    knob_btn_t *target = head_handle;
    while (target)
    {
        if (target == handle)
            return -1; // already exist.
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}

void knob_stop(knob_btn_t *handle)
{
    knob_btn_t **curr;
    for (curr = &head_handle; *curr;)
    {
        knob_btn_t *entry = *curr;
        if (entry == handle)
        {
            *curr = entry->next;
            //			free(entry);
            return; // glacier add 2021-8-18
        }
        else
            curr = &entry->next;
    }
}

void knob_ticks()
{
    knob_btn_t *target;
    for (target = head_handle; target; target = target->next)
    {
        knob_pin_handler(target);
        knob_event_checker(target);
        knob_event_handler(target);
    }
}
