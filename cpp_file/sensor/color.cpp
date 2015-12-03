#include "Comet.h"

I2C colorSensor(p9,p10);
int R,G,B,IR;       //�ԁC��,�C�ԊO
//�r���ɂ���wait�͂����炭�Œ�1�b�͂ق������ȁ[
//�Z���ƒl�擾���s�\������

//�J���[�Z���T�̒l���擾����֐�
void  get_color_value() {
    char data[8];
    int tmp;
    //start condition
    colorSensor.start();
    //device address
    colorSensor.write(0x54);
    //controll register
    colorSensor.write(0x00);
    //ADC reset enable
    colorSensor.write(0x84);

     //manual timing register 01
     colorSensor.write(0x01);
        
     //�l�ς���Ες��͂��E�E�E�i�����j
     //set manual timing reister 01
     colorSensor.write(0x03);
     //manual timing register 02
     colorSensor.write(0x02);
     //set manual timing register 02
     colorSensor.write(0xC0);
                
    //start condition
    colorSensor.start();
    //device address
    colorSensor.write(0x54);
    //controll register
    colorSensor.write(0x00);
    //ADC reset disable
    colorSensor.write(0x04);
    //stop condition
    colorSensor.stop();
    
    //������wait�Œች�b����[�H
    wait(1.0);
        
    //start condition
    colorSensor.start();
    //device address
     colorSensor.write(0x54);
    //output databyte set
    colorSensor.write(0x03);
            
    //read sensor
    colorSensor.read(0x55, data, 8);
        
    for(int i=0; i<8; i=i+2){
        tmp = data[i] << 8;  //16bit�ŏo������8bit�V�t�g
        tmp += data[i+1];
        //printf("%d\t",tmp);  
        if(i== 0){
            R = tmp;
        }else if(i == 2){
            G = tmp;
        }else if(i == 4){
            B = tmp;
        }else {
            IR = tmp;
        }
    }
    colorSensor.stop();
}

//�Z���T�Ŏ擾�����l���牽�F�������ʂ���֐�
int what_color(){
    get_color_value();
    if(IR > 30){
        //�{�[���������Ă��邩�̊m�F
        //printf("\tno_ball\n");
        return NO_BALL;
       
    }
    else{
        if(R > 35 && G < 40 && B < 35){
            //�ԐF����[
            //printf("\tred\n");
            return RED;
        }
        else if(R < 30 && G < 35 && B < 35){      //if( R < 50 && G > 30 && B > 50)
            //�F����[
            //
            //printf("\tblue\n");
            return BLUE;
        }
        //������臒l���Ȃ񂩂ȁ[
        else{ //if(R > 50 && G > 50 && B > 20){       // if(R > 90 && G > 100 && B > 40)
            //����ȊO�͉��F����ˁH
            //printf("\tyello\n");
            return YELLO;
        }
        
    }
}