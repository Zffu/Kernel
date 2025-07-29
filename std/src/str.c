#include <str.h>
#include <stdint.h>

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

int uint_to_str(unsigned int value, char *out) {
    int i = 0;
    if (value == 0) {
        out[i++] = '0';
    } else {
        while (value) {
            out[i++] = '0' + (value % 10);
            value /= 10;
        }
    }
    out[i] = '\0';

    reverse(out);
    return i;
}

void float_to_string(float f, char *out, int precision) {
    if (f < 0) {
        *out++ = '-';
        f = -f;
    }

    unsigned int int_part = (unsigned int)f;
    float frac_part = f - (float)int_part;

    int len = uint_to_str(int_part, out);
    out += len;

    *out++ = '.';

    // Multiply fractional part to required precision
    for (int i = 0; i < precision; ++i) {
        frac_part *= 10;
    }

    unsigned int frac_int = (unsigned int)(frac_part + 0.5f); // round
    len = uint_to_str(frac_int, out);
    out[len] = '\0';
}

void byte_to_hex(unsigned char byte, char *out) {
    const char hex_chars[] = "0123456789ABCDEF";
    out[0] = hex_chars[(byte >> 4) & 0x0F];  // high nibble
    out[1] = hex_chars[byte & 0x0F];         // low nibble
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

int strlen(char* s) {
    int len = 0;
    char c;
    while(c = *s++) {
        ++len;
    }
    return len;
}