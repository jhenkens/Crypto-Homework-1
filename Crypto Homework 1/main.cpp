//
//  main.cpp
//  Crypto Homework 1
//
//  Created by Johan Henkens on 4/14/13.
//  Copyright (c) 2013 Johan Henkens. All rights reserved.
//

#include <iostream>
#include <stdint.h>
#include <random>
#include "uint_var.h"
#include <string>
#include <cassert>

#define CS290BITLENGTH 512

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

void generateRandomNumbers(int64_t words,int64_t count){
    std::random_device generator;
    std::uniform_int_distribution<uint32_t> distribution(0,UINT32_MAX);
    for(int64_t i = 0; i<count;i++){
        for(int64_t o = 0; o<words;o++){
            printf("0x%08x",distribution(generator));
            if(o!=words-1){
                printf(",");
            }
        }
        printf("\n");
    }
}

void formatRandomNumbers(std::string s){
    unsigned long start = s.length()%8;
    printf("{");
    if(start!=0){
        printf("0x%s,",s.substr(0,start).c_str());
    }
    for(; start < s.length(); start+=8){
        printf("0x%s",s.substr(start,8).c_str());
        if(start+8<s.length()){
            printf(",");
        }
    }
    printf("}\n");
}

int main(int argc, const char * argv[])
{

    //Random exponent and modulo generated from openssl. Random base generated with my code once.
    // Base, Exponent, Modulus
#if CS290BITLENGTH == 256
    uint32_t num [4][8] = {
        {0x27de29e9,0xf3d7daa6,0xa016c840,0x84ed034c,0xc0cfe900,0x82308692,0x4ea18ed4,0xc675729a},
        {0xe18731ae,0x5e6c9ec,0xd6aa28d0,0xe28ec631,0x9ba1bf5e,0x90c79021,0x2c3ec4ef,0xcca8171d},
        {0xe437660d,0x9274e5e3,0xfe3db34e,0xf783fea,0xc04d3774,0x944310f4,0x15ed7634,0x5c5b38e5},
        {0xb3b7741d,0xf8e90138,0x545be70,0xc9e417aa,0x8c8ac372,0x482c85fa,0x20e52461,0xb9fbe2eb}};
#endif
#if CS290BITLENGTH == 512
    uint32_t num [4][16] = {
        {0xa0b5c2a3,0x7b3b8979,0x1a95d063,0xd27f3d82,0xb5225bb1,0x1699621a,0x3965f553,0xf3689008,0xafc7b79e,0x734fbc32,0xdb3787b0,0x53e5f90d,0x1329fea9,0x2fa30c3e,0x99ad1ed6,0x2ccfff55},
        {0x3010ecc8,0x319b658a,0x18838bb8,0x8672a8f3,0x8ae69b97,0xcc71fa27,0x2870e481,0xd49bcb92,0xff23726b,0x88fc6399,0x7fed323d,0x800959bb,0x63a6f339,0xe2787627,0xd236f558,0x2ce924d9},
        {0xac72b48c,0x66b0fd3b,0x6854ee21,0xf91f1e10,0x485819e0,0x4cd2cfe7,0x98681ca0,0x9eb8a0a6,0x60906bc1,0x91b6be76,0x93488015,0xadab9e0b,0xc4e2b336,0xfbac140d,0x5a33c1a7,0x8752c1df},
        {0x55c73bd2,0xba9b7845,0xc31c2483,0x910cbbd4,0xbc201848,0xb971403d,0x6903748c,0x94bb1da,0x7f9803f6,0x868c84af,0x483c0ce6,0xe1ed103f,0xa893e147,0xb601a2a1,0xed1f7af7,0x2d2e35c2}};
#endif
#if CS290BITLENGTH == 1024
    uint32_t num [4][32] = {
        {0x7980a593,0x501df31f,0x20c5a98c,0x38b9b433,0x94c29d68,0x611b13d4,0x95e4587f,0xe40c8ed2,0xcb5b1d0b,0x39ab6ceb,0xbb798ecb,0xd1a0ecdf,0x38db273,0x1550cde8,0xb01de5f9,0xf55b9ac6,0x8fe9eef4,0xf1bdf3e7,0xdebfb9e3,0xb4ff2647,0x5da52b89,0x99f3fb74,0x3d9e6bba,0x9368773e,0xe5493564,0x461783a1,0x9c60b736,0xb8872bfd,0x151574bd,0xfb8cde9,0xd1c78547,0x63ff7729},
        {0xb44f4d00,0x63d6b9d4,0xf9ad6d82,0x25256079,0xf4a23e83,0x9d770bfc,0x6c248c03,0xe66bba63,0x602919c9,0x75d9d630,0x1662523e,0x6944780e,0xfe19e3bd,0x31efc82d,0x67421633,0x4331ffec,0x4941215b,0x8741a792,0xd6009473,0xb216994f,0x6d99b7c9,0x8bf53500,0xa03dedb3,0x59018109,0x57ca585a,0xe31aa0ad,0x36d4be55,0x10e72cf9,0x932ac5d0,0x5d297b75,0x1ad06a3e,0x9fb3b8e1},
        {0xd2a041c7,0x3444e882,0x301f6d08,0xcf3a9d2e,0x7e10f3b9,0x9a46c984,0x121c37d0,0xebe2823d,0xaa90beec,0xfade374f,0xd15bfdf5,0x8a1b3cde,0xb108b67,0x38bfd614,0xbb42e64a,0x127eae8f,0x46e67bff,0x51c456a3,0x61472321,0xed194b85,0x34afa090,0xc818ee98,0x5bd3107a,0x6d6a7c73,0xc96f1fce,0x9e4687e7,0xd6d48ba5,0x9112296d,0x356f803a,0x2ae9cf7f,0xde23942a,0xc5969695},
        {0x34d66292,0x5fb464b2,0x405bc75c,0xc0e155c4,0xb8ee41b6,0x35cd97f3,0xd2f20f43,0xcabf9e6c,0x2966eab1,0xdb3b1e6f,0x5edbfba3,0x642d503e,0x2997403,0x751796a9,0xe9d58fbd,0xbf86649d,0x23b14074,0xd66db4b1,0xe50ded22,0x99506666,0xc5636e20,0x7610599a,0x63080e0e,0xc4e6b9c2,0x97d790d0,0x6d336eef,0xf8950762,0xbe90026f,0x75a696d5,0xadaff961,0xdbc35796,0x8037a579}};
#endif
#if CS290BITLENGTH == 2048
    uint32_t num [4][64] = {
        {0x83c24f6a,0xe336ba0b,0x1568e4d,0x70b578da,0xfae32d83,0xeb9e009f,0x735370e2,0x43839a03,0xb33fead6,0xeccef9a1,0x40848080,0xa22c740c,0xfcb89995,0xb2acc28a,0xf8d19027,0x81ad68c0,0xac0026ea,0x2af22734,0x6f87592b,0x2b413f6,0xb0355d20,0x7d145049,0x39520af,0x314d7701,0x4d6c62ed,0x39261ecb,0xf39358cd,0x27a891a7,0x593accd0,0x636767b6,0xedb2290c,0xcda9147f,0x8a5361a6,0xe3f71b4c,0x586b2ca8,0x95ca29ef,0xa908da7e,0x79979587,0x50d8ea69,0x6234a6fd,0x1e7255ed,0xaf200d55,0xe5218e4,0x6b5d4cf7,0x5dad4d15,0xdc344e2f,0x3a0ab77d,0xba4c10ac,0x79745bef,0xb8f8594,0x8ac728d3,0xddfb37a4,0x9cca527a,0x5b77b62b,0x25774eaa,0xa55db5ba,0xf387e345,0x756c2ed6,0xc55eae8b,0xaf046aa4,0x9945fd63,0x8518396f,0x4897982f,0xccfa51c7},
        {0xaab0ce15,0x80b44152,0x45030c90,0x36c8c738,0xa1c385ee,0x4aec115c,0x25610a8f,0xddf6188c,0x375b4154,0xd687a3d9,0x913d9530,0x8e1b7ff5,0x8a63ee6d,0xa6f95d41,0x1ae863e3,0x5824e6f3,0x5c1db217,0x8edb2569,0x84309ec1,0xf052cf41,0x2cdb4b19,0x8b0f2506,0x38730006,0x55ca67cb,0xebc2d069,0x66d2f244,0x3ca1e6af,0x8e364013,0xbb040912,0x3568f31d,0xf63c32c,0xca130f2c,0xbef98e13,0xa06cda1b,0x1d83ea5b,0x97216f7c,0x46993256,0x458e4686,0xec6109fd,0x94fa7df5,0x307bb115,0x8c48e99,0x4971b9d8,0x740a5748,0xf6a637fe,0x8288d0e3,0xae284fcc,0x57af4eb0,0x866238e8,0xf2b8a953,0xfb97853d,0xb96d1376,0x4beab7be,0xbd1cc640,0x36029f40,0xfe8ae1d1,0x1824902a,0xa2bdf9c6,0xc22d8e3,0x9e13a8b2,0xf7631a6e,0x936a0008,0xf002e3ad,0xda5273b1},
        {0xc37931ee,0xc7fbdb99,0x2d6b503a,0xfdcdb5f6,0xb32aac9b,0x760d8be8,0xb27dca37,0x78c0c6b2,0xaeb54c63,0x17ba8c77,0xd6295cc4,0xc5186a6f,0x29f76a34,0x3ca76dd2,0x8d388e32,0x7a2d441f,0x1467024,0xa6593c3b,0x609474d1,0xb4b0b675,0x53be3027,0x9b8cc46b,0xd988e770,0x3c324e26,0x8ee3fad4,0x6d220e4f,0x9ed4b1f0,0x18ca5489,0x78706371,0x7d9b836a,0xec8490b9,0x4a866b9d,0xd5fb726c,0xa9675bca,0xcd83fce0,0xbb59c219,0xed1d1648,0xb866df84,0x61f1dd5b,0x2263b722,0x2dea85cc,0xb16b8f80,0x8481b4d5,0xea615e56,0x34669317,0x435d29cc,0x3b5de11f,0x4433fb03,0xf1673618,0xcbb52d8e,0x4a2e9570,0xc5f00989,0x6e52dfd3,0xfadcfd91,0x297acf15,0xe18d7649,0xe7e326,0x38ddce93,0x3587fcb,0xb5478b43,0x247b96f0,0xa01ffb39,0x40ad9c81,0x8b8ec8b9},
        {0x66f8e9a,0xdcb6b0da,0xfab69319,0x6a023918,0x843e87b1,0xaa1ab92b,0x179ae5ef,0xcd24ea1c,0x99bf5cc6,0x8fc04b5e,0xf9e07a1,0xdb627e54,0x51f452fa,0x129c5cdf,0xb43a0a37,0x6470599d,0xa6ccd1f5,0x9ea1c225,0xa93fe901,0x2c2f8580,0x3fa559f8,0x1fa6bc1,0x9c1c2be9,0x3099886e,0xa45dac66,0xbd3763e1,0x22e0ec7b,0x79d6faeb,0xf0f7aaf5,0x4eaa5ba4,0x3a23471,0x72e47d77,0xbc4c7e31,0x1d13df84,0x51e609b,0xcc86485f,0xd8c41d0f,0xedeeeb0c,0x75f7bd9d,0xf70749c5,0x470b43cb,0x92a30301,0xcd187d02,0x6ceb2f95,0xa94ede2e,0x62bf8d96,0x969a5376,0xe18597c1,0x9f4ab581,0x2fd727ac,0x80b59bd,0xbf97566f,0xbfeec3af,0xfedb0c2d,0x47b76d0c,0xde30f562,0x12b3ee5f,0x4fcbf71a,0xc229e38b,0xc11f811c,0x76a223d8,0xb8d353dd,0xa59c90a8,0x6baccbe8}};
#endif
    uint_var base(CS290BITLENGTH/32,num[0]);
    uint_var exp(CS290BITLENGTH/32,num[1]);
    uint_var mod(CS290BITLENGTH/32,num[2]);
    uint_var resultPreCalc(CS290BITLENGTH/32,num[3]);
//    base.print();
//    exp.print();
//    mod.print();
    uint_var* result = &(base.modExp(exp,mod));
    assert((*result)==resultPreCalc);
//    uint_var* result2 = &(a%b);
    result->print();
//    printf("%d\n",b>0);
    return 0;
}


