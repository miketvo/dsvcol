//
// Created by miketvo on 5/26/2022.
//
#include <stdlib.h>
#include "../include/util.h"

int main ()
{
    if (!ischrin('a', "abc", 3)) return 1;
    if (!ischrin('b', "abc", 3)) return 1;
    if (!ischrin('c', "abc", 3)) return 1;
    if (ischrin('a', "def", 3)) return 1;
    if (ischrin('b', "def", 3)) return 1;
    if (ischrin('c', "def", 3)) return 1;

    char c1 = 'd';
    char c2 = 'e';
    char c3 = 'f';
    char s1[] = "abcdef";
    char s2[] = "ijkxyz";
    if (!ischrin(c1, s1, sizeof(s1) / sizeof(s1[0]))) return 1;
    if (!ischrin(c2, s1, sizeof(s1) / sizeof(s1[0]))) return 1;
    if (!ischrin(c3, s1, sizeof(s1) / sizeof(s1[0]))) return 1;
    if (ischrin(c1, s2, sizeof(s2) / sizeof(s2[0]))) return 1;
    if (ischrin(c2, s2, sizeof(s2) / sizeof(s2[0]))) return 1;
    if (ischrin(c3, s2, sizeof(s2) / sizeof(s2[0]))) return 1;

    return 0;
}
