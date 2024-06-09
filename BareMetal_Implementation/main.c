#include<stdio.h>
#include<stdint.h>

#include "led.h"


// if global var initialized with 0 or NULL then it goes to .bss not .data

//init var will be included in .data
uint8_t x = 7; 

// const var will be included in .rodata
const uint32_t const_v1 = 100;
const uint32_t const_v2 = 200;
const uint8_t const_v3 = 50;

// if global var initialized with 0 or NULL then it goes to .bss not .data
//uninit var will be included in .bss
int a = 0;

typedef struct
{
    uint8_t rollno;
    uint8_t age;
    uint8_t class;
}Student;

Student studarr[8];


int main()
{

    int var = 9;
    printf("Hello World!\n");

    func();

    var = 10;

    return 0;
}