///////////様々な関数や変数を格納する場所///////////
////////ここにあるのはどこの関数（cppファイル）でも参照可能////////

//color.cpp
GLOBAL int color;
GLOBAL int what_color();        

//servo.cpp
GLOBAL void servo_ini();
GLOBAL void servo_throw();        
GLOBAL void servo_ready();
GLOBAL void servo_up();
GLOBAL void servo_up2();   
GLOBAL void servo_catch();      

//hello_world.cpp
GLOBAL int guhu;
GLOBAL void switch_hello();

//switchで使う時の状態を格納，上から0,1,2な感じ
GLOBAL enum state{
    init_state,         //初期設定
    free_ball,          //スタートから探索エリアまで
    ball_search,        //ボール探索
    ball_shoot,         //各ボールシュート
    area_move,          //ボールが見つからない場合、探索エリアを移動
    finish
}state;

//PSD.cpp
GLOBAL float Get_PSD_high();
GLOBAL float Get_PSD_low();
GLOBAL void PSD_reset();

//encoder.cpp
GLOBAL bool encoder_flag;               //エンコーダ＆オドメトリのフラグ
GLOBAL void switch_encoder();
//GLOBAL bool file_flag;
//GLOBAL void switch_file();
//GLOBAL float coordinates[500][3];
GLOBAL void l_odometry_reset();         //現在のロボットの位置を基準にする関数
GLOBAL int r_pulses,l_pulses;           //左右のパルス
GLOBAL float r_omega,l_omega,omega;    //左右輪の回転角速度[rad/sec]
GLOBAL float g_X;                      //グローバルなx
GLOBAL float g_Y;                      //グローバルなy
GLOBAL float g_theta;                  //グローバルな角度[deg]
GLOBAL float l_X;                      //ローカルなx
GLOBAL float l_Y;                      //ローカルなy
GLOBAL float l_theta;                  //ローカルな角度[deg]

//PI.cpp
GLOBAL float l_integral,r_integral;       //左右それぞれの偏差の合計
GLOBAL void PID(int l_terget, int r_terget);

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

//line_trace.cpp
GLOBAL void Line_Trace(int goal);

//state.cpp
GLOBAL void initialize();
GLOBAL void turn_on1();
GLOBAL void turn_on2();
GLOBAL void fine();  