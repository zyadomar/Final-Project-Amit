/*
 * FP_PROGRAM.c
 *
 *  Created on: 25 Nov 2021
 *      Author: Zyad_
 */

#include"STD_TYPES.h"

void Shift(u8 Size_Arr ,u8 *Arr)
{
	u8 x;
	u8 *temp;
	temp=&Arr[Size_Arr-1];
    for(x=Size_Arr-1;x>0;x--)
	{
	     Arr[x]=Arr[x-1];
	}
	Arr[0]=*temp;
}

u8 Avg_Calc(u8 Size_Arr ,u8 *Arr)
{
	u8 i;
	u8 sum;
	u8 avg;
    for (i = 0; i < Size_Arr; ++i)
    {
    sum += Arr[i];
    }
    avg = sum/Size_Arr;
	return avg;
}
