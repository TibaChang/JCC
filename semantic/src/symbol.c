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
#include <stddef.h>
#include "symbol.h"
#include "token.h"
#include "stack.h"
#include "tkWord_Hash.h"
#include "global_var.h"
#include "exception.h"

Symbol *sym_direct_push(Stack *ss, TOKEN tk, Type *type, int val)
{
	Symbol s, *p;
	s.tk_code = tk;
	s.type.data_type = type->data_type;
	s.type.ref = type->ref;
	s.value = val;
	s.next = NULL;
	p = (Symbol*)stack_push(ss, &s, sizeof(Symbol));
	return p;
}

Symbol *sym_push(TOKEN tk, Type *type, uint32_t reg, int val)
{
	Symbol *ps, **pps;
	tkWord *ts;
	Stack *ss;

	if (stack_is_empty(&local_sym_stack) == STACK_IS_NOT_EMPTY) {
		ss = &local_sym_stack;
	} else {
		ss = &global_sym_stack;
	}

	ps = sym_direct_push(ss, tk, type, val);
	ps->reg = reg;

	/*Do NOT record struct member and anonymous symbol*/
	if ((tk & JC_STRUCT) || (tk < JC_ANOM)) {
		ts = (tkWord*)tkTable.data[(tk & ~JC_STRUCT)];
		if (tk & JC_STRUCT) {
			pps = &ts->sym_struct;
		} else {
			pps = &ts->sym_identifier;
		}
		ps->prev = *pps;
		*pps = ps;
	}
	return ps;
}


Symbol *func_sym_push(TOKEN tk, Type *type)
{
	Symbol *s, **ps;
	s = sym_direct_push(&global_sym_stack, tk, type, 0);

	ps = &((tkWord*)tkTable.data[tk])->sym_identifier;

	/*If symbol shares the same name,put function symbol at last*/
	while (*ps != NULL) {
		ps = &(*ps)->prev;
	}
	s->prev = NULL;
	*ps = s;
	return s;
}


Symbol *var_sym_put(Type *type, uint32_t reg, TOKEN tk, int addr)
{
	Symbol *sym = NULL;
	if ((reg & JC_ValMASK) == JC_LOCAL) {
		sym = sym_push(tk, type, reg, addr);
	} else if (tk && (reg & JC_ValMASK) == JC_GLOBAL) {
		sym = sym_search(tk);
		if (sym) {
			error("%s redefinition!\n", ((tkWord*)tkTable.data[tk])->str);
		} else {
			sym = sym_push(tk, type, reg | JC_SYM, 0);
		}
	}
	/*else:const string symbol*/
	return sym;
}


Symbol *sec_sym_put(char *sec, int val)
{
	tkWord *tp;
	Symbol *s;
	Type type;

	type.data_type = T_INT;
	tp = tkW_insert(sec);
	cur_token = tp->tkCode;
	s = sym_push(cur_token, &type, JC_GLOBAL, val);
	return s;
}


void sym_pop(Stack *ptop, Symbol *sym)
{
	Symbol *s, **ps;
	tkWord *ts;
	TOKEN tk;

	s = (Symbol*)stack_get_top(ptop);
	while (s != sym) {
		tk = s->tk_code;

		/*update sym_struct and sym_identifier in the tkTable*/
		if ((tk & JC_STRUCT) || (tk < JC_ANOM)) {
			ts = (tkWord*)tkTable.data[(tk & ~JC_STRUCT)];
			if (tk & JC_STRUCT) {
				ps = &ts->sym_struct;
			} else {
				ps = &ts->sym_identifier;
			}
			*ps = s->prev;
		}
		stack_pop(ptop);
		s = (Symbol*)stack_get_top(ptop);
	}
}


Symbol *struct_search(TOKEN tk)
{
	if (tk >= tkTable.count) {
		return NULL;
	} else {
		return ((tkWord*)tkTable.data[tk])->sym_struct;
	}
}


Symbol *sym_search(TOKEN tk)
{
	if (tk >= tkTable.count) {
		return NULL;
	} else {
		return ((tkWord*)tkTable.data[tk])->sym_identifier;
	}
}

























