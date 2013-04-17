//
//  uint_var.cpp
//  Crypto Homework 1
//
//  Created by Johan Henkens on 4/14/13.
//  Copyright (c) 2013 Johan Henkens. All rights reserved.
//

#include "uint_var.h"

uint_var uint_var::helper(33);


uint_var::uint_var(const int64_t size){
    numLength=size;
    num = new uint32_t[numLength];
    for (int64_t i = 0;i<numLength;i++){
        num[i]=0;
    }
}

uint_var::uint_var(const int64_t size, const uint32_t* const data){
    numLength=size;
    num = new uint32_t[numLength];
    memcpy(num,data,numLength*sizeof(uint32_t));
}


uint_var::uint_var(const uint_var& other){
    numLength = other.numLength;
    num = new uint32_t[numLength];
    memcpy(num,other.num,numLength*sizeof(uint32_t));
}

uint_var& uint_var::operator+=(const uint_var& other){
    int64_t pos = numLength-1;
    bool overflow=false;
    while(pos>=0){
        if(overflow){
            if(num[pos] != UINT32_MAX){
                overflow = false;
            }
            num[pos]++;
        }
        if(num[pos] > UINT32_MAX-other.num[pos]){
            overflow = true;
        }
        num[pos]+=other.num[pos];
        pos--;
    }
    return *this;
}

uint_var& uint_var::operator+=(const uint32_t& other){
    int64_t pos = numLength-1;
    bool overflow = false;
    
    if(num[pos] > UINT32_MAX-other){
        overflow = true;
    }
    
    num[pos]+=other;
    pos--;
    
    while(overflow && pos>=0){
        if(num[pos] != UINT32_MAX){
            overflow = false;
        }
        num[pos]++;
        pos--;
    }
    return *this;
}

uint_var& uint_var::operator-=(const uint_var& other){
    int64_t pos = numLength-1;
    bool underflow=false;
    while(pos>=0){
        if(underflow){
            if(num[pos] != 0){
                underflow = false;
            }
            num[pos]--;
        }
        if(num[pos] < other.num[pos]){
            underflow = true;
        }
        num[pos]-=other.num[pos];
        pos--;
    }
    return *this;
}

uint_var& uint_var::operator-=(const uint32_t& other){
    int64_t pos = numLength-1;
    bool underflow = false;
    
    if(num[pos] < other){
        underflow = true;
    }
    
    num[pos]-=other;
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

uint_var& uint_var::operator*(const uint_var &other){
    uint_var* result = new uint_var(numLength+other.numLength);

    for(int64_t i = other.numLength-1; i>=0; i--){
        uint32_t carry = 0;
        for( int64_t j = numLength-1; j>=0; j--){
            uint64_t temp = num[j];
            temp *= other.num[i];
            temp = (temp + carry) + (*result).num[1+j+i];
            (*result).num[1+j+i] = temp&0xFFFFFFFF;
            carry = (temp&0xFFFFFFFF00000000)>>32;
        }
        (*result).num[i]=carry;
    }
    return *result;
}

uint_var& uint_var::operator*(const uint32_t& other){
    uint_var temp(1);
    temp.num[0]=other;
    return (*this)*temp;
}

uint_var& uint_var::operator++(int){
    int64_t pos = numLength-1;
    bool overflow = false;
    
    if(num[pos] == UINT32_MAX){
        overflow = true;
    }
    
    num[pos]++;
    pos--;
    
    while(overflow && pos>=0){
        if(num[pos] != UINT32_MAX){
            overflow = false;
        }
        num[pos]++;
        pos--;
    }
    return *this;
}

uint_var& uint_var::operator--(int){
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

uint_var& uint_var::operator>>=(const uint32_t& other){
    uint32_t mask = (1<<other)-1;
    uint32_t negativeShift = sizeof(uint32_t)*8-other;
    
    int64_t pos = numLength-1;
    
    num[pos]>>=other;
    pos--;
    while(pos>=0){
        num[pos+1]|=(num[pos]&mask)<<negativeShift;
        num[pos]>>=other;
        pos--;
    }
    return *this;
}

bool uint_var::operator>(const uint32_t& other){
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

//uint_var& uint_var::modMult(const uint_var& mult,const uint_var& mod){
//    uint_var* result = new uint_var();
//    int64_t pos = numLength-1;
//    while(numLength>=0){
//        *result = (*result)*2 + (*this)*
//    }
//    *result =
//}
//
////This num, and add should all be of the length mod or smaller
//uint_var uint_var::modAdd(const uint_var& add,const uint_var& mod){
//    uint32_t temp[mod.numLength+1];
//    
//    helper
//}


uint_var& uint_var::operator=(const uint32_t& other){
    for (int64_t i = 0;i<numLength-1;i++){
        num[i]=0;
    }
    num[numLength-1]=other;
    return *this;
}

uint_var& uint_var::operator=(const uint_var& other){
    if(this!=&other){
        memcpy(num,other.num,numLength*sizeof(uint32_t));
    }
    return *this;
}
//
//uint_var& uint_var::operator+(const uint_var& other){
//    uint_var* result = new uint_var(*this);
//    (*result)+=other;
//    return *result;
//}
//
//uint_var& uint_var::operator-(const uint_var& other){
//    return uint_var(*this) -= other;
//}
//
//const uint_var& uint_var::operator+(const uint32_t& other) const{
//    uint_var* result = new uint_var(*this);
//    (*result)+=other;
//    return *result;
//}
//
//uint_var& uint_var::operator-(const uint32_t& other){
//    return uint_var(*this) -= other;
//}
//
//uint32_t uint_var::operator%(const uint32_t& other){
//    return num[numLength-1] % other;
//}

void uint_var::print(){
    int64_t pos = 0;
    printf("0x");
    while(pos<numLength){
        printf("%08llx",num[pos]);
        pos++;
    }
    printf("\n");
}