esp-idf notes
===============

# 1. dev env

## 1.1 install esp-idf under windows 10

1. visit https://dl.espressif.com/dl/esp-idf/
2. download the offline installer like `ESP-IDF v5.2.2 - Offline Installer Windows 10, 11 Size: 1.48GB`, recommend the `second latest` one 
3. install in a path whihout any non-ascii/space

## 1.2 vscode

### 1.2.1 install extentions

1. C/C++
2. ESP-IDF

### 1.2.2 configure ESP-IDF extention

`USE EXISTING SETUP`, choose the installed `ESP-IDF`

## 1.3 build example & vscode includePath settings

1. copy `frameworks/esp-idf-version/examples/get-started/hello_world` from `esp-idf` install path to anywhere else
2. open in vscode
3. on the bottom toolbar, choose `COM` port
4. set target
5. menuconfig
6. build/flash/monitor

## 1.4 vscode includePath settings

> [How to fix "include path " problems in VS code IDE?](https://esp32.com/viewtopic.php?t=18947)

after first successful build, there should be `build/compile_commands.json` appeared, thats what we need.

edit `.vscode/c_cpp_properties.json` like this:

```json
{
    "configurations": [
        {
            "name": "ESP32-S3",
            "includePath": [
                "${default}"
            ],
            "defines": [
            ],
            "cStandard": "c17",
            "cppStandard": "c++17",
            "compileCommands": "${workspaceFolder}/build/compile_commands.json"
        }
    ],
    "version": 4
}
```
