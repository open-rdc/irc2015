#include "Comet.h"

//PI����̌v�Z�Əo�͂̊֐��������[(�O���O)
//�֐�����PID�Ȃ̂�PI����Ȃ͓̂˂����܂Ȃ���(�L��֥�M)

//�E�ԗ֗p
PwmOut r_cw(p22);
DigitalOut r_ccw(p12);

//���ԗ֗p
PwmOut l_cw(p23);
DigitalOut l_ccw(p11);

//�Ƃ肠������ɐ錾���Ă���
void l_motor(float l_speed, int l_terget_speed);
void r_motor(float r_speed, int r_terget_speed);

void PID(int l_terget, int r_terget){
    float l_speed,r_speed;             //���݂̍��E�̃X�s�[�h
    float l_hensa,r_hensa;             //���E���ꂼ��̕΍�     �p�ꂾ�Ƃ悭�킩��Ȃ��̂Ń��[�}���ɂ���
    float l_output,r_output;           //�o�͗p
    
    //���x�̌v�Z
    //���荞�ݏ����̒i�K�Łv���ꂼ��̊p���x���킩���Ă���̂ŁC��������e�ԗւ̑��x���v�Z���Ă���
    l_speed = l_omega * WHEEL_RADIUS;
    r_speed = r_omega * WHEEL_RADIUS;
    
//    printf("%lf\t%lf\n", l_speed, r_speed);
    
    //�΍��̎擾
    l_hensa = l_speed - l_terget;
    r_hensa = r_speed - r_terget;
  //  printf("%lf\n",l_hensa);
    
    //�΍��̒~�ρi�ϕ��v�Z�j
    l_integral += l_hensa * DELTA_T;
    r_integral += r_hensa * DELTA_T;
    
    //�ϕ�����̐ݒ�
    if(l_integral >= 600)    l_integral = 600;
    if(l_integral < -600)    l_integral = -600;
    if(r_integral >= 600)    r_integral = 600;
    if(r_integral < -600)    r_integral = -600;
    
    //�o�͂̌v�Z
    //���̒i�K�Ńf���[�e�B�[��ɂ��Ă���
    l_output = (PID_L_KP * l_hensa + PID_L_KI * l_integral) / 100;
    r_output = (PID_R_KP * r_hensa + PID_R_KI * r_integral) / 100;
    
//    printf("%lf\t%lf\n", l_output, r_output);
    
    //�o��
    l_motor(l_output,l_terget);       
    r_motor(r_output,r_terget);
    wait(DELTA_T);
}

//�����[�^�o�͗p�֐�
//�����͍��o�́����ڕW
void l_motor(float l_speed, int l_terget_speed){
    float L = fabs(l_speed);     //��Βl�ɂ��邽�߂Ɏg�p
    if(l_speed >=0 && l_terget_speed >= 0){         //���]�����ǖڕW�܂ő���Ȃ�
        l_cw = L;   l_ccw=0;
    }
    else if( l_speed < 0 && l_terget_speed >= 0){   //���]�����ǖڕW��ʂ�߂���
        l_cw = L;   l_ccw=1;
    }
    else if( l_speed >= 0 && l_terget_speed < 0){   //�t�]�����ǖڕW�܂ő���Ȃ�
        l_cw = L;   l_ccw=0;
    }
    else{                                           //�t�]�����ǖڕW��ʂ�߂���
        l_cw = L;   l_ccw=1;
    }
}
    
//�E���[�^�o�͗p�֐�
//�����͉E�o�́��E�ڕW
void r_motor(float r_speed, int r_terget_speed){
    float R = fabs(r_speed);     //��Βl�ɂ��邽�߂Ɏg�p
    if(r_speed >=0 && r_terget_speed >= 0){
        r_cw = R;   r_ccw=0;
    }
    else if( r_speed < 0 && r_terget_speed >= 0){
        r_cw = R;   r_ccw=1;
    }
    else if( r_speed >= 0 && r_terget_speed < 0){
        r_cw = R;   r_ccw=0;
    }
    else{
        r_cw = R;   r_ccw=1;
    }
}