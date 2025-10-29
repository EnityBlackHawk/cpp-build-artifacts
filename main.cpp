#include "lib.h"
#include <execinfo.h>
#include <signal.h>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>


void printStackTrace(int skip = 0) {

    FILE *f = fopen("/proc/self/maps", "r");
    if (!f) return;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "libFoo.so")) {
            unsigned long start, end;
            char perms[5], dev[6], mapname[256];
            int inode;
            sscanf(line, "%lx-%lx %4s %*x %5s %d %s",
                   &start, &end, perms, dev, &inode, mapname);
            printf("libFoo.so loaded at 0x%lx - 0x%lx\n", start, end);
        }
    }
    fclose(f);


    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** symbols = backtrace_symbols(callstack, frames);

    std::cerr << "\n=== STACKTRACE ===\n";
    for (int i = skip; i < frames; ++i) {
        std::cerr << "#" << i - skip << " " << symbols[i] << "\n";
    }
    std::cerr << "==================\n\n";

    free(symbols);
}

void signalHandler(int sig, siginfo_t *si, void *unused) {
    std::cerr << "Caught signal " << sig << " (Segmentation Fault)\n";
    printStackTrace(3); // pula os 2 primeiros frames: signalHandler + printStackTrace
    _Exit(1);
}
int main() {

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signalHandler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);

    Foo foo;
    std::thread t( [&foo]{
        foo.print(std::string("Teste"));
    } );

    t.join();

}
