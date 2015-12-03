#include "Comet.h"
#include "QEI.h"

#define PI 3.141592

QEI r_wheel(p28, p27, NC , ROTATE_PER_REVOLUTION ,QEI::X4_ENCODING);
QEI l_wheel(p29, p30, NC , ROTATE_PER_REVOLUTION ,QEI::X4_ENCODING);

//�t�@�C�����g���Ƃ��ɊO��
//LocalFileSystem local("local");
DigitalOut myled(LED4);

//Ticker encoder;     //�G���R�[�_�p���荞��
Ticker odome;       //�I�h���g���p���荞��

float l_Rad=0.0;
float g_Rad=0.0;       //�O���[�o�����W�n�̊p�x[rad]
int cnt = 0, n = 0;

//���荞�ݎ����̊֌W��wait�������Ȃ��Ă�OK
void encoder_read(){
    r_pulses = r_wheel.getPulses();    l_pulses = l_wheel.getPulses();
    r_wheel.reset();        l_wheel.reset();
}

//�I�h���g���̌v�Z
void odometry(){
    float v;       //���݂̑��x 
    r_pulses = r_wheel.getPulses();    l_pulses = l_wheel.getPulses();
    
    //�p���x�̌v�Z
    //�p���x���p���X�̕΍���(1��]������̃p���~����\)���ǂݍ��ݎ��ԁ��M�A��~�Q��
    r_omega = (float)r_pulses / (ROTATE_PER_REVOLUTION * BUNKAINOU ) / DELTA_T / GEAR * PI * 2.0;
    l_omega = (float)l_pulses / (ROTATE_PER_REVOLUTION * BUNKAINOU ) / DELTA_T / GEAR * PI * 2.0;
    
    //�S�̂̑��x�C�p���x�̌v�Z
    v = WHEEL_RADIUS * (r_omega + l_omega) /2.0;
    omega = WHEEL_RADIUS *( r_omega - l_omega ) / T;
        
    //�p�x���v�Z
    l_Rad = omega * DELTA_T;
    g_Rad += l_Rad;
    l_theta += l_Rad * 180.0 / PI;
    g_theta = g_Rad * 180.0 / PI;
    
    //���W�̌v�Z

    l_X += v * sin(l_Rad) * DELTA_T;
    l_Y += v * cos(l_Rad) * DELTA_T;
    g_X += v * sin(g_Rad) * DELTA_T;
    g_Y += v * cos(g_Rad) * DELTA_T;
/*    cnt++;
    if(cnt == 25){
        coordinates[n][0] = l_X;
        coordinates[n][1] = l_Y;
        coordinates[n][2] = l_theta;
        n++;
        cnt = 0;
    }
//    printf("%lf, %lf, %lf\n", l_X, l_Y, l_theta);
*/    
    r_wheel.reset();        l_wheel.reset();
    l_time += DELTA_T;
}


///*
//���荞�݂̏��������邩�ǂ����̊֐�
//�����̕ϐ���int�^�ł�OK bool�ł�OK������
//flag ��ON �̎��͊��荞�݂�������
//�����̊��荞�ݓ��Ԋu�ōs���ꍇ�͏�ɂ�������珈�����Ă���
void switch_encoder(){
    r_wheel.reset();        l_wheel.reset();
    if(encoder_flag){
        //�����Ŋ��荞�݊J�n
//        encoder.attach(&encoder_read, DELTA_T);
        odome.attach(&odometry, DELTA_T);
    }
    else{
        //�����Ŋ��荞�ݏI��
//        encoder.detach();
        odome.detach();
    }
}
//*/

/*
void switch_file(){
    if(file_flag){
        FILE *fp;

        if( (fp = fopen( "/local/TEST.TXT", "w" )) == NULL )
            error( "" );
        else{
            myled = 1;
            for( int i = 0; i < n; i++ ) {
                fprintf( fp, "%lf %lf %lf\n", coordinates[i][0], coordinates[i][1], coordinates[i][2] );
                wait(0.1);
            }
            myled = 0;
            fclose(fp);
            //servo_throw();
        }
    }
    else{
    }
}
*/

///*
//���[�J���ȃI�h���g���̃��Z�b�g
//�����Ȃ��Ƃ���Ń��Z�b�g����̂͂ǂ����Ǝv�����ǁE�E�E
void l_odometry_reset(){
    l_X = 0.0;
    l_Y = 0.0;
    l_theta = 0.0;
}
//*/