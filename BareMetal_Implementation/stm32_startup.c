#include<stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128*1024)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;

// Prototype of main
int main(void);

// prototype of __libc_init_array();
void __libc_init_array(void);



void Reset_Handler(void);

void NMI_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));

/*

Now we have to inform the compiler to not put this  vector table to .data section
and include it vector table section. we have use __attribute__ ((section("SECTION_NAME")))

*/

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_Handler // funtion pointer so need to be typecasted to uint32
};

/*

or 

uint32_t vectors[] = {
    STACK_START,
    (uint32_t)&Reset_Handler // funtion pointer so need to be typecasted to uint32
};__attribute__((section(".isr_vector")))

*/


void Reset_Handler(void)
{

    /*
    1. copy .data section to SRAM

    2. Init .bss section to zero in SRAM

    3. call init functions of std library

    4. call main()

    These 4 things to be implemented in Reset Handler and for copying and init it is
    necessary to know the boundaries of each section = _etext, _sdata, _edata.
    For that we need linker script
    */

    /*1. copy .data section to SRAM*/

    // size of the section
    uint32_t size = (&_edata - &_sdata);

    // src and dst pointer for copying
    uint8_t *pDst = (uint8_t*)&_sdata; // SRAM
    uint8_t *pSrc = (uint8_t*)&_etext; // FLASH

    // start copying from FLASH to SRAM
    for(uint32_t i = 0; i<size; i++)
    {
        *pDst++ = *pSrc++;
    }


    /*2. Init .bss section to zero in SRAM*/
    size = &_ebss - &_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0;i<size;i++)
    {
        *pDst++ = 0;
    }

    /*3.call init functions of std library*/

    __libc_init_array(); // add prototype also

    /*3. call main()*/

    main();
    
}

void Default_Handler(void)
{
    while(1);
}