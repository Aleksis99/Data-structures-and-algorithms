## Анализ на алгоритми
Да бъде **анализиран** даден алгоритъм означава да бъде доказано, че той е **коректен**, и ако е коректен, да бъде  
изчислено колко **ресурси ползва** - за всеки възможен вход - като ресурсите са основно **време** и **памет**.  

В този курс ще разглеждаме само втората част от анализа на алгоритми - **сложността**.  

**“Сложност на алгоритъм”** е мярка за това **колко ресурси полза този алгоритъм.** За какви ресурси става дума?  
1. **Време.** Искаме алгоритмите ни да работят бързо.   
В този смисъл, “качествен алгоритъм” е алгоритъм, който работи бързо върху *всички* входове.  
2. **Памет.** Искаме алгоритмите ни да ползват малко памет.  
В този смисъл, “качествен алгоритъм” е алгоритъм, който ползва малко памет върху *всички* входове.  

**Сложността по време** е мярка, която ни казва как нараства времето за изпълнение на даден алгоритъм, когато  големината на входа му клони към *безкрайност*.  
**Сложността по памет** е мярка, която ни казва как нараства паметта, която даден алгоритъм ползва, когато големината на входа му клони към *безкрайност*.  

Когато разглеждаме сложността по време на алгоритми, разглеждаме *три* случая:  

 - Най-добър случай (**Best case**)  
 - Среден случай (**Average case**)  
 - Най-лош случай (**Worst case**)  
 
 Коя е най-ценната величина от трите?  
**Средният случай!** ..*Но:*  
 -   Средното време за работа обикновено се определя трудно.  
 -   Ще се фокусираме върху времето за работа **в най-лошия случай**.  


## Какво беше това сложност?

Θ(g(n)) = { f(n) | ∃c<sub>1</sub>, c<sub>2</sub> > 0, ∃n<sub>0</sub> : ∀n ≥ n<sub>0</sub>, 0 ≤ c<sub>1</sub>.g(n) ≤ f(n) ≤ c<sub>2</sub>.g(n) }
	
f(n) ≈ g(n) ⇔ f(n) = Θ(g(n)) 

### Нестрога горна граница

O(g(n)) = { f(n) | ∃c > 0, ∃n<sub>0</sub> : ∀n ≥ n<sub>0</sub>, 0 ≤ f(n) ≤ c.g(n) }

f(n) <= g(n) ⇔ f(n) = O(g(n)) 
	
### Нестрога долна граница
Ω(g(n)) = { f(n) | ∃c > 0, ∃n<sub>0</sub> : ∀n ≥ n<sub>0</sub>, 0 ≤ c.g(n) ≤ f(n) }

f(n) ≺ g(n) ⇔ f(n) = o(g(n)) 
	

### Строга горна граница

o(g(n)) = { f(n) | ∀c > 0, ∃n<sub>0</sub> : ∀n ≥ n<sub>0</sub>, 0 ≤ f(n) < c.g(n) }

f(n) >= g(n) ⇔ f(n) = Ω(g(n)) 
	
### Строга долна граница

ω(g(n)) = { f(n) | ∀c > 0, ∃n<sub>0</sub> : ∀n ≥ n<sub>0</sub>, 0 ≤ c.g(n) < f(n) }
	
f(n) ≻ g(n) ⇔ f(n) = ω(g(n)) 

## Кои бяха основните сложности с примери?

Big O Notation | Name | Example(s)
------------ | ------------- | ---------
O(1) | Constant | **Odd or Even number** <br>**Look-up table (on average)**
O(log n) | Logarithmic | **Finding element on sorted array with binary search**
O(n) | Linear | **Find max element in unsorted array**
O(n log n) | Linearithmic | **Sorting elements in array with merge sort**
O($n^2$) | Quadratic | **Duplicate elements in array (naïve)**
O($n^3$) |	Cubic | **3 variables equation solver**
O($2^n$) |	Exponential	| **Find all subsets**
O(n!) | Factorial | **Find all permutations of a given set/string**

## Защо ме вълнува сложнстта?

| n | O(1) | O(log n) | O(n) | O(n log n) | O($n^2$) | O($2^n$) | O(n!)
| - | - | - | - | - | - | - | - 
| 1	        | < 1 sec |	< 1 sec |	< 1 sec	| < 1 sec	| < 1 sec	| < 1 sec	            | < 1 sec
| 10	        | < 1 sec |	< 1 sec |	< 1 sec	| < 1 sec	| < 1 sec	| < 1 sec	            | 4 sec
| 100	        | < 1 sec |	< 1 sec |	< 1 sec	| < 1 sec	| < 1 sec	| 40170 trillion years	| > vigintillion years
| 1,000	    | < 1 sec |	< 1 sec |	< 1 sec	| < 1 sec	| < 1 sec	| > vigintillion years	| > centillion years
| 10,000	    | < 1 sec |	< 1 sec |	< 1 sec	| < 1 sec	| 2 min	    | > centillion years	| > centillion years
| 100,000	    | < 1 sec |	< 1 sec |	< 1 sec	| 1 sec	    | 3 hours	| > centillion years	| > centillion years
| 1,000,000	| < 1 sec |	< 1 sec |	1 sec	| 20 sec	| 12 days	| > centillion years	| > centillion years


