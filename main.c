#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Counts the decimal digits in a value.
 * @retval The number of decimal digits in the value.
 */
static int cnt_dec_digs(unsigned long val);

/**
 * @brief Reads an unsigned long integer value from a string.
 * @param str Str "<whitespaces><+/-/><0/0x/><digits><whitespaces/terminator>".
 * @param val Indicates memory where to store the decoded value on success.
 * @param base Base = 0..36. If base = ​0​, the numeric base is auto-detected.
 * @retval True if the value has been unambiguously decoded.
 */
static inline bool str_to_ul(const char *str, unsigned long *val, int base);

int main(int argc, char **argv)
{
    unsigned long max = 0;
    if (2 != argc || !str_to_ul(argv[1], &max, 10))
    {
        fputs("Specify the maximum number to count up to.\n", stderr);
        return EXIT_FAILURE;
    }

    const int len = cnt_dec_digs(max);

    for (unsigned long num = 1; 0 < num && max >= num; ++num)
    {
        // C func info: https://en.cppreference.com/w/c/io/fprintf
        fprintf(stdout, "[%*lu]", len, num);

        if (0 == num % 3)
        {
            // C func info: https://en.cppreference.com/w/c/io/fputs
            fputs(" fizz", stdout);
        }

        if (0 == num % 5)
        {
            // C func info: https://en.cppreference.com/w/c/io/fputs
            fputs(" buzz", stdout);
        }

        // C func info: https://en.cppreference.com/w/c/io/fputc
        fputc('\n', stdout);
    }

    return EXIT_SUCCESS;
}

static int cnt_dec_digs(unsigned long val)
{
    int cnt = 1;

    while (10 <= val)
    {
        val /= 10;
        cnt++;
    }

    return cnt;
}

static inline bool str_to_ul(const char *str, unsigned long *val, int base)
{
    if (NULL == str || NULL == val)
    {
        return false;
    }

    // C func info: https://en.cppreference.com/w/c/string/byte/strtoul
    errno = 0; // ERANGE if the converted val falls out of range of return type
    char *end = NULL; // The character past the last character interpreted
    unsigned long res = strtoul(str, &end, base);

    // C func info: https://en.cppreference.com/w/c/string/byte/isspace
    // Error if val_out_of_range or bad_val_bgn or bad_val_end
    if (0 != errno || str == end || !('\0' == *end || isspace(*end)))
    {
        return false;
    }

    *val = res;
    return true;
}
