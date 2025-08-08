vscode
======

## change c/cpp format style

settings -> C_Cpp: Clang_format_fallback Style:

```{ BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 0, AccessModifierOffset: -4}```

## 替换特定字符串后的换行符为空格​​（例如将XXX\n替换为XXX ）

1. ​​打开替换功能​​
   
   按快捷键 Ctrl+H（Windows/Linux）或 Cmd+H（Mac）打开替换面板。

2. ​​开启正则表达式模式​​
   
   点击替换面板右侧的 ​​.*​​ 图标（或按 Alt+R），确保启用正则表达式匹配。
​​
3. 输入查找内容​​

   在搜索框中输入正则表达式：

   ```regex
   (XXX)\r?\n
   ```
   - (XXX)：捕获组，匹配你的目标字符串（如XXX）。
   - \r?\n：匹配换行符（兼容Windows \r\n 和 Unix \n）。

4. ​​输入替换内容​​

   在替换框中输入：
   ```
   $1␣  // 注意：␣代表一个空格（实际输入时直接按空格键）
   ```
   - $1：引用第一个捕获组（即XXX），后面紧跟一个空格。
​​
5. 执行替换​​

   点击 ​​Replace All​​（全部替换）完成操作。

## 替换小写十六进制常量为大写

1. 单字节常量如 `0xfe -> 0xFE`
   
   查找：
   ```regex
   \b0x([a-fA-F0-9]{1})([a-f0-9]{1})\b
   ```
   替换为：
   ```regex
   0x\u$1\u$2
   ```

2. u16常量如 `0xabcd -> 0xABCD`

   查找：
   ```regex
   \b0x([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})\b
   ```
   替换为：
   ```
   0x\u$1\u$2\u$3\u$4
   ```

3. u32常量如 `0xabcdefef -> 0xABCDEFEF`

   查找：
   ```regex
   \b0x([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})([a-fA-F0-9]{1})\b
   ```
   替换为：
   ```
   0x\u$1\u$2\u$3\u$4\u$5\u$6\u$7\u$8
   ```

`\u`: VSCode的​​大写转换语法​

暂时没发现可以统一替换任意位数的方法.

## Windows资源管理器右键菜单突然没有 `Open with Code` 了

重装也不好使，只能手动修改注册表了

```reg
Windows Registry Editor Version 5.00

; Open files
[HKEY_CLASSES_ROOT\*\shell\Open with VS Code]
@="Edit with Code"
"Icon"="C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe,0"

[HKEY_CLASSES_ROOT\*\shell\Open with VS Code\command]
@="\"C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\" \"%1\""

; This will make it appear when you right click ON a folder
; The "Icon" line can be removed if you don't want the icon to appear

[HKEY_CLASSES_ROOT\Directory\shell\vscode]
@="Open with Code"
"Icon"="\"C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\",0"

[HKEY_CLASSES_ROOT\Directory\shell\vscode\command]
@="\"C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\" \"%1\""


; This will make it appear when you right click INSIDE a folder
; The "Icon" line can be removed if you don't want the icon to appear

[HKEY_CLASSES_ROOT\Directory\Background\shell\vscode]
@="Open with Code"
"Icon"="\"C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\",0"

[HKEY_CLASSES_ROOT\Directory\Background\shell\vscode\command]
@="\"C:\\Users\\jack\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe\" \"%V\""
```

参考：

- [Visual Studio Code "Open With Code" does not appear after right-clicking a folder](https://stackoverflow.com/questions/37306672/visual-studio-code-open-with-code-does-not-appear-after-right-clicking-a-folde)
- [Right click on Windows folder and open with Visual Studio Code](https://thisdavej.com/right-click-on-windows-folder-and-open-with-visual-studio-code/)

