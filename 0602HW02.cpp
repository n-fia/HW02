// 0602HW02.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
/*
- zoo 클래스의 소멸자가 모든 동적 할당된 객체를 메모리에서 올바르게 해제하는지 확인
- zoo 클래스의 addAnimal()함수가 요구사항에 따라 동물을 추가할수 있는지 확인
- zoo 클래스 내에 animals 배열이 있으며, 해당 배열의 크기가 제한
- 배열에 새로운 항목을 추가할 때, 제한된 크기를 고려하여 배열의 크기를 동적으로 확장하거나 적절히 처리하는 예외 사항이 반영되었는지 확인
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Animal {
public:
    virtual void makeSound() = 0; //순수 가상 함수
    virtual ~Animal() {}   //메모리 누수를 막기 위한 소멸자
};
class Dog : public Animal{
public:
    void makeSound() {
        cout << "mang mang mang";
    }
};
class Cat : public Animal {
public:
    void makeSound() {
        cout << "myang myang myang";
    }
};
class Cow : public Animal {
public:
    void makeSound() {
        cout << "ummmmmea";
    }
};
class Zoo {
private:
    Animal* animals[10] = {}; //동물 객체를 저장할 포인터 배열 animal
public :
    // 동물을 동물원(animals)에 추가하는 함수
    // - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
    // - 같은 동물이라도 여러 번 추가될 수 있습니다.
    // - 입력 매개변수: Animal* (추가할 동물 객체)
    // - 반환값: 없음
    void addAnimal(Animal* animal) { //매개변수 : animal 포인터
        for (int i = 0; i < 10; i++) {
            if (animals[i] == nullptr) {
                animals[i] = animal;
                i = 10;
            }
        }
    };

    //모든 동물의 행동을 수행
    // - 모든 소리를 내고 '움직이는' 동작
    void performActions() {
        for (int i = 0; i < 10; ++i) {
            if (animals[i] != nullptr) {
            animals[i]->makeSound();
            cout <<" " << animals[i] << " is move\n";
            }
        }
    };

    // Zoo 소멸자
    // - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
    // - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
    ~Zoo() {
    };
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
    cout << "Hello World!\n"<<endl;

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
    zoo.performActions();   // animals 배열의 동물울음소리를 전부 호출

    //생성한 전체 울음소리 함수 호출
    for (int i = 0; i< animal.size(); ++i) {
        cout << i+1 << "번 동물 울음소리 : ";
        animal[i]->makeSound();
        cout << endl;
    }

    //메모리해제
    for (int i = 1; i < animal.size(); ++i) {   //스택인 dog 제외하고 해제
        delete animal[i];
    }

    return 0;
}