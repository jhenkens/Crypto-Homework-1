//
//  main.cpp
//  Crypto Homework 1
//
//  Created by Johan Henkens on 4/14/13.
//  Copyright (c) 2013 Johan Henkens. All rights reserved.
//

#include <iostream>
#include <stdint.h>
#include "uint_var.h"


/*
 * n is the modulous
 * e is the exponent
 * M is the base
 */
uint64_t* ModExp( uint64_t* M, uint64_t m_bits, uint64_t* n, uint64_t n_bits, uint64_t* e, uint64_t e_bits){
    
}

int main(int argc, const char * argv[])
{
    uint_var a(4);
    a.num[3]=0xFFFFFFFFFFFFFFFF;
    a.num[2]=0xFFFFFFFFFFFFFFFF;
    a.num[1]=0x0;
    a.num[0]=0x0;
    a.print();
    a++;
    a.print();
    a--;
    a.print();
    a--;
    a.print();
    uint_var b(4);
    
    printf("%d\n",b>0);
    return 0;
}

