PCB
=======

# Terminology

- SMT: surface mount technology
- SMD: surface mount device
- PCB: printed circuit board

# Altium Designer PCB Design Rules

## Electrical: 电气规则

- Clearance: 安全间距规则
- Short Circuit: 短路规则
- UnRouted Net: 未布线网络规则
- UnConnected Pin: 未连线引脚规则

## Routing 布线规则

- Width: 走线宽度
- Routing Topology: 走线拓扑布局
- Routing Priority: 布线优先级
- Routing Layers: 布线板层线
- Routing Corners: 导线转角
- Routing Via Style: 布线过孔形式
- Fan out Control: 布线扇出控制
- Difference Pairs Routing: 差分对布线规则

## SMT 表面贴焊规则

- SMD to Corner: SMD焊盘与导线拐角处最小间距
- SMD to Plane: SMD焊盘与电源层过孔最小间距
- SMD Neck Down: SMD焊盘颈缩率

## Mask 阻焊层规则

- Solder Mask Expansion: 阻焊层收缩量
- Paste Mask Expansion: 助焊层收缩量

## Plane 电源层规则

- Power Plane Connect Style: 电源层连接类型
- Power Plane Clearance: 电源层安全间距
- Polygon Connect Style: 焊盘与覆铜连接类型

## TestPoint 测试点规则

- TestPoint Style: 测试点样式
- TestPoint Usage: 测试点使用规则

## Manufacturing 制造规则

- Minimum Anuular Ring: 焊盘铜环最小宽度规则，防止焊盘脱落
- Acute Angle: 锐角限制规则
- Hole Size: 孔径限制规则
- Layer Pairs: 配对层设置规则，设定所有钻孔电气符号（焊盘和过孔）的起始层和终止层
- Hole to Hole Clearance: 孔与孔安全间距
- Minimum Solder Mask Sliver: 最小焊膜宽度
- Silk Screen Over Component Pads: 丝印与焊盘间距
- Silk to Silk Clearance: 丝印间距
- Net Antennae: 网络天线

## High Speed 高频电路规则

- Parallel Segment: 平行铜模线段间距
- Length: 网络长度
- Matched Net Lengths: 网络长度匹配
- Daisy Chain Stub Length: 菊花状布线分支长度限制
- Vias Under SMD: SMD焊盘下过孔限制
- Maximum Via Count: 最大过孔数限制

## Placement 元件布置规则

- Room Definition: 元件集合定义
- Component Clearance: 元件间距
- Component Orientations: 元件方向
- Permitted Layers: 允许元件放置的板层
- Nets to Ignore: 网络忽略
- Height: 高度

## Signal Integrity 信号完整性规则

- Signal Stimulus: 信号激励
- Undershoot-Falling Edge: 负下冲超调量限制
- Undershoot-Rising Edge: 正下冲超调量限制
- Impedance: 阻抗
- Signal Top Value: 高电平信号规则
- Signal Base Value: 低电平信号规则
- Flight Time-Rising Edge: 上升飞行时间
- Flight Time-Falling Edge: 下降飞行时间
- Slope-Rising Edge: 上升沿时间
- Slope-Falling Edge: 下降沿时间
- Supply Nets: 电源网络规则

# Altium 画图流程

## 1. 建库

### 1.1 原理图库

1. 元件起名
2. 放置引脚——引脚功能名称
3. 指定封装——信息录入

### 1.2 PCB封装库

1. 元件起名
2. 放置引脚
3. 放置丝印
4. 放置3D外框

## 2. 画原理图

1. 放置元件
2. 连接元件
   1. 连线
   2. 网名
   3. 示意标识
3. 元件编号
4. 检查原理图正确性

## 3. 原理图到PCB，网表传递的内容

- 器件
  - 编号
  - 封装
- 网络
  - 网名
  - 包含引脚
- 模型和属性
  - 器件模型
  - 网络属性
  - 等等信息


## 4. 画电路图

1. 建立规则
   1. 依据加工厂设计能力
      1. 板厚，常用 0.8, 1.0, 1.2, 1.6, 2.0mm
      2. 走线宽度，常用 0.1mm
      3. 钻孔内径、外径，常用 0.2, 0.45mm
      4. 走线间距，常用 0.1mm
      5. 铜厚，信号线常用 1oz, 电源线常用 2oz
      6. 丝印字符，常用 0.8mm
   2. 依据个人的绘图习惯
2. 导入原理图关系——网表
3. 器件布局
4. 布线
   1. 连线
   2. 覆铜
5. PCB规则检查
