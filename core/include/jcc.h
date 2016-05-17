#ifndef __JCC_H_
#define __JCC_H_

typedef enum {
	LEX_NORMAL,
	LEX_SEPARATOR
} LexState;


void init(void);
void cleanup(void);
void color_token(int lex_state);
void syntax_indent(void);


#endif
