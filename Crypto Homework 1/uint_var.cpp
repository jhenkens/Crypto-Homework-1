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
    overflow=false;
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
    overflow = false;
    
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
    underflow=false;
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
    underflow = false;
    
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

uint_var& uint_var::operator%(const uint_var &other){
    uint_var  P(this->numLength*2);
    uint32_t* p2 = P.num;
    p2+=this->numLength;
    memcpy(p2,this->num,sizeof(uint32_t)*this->numLength);
    uint_var prev(P);
    
    uint_var D(this->numLength*2);
    for(int64_t i = 1; i<=other.numLength;i++){
        D.num[D.numLength-i]=other.num[other.numLength-i];
    }
    D<<=(uint32_t)(numLength*sizeof(uint32_t)*8);
    
    for(int64_t i = 0; i <= numLength*sizeof(uint32_t)*8; i++){
        prev=P;
        P-=D;
        if(P.underflow){
            P=prev;
        }
        D>>=1;
    }
    uint_var* result = new uint_var(other.numLength);
    memcpy((*result).num,P.num+(P.numLength-other.numLength),other.numLength*sizeof(uint32_t));
    return *result;
}


uint_var& uint_var::operator%(const uint32_t& other){
    uint_var temp(numLength);
    temp.num[numLength-1]=other;
    return (*this)%temp;
}


bool uint_var::notZero(){
    for(int64_t i = numLength-1; i>=0; i--){
        if(num[i]){
            return true;
        }
    }
    return false;
}

uint_var& uint_var::operator++(int){
    int64_t pos = numLength-1;
    overflow = false;
    
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
    underflow = false;
    
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
    if(other==0){
        return *this;
    } else if(other==sizeof(uint32_t)*8){
        for(int64_t pos = numLength-2; pos>=0;pos-- ){
            num[pos+1] = num[pos];
        }
        num[0]=0;
    } else if(other<sizeof(uint32_t)*8){
        uint32_t mask = (1<<other)-1;
        uint32_t negativeShift = sizeof(uint32_t)*8-other;
        
        
        num[numLength-1]>>=other;
        for(int64_t pos = numLength-2; pos >= 0; pos--){
            num[pos+1]|=(num[pos]&mask)<<negativeShift;
            num[pos]>>=other;
        }
    } else{
        int64_t words = other/(sizeof(uint32_t)*8);
        for(int64_t pos = numLength-1-words; pos>=0;pos-- ){
            num[pos+words] = num[pos];
        }
        for(words-=1;words>=0;words--){
            num[words]=0;
        }
        (*this)>>=(other%(sizeof(uint32_t)*8));
    }
    
    return *this;
}

uint_var& uint_var::operator<<=(const uint32_t& other){
    if(other==0){
        return *this;
    } else if(other==sizeof(uint32_t)*8){
        for(int64_t pos = 1; pos<numLength;pos++ ){
            num[pos-1] = num[pos];
        }
        num[numLength-1]=0;
    } else if(other<sizeof(uint32_t)*8){
        uint32_t negativeShift = sizeof(uint32_t)*8-other;
        uint32_t mask = ~((1<<negativeShift)-1);
        
        
        num[0]<<=other;
        for(int64_t pos = 1; pos < numLength; pos++){
            num[pos-1]|=(num[pos]&mask)>>negativeShift;
            num[pos]<<=other;
        }
    } else{
        int64_t words = other/(sizeof(uint32_t)*8);
        for(int64_t pos = words; pos<numLength;pos++ ){
            num[pos-words] = num[pos];
        }
        for(words=numLength-words;words<numLength;words++){
            num[words]=0;
        }
        (*this)<<=(other%(sizeof(uint32_t)*8));
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

bool uint_var::operator<(const uint_var& other){
    for( int64_t pos = 0; pos < numLength;pos++){
        if(num[pos]<other.num[pos]){
            return true;
        } else if(num[pos]>other.num[pos]){
            return false;
        }
    }
    return false;
}

bool uint_var::operator==(const uint_var& other){
    if(numLength!=other.numLength){ return false;}
    for( int64_t pos = 0; pos < numLength;pos++){
        if(num[pos]!=other.num[pos]){
            return false;
        }
    }
    return true;
}

uint_var& uint_var::modMult(const uint_var& mult,const uint_var& mod){
    uint_var* temp = &((*this)*mult);
    uint_var* result = &((*temp)%mod);
    delete temp;
    return *result;
}

uint_var& uint_var::modExp(const uint_var& power,const uint_var& mod){
    /* Naive implementation
     uint_var i(power.numLength);
     uint_var* result = new uint_var(numLength);
     (*result)=1;
     for( ; i<power;i++){
     result = &((*result).modMult(*this, mod));
     }
     return *result;
     */
    uint_var* result = new uint_var(numLength);
    (*result)=1;
    uint_var* temp;
    uint_var* base = new uint_var(*this);
    uint_var pow(power);
    while(pow.notZero()){
        if(pow.num[pow.numLength-1]& 1){
            temp = &((*result).modMult(*base, mod));
            delete result;
            result = temp;
        }
        pow>>=1;
        temp = &((*base).modMult(*base, mod));
        delete base;
        base = temp;
    }
    delete base;
    return *result;
}

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

uint_var::~uint_var(){
    delete[] num;
}

void uint_var::print () const {
    int64_t pos = 0;
    printf("0x");
    while(pos<numLength){
        printf("%08x",num[pos]);
        pos++;
    }
    printf("\n");
}