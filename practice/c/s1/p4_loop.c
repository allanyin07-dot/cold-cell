
#include <stdio.h>

float divider_vout(float vin, float r1, float r2)
{
    return vin*r2/(r1 + r2);
}

int main(void)
{
    float vin[10] = {5.0f, 3.3f, 3.3f, 3.3f, 5.0f, 12.0f, 4.2f, 3.3f, 3.7f, 3.3f};
    float r1[10]  = {10000, 10000, 10000, 10000, 1000, 100000, 100000, 220, 15000, 10000};
    float r2[10]  = {10000, 10000, 4700, 22000, 2200, 15000, 100000, 1000, 10000, 33600};
    printf(" #  Vout (V)  I (mA)\n");
    for (int i = 0; i < 10; i++)
    {
        float vout = divider_vout(vin[i], r1[i], r2[i]);
        float current_ma = vin[i]/(r1[i] + r2[i])*1000.0f;
        printf("%2d  %.3f    %.4f\n", i+1, vout, current_ma);
    }
    return 0;
}

