# Свързани списъци 


# Свързани списъци
Свързания списък е линейна структура от данни в която елементите не се пазят в последователна памет. Всеки елемент пази указател към следващия а ако няма следващ пазим nullptr.

```cpp
template<class T>
struct LinkedListNode {
    T data;
    LinkedListNode<T>* next;

    // Удобен конструктор!
    LinkedListNode(const T& elem, LinkedListNode<T>* n = nullptr) : data{elem}, next {n} {} 
}
```
Тук е добро място да си поговорим какво наричаме пряк и последователен достъп (или Random/direct access и Sequential access). 
* При прекия достъп можем да достъпим всеки елемент от колекцията за равно време
* При последователния достъп не можем да достъпим елемент преди да сме обходили елементите преди него в наредбата.

Свързания списък е добър пример за структура с последователен достъп. Пряк достъп имат масивите.
Има различни видове свързани списъци с които ще се занимаваме с течение на курса.
Едносвързания списък поддържа следните операции:
* push_front(const T& elem) - Добавя елемент в началото O(1)
* push_at(size_t idx, const T& elem) - Добавя елемент на индекс. O(n)
* pop_front() - Премахва елемента в началото - O(1)
* pop_at(size_t index) - Премахва елемента на позиция index O(n)

Свързания списък стандартно се представя чрез указател към първия му елемент. Доста често обаче се пази и указател към последния. Това ни помага да имаме бързо добавяне в края на списъка. Наистина, представяме списъка като два указателя - към първия и последния елемент и искаме да обединим два такива списъка това би станало за O(1) време. 

```cpp
template<class T>
class LinkedList {
private:
    struct LinkedListNode {
        T data;
        LinkedListNode<T>* next;
    };

    LinkedListNode* head;        // Началото на списъка
    LinkedListNode* tail;        // Края на списъка

public:
    void merge(const LinkedList<T>& second) {
        // O(1) сливане на два списъка без значение от размерите им
        tail->next = second.head;
        tail = second.tail;
    }
};

```
Също така, ако имаме указател към дадена позиция в списъка, можем да добавяме колкото си искаме елементи на тази позиция. Всичко става чрез пренасочване на пойнтъри.
Засега ще представяме свързания списък просто като структура с информация и указател. В следващите семинари ще разгледаме алтернативни представяния и ще видим колко точно ефикасни са спрямо дадени операции!

## Итератори
Тук на помощ идват итераторите. Итераторите са обекти, които са отговорни за обхождане на контейнери (динамичен масив, свързан списък и тн). В *C++* голяма част от STL използва итератори за постигане на целите си. 
Примерната реализация, с която ще работим, се намира във файла LinkedList.hpp. Представяме свързания списък с два указателя, където
* head сочи към първия (най-левия) елемент
  
* tail сочи към последния (най-десния) елемент
  

* Също така пазим още една допълнителна променлива от тип size_t за дължината на списъка.
   
Разгледайте реализацията, особено алгоритмите за добавяне и премахване в началото и в края. Забележете, че всеки път разглеждаме три случая:
* Дали листа е празен
* Дали листа има един елемент
* Дали листа има повече от един елемент

Вече имаме някаква примерна реализация на свързан списък. Хайде да си направим итератор и да видим колко точно сложно ще е. 
Ще направим итератора **вътрешен и публичен клас за класа LinkedList**.
```cpp
// ...
public:
class Iterator {
    private:

    public:

};
// ...
```
Сега, какво трябва да имаме в този клас? Той е отговорен за предвижване по възлите на свързания списък. Когато се придвижваме във всеки момент имаме някой текущ елемент. Следователно ще ни трябва текущ елемент. Също така, ще ни трябва начин да създадем итератор към някой елемент.
След курса по ООП това е лесна задача:
```cpp
class Iterator {
    private:
        // Текущия възел в обхождането
        LinkedListNode* currentNode;

        Iterator(LinkedListNode* arg) : currentNode { arg } {} 
    public:
};
```
Искаме да обхождаме, значи ни трябва някакъв начин да се придвижим напред. Конвенцията е тази задача да се изпълнява от operator++.
Това става по следния начин:
```cpp
// Забележете, че връщаме итератор!
Iterator& operator++() {
    // Ако сме стигнали края не правим нищо
    if(currentNode == nullptr)
        return *this;
    
    // Преместваме се една позиция надясно
    currentNode = currentNode->next;

    return *this;
}
```
Супер, вече имаме ++it. Но ще е добре и да си направим it++, не знаем за какво ще ни потрябва.

```cpp
// Защо този път връщаме Iterator а не Iterator&?
// Защото този път връщаме temporary object наречен temp. Той е заделен статично и ще се унищожи когато стигнем края на скоупа

Iterator operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
```
Напомняме, че разликата между префиксния и постфиксния operator++ е просто един "служебен" int като аргумент на постфиксния.

Супер, вече можем да се движим, но това движение става безполезно ако нямаме начин да видим каква информация имаме в currentNode. Тази задача по конвенция се изпълнява от operator\*. Супер, нека го предефинираме:
```cpp
T& operator*() {
    return currentNode->data;
}
```
Също ни трябва начин да разберем дали два итератора са равни или не. Тази задача се изпълнява от *operator==* и *operator!=*

```cpp
bool operator==(const Iterator& other) const {
    // Сравняваме ги по адреси!
    return other.currentNode == currentNode;
}

bool operator!=(const Iterator& other) const {
    return !(*this == other);
}
```
Повечето контейнери в STL имате методи begin() и end(), които връщат итератори към началото и края. Нека последваме примера им:
```cpp
Iterator begin() {
    return Iterator(head);
}

Iterator end() {
    return Iterator(nullptr);
}
```
Ние направихме конструктора на итератора private. За да извикаме Iterator(head) обаче трябва някак да имаме достъп до private конструктора на Iterator.
Това ще направим като декларираме класа LinkedList като приятелски за Iterator!
```cpp
/// ...
bool operator!=(const Iterator& other) const {
    return !(*this == other);
}
    friend class LinkedList;
/// ...
```
Вече сме готови. Нека да проверим дали нашия метод работи:
```cpp
int main() {
    LinkedList<int> ll;

    for (size_t i = 0; i < 10; i++)
        ll.pushBack(i);
    // Тук има значение дали викаме ++it или it++!
    for(LinkedList<int>::Iterator it = ll.begin(); it != ll.end(); ++it)
        std::cout << *it << " ";
}
```

## Const и итераторите
Нека разгледаме следния код:
```cpp
int main() {
    const LinkedList<int> ll;
    LinkedList<int>::Iterator beg = ll.begin();
}
```
В случая имаме грешка, понеже нямаме декларирана константна функция begin(). Нека си напишем константни begin() и end():
```cpp
const Iterator begin() const {
    return Iterator(head);
}
const Iterator end() const {
    return Iterator(nullptr);
}
```
Горния фрагмент код се компилира, но вече имаме друг проблем:
```cpp
void hack(const LinkedList<int>& ll) {
    LinkedList<int>::Iterator beg = ll.begin();
    *beg = 10;
}

int main() {
    LinkedList<int> ll;
    ll.pushBack(1);
    hack(ll);
    std::cout << ll.back();
}
```
В случая, въпреки че ll е const, отново променяме стойността му. Но защо?

В случая **beg е константен**. Той е съставен от един пойнтър, който обаче **не е константен**. В някакъв смисъл **това, че стойността на паметта към която сочи пойнтъра се променя не чупи константността на итератора**. За това ще се наложи да дефинираме още един клас, ConstIterator!
```cpp
class ConstIterator {
    private:
        // Тук вече е указател към константна памет
        const LinkedListNode* currentNode;

        ConstIterator(LinkedListNode* arg) : currentNode { arg } {}  
    public:

    ConstIterator& operator++() {
        if(currentNode == nullptr)
            return *this;
        currentNode = currentNode->next;
        return *this;
    }

    ConstIterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    const T& operator*() const {
        return currentNode->data;
    }

    bool operator==(const ConstIterator& other) const {
        return other.currentNode == currentNode;
    }

    bool operator!=(const ConstIterator& other) const {
        return !(*this == other);
    }

    friend class LinkedList;
};
```

Нещата са доста подобни, единствената разлика тук е, че имаме константен указател като тип на текущия елемент.

Реализираме следните:
```cpp
// Връща константен итератор към началото
ConstIterator cbegin() const {
    return ConstIterator(head);
}

// Връща константен итератор към края
ConstIterator cend() const {
    return ConstIterator(nullptr);
}
```
Сега, ако искам да имам итератор за константен списък, просто ще създавам ConstIterator. Примерно, искаме да итерираме константен свързан списък:

```cpp
void iterate(const LinkedList<int>& ll){
    for(LinkedList<int>::ConstIterator it = ll.cbegin(); it != ll.cend(); ++it) {
        std::cout << *it << " ";
    }
}
```

## auto
Най - вероятно вече сте чували за ключовата дума *auto*. Чрез нея карате компилатора сам да прецени какъв тип да използва за променливата. Тя е удобна когато имате дълги типове. Прави кодът по-четим и разбираем. Като всяко хубаво нещо обаче **с auto не е добре да се прекалява.**

```cpp
// Автоматично разбирам типа на it
for(auto it = ll.begin(); it != ll.end(); ++it) {
    //...
}

auto x = 5;         // х е променлива от тип int
const auto y = 10u; // y e променлива от тип const unsigned
auto f = 10.0f;     // f е променлива от тип float
const auto& r = f;  // r е променлива от тип const float&

std::list<int> ll;

auto it = ll.begin(); // it e променлива от тип std::list<int>::iterator
const auto its = ll.end(); // it е променлива от тип ?
auto itss = ll.cend(); // it е променлива от тип ?
```

## range based for loops
От c++11 езикът ни предлага начин, чрез който да пишем подобни for цикли още по - бързо.
```cpp
int main() {
    LinkedList<int> ll;

    for(const int& elem : ll) {
        std::cout << elem << " ";
    }
}
```
Този цикъл е еквивалентен на горния, просто е синтактична захар.

За по - любопитните  компилатора развива този приятен for цикъл до следното:

```cpp
{
    LinkedList<int> & __range1 = ll;

    LinkedList<int>::Iterator __begin1 = __range1.begin();

    LinkedList<int>::Iterator __end1 = __range1.end();

    for(; __begin1.operator!=(__end1); __begin1.operator++()) {
      const int & elem = __begin1.operator*();
      std::operator<<(std::cout.operator<<(elem), " ");
    }
}
```

