
#include <stdio.h>

#include <stdint.h>

int main(void)
{
    char grade = 'A';
    int step = 5;
    long big = 100000;
    float temp_c = -18.0f;
    double energy_j = 900.0;
    uint8_t duty_pct = 80;
    uint16_t counts = 3156;
    int16_t current_raw = -10;
    uint32_t ms = 60000;
    uint8_t u = 255;
    u = u + 1;
    uint16_t raw = 0xFFF6;

    printf("char:     %zu bytes\n", sizeof(grade));
    printf("int:      %zu bytes\n", sizeof(step));
    printf("long:     %zu bytes\n", sizeof(big));
    printf("float:    %zu bytes\n", sizeof(temp_c));
    printf("double:   %zu bytes\n", sizeof(energy_j));
    printf("uint8_t:  %zu bytes\n", sizeof(duty_pct));
    printf("uint16_t: %zu bytes\n", sizeof(counts));
    printf("int16_t:  %zu bytes\n", sizeof(current_raw));
    printf("uint32_t: %zu bytes\n", sizeof(ms));
    printf("u: %u\n", u);
    printf("raw: %u\n", raw);
    printf("int16_t raw: %d\n", (int16_t)raw);


    

    
    return 0;}