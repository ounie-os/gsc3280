/* type */
#include <address.h>
#include <asm/types.h>

#ifndef _TYPES_
#define _TYPES_

typedef	unsigned char u_int8_t;
typedef	unsigned short int u_int16_t;
typedef	unsigned int u_int32_t;
typedef unsigned long long int u_int64_t;

typedef	char int8_t;
typedef	short int int16_t;
typedef	int int32_t;
typedef long long int int64_t;


typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#ifdef __CHECKER__
#define __bitwise__ __attribute__((bitwise))
#else
#define __bitwise__
#endif
#ifdef __CHECK_ENDIAN__
#define __bitwise __bitwise__
#else
#define __bitwise
#endif


typedef __u16 __bitwise __le16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __le32;
typedef __u32 __bitwise __be32;
#if defined(__GNUC__)
typedef __u64 __bitwise __le64;
typedef __u64 __bitwise __be64;
#endif
typedef __u16 __bitwise __sum16;
typedef __u32 __bitwise __wsum;

#if 0
#define KSEG1(addr) ((void *)(KUBASE | (u32)(addr)))

#define KSEG1_STORE8(addr, value) *(volatile u8 *)(KSEG1(addr)) = ((u8)value & 0xff)
#define KSEG1_STORE16(addr, value) *(volatile u16 *)(KSEG1(addr)) = ((u8)value & 0xffff)
#define KSEG1_STORE32(addr, value) *(volatile u32 *)(KSEG1(addr)) = (u32)(value)

#define KSEG1_LOAD8(addr) *(volatile u8 *)(KSEG1(addr))
#define KSEG1_LOAD16(addr) *(volatile u16 *)(KSEG1(addr))
#define KSEG1_LOAD32(addr) *(volatile u32 *)(KSEG1(addr))

#define STORE8(addr, value) *(volatile u8 *)(addr) = value
#define STORE16(addr, value) *(volatile u16 *)(addr) = value
#define STORE32(addr, value) *(volatile u32 *)(addr) = value

#define LOAD8(addr) *(volatile u8 *)(addr)
#define LOAD16(addr) *(volatile u16 *)(addr)
#define LOAD32(addr) *(volatile u32 *)(addr)
#define PHY(addr) \
    (((u32)addr >= 0x80000000 && (u32)addr < 0xa0000000)? \
    (u32)addr-0x80000000:(u32)addr >= 0xa0000000? \
    (u32)addr-0xa0000000:(u32)addr) 
#endif

#endif /* _TYPES_ */
 
