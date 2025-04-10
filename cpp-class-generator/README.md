## ⚙️ Utilisation

### Cloner le dépôt :

```
git clone https://github.com/agraille/automatisation_scripts.git
```
```
cd automatisation_scripts/cpp-class-generator && make
```
```
./canonClassGenerator /path/dest "Enter one or more class"
```

## Sortie:
```c++
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
