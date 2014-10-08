#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <random>
#include <functional>
#include <algorithm>
#include <list>

using namespace std;

//for easy display of a variable
#define HCOUT(x) (cout << #x << ": " << x << endl)

void RandomTest();
void mt19937Test();
void RandomShuffleTest();
void RandomShuffleIterTest();
void Knapsack(int n);
void TSPt(int n);

int main(int argc, char** argv)
{
    HCOUT(argc);
    for (int i = 0; i < argc; ++i) {
        HCOUT(argv[i]);
    }
    //RandomTest();
    //mt19937Test();
    //RandomShuffleTest();
    //RandomShuffleIterTest();
    Knapsack(4);
    //TSPt(3);
    return 0;
}
void RandomTest()
{
    //static std::default_random_engine e{};
    //static std::uniform_int_distribution<int> d{1, 6};
    std::random_device rd;
    cout << "random_device output:" << endl;
    for (int i=0; i<5; ++i)
        cout << rd() << endl;
    std::default_random_engine e1{33};
    std::uniform_int_distribution<int> uniform_dist(1, 6);
//    //e1.seed(33);
//    //int mean = uniform_dist(e1);
    for (int i=0; i<5; ++i) {
        HCOUT(uniform_dist(e1));
    }
//    std::shuffle_order_engine<std::default_random_engine, 5> se(e1);
//    for (int i=0; i<15; ++i) {
//        HCOUT(se());
//    }
    std::default_random_engine e{33};
    std::uniform_int_distribution<> d(1, 6);
    std::function<int()> rnd = std::bind(d, e);
    for (int i=0; i<5; ++i) {
        HCOUT(rnd());
    }
    e.seed(44);
    for (int i=0; i<5; ++i) {
        HCOUT(rnd());
    }
    e.seed(33);
    for (int i=0; i<5; ++i) {
        HCOUT(rnd());
    }
//    for (int i=0; i<5; ++i) {
//        int n = roll_a_fair_die( );
//        HCOUT(n);
//        double x = roll_a_fair_die_d();
//        HCOUT(x);
//        HCOUT(sgn(x));
//    }
//  std::string str;
//  std::cout << "Please, enter a seed: ";
//  std::getline(std::cin,str);
//  std::seed_seq seed1 (str.begin(),str.end());
//  for (auto& a: str)
//    HCOUT(a);
}
void mt19937Test()
{
    mt19937 mt(33);
    std::uniform_int_distribution<> d(1, 6);
    for (int i=0; i<5; ++i) {
        HCOUT(d(mt));
    }
    mt.seed(44);
    cout << 44 << endl;
    for (int i=0; i<5; ++i) {
        HCOUT(d(mt));
    }
    mt.seed(33);
    cout << 33 << endl;
    for (int i=0; i<5; ++i) {
        HCOUT(d(mt));
    }
    random_device rd;
    int n = rd();
    mt.seed(n);
    HCOUT(n);
    for (int i=0; i<5; ++i) {
        HCOUT(d(mt));
    }
    n = rd();
    mt.seed(n);
    HCOUT(n);
    for (int i=0; i<5; ++i) {
        HCOUT(d(mt));
    }
}
void RandomShuffleTest()
{
  std::array<int,5> foo {1,2,3,4,5};

  // obtain a time-based seed:
  //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed = 33;
    std::default_random_engine e{seed};
  shuffle (foo.begin(), foo.end(), e);

  std::cout << "shuffled elements:";
  for (int& x: foo) std::cout << ' ' << x;
  std::cout << '\n';

  shuffle (foo.begin(), foo.end(), e);

  std::cout << "shuffled elements:";
  for (int& x: foo) std::cout << ' ' << x;
  std::cout << '\n';

  return;
}
void RandomShuffleIterTest()
{
    std::list<int> l(5);
    std::iota(l.begin(), l.end(), -4);

    //std::random_shuffle cannot be applied to an std::list directly
    std::vector<std::list<int>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());

    mt19937 mt(33);
    std::shuffle(v.begin(), v.end(), mt);

    std::cout << "Contents of the list: ";
    for(auto n: l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    std::cout << "Contents of the list, shuffled: ";
    for(auto i: v) {
        std::cout << *i << ' ';
    }
    std::cout << '\n';

    mt.seed(44);

    std::shuffle(v.begin(), v.end(), mt);
    std::cout << "Contents of the list, shuffled with seed 44: ";
    for(auto i: v) {
        std::cout << *i << ' ';
    }
    std::cout << '\n';
}
vector<int> KSv;
void Knapsack(int n)
{
    if (n==0) {
        for (auto x:KSv)
            cout << x;
        cout << endl;
        return;
    }
    KSv.push_back(0);
    Knapsack(n-1);
    KSv.pop_back();
    KSv.push_back(1);
    Knapsack(n-1);
    KSv.pop_back();
}
vector<int> TSPv(10);
void TSP(int i, int n)
{
    if (i==n-1) {
        for_each (TSPv.begin(), TSPv.begin()+n,
                  [](int x){cout << x;});
        cout << endl;
        return;
    }
    for (int j=i; j<n; ++j) {
        swap(TSPv[i],TSPv[j]);
        TSP(i+1, n);
        swap(TSPv[i],TSPv[j]);
    }
}
void TSPt(int n)
{
    cout << "TSP exhaustive search for "
        << n << " cties" << endl;
    iota(TSPv.begin(), TSPv.end(), 1);
    TSP(0,n);
}

