MCS-51 ASM notes
============

## 极简51单片机体系结构、程序设计与案例开发（汇编语言版）笔记

向军 清华大学出版社

### P50 (2)

BCD转ASCII的题目

```asm
ORG 0000H
AJMP MAIN

MAIN:
MOV 60H, #56H
MOV A, 60H
_________________ 
_________________ ; 求十位数的ASCII码
MOV 61H, A        ; 存结果
MOV A, 60H
_________________ 
_________________
_________________ ; 求个位数ASCII码
MOV 62H, A
END
```

答案应为

```asm
ORG 0000H
AJMP MAIN

MAIN:
MOV 60H, #56H
MOV A, 60H
ANL A, #0FH       
ORL A, #30H       ; 求个位数的ASCII码
MOV 61H, A        ; 存结果
MOV A, 60H
SWAP A 
ANL A, #0FH
ORL A, #30H       ; 求十位数ASCII码
MOV 62H, A
END
```

明显是题目的个位和十位写反了.

### P84 3-7 (1)

51单片机时钟频率6MHz，12T, 1000存入R6, R7(R6=0E8H, R7=3H), 执行循环需要多少时间

(1)

```ASM
NEXT:        ; 机器周期 ;
CLR C        ; 1        ; 清进位标志
MOV A, R6    ; 1        ; 先算低8位
SUBB A, #1   ; 1        ; 带进位的减法
MOV R6, A    ; 1        ; 存回
MOV A, R7    ; 1        ; 再算高8位
SUBB A, #0   ; 1        ; 带进位的减法，这样来算u16
MOV R7, A    ; 1        ; 存回
ORL A, R6    ; 1        ; 相当于高低位相或，不同时为0则继续循环
JNZ NEXT     ; 2        ; 检查A，非零继续NEXT，否则结束
```

单片机12T，6MHz，则每机器周期需要 

$$
1s\div{6MHz} \times 12 = 2\mu s
$$

上述单次循环总机器周期数为 10, 则执行1000次循环需要的时间应为 $1000 \times 10 \times 2\mu s = 20ms$ 


但答案中`SUBB, A, #immediate` 需要2个机器周期，而我查阅 `KEIL C51 Development Tools` (我的路径在`D:\mdk\C51\Hlp\c51tools.chm`)，`SUBB, A, #immediate` 仅需1机器周期，以`KEIL` 为准.

(2)

```ASM
LP:
MOV A, R7
DEC R7
MOV R2, 0x06
JNZ CON
DEC R6
CON:
ORL A, R2
JZ DONE
SJMP LP
DONE:
```

逻辑不通，`DEC R7`到0时会下溢到FF，所以上述循环远不止1000次.
