class IA
{
public:
    virtual void getName() = 0;
};

class B
{
public:
    void getName()
    {

    }
};

class C: public IA, public B
{
public:
    void getName();
};

int main()
{
    C c;
    c.getName();
    return 0;
}