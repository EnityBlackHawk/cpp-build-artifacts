#include "lib.h"
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>


void printStackTrace(int skip = 0) {
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
    printStackTrace(2); // pula os 2 primeiros frames: signalHandler + printStackTrace
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
    foo.print(std::string("Teste"));

}
