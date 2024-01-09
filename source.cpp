#include "source.h"

void graph::readData(std::string path = "graph.txt"){
    *this = graph();
    readPath = path;
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
    if( exist[ x ] == false || exist[ y ] == false ) return;
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
    if( dis[ y ] == 1e9 ){
        std::cout<<"不存在最短路"<<std::endl;
        return;
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

graph::graph(){
    numPoint = numedge = 0;
    e.resize(1);
    pos.resize(1);
    exist.resize(1,false);
    readPath = "";
}

void graph::saveFile(std::string path){
    // 保存图信息到文件
    // 存储点和边信息，当点不存在时跳过该点，并把后面的点编号减一，边的相应信息也要更新
    readPath = path;
    std::ofstream file(path);

    std::vector<int> delt( numPoint + 1 ),delt1;
    delt1 = delt;
    for( int i = 1 ; i <= numPoint ; i ++ ){
        delt[ i ] = delt[ i - 1 ] + ( exist[ i - 1 ] == false );
    }
    for( int i = 1 ; i <= numPoint ; i ++ ){
        delt1[ i ] = delt1[ i - 1 ] + ( exist[ i ] == false );
    }

    int tnumPoint = numPoint;

    // 遍历每条边，把有关点编号-delt
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( !exist[ i ] ){
            tnumPoint --;
            continue;
        }
    }
    numedge = 0;
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[ i ] == false ) continue;
        
        std::sort(e[i].begin(),e[i].end());
        auto erase_begin = std::unique(e[i].begin(),e[i].end());
        e[i].erase(erase_begin,e[i].end());

        for( int j = 0 ; j < e[ i ].size() ; j ++ ){
            int y = e[ i ][ j ].first;
            int x = i - delt1[ i ];
            y -= delt1[ y ];
            if( y > x ) numedge++;
        }
    }
    file<<tnumPoint<<" "<<numedge<<std::endl;
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[ i ] == false ) continue;
        file<<pos[ i ].first<<' '<<pos[ i ].second<<std::endl;
    }

    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[ i ] == false ) continue;
        for( auto &[y,dis] : e[ i ] ){
            int x = i - delt1[ i ];
            y = y - delt1[ y ];
            if( y <= x ) continue;
            file<<x<<' '<<y<<std::endl;
        }
    }

}

void graph::rePaint(){
    cleardevice();
    setbkcolor(WHITE);
    showEdge();
    showPoint();
    delay_ms(100);
}

login::login(){
    isLogin = false;
    readData();
}

void login::readData(){
    std::ifstream file("userdata.txt");
    int n;file>>n;
    for( int i = 1 ; i <= n ; i ++ ){
        std::string username,password;
        file>>username>>password;
        user.push_back({username,password});
    }
}

void login::loginIn(){
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cout<<"请输入用户名和密码"<<std::endl;
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cin>>username>>password;
    for( auto i : user ){
        if( i.first == username && i.second == password ){
            isLogin = true;
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::cout<<"登录成功"<<std::endl;
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            return;
        }
    }
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cout<<"用户名或密码错误"<<std::endl;
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
}

void login::registerIn(){
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cout<<"请输入用户名和密码"<<std::endl;
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cin>>username>>password;
    for( auto i : user ){
        if( i.first == username ){
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::cout<<"用户名已存在"<<std::endl;
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            return;
        }
    }
    user.push_back({username,password});
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
    std::cout<<"注册成功"<<std::endl;
    std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
}

void login::saveData(){
    std::ofstream file("userdata.txt");
    file<<user.size()<<std::endl;
    for( auto i : user ){
        file<<i.first<<' '<<i.second<<std::endl;
    }
}

void login::showUser(){
    for( auto i : user ){
        static int cnt = 0;
        std::cout<<++cnt<<". "<<i.first<<std::endl;
    }
}

bool login::getIsLogin(){
    return isLogin;
}

std::string login::getUsername(){
    return username;
}

void login::logout(){
    isLogin = false;
    username = "";
    password = "";
}

// solve类
solve::solve(){
    isLogin = false;
    username = "";
}

void solve::run(){
    initgraph(700, 700, 0);
    setbkcolor(WHITE);
    while( true ){
        if( !isLogin ){
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::cout<<"1.登录 2.注册 3.列出已有用户 4.退出"<<std::endl;
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::string option;
            std::cin>>option;
            bool legal = 0;
            if( option == "1" ){
                legal = 1;
                l.loginIn();
                if( l.getIsLogin() ){
                    isLogin = true;
                    username = l.getUsername();
                }
            }
            if( option == "2" ){
                legal = 1;
                l.registerIn();
                if( l.getIsLogin() ){
                    isLogin = true;
                    username = l.getUsername();
                }
            }
            if( option == "3" ){
                legal = 1;
                l.showUser();
            }
            if( option == "4" ){
                legal = 1;
                l.saveData();
                return;
            }
            if( !legal ){
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入错误"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            }
        }else{
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::cout<<"1.读入地图 2.空地图 3.添加点 4.添加边 5.显示点位置 6.删除边 7.删除点 8.最短路 9.显示点周围点 10.保存地图 11.退出登录"<<std::endl;
            std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            std::string option;
            std::cin>>option;
            g.rePaint();
            bool legal = 0;
            if( option == "1" ){
                legal = 1;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入路径"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::string path;
                std::cin>>path;
                g.readData(path);
            }
            if( option == "2" ){
                legal = 1;
                g = graph();
            }
            if( option == "3" ){
                legal = 1;
                int x,y;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"选取点位置"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;

                auto pos = getMouse();
                x = pos.first;y = pos.second;

                g.addPoint(x,y);
            }
            if( option == "4" ){
                legal = 1;
                int x,y;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"选取两点"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                x = getPointChosen(g);
                std::cout<<"已选取第一个点编号:"<<x<<'\n';
                y = getPointChosen(g);
                std::cout<<"已选取第二个点编号:"<<y<<'\n';
                g.addEdge(x,y);
            }
            if( option == "5" ){
                legal = 1;
                g.showPointPostion();
            }
            if( option == "6" ){
                legal = 1;
                int x,y;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入两点编号"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                x = getPointChosen(g);
                std::cout<<"已选取第一个点编号:"<<x<<'\n';
                y = getPointChosen(g);
                std::cout<<"已选取第二个点编号:"<<y<<'\n';
                g.deleteEdge(x,y);
            }
            if( option == "7" ){
                legal = 1;
                int x;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入点编号"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                // std::cin>>x;
                x = getPointChosen(g);
                g.deletePoint(x);
            }
            if( option == "8" ){
                legal = 1;
                int x,y;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入两点编号"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                x = getPointChosen(g);
                std::cout<<"已选取第一个点编号:"<<x<<'\n';
                y = getPointChosen(g);
                std::cout<<"已选取第二个点编号:"<<y<<'\n';
                g.dijkstra(x,y);
                // 放置点被线覆盖
                g.showPoint();
            }
            if( option == "9" ){
                legal = 1;
                int x;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入点编号"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                // std::cin>>x;
                x = getPointChosen(g);
                g.showPointsAround(x);
            }
            if( option == "10" ){
                legal = 1;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"请输入保存路径"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::string path;
                std::cin>>path;
                g.saveFile(path);
                g.readData(path);
            }
            if( option == "11" ){
                legal = 1;
                l.saveData();
                l.logout();
                isLogin = false;
                username = "";
            }
            if( option != "8" && option != "9" ){
                g.rePaint();
            }
            delay_ms(100);
            if( !legal ){
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
                std::cout<<"输入错误"<<std::endl;
                std::cout<<std::setfill('*')<<std::setw(30)<<""<<std::endl;
            }
        }
    }
    closegraph();
}

std::pair<int,int> solve::getMouse(){
    mouse_msg msg;
    for( ;is_run() ; delay_fps(60) ){
        while( mousemsg() ){
            msg = getmouse();
        }
        if( msg.is_down() ){
            return {msg.x, msg.y};
        }
    }
    return {0,0};
}

int solve::getPointChosen( graph &g ){
    mouse_msg msg;
    for( ;is_run() ; delay_fps(10) ){
        while( mousemsg() ){
            msg = getmouse();
        }
        if( msg.is_down() ){
            return g.getPointChosen(msg.x,msg.y);
        }
    }
    return 0;
}

int graph::getPointChosen(int x, int y){
    for( int i = 1 ; i <= numPoint ; i ++ ){
        if( exist[i] == false ) continue;
        if( abs( pos[i].first - x ) <= 10 && abs( pos[i].second - y ) <= 10 ){
            return i;
        }
    }
    return 0;
}