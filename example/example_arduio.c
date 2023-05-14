
#include "MultiKnob.h"

void knob_turn_clockwise(knob_btn_t *handle)
{
    // 处理顺时针旋转旋钮事件
}

void setup()
{
    knob_btn_t knob1;
    knob_init(&knob1, read_pin_level, A0, A1, HIGH, 1); // 更改所需的函数和引脚值。
    knob_evennt_attach(&knob1, TURN_CLOCKWISE, knob_turn_clockwise);
    knob_start(&knob1);
}

void loop()
{
    knob_ticks();
}