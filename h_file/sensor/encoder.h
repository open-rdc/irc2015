//encoder.cpp
GLOBAL bool encoder_flag;               //�G���R�[�_���I�h���g���̃t���O
GLOBAL void switch_encoder();
//GLOBAL bool file_flag;
//GLOBAL void switch_file();
//GLOBAL float coordinates[500][3];
GLOBAL void l_odometry_reset();         //���݂̃��{�b�g�̈ʒu����ɂ���֐�
GLOBAL int r_pulses,l_pulses;           //���E�̃p���X
GLOBAL float r_omega,l_omega,omega;    //���E�ւ̉�]�p���x[rad/sec]
GLOBAL float g_X;                      //�O���[�o����x
GLOBAL float g_Y;                      //�O���[�o����y
GLOBAL float g_theta;                  //�O���[�o���Ȋp�x[deg]
GLOBAL float l_X;                      //���[�J����x
GLOBAL float l_Y;                      //���[�J����y
GLOBAL float l_theta;                  //���[�J���Ȋp�x[deg]