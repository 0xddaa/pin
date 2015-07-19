#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "pin.H"
#include <string.h>
#include <sys/mman.h> 

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "output", "specify output file name");

int activated = 0;

INT32 Usage()
{
    cerr << "0ops app" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

BOOL open_check(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std)
{
    char *path = (char*)PIN_GetSyscallArgument(ctxt, std, 0);
    int flags = PIN_GetSyscallArgument(ctxt, std, 1);

    return (!flags && !strcmp(path, "flag"));
}

VOID syscall_check(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v)
{
    int sys_num = PIN_GetSyscallNumber(ctxt, std);
    
    if (sys_num != 3) {
        if (sys_num <= 3 && sys_num > 1) {
            if (activated) {
                if (open_check(threadIndex, ctxt, std))
                    exit(-1);
            }
        }
    } else if (sys_num != 60 && sys_num != 231) {
        if (sys_num == 37) {
            if (activated)
                exit(-1);
            activated = 1;
            if (mprotect(&activated, 0x1000, 1))
                exit(-1);
        }
        else {
            if (activated)
                exit(-1);
        }
    }
    
}

int main(int argc, char * argv[])
{
    if (PIN_Init(argc, argv)) return Usage();

    PIN_AddSyscallEntryFunction(syscall_check, 0);
    PIN_StartProgram();
    
    return 0;
}
