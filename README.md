# AI-Car-Jetson-Nano-with-ESP32
这是一次学校大作业，由于对AI与智能控制车感兴趣，且希望将个人的学习过程分享给大家，便有了这个小项目。项目不难，诚意满满，希望我们共同进步。

此项目分驱动部分，遥控部分，视觉部分以及Web控制部分。是基于ESP32与Jetson Nano做的一个小项目。其中运用到了蓝牙串口片与片之间的通信，IP私域下的多机通信，以及ESP32中便携的Web功能进行通信。具体各部分内容我会在具体文档里说明。
![2L$~~J N72AN%EB)EOA$3@Q](https://github.com/HerryDeng2004/AI_Car_JetsonNano-with-ESP32/assets/134835469/2fb7135b-31c9-4cfc-8e5d-6f5d4f3cecf5)



为了减小Git占用内存，我只把ESP32部分主要源码以main.cpp呈现。相关库我放在Lib中，方便获取与更改。

ESP32部分采用VScode+PlatformIO开发模式，有需求建议提前学习相关配置。

Jetson Nano部分可以参考JetsonYolov5和jetson-inference这两个文件，里面较为详细介绍一些基础的用法，这对于之后的加速部署起到基础作用。环境部署方面涉及例如pytorch，torchvision，pycuda，opencv等方面，这部分需要注意的细节非常多。

我将在之后把执行程序以及GUI界面上传上来，以便快速入手。

之后会更新硬件说明，硬件选型，功率适配，PCB等等部分的文件，以及个人做项目的想法和实现。于此同时还会出一些具体任务的实现，希望能够在论坛里讨论debug等等。

欢迎交流催更。qq:2949827172

-----------------------------------------------------------------------------------
最新设计方案更新
![image](https://github.com/HerryDeng2004/AI_Car_JetsonNano-with-ESP32/assets/134835469/757fbe5c-c9ea-48bc-b7c3-2e4f14681ad4)

-----------------------------------------------------------------------------------

前提：一律不回答基本常识，一律不回答软件安装问题。

赠人玫瑰，手有余香，麻烦留下你的star吧![91JZUPO@W6TY2DG~59@` 2Q](https://github.com/HerryDeng2004/AI_Car_JetsonNano-with-ESP32/assets/134835469/31404fd4-d867-4ab3-8c4b-8dadd66d654a)

