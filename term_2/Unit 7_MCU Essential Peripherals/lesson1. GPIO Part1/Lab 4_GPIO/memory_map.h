/*
 * memory_map.h
 *
 * Created: 7/7/2023 7:26:11 PM
 *  Author: Omar
 */ 


#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_



#define PORTD    *((volatile unsigned char*) 0x32)
#define DDRD     *((volatile unsigned char*) 0x31)
#define PIND     *((volatile unsigned char*) 0x30)


#define SetBit(Address,Bit)          Address |= (1<<Bit)
#define ResetBit(Address,Bit)        Address &= ~(1<<Bit)
#define ReadBit(Address,Bit)         ((Address & (1<<Bit))>>Bit)
#define ToggleBit(Address,Bit)       Address ^= (1<<Bit)





#endif /* MEMORY_MAP_H_ */