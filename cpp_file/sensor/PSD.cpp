#include "Comet.h"
#define NUM 3      //�ǂݍ��ރf�[�^��

//PSD�Z���T�̓ǂݍ��݂ƃt�B���^�����O���邽�߂̂���

AnalogIn high(p20),low(p19);     

//�\�[�g�p�t���Oqsort�Ŏg��
int float_sort(const void* x,const void* y) {
    const float* high=(const float*)x;
    const float* low=(const float*)y;
    if(*high>*low)return 1;
    if(*high<*low)return -1;
    return 0;
}

//PSD�̒l���擾����֐��~2
float Get_PSD_high() {
    float data[NUM] = {};
    int i;
    
    for(i = 0; i < NUM; i++){
        data[i] = high.read();
//        wait(PSD_DELTA_T);
    }
    
    qsort(data, NUM, sizeof(float), float_sort);

    return data[(NUM - 1) / 2];
}

float Get_PSD_low() {
    float data[NUM] = {};
    int i;
    
    for(i = 0; i < NUM; i++){
        data[i] = low.read();
    }
    
    qsort(data, NUM, sizeof(float), float_sort);

    return data[(NUM - 1) / 2];
}

void PSD_reset(){
    serch_data[0][0] = 0.0;
    serch_data[0][1] = 0.0;
    serch_data[1][0] = 0.0;
    serch_data[1][1] = 0.0;
}