#include <iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<set>
#include<cmath>
#include<iterator>
using namespace std;

const int SIZE_OF_ROUTE = 10;
const int SIZE_OF_NODE = 6;

class Node{
public:
    static int num;
    int x,y;
    Node(int x_, int y_):x(x_),y(y_){num++;};
    Node();
    int index = num;
    bool operator<(const Node&n)const {
        return index <= n.index;
    };
};
int Node::num = 1;

void ins(set<Node>&unvs, vector<Node>&R, const float (*table)[SIZE_OF_ROUTE]) {
    double min_cost = 1e5;
    set<Node>::iterator lb;
    vector<Node>::iterator ppos;
    for (auto uv = unvs.begin(); uv != unvs.end(); uv++) {
        for (auto it = R.begin(); it != R.end(); it++)
            if (table[uv->index - 1][it->index - 1] +
                table[uv->index - 1][++it->index - 1] -
                table[--it->index - 1][++it->index - 1] <= min_cost){
                min_cost = table[uv->index - 1][it->index - 1] +
                           table[uv->index - 1][++it->index - 1] -
                           table[--it->index - 1][++it->index - 1];
                lb = uv;
                ppos = it--;
            }



    }
    unvs.erase(lb);
    R.insert(ppos, *lb);

}


int main() {

    vector<Node>x;
    x.emplace_back(Node(0, 3));
    x.emplace_back(Node(0, 4));
    x.emplace_back(Node(1, 0));
    x.emplace_back(Node(1, 1));
    x.emplace_back(Node(1, 3));
    x.emplace_back(Node(2, 3));

    vector<Node>Route;
    set<Node>in_route {x[2], x[3]};
    set<Node>not_in_route {x[0], x[1], x[4], x[5]};

    float dist_tab[SIZE_OF_ROUTE][SIZE_OF_ROUTE];
    for(auto s = x.begin(); s != x.end(); s++ )
        for(auto ss = s; ss < x.end(); ss++){
//            cout << "(" <<s->x << " " << s->y << ") ";
//            cout << "(" <<ss->x << " " << ss->y << ")"<< endl;
            //C++没有x^2这种用法
            dist_tab[s->index - 1][ss->index - 1] = sqrt(pow(s->x - ss->x, 2) + pow(s->y - ss->y, 2));
            dist_tab[ss->index - 1][s->index - 1] = dist_tab[s->index - 1][ss->index - 1];
        }
//    for(int i = 0; i < 6; i++) {
//        for (int j = 0 ; j < 6; j++)
//            cout << setw(5) << setprecision(3) <<dist_tab[i][j] << ' ';
//        cout << endl;
//    }


    Route.push_back(x[2]);
    Route.push_back(x[3]);


    while(Route.size() != SIZE_OF_NODE)
        ins(not_in_route, Route, dist_tab);

    cout<< Route.size()<< endl;
    for(auto i = Route.begin(); i < Route.end(); i++)
        cout << "(" << i->x << ", " << i->y << ")" <<endl;





    return 0;
}
