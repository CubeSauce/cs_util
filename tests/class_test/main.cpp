#include <cstdio>
#include <cstdlib>

#include "cs/class.hpp"
#include "cs/containers/dynamic_array.hpp"

struct Derived_A : public Base_Class
{
    DERIVED_CLASS_BODY(Derived_A, Base_Class)
};

struct Derived_B : public Base_Class
{
    DERIVED_CLASS_BODY(Derived_B, Base_Class)
};

struct Derived_C : public Derived_B
{
    DERIVED_CLASS_BODY(Derived_C, Derived_B)
};

struct Derived_D : public Derived_C
{
    DERIVED_CLASS_BODY(Derived_D, Derived_C)
};

int main(int argc, char** argv)
{
    Base_Class base;
    Derived_A a; Derived_B b; Derived_C c; Derived_D d;
    Base_Class *base_a = &a, *base_b = &b, *base_c = &c, *base_d = &d;
  
    assert(Derived_A::is_a<Base_Class>());
    
    assert(Derived_B::is_a<Base_Class>());

    assert(Derived_C::is_a<Derived_B>());
    assert(Derived_C::is_a<Base_Class>());

    assert(Derived_D::is_a<Derived_C>());
    assert(Derived_D::is_a<Derived_B>());
    assert(Derived_D::is_a<Base_Class>());
  
    assert(!Derived_A::is_a<Derived_B>());
    assert(!Derived_B::is_a<Derived_A>());
    assert(!Derived_B::is_a<Derived_C>());

    Dynamic_Array<Base_Class*> classes = {
        base_a, base_b, base_c, base_d,
        base_b, base_c, base_d, base_a,
        base_c, base_d, base_a, base_b,
        base_d, base_a, base_b, base_c
    };

    for (Base_Class* base : classes)
    {
        switch(base->class_name())
        {
            case Derived_A::static_class_name:
            {
                printf("A Finding %s\n", base->class_name().c_str());
                break;
            }
            case Derived_B::static_class_name:
            {
                printf("B Finding %s\n", base->class_name().c_str());
                break;
            }
            case Derived_C::static_class_name:
            {
                printf("C Finding %s\n", base->class_name().c_str());
                break;
            }
            case Derived_D::static_class_name:
            {
                printf("D Finding %s\n", base->class_name().c_str());
                break;
            }
            default: return -1;
        }
    }

    return 0;
}