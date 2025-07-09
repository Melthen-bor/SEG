#ifndef SEG_BITS
#define SEG_BITS
#include <inttypes.h>
#define seg_get_bit(byte,location) ((byte&(1<<(location%8)))?1:0)
#define seg_set_bit(byte,location,value) (*byte)=(((*byte)&(255-(1<<(location%8))))|((value?1:0)<<(location%8)))
#define seg_get_byte(word,location) ((char)(word>>((location%2)*8)))
#define seg_set_byte(word,location,value) (*word)=(((*word)&(255<<(!(location%2)*8)))|(uint16_t)(((char)value)<<((location%2)*8)))
#define seg_get_word(dword,location) ((uint16_t)(dword>>((location%2)*16)))
#define seg_set_word(dword,location,value) (*dword)=(((*dword)&(65535<<(!(location%2)*16)))|(uint32_t)(((uint16_t)value)<<((location%2)*16)))
#define seg_get_dword(qword,location) ((uint32_t)(qword>>((location%2)*32)))
#define seg_set_dword(qword,location,value) (*qword)=(((*qword)&(4294967295<<(!(location%2)*32)))|(uint64_t)(((uint32_t)value)<<((location%2)*32)))
#define seg_get_high_word(pword) ((uint16_t)(seg_get_bit_width()==SEG_BIT_64?seg_get_word(seg_get_dword(pword,1),1):seg_get_bit_width()==SEG_BIT_32?seg_get_word(pword,1):0))
#define seg_get_low_word(pword) (seg_get_bit_width()==SEG_BIT_64?seg_get_word(seg_get_dword(pword,0),0):seg_get_bit_width()==SEG_BIT_32?seg_get_word(pword,0):0)
#define seg_get_nibble(byte,location) (byte&(15<<(location%2)))
#define seg_set_nible(byte,location,value) (*byte)=(((*byte)&(255-(15<<(location%2)))|((value&15)<<(location%2))))
/*
char seg_get_nibble(char,char);
void seg_set_nibble(char*,char,char);
*/
#endif