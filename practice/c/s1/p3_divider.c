
#include <stdio.h>

float divider_vout(float vin, float r1, float r2)
{
    return vin*r2/(r1 + r2);
}

int main(void)
{
    printf("Divider #3:  Vout = %.4f V\n", divider_vout(3.3f, 10000.0f, 4700.0f));
    printf("Divider #10: Vout = %.4f V\n", divider_vout(3.3f, 10000.0f, 33600.0f));
    return 0;
}