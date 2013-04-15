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



uint64_t* ModExp( uint_var& base, uint_var& exponent, uint_var& modulus, uint_var& result){
    result = 1;
    while (exponent > 0){
        if ((exponent % 2) == 1){
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) mod modulus
    return result
            
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
    b.num[3]=0x1000000000000001;
    b.num[2]=0x0100000000000001;
    b.print();
    b>>=4;
    b.print();
    
    printf("%d\n",b>0);
    return 0;
}

