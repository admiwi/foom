#ifndef _FOOM_GRAMMER_
#define _FOOM_GRAMMER_


// 0x01-0x1f  ctrl chars
#define GLEN 15

#define STMT "\x1"
#define STMTS "\x2"
#define EXPR "\x3"
#define CLOSURE "\x4"
#define WS "\x5" 
#define TYPE "\x6"
#define ID "\x7"
#define TERM "\x8"
#define OP "\x9"
#define CASE_STMT "\xA"
#define WHILE_STMT "\xB"
#define FOR_STMT "\xC"
#define IF_STMT "\xD"

#define LASTG 0x20

#define END "\0"
#define END2 END,END
#define END3 END2,END
#define END4 END3,END
#define END5 END4,END
#define END6 END5,END
#define END7 END6,END
#define END8 END7,END

#define GEND {"\0"}

production * gen_if();

#endif
