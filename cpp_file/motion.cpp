#include "Comet.h"


///*停止用関数
void stop(){
    int l = 40, r = 40;
    //徐々に下げていく感じ
    for(float n = 0.0; n < 0.02; n += DELTA_T){   
        PID(l,r);
        l -= 10;
        r -= 10;
    }
    for(float i = 0.0; i < 0.2; i += DELTA_T){
        l_integral=0;   r_integral=0;
        PID(0,0);
    }
}



//ボール発見用関数
void tansaku(){
    serch_data[1][0] = Get_PSD_low();   serch_data[1][1] = l_theta;
    float high = Get_PSD_high();
    
    //条件は後で変えよう
    if(high >= 0.4){   //high >= 0.24
        if(serch_data[0][0] < serch_data[1][0] ){   //更新
            serch_data[0][0] = serch_data[1][0];
            serch_data[0][1] = serch_data[1][1];
         }
    }
}

///*回転用関数
//角度＆早い方と遅い方の2つのモードを指定する
//引数のdegはどれくらい回転したいかの角度
void turn(float deg, bool mode){
    l_odometry_reset();
    if(mode){       //早い方
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 4.0){   //右回転
                PID(200,-200);
            }       
        }
        else{
            while( ( l_theta - deg ) < -4.0){   //左回転
                PID(-200,200);
            }
        }
    }
    else{       //遅い方あとは同上
        if(l_theta > deg ){
            while( ( l_theta - deg ) > 1.5){   //右回転
                tansaku();
                PID(100,-100);
             }
        }
        else{
            while( ( l_theta - deg ) < -1.5){   //左回転
                tansaku();
                PID(-100,100);
            }
        }
    }
    stop();
}
//*/

///*
//グローバル座標系で回転する関数
//制度がなー(´;ω;｀)
void g_turn(float deg){
    l_odometry_reset();
    if(g_theta > deg ){
        while( ( g_theta - deg ) > 0.1){   //右回転
            PID(200,-200);
        }
    }
    else{
        while( ( g_theta - deg ) < -0.1){   //左回転
            PID(-200,200);
        }
    }
    stop();
}
//*/

///*
//探索用関数
void serch(){
//    l_odometry_reset();
    PSD_reset();
    turn(-90,FAST);
    turn(180,SLOW);
    
    if( serch_data[0][0] == 0.0 ){
        turn(-90, FAST);
        move_flag = ON;
    }
    else{
        turn(serch_data[0][1]-175,FAST);
        stop();
        Ball_Catch();
    }
}
//*/

///*
//ボールをキャッチする関数
void Ball_Catch(){
    float serch_dis = 66.294 * pow((double)serch_data[0][0], -1.218);
    wait(0.5);
    l_odometry_reset();
    wait(0.5);
    
    if(serch_dis <= 350 ){
       servo_ready();
       while(l_Y <= serch_dis - 80)
            PID(150, 150);
        stop();
        servo_catch();
        while(l_Y >= 5)
            PID(-150, -150);
        stop();
        turn(-1 * serch_data[0][1] + 90, FAST);
        wait(0.5);
    }
    else{
        turn(-92, FAST);
        move_flag = ON;
        l_odometry_reset();
        PSD_reset();
    }
}
//*/


///*
//回収用関数
void Ball_Shoot(){
    if(color == RED || color == YELLO){     //赤か黄色だったら右を向くよ
        turn(-80, FAST);  
    }
    if(color == BLUE ){                     //青だったら少し前進するよ
        for(float i = 0.0; i < 1.0; i += DELTA_T){
            PID(350,350);
        }
        stop();
    }
    
    wait(1);
    servo_throw();
    wait(1);
    
    servo_up2();
    wait(1);
    
    if(color == RED || color == YELLO){
        turn(-100, FAST);
        wait(1);
    }
    else if( color == BLUE){
        for(float i = 0.0; i < 1.0; i += DELTA_T){
            PID(-200,-200);
        }
        stop();
        turn(180, FAST);
        wait(1);
    }
}
//*/