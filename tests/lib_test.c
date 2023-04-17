#include "../include/count.h"
#include <check.h>
#include <stdio.h>

START_TEST (test_count_files)
{
    printf("TEST");
    printf("%i", count_files("/usr/share", 0));
}
END_TEST

int main(void)
{
    return 0;
}