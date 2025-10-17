STM32 notes
===========

## share memory between bootloader and application

1. Change bootloader/application's ld script, add a `SHARED_MEMORY` memory and a `.shared_mem` region:
   ```ld
   /* Specify the memory areas */
   MEMORY
   {
   RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 64K - 4
   SHARED_MEMORY (xrw) : ORIGIN = 0x2000FFFC, LENGTH = 4
   FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 64K
   }

   SECTIONS
   {
     ...

     .shared_mem :
     {
       . = ALIGN(4);
       __shared_mem_start__ = .;
       *(.shared_mem)
       *(.shared_mem*)
       __shared_mem_end__ = .;
     } > SHARED_MEMORY

     ...
   }
   ```

   I allocated a `4B` shared memory, you can change it to any size you want.
2. Declare variable at `.shared_mem` for bootloader/application:
   ```c
   __attribute__((section(".shared_mem"))) uint32_t my_shared_value;
   ```
3. Test it.
   At bootloader, change `my_shared_value` to any specific value, jump to application and print it, see if its the same value.

4. Refs:
   1. [LAT0816_STM32CubeIDE实用技巧之ld链接文件_v1.0.pdf](https://www.stmcu.com.cn/Designresource/detail/LAT/710398)
   2. [Sharing MCU memory region between bootloader and application](https://www.reddit.com/r/embedded/comments/f2yqr0/sharing_mcu_memory_region_between_bootloader_and/)

5. Problem:
   This method will create a hex80 record to init `my_shared_value` at `0x20001FFFC`:
   ```hex80
   :020000042000DA
   :01FFFC000004
   ```
   Which will generate a very big `bin` file(about 384MB)

6. Improve:
   ```ld      
   /* Specify the memory areas */
   MEMORY
   {
   RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 64K
   FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 64K
   }
   
   _shared_mem_size = 12; /* 12字节共享内存 */
   _shared_mem_addr = ORIGIN(RAM) + LENGTH(RAM) - _shared_mem_size; /* 放在RAM末尾 */
   
   /* Define output sections */
   SECTIONS
   {
      /* other sections */
      /* 共享内存 - 绝对地址 */
     .shared_mem _shared_mem_addr (NOLOAD) : {
       KEEP(*(.shared_mem))
     } > RAM
     
     /* 堆栈设置 */
     _estack = _shared_mem_addr - 4; /* 4字节缓冲 */
   
   }
   ```

   之所以要`12`字节，是由于上电冷启动时该区域指定了`NOLOAD` 不会被初始化，值是随机的，需要加一些措施来保证数据有效（如魔数、CRC校验等），这里给出我使用的结构和函数：
   
   ```c
   #define SYSTEM_CONTEXT_MAGIC 0x20502025

   typedef struct {
       uint32_t magic;
       union {
           uint32_t u;
           struct {
               uint8_t dfu : 1;                // whether to enter DFU mode (stay in bootloder and wait for host commands)
               uint8_t onchip_app_valid : 1;   // whether on-chip application is valid
               uint8_t onchip_meta_valid : 1;  // whether on-chip factory metadata is valid
               uint8_t appid : 2;              // current running application id, 0: factory, 1: app1, 2: app2
               uint8_t otaid : 1;              // current old ota info id (which is ready to overwrite), 0: master, 1: backup
               uint8_t resv : 2;               // reserved
   
               uint8_t resv2[3];  // reserved
           } st;
       } dat;
       uint32_t crc;  // crc of magic and dat
   } system_context_t;

   void init_system_context(void) {
       sysctx.magic = SYSTEM_CONTEXT_MAGIC;
       sysctx.dat.u = 0;
       sysctx.dat.st.dfu = 0;
       sysctx.dat.st.onchip_app_valid = 0;
       sysctx.dat.st.onchip_meta_valid = 0;
       sysctx.dat.st.appid = FLASH_APP_ID_FACTORY;
       sysctx.dat.st.otaid = FLASH_OTA_ID_MASTER;  // default to master
       sysctx.crc = hb_crc32((uint8_t *)&sysctx.magic, sizeof(sysctx.magic) + sizeof(sysctx.dat));
   }
   
   bool is_system_context_valid(void) {
       uint32_t crc;
       if (sysctx.magic != SYSTEM_CONTEXT_MAGIC) {
           return false;
       }
       crc = hb_crc32((uint8_t *)&sysctx.magic, sizeof(sysctx.magic) + sizeof(sysctx.dat));
       if (crc != sysctx.crc) {
           return false;
       }
       return true;
   }
   
   void save_system_context(void) {
       sysctx.magic = SYSTEM_CONTEXT_MAGIC;
       sysctx.crc = hb_crc32((uint8_t *)&sysctx.magic, sizeof(sysctx.magic) + sizeof(sysctx.dat));
   }
   ```

   这样在冷启动时由`bootloader`初始化并设置`sysctx`值，跳转到`app`后可以由`app`读写，如`app`收到上位机命令时设置`dfu=1`并软复位，使`bootloader` 不要自动跳转到`app`.