#include "Comet.h"

DigitalOut L1(LED1),L2(LED2),L3(LED3),L4(LED4);

//�S�̂̏������̏���
void initialize(){
    l_time = 0.0;                                 //���Ԃ̏�����
    stop();         wait(1);                    //�d������ꂽ����̓��[�^����]���邽�ߎ~�߂Ă����K�v����                   
    servo_ini();                                //�T�[�{�̏����p�� 
    wait(0.5);                              
    r_pulses = 0;   l_pulses = 0;               //�p���X�̏�����
    serch_data[1][0] = 0.0;
    g_X = g_Y = g_theta = 0.0;                  //�I�h���g���̏�����
    l_odometry_reset();
    l_theta = 0;                                //���[�J���p�x�̏�����
    serch_data[1][0]= 0.0;                      //0=�߂���  1����     dis�Cdeg
    encoder_flag = ON;  switch_encoder();       //�G���R�[�_�̃t���OON   ���������p���X�̏���(�O�̂���)
    move_flag = OFF;    
}

void fine(){//�I�������鎞�̏���
            //�p�t�H�[�}���X�Ƃ�����
    turn(180,FAST);
    if(color != YELLO)
        Line_Trace(4 - color);
    else
        Line_Trace(5 - color);
    
    //�����悤�E�E�E(* _��_)...
    while(l_Y <= 250)
        PID(100, 100);
    turn(180, FAST);
    wait(0.5);
    servo_performance();
    while(1){
        PID(0,0);
    }
}