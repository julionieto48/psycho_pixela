/*
  ==============================================================================

    IPQMF_Synthesis.h
    Created: 19 May 2019 9:58:18pm
    Author:  MAC

  ==============================================================================
*/

#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>

extern float d[512];

class IPQMF_Synthesis{
public:
    
    IPQMF_Synthesis(){
        memset(v, 0, sizeof(v));
        memset(u, 0, sizeof(u));
        memset(w, 0, sizeof(w));
        part_sum = 0;
        part_sum2 = 0;
        
        //cálculo de la matriz moduladora N para la síntesis
        for(int k = 0; k < 32; k++){
            for (int r = 0; r < 64; r++) {
                N_k_r[k][r] = cos((2*k+1)*(r+16)*(M_PI/64));
            }
        }
    };
    
    ~IPQMF_Synthesis(){};
    
    float *IPQMF_Filtering(float y[]);
    
private:
    
    float v[1024];
    float u[512];
    float w[512];
    float N_k_r[32][64];
    float part_sum, part_sum2;
};
