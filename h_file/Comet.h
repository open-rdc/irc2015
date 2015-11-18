#include "mbed.h"
#include "robo_para.h"  //ロボットのパラメータ
#include "define.h"     //その他変数用

//疑似命令
#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "function.h"           //関数宣言