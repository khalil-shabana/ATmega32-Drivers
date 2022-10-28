/*
 * Data_types.h
 *
 *  Created on: Jul 22, 2022
 *      Author: Khalil
 */

#ifndef REPO_LIB_DATA_TYPES_H_
#define REPO_LIB_DATA_TYPES_H_

typedef unsigned char u8_t;
typedef signed char s8_t;

typedef unsigned short u16_t;
typedef signed short s16_t;

typedef unsigned long u32_t;
typedef signed long s32_t;

typedef unsigned long long u64_t;
typedef signed long long s64_t;

typedef float f32_t;
typedef double f64_t;

#define TRUE	(u8_t)0x01
#define FALSE	(u8_t)0x00
#define NULLPTR ((void*)0)
#endif /* REPO_LIB_DATA_TYPES_H_ */
