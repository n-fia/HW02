// 0602HW02.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Animal {
public:
    virtual void makeSound() = 0;
    virtual ~Animal() {}
};
class Dog : public Animal{
public:
    void makeSound() {
        cout << "mang mang mang\n";
    }
};
class Cat : public Animal {
public:
    void makeSound() {
        cout << "myang myang myang\n";
    }
};
class Cow : public Animal {
public:
    void makeSound() {
        cout << "ummmmmea\n";
    }
};
class Zoo {
private:
    Animal* animals[10] = {};
public :

    void addAnimal(Animal* animal) {
        for (int i = 0; i < 10; i++) {
            if (animals[i] == nullptr) {
                animals[i] = animal;
                i = 10;
            }
        }
    };

    void performActions() {
        for (int i = 0; i < 10; ++i) {
            if (animals[i] != nullptr) {
            animals[i]->makeSound();
            }
        }
    };

    ~Zoo() { };
};

Animal* createRandomAnimal() {
    // 랜덤 동물을 생성하는 함수
    int num = rand() % 3;   //0부터 2까지 랜덤 정수 생성

    Animal* ranAnimal;

    switch (num) {
        case 0:
            ranAnimal= new Dog();
            break;
        case 1:
            ranAnimal = new Cat();
            break;
        default:
            ranAnimal = new Cow();
            break;
    }
    return ranAnimal;
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); //랜덤 시드 생성

    vector<Animal*> animal;
    Dog dog;
    Zoo zoo;

    animal.push_back(&dog);         // 스택에 저장 > delete하면 안 됨. 이중 delete
    animal.push_back(new Cat());    // 힙에 저장 > detele해야 됨.
    animal.push_back(new Cow());

    cout << "동물원의 랜덤 동물 울음소리\n";
    for (size_t i = 0; i < 10; i++)
    {
    zoo.addAnimal(createRandomAnimal());    //addAnimal 함수 10번(계속 createRandomAnimal이 호출)
    }
    zoo.performActions();   // animals 배열의 동물 울음소리 호출

    //생성한 모든 동물의 울음소리 함수 호출
    for (int i = 0; i< animal.size(); ++i) {
        cout << i+1 << "번 동물 울음소리 : ";
        animal[i]->makeSound();
    }

    //메모리해제
    for (int i = 1; i < animal.size(); ++i) {   //스택인 dog 제외하고 해제
        delete animal[i];
    }

    return 0;
}