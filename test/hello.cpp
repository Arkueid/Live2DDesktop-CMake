#include <stdio.h>

class B
{
public:
    virtual void print() = 0;
};

class C
{
public:
    C();
    virtual ~C(); 
};


class A: public C,  public B
{
public:
    int aa;
    A()
    {

    }
    virtual ~A();
private:
    int a, piece;
    void print()
    {
        printf("Hello, world!\n");
    }
};

C::C()
{

}

C::~C()
{

}

A::~A()
{

}

int main()
{
    A a;
    B* b = (B*)&a;
    b->print();
    return 0;
}