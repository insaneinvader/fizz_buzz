// *****************************************************************************

#include <stdio.h>

// *****************************************************************************

static unsigned int get_dec_digits_cnt(unsigned int number);

// *****************************************************************************

int main()
{
    const unsigned int num_max = 100;
    const unsigned int num_max_digits = get_dec_digits_cnt(num_max);

    for(unsigned int num = 1; num <= num_max; ++num)
    {
        printf("[%*u]", num_max_digits, num);

        if(0 == (num % 3)) fputs(" fizz", stdout);

        if(0 == (num % 5)) fputs(" buzz", stdout);

        fputs("\n", stdout);
    }

    return 0;
}

// *****************************************************************************

static unsigned int get_dec_digits_cnt(unsigned int number)
{
    unsigned int digits_cnt = 1;

    for(; number >= 10; number /= 10, ++digits_cnt);

    return digits_cnt;
}

// *****************************************************************************
