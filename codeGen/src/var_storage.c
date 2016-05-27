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


#include "global_var.h"
#include "var_storage.h"

void clearVarInitFlag(void)
{
	var_has_init = VAR_NOT_INIT;
}

void setVarInitFlag(void)
{
	var_has_init = VAR_HAS_INIT;
}


uint32_t isVarHasInit(void)
{
	if (var_has_init == VAR_HAS_INIT) {
		return VAR_HAS_INIT;
	} else {
		return VAR_NOT_INIT;
	}
}





