#include "perms.h"

#include <stddef.h>

// TODO: Den her funktion virker kun for en utrolig begrænset mængde input (u-r)
// Fra starten virker det kun for o-r.
// Den skulle også gerne virke for:
// - u, g, o
// - + og -
// - r, w, x, rw, rx, wx, rwx (eller en anden rækkefølge af dem)
bool chmod(const char *input, struct perms_t *perms) {
    if (!input || !perms) return false;

    //1. Læs input:
    char subj = input[0]; // u / g / o / a
    char op = input[1]; // + eller -
    if ((subj != 'u' && subj != 'g' && subj != 'o' && subj != 'a') ||
        (op != '+' && op != '-'))
    {
        return false;
    }
    if (input[2] == '\0') return false;

    // 2. Byg masken
    uint32_t mask = 0;
    for (size_t i = 2; input[i] != '\0'; i++)
    {
        char r = input[i];

        if (r == 'r')
        {
            if (subj == 'u' || subj == 'a') mask |= USER_READ;
            if (subj == 'g' || subj == 'a') mask |= GROUP_READ;
            if (subj == 'o' || subj == 'a') mask |= OTHER_READ;
        }
        else if (r == 'w')
        {
            if (subj == 'u' || subj == 'a') mask |= USER_WRITE;
            if (subj == 'g' || subj == 'a') mask |= GROUP_WRITE;
            if (subj == 'o' || subj == 'a') mask |= OTHER_WRITE;
        }
        else if (r == 'x')
        {
            if (subj == 'u' || subj == 'a') mask |= USER_EXECUTE;
            if (subj == 'g' || subj == 'a') mask |= GROUP_EXECUTE;
            if (subj == 'o' || subj == 'a') mask |= OTHER_EXECUTE;
        }
        else
        {
            return false; //ukendt tegn
        }
    }

    // 3. Brug operatoren
    if (op == '+')
    {
        perms->bits |= mask; //tænd bits
    } else
    {
        perms->bits &= ~mask;
    }

    // Når man AND'er med en maske med 0'er i, slukker man for enkelte bits
    // Når man OR'er med en maske med 1'er i, tænder man for enkelte bits

    // Hvis OTHER_READ er 0b000'000'100
    // så er ~OTHER_READ  0b111'111'011
    //
    // Eksempel:
    // 0644 og o-r giver 0640
    // og når man &'er med den maske, bliver den mindste bit sat til 0, og de resterende bits forbliver som de er.
    // perms->bits &= ~OTHER_READ;
    return true;
}
