#include "Comet.h"

DigitalOut L1(LED1),L2(LED2),L3(LED3),L4(LED4);

//全体の初期化の処理
void initialize(){
    stop();         wait(1);                    //電源を入れた直後はモータが回転するため止めておく必要あり                   
    servo_ini();                                //サーボの初期姿勢 
    wait(1);                              
    r_pulses = 0;   l_pulses = 0;               //パルスの初期化
    serch_data[1][0] = 0.0;
    g_X = g_Y = g_theta = 0.0;                    //オドメトリの初期化
    l_odometry_reset();
    l_theta = 0;                                //ローカル角度の初期化
    serch_data[1][0]= 0.0;    //0=近い方  1＝今     dis，deg
    encoder_flag = ON;  switch_encoder();       //エンコーダのフラグON   ＆もう一回パルスの初期(念のため)
    move_flag = OFF;    //file_flag = OFF;
}

void turn_on1(){
    L1 = 1;
    wait(0.5);
    L1 = 0;
}

void turn_on2(){
    L2 = 1;
    wait(0.5);
    L2 = 0;
}
void fine(){//終了させる時の処理
            //パフォーマンスとかかな
    servo_throw();
    while(1){
        PID(0,0);
    }
}






