# MultiKnob库

本库提供了一个用于微控制器项目的多旋钮输入解决方案。

---

## 兼容性

该库尚未经过测试。

---

## 安装

1. 下载MultiKnob.h和MultiKnob.c文件。
2. 将两个文件添加到您的项目目录中。
3. 在主程序中包含MultiKnob.h。

---

## 使用方法

1. 使用knob_init()创建旋钮对象。
2. 使用knob_event_attach()将回调函数附加到旋钮事件上。
3. 使用knob_start()开始监视旋钮活动。
4. 在程序的主循环中，调用knob_ticks()以检查旋钮事件并执行附加的回调函数。

---

## 示例代码

```c

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
```

---

## API参考

***knob_init()***


初始化旋钮对象及其相关引脚。

参数:

- handle: 指向要初始化的旋钮对象的指针。
- get_pin_level: 指向返回给定引脚当前状态的函数指针。
- aio_pin: 对应于旋钮的AIO引脚的模拟输入引脚。
- bio_pin: 对应于旋钮的BIO引脚的二进制输入输出引脚。
- active_level: 表示活动逻辑状态电平的整数。高电平为1，低电平为0。
- knob_id: 表示用户应用程序的旋钮ID的整数。

***knob_evennt_attach()***


将回调函数附加到旋钮事件上。

参数:

- handle: 指向旋钮对象的指针。
- event: 要将回调函数附加到的旋钮事件。
- cb: 触发事件时要执行的回调函数。

***knob_evennt_detach()***


从旋钮事件中分离回调函数。

参数:

- handle: 指向旋钮对象的指针。
- event: 要从其中分离回调函数的旋钮事件。

***knob_start()***


将旋钮对象添加到监视列表并开始监视。

参数:

- handle: 指向要开始监视的旋钮对象的指针。

返回值:

- 如果对象正在监视，则返回-1。

***knob_stop()***


从监视列表中删除旋钮对象。

参数:

- handle: 指向要删除的旋钮对象的指针。

***get_knob_event()***


返回当前的旋钮事件。

参数:

- handle: 指向要检查其事件的旋钮对象的指针。

返回值:

- 当前的旋钮事件。

***knob_ticks()***
检查所有受监视的旋钮的事件并相应地执行回调函数。应重复在主循环中调用。

## 版权

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

## 参考/引用

1. [优雅的对旋转编码器消抖（EC11,正交)](https://zhuanlan.zhihu.com/p/453130384).[liu-zi-gui](https://www.zhihu.com/people/liu-zi-gui)

2. [MultiButton)](https://github.com/0x1abin/MultiButton.git).[0x1abin](https://github.com/0x1abin)
