#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

void MenuTask()
{
    cout << "    Menu Task\n";
    cout << "    1.  Task 1\n";
    cout << "    2.  Task 2\n";
    cout << "    3.  Task 3\n";
    cout << "    4.  Exit\n";
}

// Base class
class Base
{
protected:
    int dat;

public:
    Base() : dat(1) {}
    Base(double d) : dat(d) {}
};

// Non-virtual classes
class D1 : protected Base
{
protected:
    int d1;

public:
    D1() : d1(1) {}
    D1(int d) : d1(d) {}
    D1(int d, int dt) : Base(dt), d1(d) {}
};

class D2 : protected Base
{
protected:
    int d2;

public:
    D2() : d2(1) {}
    D2(int d) : d2(d) {}
    D2(int d, int dt) : Base(dt), d2(d) {}
};

class E1 : protected Base, protected D1
{
protected:
    double e1;

public:
    E1() : e1(1) {}
    E1(int e) : e1(e) {}
    E1(int e, int et, int a, int b) : Base(et), D1(a, b), e1(e) {}
};

class E2 : protected Base, protected D2
{
protected:
    double e2;

public:
    E2() : e2(1) {}
    E2(int e) : e2(e) {}
    E2(int e, int et, int a, int b) : Base(et), D2(a, b), e2(e) {}
};

class R : protected E1, protected E2
{
protected:
    double r;

public:
    R() : r(1) {}
    R(int r) : r(r) {}
    R(int e1, int e2, int e3, int e4, int e5, int e6, int e7, int e8, double e9)
        : E1(e1, e2, e3, e4), E2(e5, e6, e7, e8), r(e9) {}
};

// Virtual classes
class D1V : virtual protected Base
{
protected:
    int d1;

public:
    D1V() : d1(1) {}
    D1V(int d) : d1(d) {}
    D1V(int d, int dt) : Base(dt), d1(d) {}
};

class D2V : virtual protected Base
{
protected:
    int d2;

public:
    D2V() : d2(1) {}
    D2V(int d) : d2(d) {}
    D2V(int d, int dt) : Base(dt), d2(d) {}
};

class E1V : virtual protected Base, virtual protected D1V
{
protected:
    double e1;

public:
    E1V() : e1(1) {}
    E1V(int e) : e1(e) {}
    E1V(int e, int et, int a, int b) : Base(et), D1V(a, b), e1(e) {}
};

class E2V : virtual protected Base, virtual protected D2V
{
protected:
    double e2;

public:
    E2V() : e2(1) {}
    E2V(int e) : e2(e) {}
    E2V(int e, int et, int a, int b) : Base(et), D2V(a, b), e2(e) {}
};

class RV : virtual protected E1V, virtual protected E2V
{
protected:
    double r;

public:
    RV() : r(1) {}
    RV(int r) : r(r) {}
    RV(int e1, int e2, int e3, int e4, int e5, int e6, int e7, int e8, double e9)
        : E1V(e1, e2, e3, e4), E2V(e5, e6, e7, e8), r(e9) {}
};

// Abstract class
class Function
{
public:
    virtual double calculate(double x) const = 0;
    virtual ~Function() {}
};

class Line : public Function
{
private:
    double a, b;

public:
    Line(double a, double b) : a(a), b(b) {}

    double calculate(double x) const override
    {
        return a * x + b;
    }
};

class Ellipse : public Function
{
private:
    double a, b;

public:
    Ellipse(double a, double b) : a(a), b(b) {}

    double calculate(double x) const override
    {
        return sqrt(1 - (x * x) / (a * a)) * b;
    }
};

class Hyperbola : public Function
{
private:
    double a, b;

public:
    Hyperbola(double a, double b) : a(a), b(b) {}

    double calculate(double x) const override
    {
        return sqrt((x * x) / (a * a) - 1) * b;
    }
};

// Entity classes
class Entity
{
protected:
    string name;

public:
    Entity() {}
    Entity(string name) : name(name) {}
    virtual ~Entity() {}
    virtual void printInfo()
    {
        cout << "Name: " << name << endl;
    }
    friend istream &operator>>(istream &in, Entity &entity)
    {
        cout << "Input name ";
        in >> entity.name;
        return in;
    }
    friend ostream &operator<<(ostream &out, const Entity &entity)
    {
        out << "Name: " << entity.name << endl;
        return out;
    }
};

class Worker : public Entity
{
protected:
    int salary;

public:
    Worker() {}
    Worker(string name, int salary) : Entity(name), salary(salary) {}
    ~Worker() override {}
    void printInfo() override
    {
        Entity::printInfo();
        cout << "Salary: " << salary << endl;
    }
    friend istream &operator>>(istream &in, Worker &worker)
    {
        in >> static_cast<Entity &>(worker);
        cout << "Input salary ";
        in >> worker.salary;
        return in;
    }
    friend ostream &operator<<(ostream &out, const Worker &worker)
    {
        out << static_cast<const Entity &>(worker);
        out << "Salary: " << worker.salary << endl;
        return out;
    }
};

class FamilyParent : public Entity
{
protected:
    int children;

public:
    FamilyParent() {}
    FamilyParent(string name, int children) : Entity(name), children(children) {}
    ~FamilyParent() override {}
    void printInfo() override
    {
        Entity::printInfo();
        cout << "Number of children: " << children << endl;
    }
    friend istream &operator>>(istream &in, FamilyParent &parent)
    {
        in >> static_cast<Entity &>(parent);
        cout << "Input number of children ";
        in >> parent.children;
        return in;
    }
    friend ostream &operator<<(ostream &out, const FamilyParent &parent)
    {
        out << static_cast<const Entity &>(parent);
        out << "Number of children: " << parent.children << endl;
        return out;
    }
};

class WorkerFamilyParent : public Worker, public FamilyParent
{
public:
    WorkerFamilyParent() {}
    WorkerFamilyParent(string name, int salary, int children) : Worker(name, salary), FamilyParent(name, children) {}
    ~WorkerFamilyParent() override {}
    void printInfo() override
    {
        Worker::printInfo();
        cout << "Number of children: " << children << endl;
    }
    friend istream &operator>>(istream &in, WorkerFamilyParent &workerParent)
    {
        in >> static_cast<Worker &>(workerParent);
        cout << "Input number of children ";
        in >> workerParent.children;
        return in;
    }
    friend ostream &operator<<(ostream &out, const WorkerFamilyParent &workerParent)
    {
        out << static_cast<const Worker &>(workerParent);
        out << "Number of children: " << workerParent.children << endl;
        return out;
    }
};

int main()
{
    MenuTask();

    int choice;

    do
    {
        cout << "Choice ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Task 1
        {
            R a, b(1, 2, 3, 4, 5, 6, 7, 8, 9.1);
            RV av, bv(1, 2, 3, 4, 5, 6, 7, 8, 9.1);

            cout << "Non-virtual" << endl;
            cout << "Base size = " << sizeof(Base) << endl;
            cout << "D1 size = " << sizeof(D1) << endl;
            cout << "D2 size = " << sizeof(D2) << endl;
            cout << "E1 size = " << sizeof(E1) << endl;
            cout << "E2 size = " << sizeof(E2) << endl;
            cout << "R size = " << sizeof(R) << endl;
            cout << endl;

            cout << "Virtual" << endl;
            cout << "D1V size = " << sizeof(D1V) << endl;
            cout << "D2V size = " << sizeof(D2V) << endl;
            cout << "E1V size = " << sizeof(E1V) << endl;
            cout << "E2V size = " << sizeof(E2V) << endl;
            cout << "RV size = " << sizeof(RV) << endl;
            choice = 3;
            break;
        }
        case 2: // Task 2
        {
            double a, b, x;

            cout << "Input a, b for line ";
            cin >> a >> b;
            Line line(a, b);
            cout << "Input a, b for ellipse ";
            cin >> a >> b;
            Ellipse ellipse(a, b);
            cout << "Input a, b for hyperbola ";
            cin >> a >> b;
            Hyperbola hyperbola(a, b);
            cout << "Input x ";
            cin >> x;

            cout << "Line" << endl;
            cout << "y = " << line.calculate(x) << endl;
            cout << "Ellipse" << endl;
            cout << "y = " << ellipse.calculate(x) << endl;
            cout << "Hyperbola" << endl;
            cout << "y = " << hyperbola.calculate(x) << endl;
            choice = 3;
            break;
        }
        case 3: // Task 3
        {
            Worker worker;
            cin >> worker;
            cout << worker;

            FamilyParent parent;
            cin >> parent;
            cout << parent;

            WorkerFamilyParent workerParent;
            cin >> workerParent;
            cout << workerParent;
            choice = 3;
            break;
        }
        case 4: // Exit
            break;
        default:
            cout << "Invalid choice\n";
            break;
        }
    } while (choice != 3);

    return 0;
}