# AI-Car-Jetson-Nano-with-ESP32
这是一次学校大作业，由于对AI与智能控制车感兴趣，且希望将个人的学习过程分享给大家，便有了这个小项目。项目不难，诚意满满，希望我们共同进步。

此项目分驱动部分，遥控部分，视觉部分以及Web控制部分。是基于ESP32与Jetson Nano做的一个小项目。其中运用到了蓝牙串口片与片之间的通信，IP私域下的多机通信，以及ESP32中便携的Web功能进行通信。具体各部分内容我会在具体文档里说明。

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

车辆样图

![image](https://github.com/user-attachments/assets/bcb20e37-c1fc-4e12-ade2-6bec9a9b4578)

网页样图

![image](https://github.com/user-attachments/assets/7483aa4d-453c-4afb-a656-7fe4c5830302)

GPS定位图

![image](https://github.com/user-attachments/assets/24f5d9ec-6b34-4734-a075-bc1b9413106c)

用户端网页监视（RTP方案）

![image](https://github.com/user-attachments/assets/1d34b202-600f-42ca-8744-67dde6d11007)

边缘端流程图

![image](https://github.com/user-attachments/assets/2b78f7aa-89f0-4711-801b-39ab5c1a4979)

