#include <graphics.h>
#include<vector>
#include<string>
class graph{
private:
    // 节点位置
    std::vector<std::pair<int,int>> pos;
    // 边 <节点编号，距离>
    std::vector<std::vector<std::pair<int,double>>> e;

    int numPoint,numedge;
public:

    void readData(std::string path);

    double caldis( int x, int y );

    void showPoint();
    void showEdge();

    void addPoint( int x, int y );
    void addEdge( int x, int y );

    void showPointPostion();
    void deleteEdge( int x, int y );

};