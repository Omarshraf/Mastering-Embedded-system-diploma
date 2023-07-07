/*
 * memory_map.h
 *
 * Created: 7/7/2023 4:40:24 PM
 *  Author: Omar
 */ 


#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_


#define PORTD    *((volatile unsigned char*) 0x32)
#define DDRD	 *((volatile unsigned char*) 0x31)
#define PIND	 *((volatile unsigned char*) 0x30)




#endif /* MEMORY_MAP_H_ */