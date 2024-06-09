ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text)
        *(.text.*)
        *(.init)
        *(.fini)
        *(.rodata)

        /*
        For any assignment ; will be used.
        new address of the location counter will be updated with word boundary
        using ALIGN(4) command and then it will be stored to _etext
        */
        . = ALIGN(4);
        /*
        Location Counter only tracks VMA not LMA. 
        It will contain updated addresses for .text section
        */
        _etext = .; 
    }> FLASH

    /*this will give laod address of the data section. and have to modify satrtup.c accordingly*/

    _la_data = LOADADDR(.data); 
    
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH  /*>VMA AT> LMA*/

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        *(.COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
        __end__ = .;
    }> SRAM
}