#include "Comet.h"


///*停止用関数
void stop(){
/*    int l = 50, r = 50;
    //徐々に下げていく感じ
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



//ボール発見用関数
void tansaku(){
    serch_data[1][0] = Get_PSD_low();   serch_data[1][1] = l_theta;
    float high = 66.294 * pow((double)Get_PSD_high(), -1.218);
    
    //条件は後で変えよう
    if(high <= 360){   //high >= 0.24
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
            while( ( l_theta - deg ) > 5.0){   //右回転
                PID(250,-250);
            }       
        }
        else{
            while( ( l_theta - deg ) < -5.0){   //左回転
                PID(-250,250);
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
//ボールをキャッチする関数
void Ball_Catch(){
    float serch_dis = 66.294 * pow((double)serch_data[0][0], -1.218);
    l_odometry_reset();
    wait(0.25);
    
    if(serch_dis <= 350 ){      //探索エリアの幅的に400は欲しいけど誤差がなぁ...
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
                turn(-1 * serch_data[0][1] - 90, FAST);     //後ろを向く(右回転)
            else
                turn(-1 * serch_data[0][1] + 270, FAST);     //後ろを向く(左回転)
        }
        else
            turn(-1 * serch_data[0][1] + 90, FAST);     //正面を向く
        wait(0.25);
    }
    else{
        turn(-92, FAST);        //-92 は小細工...
        color = NO_BALL;
        move_flag = ON;
        l_odometry_reset();
    }
    PSD_reset();
}
//*/


///*
//回収用関数
void Ball_Shoot(){
    if(color == RED)     //黄色は青のところから投げるよー
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