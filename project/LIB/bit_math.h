/*
 * BIT_MATH.h
 *
 * Created: 9/6/2026 5:23:48 AM
 * Author: Sarah 
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG, BIT) (REG) |= (1 << (BIT))
#define CLR_BIT(REG, BIT) (REG) &= ~(1 << (BIT))
#define TOG_BIT(REG, BIT) (REG) ^= (1 << (BIT))
#define GET_BIT(REG, BIT) (((REG) >> (BIT)) & 1)

#endif /* BIT_MATH_H_ */
