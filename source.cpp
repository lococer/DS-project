#include "source.h"
#include <cstdio>
#include <process.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
void graph::readData(std::string path = "E:\\DS-project\\graph.txt"){
    std::ifstream file(path);
    int n,m;file>>n>>m;
    numPoint = n;numedge = m;
    pos.resize( 1 ); // 不使用下标0
    e.resize( n + 1 );

    for( int i = 1 ; i <= n ; i ++ ){
        int x,y;file>>x>>y;
        pos.push_back(std::make_pair(x,y));
    }

    for( int i = 1 ; i <= m ; i ++ ){
        int x,y;file>>x>>y;
        e[ x ].push_back({y,caldis(x,y)});
        e[ y ].push_back({x,caldis(x,y)});
    }

}


double graph::caldis( int x, int y ){
    double disx = abs( pos[x].first - pos[y].first );
    double disy = abs( pos[x].second - pos[y].second );
    return sqrt( disx * disx + disy * disy );
}

void graph::showPoint(){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        setcolor(RED);
        setfillcolor(RED);
        fillellipse(pos[i].first,pos[i].second,5,5);
    }
}

void graph::showEdge(){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        for( int j = 0 ; j < e[i].size() ; j ++ ){
            int x = i , y = e[i][j].first;
            setcolor(BLACK);
            line(pos[x].first,pos[x].second,pos[y].first,pos[y].second);
        }
    }
}

void graph::addPoint( int x, int y ){
    pos.push_back(std::make_pair(x,y));
    numPoint ++;
    e.resize( numPoint + 1 );
}

void graph::addEdge( int x, int y ){
    e[ x ].push_back({y,caldis(x,y)});
    e[ y ].push_back({x,caldis(x,y)});
    numedge ++;
}

void graph::showPointPostion(){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        std::cout<<"点"<<i<<":"<<pos[i].first<<" "<<pos[i].second<<std::endl;
    }
}

void graph::deleteEdge( int x, int y ){
    for( int i = 0 ; i < e[x].size() ; i ++ ){
        if( e[x][i].first == y ){
            e[x].erase(e[x].begin() + i);
            break;
        }
    }
    for( int i = 0 ; i < e[y].size() ; i ++ ){
        if( e[y][i].first == x ){
            e[y].erase(e[y].begin() + i);
            break;
        }
    }
    numedge --;
}