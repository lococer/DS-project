#include <iostream>
#include <stdio.h>
#include "source.h"

bool action(graph &g){
    int option = 0;
    std::cout<<"1.加点 2.加边 3.退出 4.显示点信息 5.删边"<<std::endl;
    std::cin>>option;
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
    cleardevice();
    g.showPoint();
    g.showEdge();
    delay_ms(100);
    return true;
}


int main() {


    initgraph(700, 700, 0);
    setbkcolor(WHITE);

    graph g;
    g.readData("E:\\DS-project\\graph.txt");
    g.showPoint();
    g.showEdge();

    while(action(g));
    

    getch();

    closegraph();
    return 0;
}