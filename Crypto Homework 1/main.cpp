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

//
//
//uint64_t* ModExp( uint_var& base, uint_var& exponent, uint_var& modulus, uint_var& result){
//    result = 1;
//    while (exponent > 0){
//        if ((exponent % 2) == 1){
//            result = (result * base) % modulus;
//        }
//        exponent >>= 1;
//        base = (base * base) mod modulus
//    return result
//            
//}

int main(int argc, const char * argv[])
{
    uint32_t arr[] = {0xFFFFFFFF,0xFFFFFFFF};
    uint_var a(2,arr);
    uint32_t arr2[] = {0,857};
    uint_var b(a);
    uint_var* result = &(a*b);
    a.print();
    result->print();
    a.print();
//    printf("%d\n",b>0);
    return 0;
}

