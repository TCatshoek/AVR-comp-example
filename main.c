#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define GUARD_VALUE 0xFEEDCAFE

int main() {
    // We want direct control over memory layout, so put things in a struct so the compiler doesn't pull a fast one on us
    // It tends to reorganize the variables so that the guard value is before the buffer in memory.
    struct {
        char buf[256];
        uint32_t guard;
    } locals;
    locals.guard = GUARD_VALUE;

    gets(locals.buf);

    // Poor mans stack canary :)
    if (locals.guard != GUARD_VALUE) {
        printf("Hacking detected! 0x%08x\n", locals.guard);
        abort(); // Or somehow signal the "competition manager" that we found a crash?
    }

    printf("Echo: %s", locals.buf);

    return 0;
}
