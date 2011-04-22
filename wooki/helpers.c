#include <wooki.h>
#include "chewbacca.h"

void syntax_print(void) { syntax("print", _("[object]")); }
void help_print(void) {
    out(_("Print an object.\n"
        "Available built-in objects:\n"
        "\tobjects\t\tList installed objects.\n"
        "\tregisters\tList interpreter registers values\n"
        "\tewok\t\tInformation about the memory management\n"));
}


void syntax_debug(void) { syntax("debug", _("[level]")); }
void help_debug(void) {
    out(_("Set debug level.\n"
        "\tInformations about the interpreter and data structs\n"
        "\tare printed to stderr according to level set.\n"
        "\tExample: debug 1  -- Set to basic debug\n"
        "\t0\tno debug. Only errors are showed.\n"
        "\t1\tbasic debug.\n"
        "\t2\textreme debug.\n"
        "\t3\tnon-sense debug. Not recommended for users.\n"));
    syntax_debug();
}


void syntax_random(void) { syntax("rnd", _("[from] [to] [destination]")); }
void help_random(void) {
    out(_("Generate a random value.\n"
        "\tGenerate a random value and throw to the destination.\n"
        "\tThe destination can be a register, a buffer or a opcode\n"
        "\tExample: rnd 10 40 %%eax  -- Random between 10 and 40, "
        "store in %%eax\n"));
    syntax_random();
}


void syntax_type(void) {
    syntax("type", "[int,int64,char,bool,double,float,double]");
}
void help_type(void) {
    out(_("Set data type to be stored.\n"
        "\tAfter allocate an object the type is fixed,\n"
        "\tand will not be able to change anymore.\n"
        "\tExample: type int  -- Set data type to integers\n"));
    syntax_type();
}


void syntax_optmem(void) { syntax("optmem", _("[boolean]")); }
void help_optmem(void) {
    out(_("Memory Optimization\n"
        "\t If activated, when a new data is going to be pushed to\n"
        "\ta data structure, register or buffer, the interpreter\n"
        "\twill search into already allocated data for same value.\n"
        "\tIf found, a reference to this data is passed, avoiding\n"
        "\t Note: memory optimization must be defined in the very start\n"
        "\tof the program!\n"
        "\tmemory duplication.\n"
        "\tActivate: optmem 1\n"
        "\tDeactivate: optmem 0\n"));
    syntax_optmem();
}


void syntax_forloop(void) {
    syntax("for", _("[from] to [to] (step [step]), [command]"));
}
void help_forloop(void) {
    out(_("Run a loop iteration\n"
        "\tExecute a command, passing values between\n"
        "\ta range, and if defined stepping values.\n"
        "\tExamples:\n"
        "\t\tfor 1 to 5, append          -- Equivalent: append 1 2 3 4 5\n"
        "\t\tfor 2 to 10 step 2, append  -- Equivalent: append 2 4 6 8 10\n")
        );
    syntax_forloop();
}


void syntax_repeat(void) {
    syntax("repeat", _("[times], [command]"));
}
void help_repeat(void) {
    out(_("TODO"));
    syntax_repeat();
}


void syntax_meminfo(void) { syntax("meminfo", ""); }
void help_meminfo(void) {
    out(_("Show Memory Analysis\n"
        "\tUse this command to see the program memory status.\n"));
    syntax_meminfo();
}


void syntax_ewok(void) { syntax("ewok", ""); }
void help_ewok(void) {
    out(_("Garbage Collector\n"
        "\tInvoke Ewoks to free input data.\n"));
    syntax_ewok();
}


void syntax_exit(void) { syntax("exit", ""); }
void help_exit(void) {
    out(_("Exit Interpreter\n"
        "\tExit from interpreter program returning status OK to system.\n"));
    syntax_exit();
}


void syntax_new(void) { syntax("new", "[object]"); }
void help_new(void) {
    out(_("Create an instance of object. When command new is executed\n"
        "the command \"sel [object]\" is implicitly run.\n"));
    syntax_new();
}


void syntax_push(void) { syntax("push", "[values]"); }
void help_push(void) {
    out(_("Push values into data structure\n"
        "\tExample: push 1 2 3\n"));
    syntax_push();
}


void syntax_sel(void) { syntax("sel", "[object]"); }
void help_sel(void) {
    out(_("Select an object to work with.\n"));
    syntax_sel();
}
