#include <unistd.h>
#include <stdarg.h>

void ft_putstr(char *str, int *len)
{
    int i = 0;

    if (!str)
        str = "(null)";
    while (str[i])
    {
        *len += write(1, &str[i], 1);
        i++;
    }
}

void    ft_putnbr(long long int nbr, int base, int *len)
{
    char *str = "0123456789abcdef";

    if (nbr < 0)
    {
        nbr *= -1;
        *len += write(1, "-", 1);
    }
    if (nbr > base)
        ft_putnbr(nbr / base, base, len);
    *len += write(1, &str[nbr % base], 1);
}

int ft_printf(const char *str, ...)
{
    int len = 0;
    int i = 0;
    va_list ap;

    va_start(ap, str);
    while (str[i])
    {
        if (str[i] == '%' && (str[i + 1] == 's' || str[i + 1] == 'd' || str[i + 1] == 'x'))
        {
            i++;
            if (str[i] == 's')
                ft_putstr(va_arg(ap, char *), &len);
            else if (str[i] == 'd')
                ft_putnbr((int)va_arg(ap, int), 10, &len);
            else if (str[i] == 'x')
                ft_putnbr((long long int)va_arg(ap, unsigned int), 16, &len);
            i++;
        }
        else
        {
            len += write(1, &str[i], 1);
            i++;
        }
    }
    va_end(ap);
    return (len);
}