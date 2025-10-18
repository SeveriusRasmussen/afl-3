#include <assert.h>
#include <stdio.h>
#include "perms.h"

int main(int argc, char *argv[]) {
    // Test 1
    {
        struct perms_t file_a = { 0644 };
        printf("Test 1 before: %o\n", file_a.bits);
        struct perms_t expect = { 0640 };
        printf("Test 1 expect: %o\n", expect.bits);
        bool success = chmod("o-r", &file_a);
        printf("Test 1 after:  %o\n", file_a.bits);
        assert(success && file_a.bits == expect.bits);
        printf(" -> Test 1 gik godt!\n");
    }

    // Test 2
    {
        struct perms_t file_b = { 0777 };
        printf("Test 2 before: %o\n", file_b.bits);
        struct perms_t expect = { 0666 };
        printf("Test 2 expect: %o\n", expect.bits);
        bool success = chmod("a-x", &file_b);
        printf("Test 2 after:  %o\n", file_b.bits);
        assert(success && file_b.bits == expect.bits);
        printf(" -> Test 2 gik godt!\n");
    }

    // Test 3
    {
        struct perms_t file_c = { 0400 };
        printf("Test 3 before: %o\n", file_c.bits);
        struct perms_t expect = { 0700 };
        printf("Test 3 expect: %o\n", expect.bits);
        bool success = chmod("u+wx", &file_c);
        printf("Test 3 after:  %o\n", file_c.bits);
        assert(success && file_c.bits == expect.bits);
        printf(" -> Test 3 gik godt!\n");
    }

    // Test det giver fejl meddelelse:
    {
        struct perms_t file_d = { 0333 };
        printf("Test 4 before: %o\n", file_d.bits);
        struct perms_t expect = { 0000 };
        printf("Test 4 expect: %o\n", expect.bits);
        bool success = chmod("a-wh", &file_d);
        printf("Test 4 after:  %o\n", file_d.bits);
        assert(success && file_d.bits == expect.bits);
        printf(" -> Test 4 gik godt!\n");
    }

    return 0;
}
