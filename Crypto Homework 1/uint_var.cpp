//
//  uint_var.cpp
//  Crypto Homework 1
//
//  Created by Johan Henkens on 4/14/13.
//  Copyright (c) 2013 Johan Henkens. All rights reserved.
//

#include "uint_var.h"

uint_var::uint_var(int64_t size){
    numLength=size;
    num = (uint64_t*) malloc(sizeof(uint64_t)*numLength);
    for (int64_t i = 0;i<numLength;i++){
        num[i]=0;
    }
}

uint_var uint_var::operator++(int){
    int64_t pos = numLength-1;
    bool overflow = false;
    
    if(num[pos] == UINT64_MAX){
        overflow = true;
    }
    
    num[pos]++;
    pos--;
    
    while(overflow && pos>=0){
        if(num[pos] != UINT64_MAX){
            overflow = false;
        }
        num[pos]++;
        pos--;
    }
    return *this;
}

uint_var uint_var::operator--(int){
    int64_t pos = numLength-1;
    bool underflow = false;
    
    if(num[pos] == 0){
        underflow = true;
    }
    
    num[pos]--;
    pos--;
    
    while(underflow && pos>=0){
        if(num[pos] != 0){
            underflow = false;
        }
        num[pos]--;
        pos--;
    }
    return *this;
}

bool uint_var::operator>(const uint64_t& other){
    if(num[numLength-1] > other){
        return true;
    } else{
        int64_t pos = numLength-2;
        while(pos>=0){
            if(num[pos]!=0){
                return true;
            }
            pos--;
        }
    }
    return false;
}

void uint_var::print(){
    int64_t pos = 0;
    printf("0x");
    while(pos<numLength){
        printf("%016llx",num[pos]);
        pos++;
    }
    printf("\n");
}