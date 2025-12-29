#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

class Izd{
    private:
        string name;
        string author;
    public:
        string getname(){
            return name;
        }
        string getauthor(){
            return author;
        }
        Izd(string n, string a):name(n), author(a){};
        
};

class Book:public Izd{
    private:
        int year;
        int pages;
    public:
        int getyear(){
            return year;
        }
        int getpages(){
            return pages;
        }
        Book(string n, string a, int y, int p):Izd(n,a), year(y), pages(p){};
        ~Book(){cout << "\nКнига Удалена";}
        void getinfo(){
            cout <<"name: " << getname() << "\nauthor: " << getauthor()
                <<"\nyear: " << getyear() << "\npages: " << getpages();
        }
};

int main() {
	// your code goes here
    Book a("oop", "someone",1978,90);
    a.getinfo();
}
