//motion.cpp
GLOBAL bool move_flag;                  //探索エリア移動フラグ
GLOBAL void turn(int deg);
GLOBAL void turn(float deg, bool mode);
GLOBAL void g_turn(float deg);
GLOBAL void stop();
GLOBAL void tansaku();
GLOBAL void serch();
GLOBAL void Ball_Catch();
GLOBAL void Ball_Shoot();
GLOBAL float serch_data[2][2];    //0=近い方  1＝今     dis，deg