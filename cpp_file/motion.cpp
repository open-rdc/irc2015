#include "Comet.h"


///*��~�p�֐�
void stop(){
/*    int l = 50, r = 50;
    //���X�ɉ����Ă�������
    for(float n = 0.0; n < 0.02; n += DELTA_T){   
        PID(l,r);
        l -= 10;
        r -= 10;
    }
*/    for(float i = 0.0; i < 0.2; i += DELTA_T){
        l_integral=0;   r_integral=0;
        PID(0,0);
    }
}



//�{�[�������p�֐�
void tansaku(){
    serch_data[1][0] = Get_PSD_low();   serch_data[1][1] = l_theta;
    float high = 66.294 * pow((double)Get_PSD_high(), -1.218);
    
    //�����͌�ŕς��悤
    if(high <= 360){   //high >= 0.24
        if(serch_data[0][0] < serch_data[1][0] ){   //�X�V
            serch_data[0][0] = serch_data[1][0];
            serch_data[0][1] = serch_data[1][1];
         }
    }
}

///*��]�p�֐�
//�p�x���������ƒx������2�̃��[�h���w�肷��
//������deg�͂ǂꂭ�炢��]���������̊p�x
void turn(float deg, bool mode){
    l_odometry_reset();
    if(mode){       //������
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 5.0){   //�E��]
                PID(250,-250);
            }       
        }
        else{
            while( ( l_theta - deg ) < -5.0){   //����]
                PID(-250,250);
            }
        }
    }
    else{       //�x�������Ƃ͓���
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 1.5){   //�E��]
                tansaku();
                PID(100,-100);
             }
        }
        else{
            while( ( l_theta - deg ) < -1.5){   //����]
                tansaku();
                PID(-100,100);
            }
        }
    }
    stop();
}
//*/

///*
//�O���[�o�����W�n�ŉ�]����֐�
//���x���ȁ[(�L;��;�M)
void g_turn(float deg){
    l_odometry_reset();
    if(g_theta > deg ){
        while( ( g_theta - deg ) > 0.1){   //�E��]
            PID(200,-200);
        }
    }
    else{
        while( ( g_theta - deg ) < -0.1){   //����]
            PID(-200,200);
        }
    }
    stop();
}
//*/

///*
//�T���p�֐�
void serch(){
//    l_odometry_reset();
    PSD_reset();
    turn(-90,FAST);
    turn(180,SLOW);
    
    if( serch_data[0][0] == 0.0){
        turn(-90, FAST);
        color = NO_BALL;
        move_flag = ON;
        l_odometry_reset();
    }
    else
        Ball_Catch();
}
//*/

///*
//�{�[�����L���b�`����֐�
void Ball_Catch(){
    float serch_dis = 66.294 * pow((double)serch_data[0][0], -1.218);
    l_odometry_reset();
    wait(0.25);
    
    if(serch_dis <= 350 ){      //�T���G���A�̕��I��400�͗~�������ǌ덷���Ȃ�...
        turn(serch_data[0][1]-174,FAST);
        stop();
        wait(0.25);
        servo_ready();
        while(l_Y <= serch_dis - 80)     //serch_dis - 80
            PID(150, 150);
        stop();
        servo_catch();
        while(l_Y >= 5)
            PID(-150, -150);
        stop();
        wait(0.25);
        color = what_color();
        if(color != NO_BALL){
            if(serch_data[0][1] <= 90)
                turn(-1 * serch_data[0][1] - 90, FAST);     //��������(�E��])
            else
                turn(-1 * serch_data[0][1] + 270, FAST);     //��������(����])
        }
        else
            turn(-1 * serch_data[0][1] + 90, FAST);     //���ʂ�����
        wait(0.25);
    }
    else{
        turn(-92, FAST);        //-92 �͏��׍H...
        color = NO_BALL;
        move_flag = ON;
        l_odometry_reset();
    }
    PSD_reset();
}
//*/


///*
//����p�֐�
void Ball_Shoot(){
    if(color == RED)     //���F�͐̂Ƃ��납�瓊�����[
        turn(-80, FAST);  
    else if(color == YELLO)
        turn(40, FAST);
    
    wait(0.25);
    servo_throw();
    wait(0.25);
    
    servo_ini();
    wait(0.25);
    
    if(color == RED)
        turn(-100, FAST);
    else if(color == YELLO)
        turn(140, FAST);
    else
        turn(180, FAST);
    wait(0.25);
}
//*/