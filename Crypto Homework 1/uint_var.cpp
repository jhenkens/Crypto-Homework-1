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
    int64_t pos = 1;
    overflow=false;
    while(pos<=other.numLength){
        if(overflow){
            if(num[numLength-pos] != UINT32_MAX){
                overflow = false;
            }
            num[numLength-pos]++;
        }
        if(num[numLength-pos] > UINT32_MAX-other.num[other.numLength-pos]){
            overflow = true;
        }
        num[numLength-pos]+=other.num[other.numLength-pos];
        pos++;
    }
	while(overflow && pos<=numLength){
        if(num[numLength-pos] != UINT32_MAX){
            overflow = false;
        }
        num[numLength-pos]++;
        pos++;
	}
    return *this;
}

uint_var& uint_var::operator-=(const uint_var& other){
    int64_t pos = 1;
    underflow=false;
    while(pos<=other.numLength){
        if(underflow){
            if(num[numLength-pos] != 0){
                underflow = false;
            }
            num[numLength-pos]--;
        }
        if(num[numLength-pos] < other.num[other.numLength-pos]){
            underflow = true;
        }
        num[numLength-pos]-=other.num[other.numLength-pos];
        pos++;
    }
    while(underflow && pos<=numLength){
        if(num[numLength-pos] != 0){
            underflow = false;
        }
        num[numLength-pos]--;
        pos++;
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



//uint_var& uint_var::operator-=(const uint32_t& other){
//    int64_t pos = numLength-1;
//    underflow = false;
//    
//    if(num[pos] < other){
//        underflow = true;
//    }
//    
//    num[pos]-=other;
//    pos--;
//    
//    while(underflow && pos>=0){
//        if(num[pos] != 0){
//            underflow = false;
//        }
//        num[pos]--;
//        pos--;
//    }
//    
//    return *this;
//    
//}

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

//uint_var& uint_var::operator*(const uint32_t& other){
//    uint_var temp(1);
//    temp.num[0]=other;
//    return (*this)*temp;
//}

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


//uint_var& uint_var::operator%(const uint32_t& other){
//    uint_var temp(numLength);
//    temp.num[numLength-1]=other;
//    return (*this)%temp;
//}


bool uint_var::notZero(){
    for(int64_t i = numLength-1; i>=0; i--){
        if(num[i]){
            return true;
        }
    }
    return false;
}

//uint_var& uint_var::operator++(int){
//    int64_t pos = numLength-1;
//    overflow = false;
//    
//    if(num[pos] == UINT32_MAX){
//        overflow = true;
//    }
//    
//    num[pos]++;
//    pos--;
//    
//    while(overflow && pos>=0){
//        if(num[pos] != UINT32_MAX){
//            overflow = false;
//        }
//        num[pos]++;
//        pos--;
//    }
//    return *this;
//}

//uint_var& uint_var::operator--(int){
//    int64_t pos = numLength-1;
//    underflow = false;
//    
//    if(num[pos] == 0){
//        underflow = true;
//    }
//    
//    num[pos]--;
//    pos--;
//    
//    while(underflow && pos>=0){
//        if(num[pos] != 0){
//            underflow = false;
//        }
//        num[pos]--;
//        pos--;
//    }
//    return *this;
//}

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

//bool uint_var::operator>(const uint32_t& other){
//    if(num[numLength-1] > other){
//        return true;
//    } else{
//        int64_t pos = numLength-2;
//        while(pos>=0){
//            if(num[pos]!=0){
//                return true;
//            }
//            pos--;
//        }
//    }
//    return false;
//}

bool uint_var::operator<(const uint_var& other){
    int64_t diff = numLength-other.numLength;
    if(diff>0){
        for(int i = 0; i < diff; i++){
            if(num[i]!=0){
                return false;
            }
        }
        for( int64_t pos = 0; pos < other.numLength;pos++){
            if(num[pos+diff]<other.num[pos]){
                return true;
            } else if(num[pos+diff]>other.num[pos]){
                return false;
            }
        }
    }
    else if(diff<0){
        for(int i = 0; i < -diff; i++){
            if(other.num[i]!=0){
                return true;
            }
        }
        for( int64_t pos = 0; pos < numLength;pos++){
            if(num[pos]<other.num[pos+diff]){
                return true;
            } else if(num[pos]>other.num[pos+diff]){
                return false;
            }
        }
    }
    else {
        for( int64_t pos = 0; pos < numLength;pos++){
            if(num[pos]<other.num[pos]){
                return true;
            } else if(num[pos]>other.num[pos]){
                return false;
            }
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

//Assumes that this, and multi, are both < mod
uint_var& uint_var::modMult(const uint_var& mult,const uint_var& mod){
#ifndef MULTSHIFTADD
    uint_var* temp = &((*this)*mult);
    uint_var* result = &((*temp)%mod);
    delete temp;
    return *result;
#else
    uint_var* temp = new uint_var(mod.numLength+1);
    uint_var* result;
    uint32_t wS = (sizeof(uint32_t)*8);
    for(uint32_t i = 0; i < numLength*wS;i++){
        uint32_t word = (i/wS);
        uint32_t shift = wS-1-(i%wS);
        uint32_t mask = 1u<<shift;
        (*temp)<<=1;
        if(num[word]&mask){
            (*temp)+=mult;
        }
        if(!((*temp)<mod)){
            (*temp)-=mod;
        }
        if(!((*temp)<mod)){
            (*temp)-=mod;
        }
    }
    result = new uint_var(mod.numLength);
    memcpy((*result).num,(*temp).num+1,mod.numLength*sizeof(uint32_t));
    delete temp;
    return *result;
#endif
}


//Index from highest magnitude first. aka, index 0 is highest significant bit.
bool uint_var::operator[](uint32_t pos){
    uint32_t wS = (sizeof(uint32_t)*8);
    uint32_t word = pos/wS;
    uint32_t shift = wS-1-(pos%wS);
    uint32_t mask = 1u<<shift;
    return (num[word]&mask)>>shift;
}

uint_var& uint_var::modExp(const uint_var& power,const uint_var& mod){
#ifndef MODEXPMARY
    //Binary method
    uint_var* result = new uint_var(numLength);
    uint32_t mask = 0x80000000;
    uint32_t word = 0;
    if ( power.num[0]&mask){
        (*result)=(*this);
    } else{
        (*result)=1;
    }
    mask>>=1;
    
    uint_var* temp;
    for(int i = 1; i < power.numLength*sizeof(uint32_t)*8;i++){
        temp=&(*result).modMult(*result,mod);
        delete result;
        result = temp;
        if(power.num[word]&mask){
            temp=&(*result).modMult(*this,mod);
            delete result;
            result = temp;
        }
        if(mask==1){
            word++;
            mask=0x80000000;
        } else{
            mask>>=1;
        }
    }
    return *result;
#else
    //4-ary method
    uint_var* base2 = &(this->modMult(*this, mod));
    uint_var* base3 = &(base2->modMult(*this, mod));
    uint_var* base4 = &(base3->modMult(*this, mod));
    uint_var* base5 = &(base4->modMult(*this, mod));
    uint_var* base6 = &(base5->modMult(*this, mod));
    uint_var* base7 = &(base6->modMult(*this, mod));
    uint_var* base8 = &(base7->modMult(*this, mod));
    uint_var* base9 = &(base8->modMult(*this, mod));
    uint_var* base10 = &(base9->modMult(*this, mod));
    uint_var* base11 = &(base10->modMult(*this, mod));
    uint_var* base12 = &(base11->modMult(*this, mod));
    uint_var* base13 = &(base12->modMult(*this, mod));
    uint_var* base14 = &(base13->modMult(*this, mod));
    uint_var* base15 = &(base14->modMult(*this, mod));
    uint_var* bases[16] = {NULL,this,base2,base3,base4,base5,base6,base7,base8,base9,base10,base11,base12,base13,base14,base15};
    
    uint_var* result = new uint_var(numLength);
    uint32_t mask = 0xF0000000;
    uint32_t word = 0;
    uint32_t shift = 28;
    uint32_t curr = (power.num[0]&mask)>>shift;
    if(curr == 0){
        (*result)=1;
    } else{
        (*result)=*(bases[curr]);
    }
    mask>>=4;
    shift-=4;
    
    uint_var* temp;
    for(int i = 1; i < power.numLength*sizeof(uint32_t)*8/4;i++){
        curr = (power.num[word]&mask)>>shift;
        temp=&(*result).modMult(*result,mod);
        delete result;
        result=&(*temp).modMult(*temp,mod);
        delete temp;
        temp=&(*result).modMult(*result,mod);
        delete result;
        result=&(*temp).modMult(*temp,mod);
        delete temp;
        
        if(curr){
            temp=&(*result).modMult(*bases[curr],mod);
            delete result;
            result = temp;
        }
        if(mask==0xF){
            word++;
            mask=0xF0000000;
            shift=28;
        } else{
            mask>>=4;
            shift-=4;
        }
    }
    for (int i = 2; i < 16; i++){
        delete bases[i];
    }
    return *result;
#endif
}

uint_var& uint_var::modExp(const uint32_t& power,const uint_var& mod, uint32_t i){
    //Binary method
    uint_var* result = new uint_var(numLength);
    uint32_t mask = 0x80000000>>i;
    while(!(power&mask) && i<-1+sizeof(uint32_t)*8){
        i++;
        mask>>=1;
    }
    if ( power&mask){
        (*result)=(*this);
    } else{
        (*result)=1;
    }
    mask>>=1;
    i++;
    
    uint_var* temp;
    for(; i < sizeof(uint32_t)*8;i++){
        temp=&(*result).modMult(*result,mod);
        delete result;
        result = temp;
        if(power&mask){
            temp=&(*result).modMult(*this,mod);
            delete result;
            result = temp;
        }
        mask>>=1;
    }
    return *result;
}

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