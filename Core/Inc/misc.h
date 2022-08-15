#pragma once

float float_constraint(float x, float min, float max)
{
    if(x > max) x = max;
    if(x < min) x = min;
    return x;
}


int int_constraint(int x, int min, int max)
{
    if(x > max) x = max;
    if(x < min) x = min;
    return x;
}