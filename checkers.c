#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define RED "\x1B[31m"
#define BLU "\x1B[34m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void InitBoard(char a[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i == 0 || i == 2 || i == 6) && (j == 1 || j == 3 || j == 5 || j == 7))
            {
                if (i == 6)
                {
                    a[i][j] = '*';
                    setlocale(LC_CTYPE, "");
                    wchar_t star = 0x2605;
                    wprintf(BLU L"%lc" RESET, star);
                }
                else
                {
                    a[i][j] = '*';
                    setlocale(LC_CTYPE, "");
                    wchar_t star = 0x2605;
                    wprintf(RED L"%lc" RESET, star);
                }
            }
            else if ((i == 1 || i == 5 || i == 7) && (j == 0 || j == 2 || j == 4 || j == 6))
            {
                if (i == 1)
                {
                    a[i][j] = '*';
                    setlocale(LC_CTYPE, "");
                    wchar_t star = 0x2605;
                    wprintf(RED L"%lc" RESET, star);
                }
                else
                {
                    a[i][j] = '*';
                    setlocale(LC_CTYPE, "");
                    wchar_t star = 0x2605;
                    wprintf(BLU L"%lc" RESET, star);
                }
            }
            else
            {
                a[i][j] = '.';
                setlocale(LC_CTYPE, "");
                wchar_t dot = 0x2022;
                wprintf(WHT L"%lc" RESET, dot);
            }
        }
        printf("\n");
    }
}

int main(void)
{
    char a[8][8];
    InitBoard(a);
}
// #include <stdio.h>
// #include <wchar.h>
// #include <locale.h>

// int main() {
//     setlocale(LC_CTYPE, "");
//     wchar_t star = 0x2605;
//     wprintf(L"%lc\n", star);
// }
