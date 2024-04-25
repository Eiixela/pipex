#include <stdio.h>

static char *check_space_quotes(char *s)
{
    int i = 0;
    int j = 0;
    int firstQuoteFound = 0;

    while (s[i] != '\0')
    {
        if (s[i] == 39)  // 39 is the ASCII code for single quote (')
        {
            if (!firstQuoteFound)
            {
                s[j++] = s[i++];
                firstQuoteFound = 1;
                continue;
            }
            
            s[j++] = s[i++];  // Copy the current single quote
            while (s[i] != 39 && s[i] != '\0')
            {
                if (s[i] == 32)  // 32 is the ASCII code for space
                    s[j++] = 71;  // 71 is the ASCII code for 'G'
                else
                    s[j++] = s[i];
                i++;
            }
            if (s[i] == 39)
                s[j++] = s[i++];  // Copy the closing single quote
        }
        else
        {
            s[j++] = s[i++];
        }
    }
    s[j] = '\0';  // Null-terminate the modified string

    return s;
}

int main()
{
    char s[] = "cc' la 'famille";
    char *s2 = check_space_quotes(s);
    printf("%s\n", s2);
    return 0;
}

