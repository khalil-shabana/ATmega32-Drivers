/*
 * Bit_Mask.h
 *
 *  Created on: Jul 22, 2022
 *      Author: Khalil
 */

#ifndef REPO_LIB_BIT_MASK_H_
#define REPO_LIB_BIT_MASK_H_

#define SET_BIT(reg,bit) (reg|= 1<<bit)
#define CLEAR_BIT(reg,bit) (reg&= ~(1<<bit))
#define TOGGLE_BIT(reg,bit) (reg^= 1<<bit)
#define GET_BIT(reg,bit) ((reg & (1<<bit))>>bit)

#endif /* REPO_LIB_BIT_MASK_H_ */
