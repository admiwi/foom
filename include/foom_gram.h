#ifndef _FOOM_GRAMMER_
#define _FOOM_GRAMMER_


#define GLEN 15

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

void gProgram(token *);
#endif
