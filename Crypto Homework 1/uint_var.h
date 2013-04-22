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
#include <cstring>
#include <cstdint>

#endif /* defined(__Crypto_Homework_1__uint_var__) */


/*
 All operations assume uint_var arguments are of the same size. Assertions are not made 
    in order to save a few cycles.
 */
struct uint_var
{

    uint32_t* num;
    int64_t numLength;
    bool underflow;
    bool overflow;
    
    uint_var(const int64_t size);
    uint_var(const int64_t size, const uint32_t* const data);
    uint_var(const uint_var& other);
    uint_var& operator+=(const uint_var& other);
    uint_var& operator+=(const uint32_t& other);
    uint_var& operator-=(const uint_var& other);
    bool operator[](uint32_t pos);
//    uint_var& operator-=(const uint32_t& other);
    uint_var& operator*(const uint_var& other);
//    uint_var& operator*(const uint32_t& other);
    uint_var& operator%(const uint_var& other);
//    uint_var& operator%(const uint32_t& other);
    
    
//    uint_var& operator++(int);
//    uint_var& operator--(int);
    uint_var& operator>>=(const uint32_t& other);
    uint_var& operator<<=(const uint32_t& other);
    uint_var& modMult(const uint_var& mult,const uint_var& mod);
//    uint_var& modAdd(const uint_var& add,const uint_var& mod);
//    uint_var& modSub(const uint_var& sub,const uint_var& mod);
    uint_var& modExp(const uint_var& exp,const uint_var& mod);
    uint_var& modExp(const uint32_t& exp,const uint_var& mod, uint32_t startPos = 0);
    
    bool operator>(const uint32_t& other);
    bool operator<(const uint_var& other);
    bool operator==(const uint_var& other);
    bool notZero();
    
    uint_var& operator=(const uint32_t& other);
    uint_var& operator=(const uint_var& other);
    
    void  print() const;
    ~uint_var();

private:
    static uint_var helper;
};