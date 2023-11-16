 ## Задачи

**Задача 1:** Даден е списък **l** с елементи списъци от естествени числа в интервала [0,..,9]. От всеки списък l_i получаваме две числа по следния начин:  
- Обхождайки го отпред назад, получваме число n_i.  
- Обхождайки го отзад напред, получаваме число n_i_reversed.  

Да се дефинира функция, която *намира сумата n_i + n_i_reversed за 0 <= i <= l.size() - 1*.  

*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
1 -> 2                        809
|                             (12 + 21 + 234 + 432 + 55 + 55)
v
2 -> 3 -> 4
|
v
empty
|
v
5 -> 5
```

**Задача 2 (Контролно 2021):** Даден е списък **l** с n елемента.  
Да се дефинира функция *shuffle()*, която получава адреса на първия елемент на списъка. Функцията да пренарежда възлите на списъка така, че *елементите от втората половина на списъка да се преместят в началото на списъка, но в обратен ред* (при списъци с нечетен брой елементи считаме средния елемент за принадлежащ към първата половина на списъка).  

*Пример:*
*L1 → L2 → L3 → L4 → L5 се преобразува до L5 → L4 → L1 → L2 → L3*  

**Задача 3 (Контролно 2021):** Даден е списък **l** с елементи стекове.  
Да се дефинира функция *equalize(l)*, която размества елементите на стековете така, че *да няма два стека в l с разлика в броя на елементите, по-голяма от 1*.  

*Пример:*  
*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
5 -> 4 -> 3 -> 2 -> 1         5 -> 4 -> 3
|                             |
v                             v
7 -> 6                        7 -> 6 -> 1
|                             |
v                             v
11 -> 10 -> 9 -> 8            11 -> 10 -> 9
|                             |
v                             v
12                            12 -> 2 -> 8
```