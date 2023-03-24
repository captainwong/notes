# 迪文 T5L 系列芯片开发笔记

## 一、开发方式

参见 [熊家余--T5L迪文屏C51开发教程--环境搭建](https://www.yuanzige.com/course/detail/80041?section_id=81072).

### 1.1 `TA` 指令集开发

根据芯片指令集开发，复杂.

### 1.2 `DGUS` 开发

以下两种开发方式互斥.

#### 1.2.1 `DWIN OS` 开发

基于迪文提供的虚拟机（内核固件 `T5L_OS*.bin`）开发，可以用 `C` 语言或汇编开发，用 `C` 语言开发时要用迪文提供的 `DWIN C Compiler` 编译，用汇编语言开发时要用迪文提供的 `OSBuild` 编译.

复杂.

#### 1.2.2 `C51` 开发

即传统的 `C51` 单片机开发方式，`C` 语言编写，`Keil` 编译，使用迪文的 `DownLoadFor8051.exe` 烧写，直接替代迪文原厂 `T5S_OS*.bin`.

新手友好.

## 二、`C51` 开发环境搭建

- `Keil`
- [C51V961.EXE](https://armkeil.blob.core.windows.net/eval/C51V961.EXE) 
- `stc-isp-v6.91L.exe`

`keil` 报 `RESTRICTED VERSION WITH 0800H BYTE CODE SIZE LIMIT` 错误，重新跑 `keygen.exe`，选择 `Prof. Developers Kit (Plus)` 生成个新的 `LIC`.

## 三、Keil C 编程注意事项

### 3.1 `callback` 函数如果带参数，一般要定义为 `reentrant`

```c
// in a mudule like cb.h
typedef void(*callback_t)(const char*);
void register_callback(callback_t cb);
void callback_handle();

// in a module c file like cb.c
static callback_t the_cb = NULL;
void register_callback(callback_t cb){
    the_cb = cb;
}

void callback_handle()
{
    // do inner jobs, check if need call callback
    if(the_cb)
        the_cb("some string");
}

// in main.c
void my_callback(const char* str) reentrant
{
    // do something
    printf("%s\n", str);
}

int main()
{
    register_callback(my_callback);

    while(1){
        callback_handle();
    }
}
```

如果不加 `reentrant`，会出现莫名其妙的错误，例如变量被改写，缓冲区越界等.