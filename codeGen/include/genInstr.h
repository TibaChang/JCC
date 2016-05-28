/*
 * Copyright (c) 2016, Chang Jia-Rung, All Rights Reserved
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __GEN_INSTR_H_
#define __GEN_INSTR_H_

#include "global_var.h"
#include "stdint.h"

/*instruction type*/
#define VALUE_REG     0x0
#define REG_REG       0x1
#define VALUE_OFFSET  0x2

#define instrMOV_VAL_REG(byte_size,value,reg)          instrMOV(VALUE_REG, byte_size, value, reg, NULL, NULL)
#define instrMOV_REG_REG(byte_size, reg_1, reg_2)      instrMOV(REG_REG, byte_size, NULL, reg_1, reg_2, NULL)
#define instrMOV_VAL_OFFSET(byte_size, value, offset)  instrMOV(VALUE_OFFSET, byte_size, value, NULL, NULL, offset)

void instrMOV(uint32_t instrType, uint32_t byte_size, uint32_t value, char *reg_1, char *reg_2, uint32_t offset);



#endif

