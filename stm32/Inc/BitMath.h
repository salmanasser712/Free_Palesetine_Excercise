#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define toggle(x, bit) (x = (1 << bit) ^ x)
#define SET_BIT(x, bit) (x = (x | (1 << bit)))
#define CLR_BIT(x, bit) (x = (x & (~(1 << bit))))
#define GET_BIT(x, bit) ((x >> bit) & 1)

#endif
