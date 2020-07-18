/*
  ==============================================================================

    PQMF_Analysis.h
  

  ==============================================================================
*/

#pragma once

#include <math.h>
#include <cstring>
#include <iostream>

extern float c[512];

class PQMF_Analysis{
public:
    PQMF_Analysis(){
        memset(z, 0, sizeof(z));
        memset(s, 0, sizeof(s));
        part_sum = 0;
        part_sum2 = 0;
        block_index = 0;
        num_blocks = 16;
        jj = 0;
        
        //cálculo de la matriz moduladora M para el análisis
        for(int k = 0; k < 32; k++){
            for (int r = 0; r < 64; r++) {
                M_k_r[k][r] = cos((k+0.5)*(r-16)*(M_PI/32));
            }
        }
    };
    
    ~PQMF_Analysis(){};
    
    float *PQMF_Filtering(float x[]);
    
private:
    int block_index, num_blocks, jj;
    float z[512];
    float s[64];
    float M_k_r[32][64];
    float part_sum, part_sum2;
};






