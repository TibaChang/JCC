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
#include <string.h>
#include "genInstr.h"
#include "genVar.h"
#include "exception.h"


/* Suffix	Name	      Size
 *   B	    BYTE    	1 byte (8 bits)
 *   W	    WORD    	2 bytes (16 bits)
 *   L	    LONG    	4 bytes (32 bits)
 *   Q	    QUADWORD	8 bytes (64 bits)
 */
static void instrAddSuffix(char *origin_instr, uint32_t byte_size)
{
	char *suffix;
	switch (byte_size) {
	case 1:
		suffix = "b";
		break;
	case 4:
		suffix = "l";
		break;
	case 8:
		suffix = "q";
		break;
	default:
		error("Instruct size error!");
		break;
	}
	strcat(origin_instr, suffix);
}



/*user should not use this function directly,the macro is better*/
void instrMOV(uint32_t instrType, uint32_t byte_size, uint32_t value, char *reg_1, char *reg_2, uint32_t offset)
{
	char instr[5] = "mov";
	instrAddSuffix(instr, byte_size);

	asmPrintf("    ");
	switch (instrType) {
	case VALUE_REG:
		asmPrintf("%s    $%d,%%%s\n", instr, value, reg_1);
		break;
	case REG_REG:
		asmPrintf("%s    %%%s, %%%s\n", instr, reg_1, reg_2);
		break;
	case VALUE_OFFSET:
		asmPrintf("%s    $%d, %d(%%rbp)\n", instr, value, offset);
		break;
	default:
		error("MOV instruction type error");
		break;
	}
}


