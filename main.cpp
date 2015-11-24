#define GLOBAL_INSTANCE
#include "Comet.h"

/*
int main(){     //本走行用  (これから書いていく)
    
    initialize();
    int color;
    int ball_count = 0;
    bool area_flag = OFF;
    state = INIT_STATE;

    while(1){
        switch(state){
            case INIT_STATE:
                initialize();
                state = FREE_BALL;
                break;
            case FREE_BALL:
                Line_Trace(2);
                Ball_Shoot();
                Line_Trace(2);
                state = BALL_SEARCH;
                break;
            case BALL_SEARCH:
                serch();
                if(move_flag){
                    state = AREA_MOVE;
                }
                else{
                    g_turn(0.0);
                    if(area_flag){
                        Line_Trace(1);
                    }
                    state = BALL_SHOOT;
                }
                break;
            case BALL_SHOOT:
                color = what_color();
                Line_Trace(color);
                Ball_Shoot();
                ball_count++;
                if(ball_count == 15){
                    state = FINISH;
                }
                else{
                    Line_Trace(color);
                    state = BALL_SEARCH;
                }
                break;
            case AREA_MOVE:
                g_turn(180);
                for(float i = 0; i < 4; i+=DELTA_T){
                    PID(100, 100);
                }
                for(float i=0; i<0.5; i+=DELTA_T){
                    stop();
                }
                move_flag = OFF;
                area_flag = ON;
                state = BALL_SEARCH;
                break;
            case FINISH:
                Line_Trace(4 - color);
                g_turn(0);
                while(1){
                    stop();
                }
        }        
    }
}
*/

//-----------------------------------------------------------------------------------

/*
int main(){
    initialize();
    int ball_count = 0;
    
    g_turn(180);
    while(ball_count < 3){
        serch();
        g_turn(0);
        wait(1);
        for(int i = 0; i < 2; i++){
            color = what_color();
        }
    
        Line_Trace(color);
        if(color != NO_BALL){
            Ball_Shoot();
            ball_count++;
        }
        Line_Trace(color);
        
        l_odometry_reset();
        turn(180, FAST);
        g_theta = 0.0;
        
        wait(2);
    }
    while(1){
        stop();
    }
}
*/

//--------------------------------------------------------------------------------------

/*
int main(){     //ボールシュート確認用    (ボールは手動でカップに乗せる)
    initialize();
    
    int ball_count = 0;
//    state = INIT_STATE;

    while(ball_count < 15){
        wait(1);
        for(int i = 0; i < 2; i++){
            color = what_color();
        }
    
        Line_Trace(color);
        if(color != NO_BALL){
            Ball_Shoot();
            ball_count++;
        }
        Line_Trace(color);
        
        l_odometry_reset();
        turn(180, FAST);
        g_theta = 0.0;
        
        wait(2);
    }
}
*/

//----------------------------------------------------------------------------------------------------------

/*
int main(){     //エリア移動確認用
    initialize();
    bool area_flag = OFF;
    
    while(1){
        serch();
        color = what_color();
        g_turn(0);
        if(color != 0){
            move_flag = OFF;
            printf("a");
        }
        if(move_flag){
            for(float i = 0; i < 1.5; i+=DELTA_T){
                PID(200, 200);
            }
            PSD_reset();
            area_flag = ON;
            
        }
        else{
            printf("\n");
            turn(180, FAST);
            if(area_flag){
                Line_Trace(1);
            }
        }
    }
}
*/

//-------------------------------------------------------------------------------------------------------------------

/*
int main(){     //Line_Trace 確認用   (特に曲がり角)
                //Line_Trace 関数を少し変える必要あり
    initialize();
    
    while(1){
        Line_Trace(1);
        turn(180.0,FAST);
        stop();
    }
}
*/

//--------------------------------------------------------------------------------------------------------------------------

/*
int main(){     //カラー閾値確認用
    initialize();
    
    while(1){
        what_color();
    }
}
*/

//--------------------------------------------------------------------------------------------------------------------------

/*
int main(){
    initialize();
    int mode = 1;       //0:turn, 1:g_turn
    
    while(1){
        if(mode == 0){
            turn(180, FAST);
            turn(180, FAST);
        }else if(mode == 1){
            g_turn(0);
            g_turn(180);
        }
    }
}
*/

//-----------------------------------------------------------------------------------------------------------------------------

/*
int main(){     //PID調整用
    initialize();
    int l = 450, r = 450;
    
    while(1){
       for(float i = 0; i < 1.0; i+=DELTA_T){
            PID(l, r);
        }
        stop();
        wait(1);
        for(float i = 0; i < 1.0; i+=DELTA_T){
            PID(-l, -r);
        }
        stop();
        wait(1);
        
        l -= 50;
        r -= 50;
        
        if(l == 0 || r == 0) break;
    }
    
    stop();
}
*/

//-------------------------------------------------------------------------------------------------------------

/*
int main(){     //サーボ動作確認用
//    servo_ini();
    wait(1);
//    servo_throw();
    servo_ready();
//    servo_up();
    servo_catch();
}
*/

//-------------------------------------------------------------------------------------------------------------        

/*
int main(){     //探索動作確認用
    initialize();
    serch(); 
}
*/

//-------------------------------------------------------------------------------------------------------------

///*
int main(){     //第3回試走会用
    int ball_count = 0;
    bool area_flag = OFF;
    float serch_posi = 0.0;
    float move_dis = 0.0;
    state = INIT_STATE;
//    color = RED;    
    while(1){       //while開始
        switch(state){
            case INIT_STATE:
                initialize();
                state = FREE_BALL;
                //state = BALL_SEARCH;
                break;
            
            case FREE_BALL:
                Line_Trace(3);
                turn(85.0, FAST);
                wait(0.5);
                servo_throw();
                wait(0.3);
                servo_ini();
                wait(0.3);
                turn(-85.0,FAST);
                Line_Trace(2);
                state = BALL_SEARCH;
                break;
                
            case BALL_SEARCH:
                    
                if(move_flag){
                    while(l_Y <= move_dis)
                        PID(200, 200);
                    stop();
                    move_flag = OFF;
                    turn_on1();
                }
                else{
                    if(color != NO_BALL){
                    while(l_Y <= serch_posi)
                    PID(200, 200);
                    stop();
                    turn_on2();
                    }
                }
            
                wait(0.5);
                serch();
                state = BALL_SHOOT;
                break;
                
            case BALL_SHOOT:
                wait(0.5);
                wait(0.5);
                color = what_color();
                if(color != 4){         //色を得られたら
                    turn(180, FAST);
                    wait(0.5);
                    if(area_flag)
                        Line_Trace(color + 1);
                    else
                        Line_Trace(color);
                    Ball_Shoot();
                    Line_Trace(color);
                    ball_count++;
                }
                state = BALL_SEARCH;
                
                if(move_flag)
                    state = AREA_MOVE;
                if(ball_count == 15)     //ボールを3個回収したら終了モーションへ
                    state = FINISH;
                break;
                
            case AREA_MOVE:
                move_dis = 200;
                serch_posi += move_dis;
                area_flag = ON;
                state = BALL_SEARCH;
                break;
            
            case FINISH:
                fine();
                break;
            
        }//switch終了
    }//while終了
}//main終了
//*/