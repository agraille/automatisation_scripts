## ⚙️ Utilisation

### Cloner le dépôt :

```
git clone https://github.com/agraille/automatisation_scripts.git
```
```
cd cpp-class-generator && make
```
```
./canonClassGenerator "Enter one or more class"
```

## Sortie:
```c++
// MyClass.hpp
#ifndef MYCLASS_HPP
#define MYCLASS_HPP

class MyClass {

  public:
      MyClass();
      MyClass(const MyClass& other);
      ~MyClass();
      MyClass& operator=(const MyClass& other);
  
  private:
    // membres privés
};

#endif // MYCLASS_HPP
```
```c++
// MyClass.cpp
#include "MyClass.hpp"

MyClass::MyClass(){
}

MyClass::MyClass(const MyClass& copy){
    // copie member
}

MyClass::~MyClass(){
}

MyClass& MyClass::operator=(const MyClass& other){
    if (this != &other) {
        // copie member
    }
    return *this;
}

```
