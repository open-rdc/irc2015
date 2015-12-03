#include "Comet.h"

//BusOut myled(LED1, LED2, LED3, LED4);

DigitalIn ll(p8),l(p7),r(p6),rr(p5);

void Line_Trace(int cross_line_count){
    int e,f,g,h;
    float limit = 0.2;
    int num = 0;
    float timer = 0.0;
    int count = 0;
    
    PID(150, 150);
    wait(DELTA_T);
    PID(300, 300);
    wait(DELTA_T);
    
    while( count != cross_line_count ){
        
        e = ll.read();
        num += e;
        num = num << 1;
        
        f = l.read();
        num += f;
        num = num << 1;
        
        g = r.read();
        num += g;
        num = num << 1;
        
        h = rr.read();
        num += h;
        
        if(num == 0 || num == 1  || num == 8){
            if(timer > limit){
                timer = 0.0;
                count++;
                //printf("%d\n",count);
            }
            PID(450, 450);
        }    
/*
        else if(num == 7 || num == 11)                          //l が反応
            PID(45, 400);                       //-100,600
        else if(num == 13 || num == 14)                          //r が反応
            PID(400, 55);
        else                                   //その他は前進
            PID(400, 400);
*/
        else if(num == 11)                      //l反応
            PID(190, 450);
        else if(num == 3 || num == 7)           //ll, ll+l反応
            PID(35, 450);
        else if(num == 13)                      //r反応
            PID(450, 55);
        else if(num == 12 || num == 14)         //rr, rr+r反応
            PID(450, 40);
        else
            PID(450, 450);
        num = 0;
        timer += DELTA_T;
    }
    PID(300, 300);
    wait(DELTA_T);
    PID(150, 150);
    wait(DELTA_T);
    stop();
    l_odometry_reset();
}

void Line_Trace(){
    int e,f,g,h;
    int num = 0;
        
    e = ll.read();
    num += e;
    num = num << 1;
        
    f = l.read();
    num += f;
    num = num << 1;
        
    g = r.read();
    num += g;
    num = num << 1;
        
    h = rr.read();
    num += h;
          
    if(num == 7 || num == 11)                          //l が反応
        PID(200, 350);                       
    else if(num == 13 || num == 14)                          //r が反応
        PID(350, 200);
    else                                   //その他は前進
        PID(350, 350);
}