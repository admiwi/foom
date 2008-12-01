#ifndef _FOOM_UTIL_
#define _FOOM_UTIL_

#define is_lchar(A) ((A)>='a'&&(A)<='z')
#define is_uchar(A) ((A)>='A'&&(A)<='Z')
#define is_char(A)  (is_lchar(A)||is_uchar(A)||A=='_')
#define is_num(A)   ((A)>='0'&&(A)<='9')
#define is_ws(A)    ((A)=='\n'||(A)=='\t'||(A)==' ')
#define is_irrel(A) ((A)=='\r'||(A)=='\0')
#define is_op(A)  (((A)>='!'&&(A)<='/')||((A)>=':'&&(A)<='@')||((A)>='['&&(A)<='^')||((A)>='{'&&(A)<='~')||(A)=='`')

#define flaged(A,B) (A&(B))
#define set_flag(A,B)    (A|=(B))
#define toggle_flag(A,B) (A=(A^B))
#define clear_flag(A,B)  (A=(A&(~B)))

char * resize_string(char*, int);

#endif
