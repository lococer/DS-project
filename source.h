#include <graphics.h>
#include <vector>
#include <string>
#include <cstdio>
#include <process.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <queue>
/*
    待完成：
    1.用户登录界面
    2.保存图信息到文件{
        1.点信息
        2.边信息
        3.删除不存在的点重新编号，边信息也要更新，点编号和城市信息映射更新
    }
    3.选择导入的图
    4.优化界面和排版
    6.点编号和城市信息映射
*/

class graph{
private:
    // 节点位置
    std::vector<std::pair<int,int>> pos;
    // 点是否还存在
    std::vector<bool> exist;
    // 边 <节点编号，距离>
    std::vector<std::vector<std::pair<int,double>>> e;

    int numPoint,numedge;
    // 最短路信息
public:

    void readData(std::string path);

    double caldis( int x, int y );

    void showPoint();
    void showEdge();

    void addPoint( int x, int y );
    void addEdge( int x, int y );

    void showPointPostion();
    void deleteEdge( int x, int y );
    void deletePoint( int x );

    void dijkstra( int x, int y );

    void showPointsAround( int x );

};