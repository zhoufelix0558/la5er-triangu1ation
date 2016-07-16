##项目内容
Felix   2016年7月16日

光斑定位算法主要包括定位算法和后处理的卡尔曼滤波算法。

location定位算法的流程：
1. 快步模糊寻找函数		point_nclear()
2. 寻找左右边缘函数		bi_side_search()
3. 自调节质心函数			zhixin()

kalman滤波算法


注：test.c是测试location函数专用的c语言函数
- 在dsp板子上不支持double和int的类型，在移植平台的时候要将其改成float和uint32_t类型
- 其中uint32_t类型在<stdint.h>里面定义。
