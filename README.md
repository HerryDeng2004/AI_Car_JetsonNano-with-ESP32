# AI-Car-Jetson-Nano-with-ESP32
这是一次学校微机原理大作业，由于对AI与智能控制车感兴趣，且希望将个人的学习过程分享给大家，便有了这个小项目。项目不难，诚意满满，希望我们共同进步。

此项目分驱动部分，遥控部分，视觉部分以及Web控制部分。是基于ESP32与Jetson Nano做的一个小项目。其中运用到了蓝牙串口片与片之间的通信，IP私人域下的多机通信，以及ESP32中便携的Web功能进行通信。具体各部分内容我会在具体文档里说明。
![I 12SVH@U`)BH%7@ }}`@WT](https://github.com/HerryDeng2004/Smart-AI-Car-Jetson-Nano-with-ESP32-/assets/134835469/3215ea22-36e8-4adc-b3be-f7703552720d)


为了减小Git占用内存，我只把ESP32部分主要源码以main.cpp呈现。相关库我放在Lib中，方便获取与更改。

ESP32部分采用VScode+PlatformIO开发模式，有需求建议提前学习相关配置。

目前暂时只更新到驱动部分及遥控部分
