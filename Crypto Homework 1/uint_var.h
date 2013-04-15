//
//  uint_var.h
//  Crypto Homework 1
//
//  Created by Johan Henkens on 4/14/13.
//  Copyright (c) 2013 Johan Henkens. All rights reserved.
//

#ifndef __Crypto_Homework_1__uint_var__
#define __Crypto_Homework_1__uint_var__

#include <iostream>
#include <stdint.h>

#endif /* defined(__Crypto_Homework_1__uint_var__) */

struct uint_var
{

    uint64_t* num;
    int64_t numLength;
    
    uint_var(int64_t size);

    uint_var operator+(const uint_var& other);
    uint_var operator-(const uint_var& other);
    uint_var operator++(int);
    uint_var operator--(int);
    uint_var operator>>=(const uint64_t& other);
    uint_var operator*=(const uint_var& other);
    uint_var operator%=(const uint_var& other);
    uint_var modMult(const uint_var& mult,const uint_var& mod);
    uint_var modAdd(const uint_var& add,const uint_var& mod);
    uint_var modSub(const uint_var& sub,const uint_var& mod);

    
//    bool operator<(const uint_var& other);
//    bool operator<(const uint64_t& other);
    bool operator>(const uint64_t& other);
    
    void operator=(const uint64_t& other);
    uint64_t operator%(const uint64_t& other);
    
    void print();

private:
    static uint_var helper;
};