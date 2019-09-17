
#include <stdio.h>
#include <math.h>
#include "utility.h"
#include "tim.h"
#include "motor.h"
#define IHSV57_CONTROL
#include "iHSV57.h"

uint8_t MotionStatus=0;//电机运动状态 1:运动 0:停止
//speedRampData cameraMotor               = {STOP,CW,0,0,0,0,0};


//电机初始化
void iHSV57Init()
{
    //初始化设定电机的加减速,速度值等
    motor1Device.motorInfo.accel = 10;
    motor1Device.motorInfo.decel = 10;
    motor1Device.motorInfo.speed = 200;
    motor1Device.numb = 1;
    motor1Device.i = 0;
    motor1Device.last_accel_delay = 0;
    motor1Device.new_step_delay = 0;
    motor1Device.rest = 0;
    motor1Device.step_count = 0;
    
    motor2Device.motorInfo.accel = 100;
    motor2Device.motorInfo.decel = 100;
    motor2Device.motorInfo.speed = 500;
    motor2Device.numb = 2;
    motor2Device.i = 0;
    motor2Device.last_accel_delay = 0;
    motor2Device.new_step_delay = 0;
    motor2Device.rest = 0;
    motor2Device.step_count = 0;
    
    motor3Device.motorInfo.accel = 100;
    motor3Device.motorInfo.decel = 100;
    motor3Device.motorInfo.speed = 500;
    motor3Device.numb = 3;
    motor3Device.i = 0;
    motor3Device.last_accel_delay = 0;
    motor3Device.new_step_delay = 0;
    motor3Device.rest = 0;
    motor3Device.step_count = 0;
    
    motor4Device.motorInfo.accel = 10;
    motor4Device.motorInfo.decel = 10;
    motor4Device.motorInfo.speed = 200;
    motor4Device.numb = 4;
    motor4Device.i = 0;
    motor4Device.last_accel_delay = 0;
    motor4Device.new_step_delay = 0;
    motor4Device.rest = 0;
    motor4Device.step_count = 0;
    
    
    cameraMotorDevice.motorInfo.accel = 50;
    cameraMotorDevice.motorInfo.decel = 50;
    cameraMotorDevice.motorInfo.speed = 200;
    cameraMotorDevice.numb = 5;
    cameraMotorDevice.i = 0;
    cameraMotorDevice.last_accel_delay = 0;
    cameraMotorDevice.new_step_delay = 0;
    cameraMotorDevice.rest = 0;
    cameraMotorDevice.step_count = 0;
    cameraMotorDevice.motorType = CAMERA_MOTOR;
    
    cutMoveMotorDevice.motorInfo.accel = 50;
    cutMoveMotorDevice.motorInfo.decel = 50;
    cutMoveMotorDevice.motorInfo.speed = 200;
    cutMoveMotorDevice.numb = 5;
    cutMoveMotorDevice.i = 0;
    cutMoveMotorDevice.last_accel_delay = 0;
    cutMoveMotorDevice.new_step_delay = 0;
    cutMoveMotorDevice.rest = 0;
    cutMoveMotorDevice.step_count = 0;
    cutMoveMotorDevice.motorType = XCUT_MOTOR;
}

//相对运动: step:目标位置 accel:加速度 decel:减速度 speed:速度
void cameraAxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    uint32_t max_s_lim; //达到最大速度时的步数
    uint32_t accel_lim; //必须开始减速的步数(如果加速没有达到最大速度)
    float ftemp=0.0;

    if(step < 0) // 步数为负数(负方向运动)
    {
        cameraMotor.dir = CCW;     //逆时针旋转
        CAMERA_MOTOR_DIR(1); //改变电机的方向
        step =-step;       //获取步数绝对值
    }
    else //正方向运行
    {
        cameraMotor.dir = CW;       //顺时针方向旋转
        CAMERA_MOTOR_DIR(0);  
    }

    if(step == 1) //移动一步
    {
        cameraMotor.accel_count = -1;  //只移动一步
        cameraMotor.run_state = DECEL; //减速状态
        cameraMotor.step_delay = 1000;
    }
    else if(step != 0)
    {
        //设置最大速度极限, 计算得到min_delay用于定时器的计数器的值(最小定时器时间间隔值)
        //min_delay = (alpha*freq)/speed
        cameraMotor.min_delay = (int32_t)(A_T_x100/speed);

        //通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.01rad/sec^2
        //step_delay = freq*sqrt(2*alpha/accel)
        cameraMotor.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ/accel))/100);
            
        //加速到最大速度时所需步数
        //max_s_lim = speed^2 / (2*alpha*accel)
        max_s_lim = (long)(speed*speed/(A_x20000*accel/100));
            
        // 如果达到最大速度小于0.5步，我们将四舍五入为0
        // 但实际我们必须移动至少一步才能达到想要的速度   
        if(max_s_lim == 0){
            max_s_lim = 1;
        }

        //减速之前的移动的步数(即加速阶段移动的步数+匀速阶段的步数)
        //n1 = (n1+n2)decel/(accel + decel)
         accel_lim = (long)(step*decel/(accel+decel)); //按照达到最大速度去计算的
        // 我们必须加速至少1步才能才能开始减速.
        if(accel_lim == 0){
            accel_lim = 1;
        }

        //减速阶段所需步数
        if(accel_lim <= max_s_lim){ //没有达到最大速度时
            cameraMotor.decel_val = accel_lim - step;
        }else{ //达到最大速度时
            cameraMotor.decel_val =-(long)(max_s_lim*accel/decel);
        }
        
        // 当只剩下一步我们必须减速
        if(cameraMotor.decel_val == 0){
            cameraMotor.decel_val = -1;
        }

         //计算开始减速时的位置,在总步数中的位置
        cameraMotor.decel_start = step + cameraMotor.decel_val;

        // 如果最大速度很慢，我们就不需要进行加速运动
        if(cameraMotor.step_delay <= cameraMotor.min_delay)
        {
            cameraMotor.step_delay = cameraMotor.min_delay;
            cameraMotor.run_state = RUN;
        }else{
            cameraMotor.run_state = ACCEL;
        }

        // 复位加速度计数值.
        cameraMotor.accel_count = 0;
    }
    
    if(step != 0)
    {
        f_cameraMotorStatus = 1;
        pluseCount = 0;
        CAMERA_MOTOR_ENABLE();
        CAMERA_MOTOR_UNSLEEP();
        CAMERA_MOTOR_PULSE(0);
        TIM_SetAutoreload(TIM5, cameraMotor.step_delay);       //设置自动重装载
        TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    }
}


#if 1
//相对运动: step:目标位置 accel:加速度 decel:减速度 speed:速度
void cutMotorAxisMoveRel(int32_t step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    uint32_t max_s_lim; //达到最大速度时的步数
    uint32_t accel_lim; //必须开始减速的步数(如果加速没有达到最大速度)
    float ftemp=0.0;

    if(step < 0) // 步数为负数(负方向运动)
    {
        cutMotor.dir = CCW;     //逆时针旋转
        CUT_MOVE_MOTOR_DIR(0); //改变电机的方向
        step =-step;       //获取步数绝对值
    }
    else //正方向运行
    {
        cutMotor.dir = CW;       //顺时针方向旋转
        CUT_MOVE_MOTOR_DIR(1);   // 
    }

    if(step == 1) //移动一步
    {
        cutMotor.accel_count = -1;  //只移动一步
        cutMotor.run_state = DECEL; //减速状态
        cutMotor.step_delay = 1000;
    }
    else if(step != 0)
    {
        //设置最大速度极限, 计算得到min_delay用于定时器的计数器的值(最小定时器时间间隔值)
        //min_delay = (alpha*freq)/speed
        cutMotor.min_delay = (int32_t)(A_T_x100/speed);

        //通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.01rad/sec^2
        //step_delay = freq*sqrt(2*alpha/accel)
        cutMotor.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ/accel))/100);
            
        //加速到最大速度时所需步数
        //max_s_lim = speed^2 / (2*alpha*accel)
        max_s_lim = (long)(speed*speed/(A_x20000*accel/100));
            
        // 如果达到最大速度小于0.5步，我们将四舍五入为0
        // 但实际我们必须移动至少一步才能达到想要的速度   
        if(max_s_lim == 0){
            max_s_lim = 1;
        }

        //减速之前的移动的步数(即加速阶段移动的步数+匀速阶段的步数)
        //n1 = (n1+n2)decel/(accel + decel)
         accel_lim = (long)(step*decel/(accel+decel)); //按照达到最大速度去计算的
        // 我们必须加速至少1步才能才能开始减速.
        if(accel_lim == 0){
            accel_lim = 1;
        }

        //减速阶段所需步数
        if(accel_lim <= max_s_lim){ //没有达到最大速度时
            cutMotor.decel_val = accel_lim - step;
        }else{ //达到最大速度时
            cutMotor.decel_val =-(long)(max_s_lim*accel/decel);
        }
        
        // 当只剩下一步我们必须减速
        if(cutMotor.decel_val == 0){
            cutMotor.decel_val = -1;
        }

         //计算开始减速时的位置,在总步数中的位置
        cutMotor.decel_start = step + cutMotor.decel_val;

        // 如果最大速度很慢，我们就不需要进行加速运动
        if(cutMotor.step_delay <= cutMotor.min_delay)
        {
            cutMotor.step_delay = cutMotor.min_delay;
            cutMotor.run_state = RUN;
        }else{
            cutMotor.run_state = ACCEL;
        }

        // 复位加速度计数值.
        cutMotor.accel_count = 0;
    }
    
    if(step != 0)
    {
				cutMoveMotorPluseCount = 0;
        CUT_MOVE_MOTOR_PIN_RESET();
        TIM_SetAutoreload(TIM6, cutMotor.step_delay);       //设置自动重装载
        TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    }
}
#endif


