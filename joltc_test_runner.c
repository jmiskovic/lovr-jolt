#include <stdio.h>
#include <stdint.h>

uint32_t JoltCTest_Basic1(void);
uint32_t JoltCTest_Basic2(void);
uint32_t JoltCTest_HelloWorld(void);


int main() {
    printf("JoltCTest_Basic1: %s\n",     JoltCTest_Basic1() == 1     ? "OK" : "FAIL");
    printf("JoltCTest_Basic2: %s\n",     JoltCTest_Basic2() == 1     ? "OK" : "FAIL");
    printf("JoltCTest_HelloWorld: %s\n", JoltCTest_HelloWorld() == 1 ? "OK" : "FAIL");
    return 0;
}
