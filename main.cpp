#include "main.h"
//-------------------------------
void _use_grivity(Fluid_datas temp){
    //检测实体和流体碰撞，下坠，debug用
    for (auto& v1 : temp.datas) {
        for (auto& v2 : v1) {
            for (auto& v3 : v2) {
                v3 = 0;
            }
            //cnmd
            
        }
    }
}

void start_calmulate(Fluid_datas datas,double limit_time){
    auto timer = 0;
    while (timer < limit_time)
    {
        //主操作
        timer += tick;
    }

}



//------------------------------
void _init_datas(Fluid_datas temp){
    
}
auto devide(Fluid_datas temp){
    auto new_fluid_datas = temp;


    return new_fluid_datas;
}
