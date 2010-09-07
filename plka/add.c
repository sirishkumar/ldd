#include<stdio.h>
#include<stdlib.h>

int add (int a, int b) {
        return a+b;
}

int main() {
        int a,b;
        a = 3;
        b = 4;
        int ret = add(a,b);
        printf("Result: %u\n", ret);

        exit(0);
}
