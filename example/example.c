#include "../src/MultiKnob.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
uint8_t read_knob_GPIO(uint8_t knob_id)
{
    srand(time(0));
    return rand() % 2;
}

void knob_event_listener(void *handle)
{
    knob_btn_t *knob = (knob_btn_t *)handle;
    printf("Knob%u:%d:%d\n", knob->id, knob->state, knob->event);
}

int main()
{
    static uint8_t btn1_event_val;
    knob_btn_t btn1;

    knob_init(&btn1, read_knob_GPIO, 0U, 1U, GPIO_HIGH, 1);
    knob_evennt_attach(&btn1, TURN_CLOCKWISE, knob_event_listener);
    knob_start(&btn1);
    while (1)
    {
        knob_ticks();
        Sleep(1);
        btn1_event_val = get_knob_event(&btn1);
    }
}
