#include <iostream>
#include <vector>
#include <ctime>
const int tick = 0.01;//一个tick帧
struct Fluid_datas
{
    int demonsion = 3;
    int size_x = 100;
    int size_y = 100;
    int size_z = 100;
    std::vector<std::vector<std::vector<long int>>> datas;
    //数据供参考
};

class Loader
{
private:
    /* data */
    void _init_datas(Fluid_datas temp);
public:
};


class Solver
{
private:
    /* data */
    void _use_grivity(Fluid_datas);//名字别当真，debug用的
    void start_calmulate(Fluid_datas,double limit_time);
public:
};


class Devider
{
private:
    auto devide(Fluid_datas);
public:
};
