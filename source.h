#include <graphics.h>
#include <vector>
#include <string>
#include <cstdio>
#include <process.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <queue>
#include <algorithm>
#include <iomanip>
/*
    待完成：
    1.用户登录界面 done
    2.保存图信息到文件{
        1.点信息 done
        2.边信息 done
        3.删除不存在的点重新编号，边信息也要更新，点编号和城市信息映射更新
    }
    3.选择导入的图 done
    4.优化界面和排版 done
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
    std::string readPath;
public:
    graph();
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
    void saveFile(std::string path);
    void rePaint();
    int getPointChosen(int x, int y);
    bool existEdge( int x , int y );
};

// login类，能从当前目录下的userdata.txt 读取用户名和密码，实现登录和注册功能
class login{
private:
    std::vector<std::pair<std::string,std::string>> user;
    std::string username;
    std::string password;
    bool isLogin;
public:
    login();
    void readData();
    void loginIn();
    void registerIn();
    void saveData();
    void showUser();
    bool getIsLogin();
    std::string getUsername();
    void logout();
};

// solve类，实现用户交互界面
class solve{
private:
    graph g;
    login l;
    bool isLogin;
    std::string username;
public:
    solve();
    void run();
    std::pair<int,int> getMouse();
    int getPointChosen(graph &g );
};
