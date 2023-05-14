# MultiKnob Library

This library provides a multi-knob input solution for microcontroller projects.

---

## Compatibility

This library has not been tested.

---

## Installation

1. Download the MultiKnob.h and MultiKnob.c files.
2. Add both files to your project directory.
3. Include MultiKnob.h in the main application.

---

## Usage

1. Use knob_init() to create the knob object.
2. Use knob_event_attach() to attach the callback function to the knob event.
3. Use knob_start() to start monitoring the knob activity.
4. In the main loop of the program, call knob_ticks() to check the knob event and execute the attached callback function.

---

## Sample Code

```c

#include "MultiKnob.h"

void knob_turn_clockwise(knob_btn_t *handle)
{
// Handle clockwise knob events
}

void setup()
{
knob_btn_t knob1.
knob_init(&knob1, read_pin_level, A0, A1, HIGH, 1); // Change the desired function and pin value.
knob_evennt_attach(&knob1, TURN_CLOCKWISE, knob_turn_clockwise).
knob_start(&knob1).
}

void loop()
{
knob_ticks().
}
```

---

## API Reference

***knob_init()***


Initialize the knob object and its associated pins.

Parameters.

- handle: Pointer to the knob object to be initialized.
- get_pin_level: Pointer to a function that returns the current state of the given pin.
- aio_pin: The analog input pin corresponding to the AIO pin of the knob.
- bio_pin: Binary input and output pin corresponding to the BIO pin of the knob.
- active_level: integer indicating the active logic state level. High level is 1, low level is 0.
- knob_id: Integer indicating the knob ID of the user application.

***knob_evennt_attach()***


Attaches a callback function to a knob event.

Arguments.

- handle: A pointer to the knob object.
- event: The event of the knob to attach the callback function to.
- cb: the callback function to be executed when the event is triggered.

***knob_evennt_detach()***


Detach the callback function from the knob event.

Arguments.

- handle: Pointer to the knob object.
- event: The event of the knob from which to detach the callback function.

***knob_start()***


Add the knob object to the watch list and start monitoring.

Parameters.

- handle: A pointer to the knob to start monitoring.

Return value.

- If the object is being monitored, -1 is returned.

***knob_stop()***


Delete the knob from the watch list.

Arguments.

- handle: Pointer to the knob to be deleted.

***get_knob_event()***


Return the current knob event.

Arguments.

- handle: Pointer to the knob to check its event.

Return value.

- The current knob event.

***knob_ticks()***


checks the events of all monitored knobs and executes the callback function accordingly. Should be called repeatedly in the main loop.

## Copyright

``` txt
MIT License

Copyright (c) 2018 Zibin Zheng

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

```

## Reference/Quote

1. [Elegant de-jittering of rotary encoders (EC11,quadrature)](https://zhuanlan.zhihu.com/p/453130384). [liu-zi-gui](https://www.zhihu.com/people/liu-zi-gui)

2. [MultiButton)](https://github.com/0x1abin/MultiButton.git). [0x1abin](https://github.com/0x1abin)
