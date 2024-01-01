#include "source.h"

void graph::readData(std::string path = "E:\\DS-project\\graph.txt"){
    std::ifstream file(path);
    int n,m;file>>n>>m;
    numPoint = n;numedge = m;
    pos.resize( 1 ); // 不使用下标0
    e.resize( n + 1 );
    exist.resize( n + 1 , true );
    exist[0] = false;


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
    // #include <graphics.h>

    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[i] == false ) continue;
        setcolor(YELLOW);
        setfillcolor(YELLOW);
        fillellipse(pos[i].first,pos[i].second,10,10);
    }
    // 在点中间显示编号
    // 透明显示
    setbkmode(TRANSPARENT);

    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[i] == false ) continue;
        setcolor(BLACK);
        setfont(20,0,"宋体");
        char s[10];
        sprintf(s,"%d",i);
        outtextxy(pos[i].first-5,pos[i].second-9,s);
    }
    
}

void graph::showEdge(){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[i] == false ) continue;
        for( int j = 0 ; j < e[i].size() ; j ++ ){
            int x = i , y = e[i][j].first;
            setcolor(BLACK);
            setlinestyle(PS_SOLID, 1 , 5);
            line(pos[x].first,pos[x].second,pos[y].first,pos[y].second);
        }
    }
}

void graph::addPoint( int x, int y ){
    pos.push_back(std::make_pair(x,y));
    numPoint ++;
    exist.push_back(true);
    e.resize( numPoint + 1 );
}

void graph::addEdge( int x, int y ){
    e[ x ].push_back({y,caldis(x,y)});
    e[ y ].push_back({x,caldis(x,y)});
    numedge ++;
}

void graph::showPointPostion(){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[i] == false ) continue;
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

void graph::deletePoint( int x ){
    for( auto i : e[ x ] ){
        int y = i.first;
        for( int j = 0 ; j < e[ y ].size() ; j ++ ){
            if( e[y][j].first == x ){
                e[y].erase(e[y].begin()+j);
                break;
            }
        }
    } 
    e[x].clear();
    exist[x] = false;
}

void graph::dijkstra( int x, int y ){
    
    std::priority_queue<std::pair<int,double>> q;
    std::vector<double> dis( numPoint + 1 , 1e9 );
    std::vector<bool> vis( numPoint + 1 , false );
    std::vector<int> pre( numPoint + 1 , -1 );
    dis[x] = 0;
    q.push({0,x});
    while( !q.empty() ){
        int u = q.top().second;q.pop();
        if( vis[u] ) continue;
        vis[u] = true;
        for( auto i : e[u] ){
            int v = i.first;
            double w = i.second;
            if( dis[v] > dis[u] + w ){
                dis[v] = dis[u] + w;
                pre[v] = u;
                q.push({-dis[v],v});
            }
        }
    }
    std::cout<<"最短距离为"<<dis[y]<<std::endl;

    // 画出最短路
    int now = y;
    while( now != -1 ){
        setcolor(RED);
        setlinestyle(PS_SOLID, 1, 5);
        if( pre[now] != -1 ){
            line(pos[now].first,pos[now].second,pos[pre[now]].first,pos[pre[now]].second);
        }
        now = pre[now];
    }

}

void graph::showPointsAround( int x ){
    for( auto i : e[x] ){
        int y = i.first;
        setcolor(RED);
        setfillcolor(RED);
        fillellipse(pos[y].first,pos[y].second,10,10);
        setcolor(BLACK);
        setfont(20,0,"宋体");
        char s[10];
        sprintf(s,"%d",y);
        outtextxy(pos[y].first-5,pos[y].second-9,s);
    }
}