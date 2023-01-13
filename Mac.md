- [Mac Notes](#mac-notes)
  - [一、VMware 安装 macOS](#一vmware-安装-macos)
  - [二、VMware macOS 硬盘扩容](#二vmware-macos-硬盘扩容)
  - [三、制作可启动U盘](#三制作可启动u盘)
    - [0. 起因](#0-起因)
    - [1. 下载app格式的系统镜像](#1-下载app格式的系统镜像)
    - [2. 制作可启动的 dmg](#2-制作可启动的-dmg)
    - [3. 挂载 dmg](#3-挂载-dmg)
    - [4. 将 app 镜像写入 dmg](#4-将-app-镜像写入-dmg)
    - [5. 卸载 dmg](#5-卸载-dmg)
    - [6. 将 dmg 转为 cdr](#6-将-dmg-转为-cdr)
    - [7. cdr 重命名为 iso](#7-cdr-重命名为-iso)
    - [Refs](#refs)



# Mac Notes

## 一、VMware 安装 macOS

环境 `Win10 + VMware® Workstation 15 Pro, 15.1.0 build-13591040`

下载 `https://github.com/paolo-projects/unlocker`

由于要下载的 `com.vmware.fusion.zip.tar` 内 `darwin*.iso` 比库作者写的多了一层 `x86_x64`，因此修改 `gettools.py`:

```diff
diff --git a/gettools.py b/gettools.py
index 7ead41e..c647cc4 100755
--- a/gettools.py
+++ b/gettools.py
@@ -145,13 +145,13 @@ def main():

        print('Extracting files from com.vmware.fusion.zip...')
        cdszip = zipfile.ZipFile(convertpath(dest + '/tools/com.vmware.fusion.zip'), 'r')
-       cdszip.extract('payload/VMware Fusion.app/Contents/Library/isoimages/darwin.iso', path=convertpath(dest + '/tools/'))
-       cdszip.extract('payload/VMware Fusion.app/Contents/Library/isoimages/darwinPre15.iso', path=convertpath(dest + '/tools/'))
+       cdszip.extract('payload/VMware Fusion.app/Contents/Library/isoimages/x86_x64/darwin.iso', path=convertpath(dest + '/tools/'))
+       cdszip.extract('payload/VMware Fusion.app/Contents/Library/isoimages/x86_x64/darwinPre15.iso', path=convertpath(dest + '/tools/'))
        cdszip.close()

        # Move the iso and sig files to tools folder
-       shutil.move(convertpath(dest + '/tools/payload/VMware Fusion.app/Contents/Library/isoimages/darwin.iso'), convertpath(dest + '/tools/darwin.iso'))
-       shutil.move(convertpath(dest + '/tools/payload/VMware Fusion.app/Contents/Library/isoimages/darwinPre15.iso'), convertpath(dest + '/tools/darwinPre15.iso'))
+       shutil.move(convertpath(dest + '/tools/payload/VMware Fusion.app/Contents/Library/isoimages/x86_x64/darwin.iso'), convertpath(dest + '/tools/darwin.iso'))
s/Library/isoimages/x86_x64/darwinPre15.iso'), convertpath(dest + '/tools/darwinPre15.iso'))

        # Cleanup working files and folders
        shutil.rmtree(convertpath(dest + '/tools/payload'), True)
```

不想每次执行 `win-install.bat` 都下载，因为下载有点卡，可以先执行 `gettools.py` 再执行 `win-install.bat`，修改如下

```diff
diff --git a/win-install.cmd b/win-install.cmd
index 74f63d5..331747f 100644
--- a/win-install.cmd
+++ b/win-install.cmd
@@ -44,11 +44,11 @@ xcopy /F /Y "%InstallPath%vmwarebase.dll" .\backup\

 echo.
 echo Patching...
-python unlocker.py
+.\python\python.exe .\unlocker.py

 echo.
 echo Getting VMware Tools...
-python gettools.py
+rem python\python.exe gettools.py
 xcopy /F /Y .\tools\darwin*.* "%InstallPath%"

 echo.
@@ -61,3 +61,4 @@ net start vmware-view-usbd > NUL 2>&1
 popd
 echo.
 echo Finished!
+pause
```

然后就可以启动 `VMware` 安装 `MacOS` 了，我用的 `VMware` 版本 `15.1.0`，最高只识别 `Mac OS 10.14`，系统镜像可以到这里下载 

https://archive.org/details/mac-osx-mojave-iso

一路安装不提.


## 二、VMware macOS 硬盘扩容

参考 [VMware虚拟机Mac OS X如何调整扩展硬盘大小](https://blog.csdn.net/juzihongle1/article/details/73799888)

关机，调整硬盘，扩展一些容量，开机，执行

`diskutil list`

输出如下

```
jackdeMac:~ jack$ diskutil list
/dev/disk0 (internal, physical):
   #:                       TYPE NAME                    SIZE       IDENTIFIER
   0:      GUID_partition_scheme                        *128.8 GB   disk0
   1:                        EFI EFI                     209.7 MB   disk0s1
   2:                 Apple_APFS Container disk1         80.0 GB    disk0s2
```

`disk0s2` 就是要扩展的分区，可以看到硬盘总容量为 `128.8GB`，下面扩容时不可超过该容量. 执行

`sudo diskutil apfs resizeContainer disk0s2 120GB`

输出如下

```
jackdeMac:~ jack$ sudo diskutil apfs resizeContainer disk0s2 120GB
Started APFS operation
Aligning grow delta to 40,000,000,000 bytes and targeting a new physical store size of 120,000,000,000 bytes
Determined the maximum size for the targeted physical store of this APFS Container to be 128,638,234,624 bytes
Resizing APFS Container designated by APFS Container Reference disk1
The specific APFS Physical Store being resized is disk0s2
Verifying storage system
Using live mode
Performing fsck_apfs -n -x -l -S /dev/disk0s2
Checking the container superblock
Checking the EFI jumpstart record
Checking the space manager
Checking the space manager free queue trees
Checking the object map
Checking volume
Checking the APFS volume superblock
The volume machd was formatted by hfs_convert (945.275.7) and last modified by apfs_kext (945.275.7)
Checking the object map
Checking the snapshot metadata tree
Checking the snapshot metadata
Checking the extent ref tree
Checking the fsroot tree
Checking volume
Checking the APFS volume superblock
The volume Preboot was formatted by hfs_convert (945.275.7) and last modified by apfs_kext (945.275.7)
Checking the object map
Checking the snapshot metadata tree
Checking the snapshot metadata
Checking the extent ref tree
Checking the fsroot tree
Checking volume
Checking the APFS volume superblock
The volume Recovery was formatted by diskmanagementd (945.275.7) and last modified by apfs_kext (945.275.7)
Checking the object map
Checking the snapshot metadata tree
Checking the snapshot metadata
Checking the extent ref tree
Checking the fsroot tree
Checking volume
Checking the APFS volume superblock
The volume VM was formatted by apfs.util (945.275.7) and last modified by apfs_kext (945.275.7)
Checking the object map
Checking the snapshot metadata tree
Checking the snapshot metadata
Checking the extent ref tree
Checking the fsroot tree
Verifying allocated space
The volume /dev/disk0s2 appears to be OK
Storage system check exit code is 0
Growing APFS Physical Store disk0s2 from 80,000,000,000 to 120,000,000,000 bytes
Modifying partition map
Growing APFS data structures
Finished APFS operation
jackdeMac:~ jack$ 
```

## 三、制作可启动U盘

### 0. 起因

`macbook pro 2015 春` 终于挂了，`Wi-Fi` 打不开，试过各种方法无法解决，干脆重装系统试试.

### 1. 下载app格式的系统镜像

- macOS Ventura https://apps.apple.com/us/app/macos-ventura/id1638787999?mt=12

- macOS Monterey                            https://apps.apple.com/cn/app/macos-monterey/id1576738294?ls=1&mt=12

- macOS BigSur 11.6.1                    https://apps.apple.com/cn/app/macos-big-sur/id1526878132?ls=1&mt=12

- macOS Catalina 10.15.7               https://apps.apple.com/cn/app/macos-catalina/id1466841314?ls=1&mt=12

- macOS Mojave 10.14.6                https://apps.apple.com/cn/app/macos-mojave/id1398502828?ls=1&mt=12

- macOS High Sierra 10.13.6        https://apps.apple.com/cn/app/macos-high-sierra/id1246284741?ls=1&mt=12

- macOS Sierra 10.12.6                   https://apps.apple.com/cn/app/macos-sierra/id1127487414?ls=1&mt=12


找一个想要安装的系统版本，以 `Ventura` 为例，`Safari` 访问 `https://apps.apple.com/us/app/macos-ventura/id1638787999?mt=12`，自动跳转到 `App Store`，下载后取消安装.

在访达内前往 `应用程序`，找到下载的 `安装 macOS Ventura.app`，右键显示简介，查看文件大小为 `12.26GB`.

### 2. 制作可启动的 dmg

执行

`hdiutil create -o ~/Desktop/macOS\ Ventura -size 12.8GB -layout SPUD -fs HFS+J`

- `-o` 存放路径
- `-size` 要比 `app` 镜像大，预留约 `500MB` 的空间.
- `-layout SPUD` 镜像为单分区模式
- `-fs HFS+J` 分区格式为 `macOS Extended`

输出

`created: /Users/jack/Desktop/macOS Ventura.dmg`

### 3. 挂载 dmg

`hdiutil attach ~/Desktop/macOS\ Ventura.dmg -noverify -mountpoint /Volumes/macOS\ Ventura`

- `-noverify` 不验证
- `-mountpoint` 挂载路径

输出

```
jackdeMac:~ jack$ hdiutil attach ~/Desktop/macOS\ Ventura.dmg -noverify -mountpoint /Volumes/macOS\ Ventura
/dev/disk2          	Apple_partition_scheme         	
/dev/disk2s1        	Apple_partition_map            	
/dev/disk2s2        	Apple_HFS                      	/Volumes/macOS Ventura
jackdeMac:~ jack$ 
```

### 4. 将 app 镜像写入 dmg

执行

`sudo /Applications/Install\ macOS\ Ventura.app/Contents/Resources/createinstallmedia --volume /Volumes/macOS\ Ventura`

提示空间不足，差了 `660.8 MB`...

```
jackdeMac:~ jack$ sudo /Applications/Install\ macOS\ Ventura.app/Contents/Resources/createinstallmedia --volume /Volumes/macOS\ Ventura
Password:
/Volumes/macOS Ventura is not large enough for install media. An additional 660.8 MB is needed.
jackdeMac:~ jack$ 
```

重来一遍，先卸载 dmg

```
jackdeMac:~ jack$ hdiutil detach /Volumes/macOS\ Ventura/
"disk2" ejected.
jackdeMac:~ jack$ 
```

再删除 dmg

`rm -f ~/Desktop/macOS\ Ventura.dmg`

创建 dmg

```
jackdeMac:~ jack$ hdiutil create -o ~/Desktop/macOS\ Ventura -size 14GB -layout SPUD -fs HFS+J
created: /Users/jack/Desktop/macOS Ventura.dmg
jackdeMac:~ jack$ 
```

再次挂载

```
jackdeMac:~ jack$ hdiutil attach ~/Desktop/macOS\ Ventura.dmg -noverify -mountpoint /Volumes/macOS\ Ventura
/dev/disk2          	Apple_partition_scheme         	
/dev/disk2s1        	Apple_partition_map            	
/dev/disk2s2        	Apple_HFS                      	/Volumes/macOS Ventura
jackdeMac:~ jack$ 
```

再次写入

```
jackdeMac:~ jack$ sudo /Applications/Install\ macOS\ Ventura.app/Contents/Resources/createinstallmedia --volume /Volumes/macOS\ Ventura
Password:
Ready to start.
To continue we need to erase the volume at /Volumes/macOS Ventura.
If you wish to continue type (Y) then press return: y
Erasing disk: 0%... 10%... 20%... 30%... 100%
Making disk bootable...
Copying to disk: 0%... 10%... 20%... 30%... 40%... 50%... 60%... 70%... 80%... 90%... 100%
Install media now available at "/Volumes/Install macOS Ventura"
jackdeMac:~ jack$ 
```

### 5. 卸载 dmg

`hdiutil detach /Volumes/Install\ macOS\ Ventura/`

```
jackdeMac:~ jack$ hdiutil detach /Volumes/Install\ macOS\ Ventura/
"disk2" ejected.
jackdeMac:~ jack$ 
```

### 6. 将 dmg 转为 cdr

`hdiutil convert ~/Desktop/macOS\ Ventura.dmg -format UDTO -o ~/Desktop/macOS\ Ventura`

```
jackdeMac:~ jack$ ls -l ~/Desktop/
total 29360128
-rw-r--r--@ 1 jack  staff  15032385536  1 12 04:30 macOS Ventura.dmg
jackdeMac:~ jack$ hdiutil convert ~/Desktop/macOS\ Ventura.dmg -format UDTO -o ~/Desktop/macOS\ Ventura
正在读取Driver Descriptor Map（DDM：0）…
正在读取Apple（Apple_partition_map：1）…
正在读取（Apple_Free：2）…
正在读取disk image（Apple_HFS：3）…
............................................................................................
已耗时：10m 15.270s
速度：23.3M 字节/秒
节省：0.0%
created: /Users/jack/Desktop/macOS Ventura.cdr
jackdeMac:~ jack$ ls -l ~/Desktop/
total 58720256
-rw-r--r--  1 jack  staff  15032385536  1 12 04:42 macOS Ventura.cdr
-rw-r--r--@ 1 jack  staff  15032385536  1 12 04:30 macOS Ventura.dmg
jackdeMac:~ jack$ 
```

### 7. cdr 重命名为 iso

```
jackdeMac:~ jack$ mv ~/Desktop/macOS\ Ventura.cdr ~/Desktop/macOS\ Ventura.iso
jackdeMac:~ jack$ ls -l ~/Desktop/
total 58720256
-rw-r--r--@ 1 jack  staff  15032385536  1 12 04:30 macOS Ventura.dmg
-rw-r--r--  1 jack  staff  15032385536  1 12 04:42 macOS Ventura.iso
```

`cdr` 就是 `iso`，不需额外转换，只需重命名. 现在 `iso` 已经可以用来制作可引导U盘了.



### Refs

- [macOS原版系统下载及制作ISO可引导镜像，让你零成本也能体验最新苹果系统](https://www.youtube.com/watch?v=f0eq85u6gwA)
- [在苹果系统下制作macOS的U盘启动盘，安装系统不求人](https://www.youtube.com/watch?v=4q4yQDn5zLY)
- [在Windows下制作macOS的启动安装U盘，一键制作成功](https://www.youtube.com/watch?v=UCsqTWnyJSE)

