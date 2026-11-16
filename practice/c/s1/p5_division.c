
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    printf("%d\n", 5/2);
    printf("%d\n", 5%2);
    printf("%f\n", 5.0/2);
    printf("%f\n", (float)5/2);
    printf("%f\n", (float)(5/2));
    uint16_t counts = 3156;
    float bad = counts/ 4095 * 3.3f;
    float good = counts * 3.3f /4095;
    printf("%.3f Vbad, %.3f Vgood\n", bad,good);
    return 0;
}
