#ifndef _FONT_CHINESE_H_
#define _FONT_CHINESE_H_

#include "zf_common_typedef.h"

const uint8 chinese_loading[][16]={
    {0x20,0x00,0x10,0x00,0x01,0xFC,0xFC,0x44,0x08,0x44,0x10,0x44,0x10,0x44,0x34,0x44},
    {0x58,0x44,0x94,0x44,0x14,0x44,0x10,0x84,0x10,0x84,0x11,0x04,0x12,0x28,0x14,0x10},/*"初",0*/
    {0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x40,0xFC,0x48,0x24,0x84,0x25,0xFE,0x24,0x82},
    {0x24,0x00,0x48,0xFC,0x28,0x84,0x10,0x84,0x28,0x84,0x44,0x84,0x80,0xFC,0x00,0x84},/*"始",1*/
    {0x08,0x80,0x08,0x80,0x08,0x84,0x10,0x88,0x10,0x90,0x30,0xA0,0x30,0xC0,0x50,0x80},
    {0x91,0x80,0x12,0x80,0x14,0x80,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x7E,0x10,0x00},/*"化",2*/
};

const uint8 chinese_nodata[][16]={
    {0x00,0x00,0x3F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xFC,0x04,0x80},
    {0x04,0x80,0x04,0x80,0x08,0x80,0x08,0x80,0x10,0x84,0x20,0x84,0x40,0x7C,0x80,0x00},/*"无",0*/
    {0x02,0x00,0x02,0x00,0xFF,0xFE,0x04,0x00,0x04,0x00,0x0F,0xF0,0x08,0x10,0x18,0x10},
    {0x24,0x28,0x14,0x28,0x08,0x10,0x14,0x10,0x22,0x28,0x42,0x48,0x80,0x84,0x01,0x02},/*"效",1*/
    {0x08,0x20,0x49,0x20,0x2A,0x20,0x08,0x3E,0xFF,0x44,0x2A,0x44,0x49,0x44,0x88,0xA4},
    {0x10,0x28,0xFE,0x28,0x22,0x10,0x42,0x10,0x64,0x28,0x18,0x28,0x34,0x44,0xC2,0x82},/*"数",2*/
    {0x20,0x00,0x23,0xFC,0x22,0x04,0x22,0x04,0xFB,0xFC,0x22,0x20,0x22,0x20,0x2B,0xFE},
    {0x32,0x20,0xE2,0x20,0x22,0xFC,0x22,0x84,0x22,0x84,0x24,0x84,0xA4,0xFC,0x48,0x84},/*"据",3*/
};

#endif