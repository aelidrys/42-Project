#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
public:
    // Virtual method table under the hood
    virtual int v_fun(N &other) {
        // Some overloaded arithmetic logic...
    }

    N(int value) {
        this->id = value;
    }

    void setAnnotation(char *str) {
        // Vulnerable copy happening inside here!
        strcpy(this->annotation, str); 
    }

private:
    int id;
    char annotation[100]; // Allocated inside the class structure
};

int main(int argc, char **argv) {
    // 0x80485fe: cmpl $0x1, 0x8(%ebp) -> if (argc <= 1)
    if (argc <= 1) {
        exit(1); 
    }

    // 0x8048610: allocates 0x6c (108 bytes) for Object 1
    N *n1 = new N(5);   // stored at 0x1c(%esp) (0x804a008)

    // 0x8048632: allocates 0x6c (108 bytes) for Object 2
    N *n2 = new N(6);   // stored at 0x18(%esp) (0x804a078)

    // 0x8048664: grabs argv[1] and sets annotation on n1
    n1->setAnnotation(argv[1]);

    // 0x804867c - 0x8048693: Virtual Function Call!
    // Triggers an operator operation or virtual method call:
    n2->v_fun();

    return 0;
}