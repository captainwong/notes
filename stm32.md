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

