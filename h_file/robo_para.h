//////���{�b�g�̏����i�[����t�@�C��/////////
#define WHEEL_RADIUS 25.5           //�ԗ֔��a[mm]
#define GEAR 44.0                     //�M�A��
#define T 190.0                       //�ԗ֊ԋ���[mm]

#define ROTATE_PER_REVOLUTION 100.0   //1��]������̃p���X
#define BUNKAINOU 4.0                //����\

#define DELTA_T 0.005                //�������0.02[s]=20[ms]
#define PSD_DELTA_T 0.01             //PSD�p�������

///////////////�T�[�{���[�^�p�ϐ����i�[/////////////////////////
/////////////////////id 0����////////////////////////////////
#define SERVO_0 0                                       
#define SERVO_0_UPWARD 4900                                 
#define SERVO_0_LOWER 7500                               
#define SERVO_0_THROW 7100                             
                                                        
#define SERVO_1 1                                       
#define SERVO_1_OPEN 7500                               
#define SERVO_1_CLOSE 11500                              
////////////////////////////////////////////////////////////

//���S����̋���
//�g��Ȃ��\�����E�E�E
#define PHOTO_LL -40                    //��ԍ��̃Z���T�̋���
#define PHOTO_L -20                     //���S���̃Z���T�̋���
#define PHOTO_R 20                      //���S�E�̃Z���T�̋���
#define PHOTO_RR 40                     //��ԉE�̃Z���T�̋���

//////////���䂷��Ƃ��Ɏg�p//////////////////
#define PID_R_KP -0.19           //�E�ԗ�P�Q�C��                 //-0.2//-0.284
#define PID_R_KI -0.38        //I�Q�C��-0.08
#define PID_R_KD 0.0        //D�Q�C��

#define PID_L_KP -0.26        //���ԗ�P�Q�C��-0.09   -0.078       //-0.158//-0.28//-0.165
#define PID_L_KI -0.36        //I�Q�C��-0.06//0.28
#define PID_L_KD 0.0        //D�Q�C��

#define LINE_KP 0.0         //���C���g���[�X�pP�Q�C��
#define LINE_KI 0.0         //I�Q�C��
#define LINE_KD 0.0         //D�Q�C��