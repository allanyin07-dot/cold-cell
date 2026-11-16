
#include <stdio.h>

int main(void)
{   float v = 3.7f;
    float r = 5.0f;
    float i = v / r;
    float p = v * i;
    printf("Heater: R = %.1f ohm, I = %.2f A\n", r, i);
    printf("Power (%%f)   = %f W\n", p);
    printf("Power (%%.2f) = %.2f W\n", p);
    printf("Power (%%.1f) = %.1f W\n", p);
    
    return 0;}