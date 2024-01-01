#include "source.h"

void rePaint(graph &g){
    cleardevice();
    setbkcolor(WHITE);
    g.showEdge();
    g.showPoint();
    delay_ms(100);
}


bool action(graph &g){
    int option = 0;
    std::cout<<"1.加点 2.加边 3.退出 4.显示点信息 5.删边 6.删点 7.计算最短路 8.显示周围节点"<<std::endl;
    std::cin>>option;
    rePaint(g);
    if( option == 1 ){
        int x,y;
        std::cout<<"输入横纵坐标"<<std::endl;
        std::cin>>x>>y;
        g.addPoint(x,y);
    }
    if( option == 2 ){
        int x,y;
        std::cout<<"输入两点编号"<<std::endl;
        std::cin>>x>>y;
        g.addEdge(x,y);
    }
    if( option == 3 ){
        return false;
    } 
    if( option == 4 ){
        g.showPointPostion();
    }
    if( option == 5 ){
        int x,y;
        std::cout<<"输入两点编号"<<std::endl;
        std::cin>>x>>y;
        g.deleteEdge(x,y);
    }
    if( option == 6 ){
        int x;
        std::cout<<"输入点编号"<<std::endl;
        std::cin>>x;
        g.deletePoint(x);
    }
    if( option == 7 ){
        int x,y;
        std::cout<<"输入两点编号"<<std::endl;
        std::cin>>x>>y;
        g.dijkstra(x,y);
        // 放置点被线覆盖
        g.showPoint();
    }
    if( option == 8 ){
        int x;
        std::cout<<"输入点编号"<<std::endl;
        std::cin>>x;
        g.showPointsAround(x);
    }
    if( option != 7 && option != 8 ){
        rePaint(g);
    }
    delay_ms(100);
    return true;
}


int main() {


    initgraph(700, 700, 0);
    setbkcolor(WHITE);

    graph g;
    g.readData("E:\\DS-project\\graph.txt");
    g.showEdge();
    g.showPoint();
    delay_ms(100);

    while(action(g));
    
    closegraph();
    return 0;
}