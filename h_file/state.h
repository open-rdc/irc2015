//switch�Ŏg�����̏�Ԃ��i�[�C�ォ��0,1,2�Ȋ���
GLOBAL enum state{
    init_state,         //�����ݒ�
    free_ball,          //�X�^�[�g����T���G���A�܂�
    ball_search,        //�{�[���T��
    ball_shoot,         //�e�{�[���V���[�g
    area_move,          //�{�[����������Ȃ��ꍇ�A�T���G���A���ړ�
    finish
}state;

//state.cpp
GLOBAL void initialize();
GLOBAL void fine();
GLOBAL float l_time;