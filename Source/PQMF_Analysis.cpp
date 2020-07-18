/*
  ==============================================================================

    PQMF_Analysis.cpp
    Created: 19 May 2019 9:58:00pm
    Author:  MAC

  ==============================================================================
*/

#include "PQMF_Analysis.h"

float *PQMF_Analysis::PQMF_Filtering(float x[]){
    
    block_index %= 16;
    jj = 0;
    for(int i = 0; i < 512; i++) {
        jj = i + 480 - block_index*32;
        if (i >= 32*(block_index + 1)){
            jj = i - 32*(block_index + 1);
        }
        z[i] = c[i] * x[jj];
    }
    
    block_index++;
    
    for (auto r = 0; r < 64; r++) {
        part_sum = 0;
        for (auto j = 0; j < 8; j++){
            part_sum = part_sum + z[r + 64*j];
        }
        s[r] = part_sum;
    }
    
    static float y[32];
    
    for (auto k = 0; k < 32; k++){
        part_sum2 = 0;
        for (auto r = 0; r < 64; r++){
            part_sum2 += M_k_r[k][r] * s[r];
            //part_sum2 += cos((k+0.5)*(r-16)*(M_PI/32)) * s[r];
        }
        y[k] = part_sum2;
    }
    
    return y;
}


// Frequency inversion
/*
 if ((block_index) % 2 == 1){
 for(int i = 1; i <= 32; i+=2){
 y[i] = -y[i];
 }
 }
 */
