
#include <iostream>
#include <string>
#include <vector>

class Base
{
public:
    Base(const std::string& id) :
        id_{id}
    {}

    void write() const
    {
        std::cout << id_ << std::endl;
    }

protected:
    std::string id_{""};
};

class Derived1 : public Base
{
public:
    Derived1() :
        Base{"derived class #1"}
    {}
};

class Derived2 : public Base
{
public:
    Derived2() :
        Base{"derived class #2"}
    {}
};

int main(int argc, char const* argv[])

{
    // create vars
    auto d1 = Derived1{};
    auto d2 = Derived2{};
    std::vector<Base> container{};

    // shove derived classes into container by base class
    container.push_back(static_cast<Base>(d1));
    container.push_back(static_cast<Base>(d2));

    // loop over container to view results
    for (const auto& entry : container)
    {
        entry.write();
    }
    return 0;
}
