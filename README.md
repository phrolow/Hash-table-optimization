# Оптимизация хеш-таблиц

Доброго дня всем читающим! В этом проекте я исследовал возможности оптимизации времени поиска в хеш-таблицах. Таким образом, моя работа не ставит целью оптимизировать время заполнения хеш-таблицы и удаления элементов из неё или же сократить расход памяти - я хочу понять цену и предел оптимизации по времени.
## О хеш-таблицах

**Хеш-таблица** — это структура данных, реализующая интерфейс ассоциативного массива, а именно, она позволяет хранить пары (ключ, значение) и выполнять три операции: операцию добавления новой пары, операцию удаления и операцию поиска пары по ключу.

В этом проекте я работаю с **хеш-таблицами, основанными на методе цепочек**. Такая хеш-таблица представляет собой массив спиков, при этом номер списка, где хранится значение, вычисляется хеш-функцией от ключа; каждое новое значение добавляется в хвост списка. 

![Хуеш-таблица](/images/Hash_table.jpg)

**Хеш-функция** - функция, принимающая массив входных данных произвольной длины и возвращающая битовую последовательность установленной длины. В нашем случае хеш-функции принимают строку и возвращают 32 бита.

Также я активно использую термин **коллизия** - два различных входных блока данных *x* и *y* для хеш-функции *H* таких, что *H(x)=H(y)*.
 ## Входные данные

Представлю данные своего ноутбука:
 - **Процессор** AMD Ryzen 3 4300U со встроенной видеокартой
 - **Оперативная память** 12 ГБ
 - **ОС** Ubuntu 22.04.2 LTS 64-bit

О софтовой части. Я сохранял в хеш-таблицу английский текст трагедии Шекспира "Гамлет". С целью получить при наилучшем распределении в среднем 10-20 слов в списке, я использовал хеш-таблицу размером **317**; выбор числа также обусловлен тем, что хеш-таблицы, имеющие размером простое число, имеют меньше коллизий. Для таблиц использованы [двусвязные списки](https://github.com/phrolow/List), написанные мной полугодом раннее.

На данном этапе программа компилируется без какой-либо оптимизации, в т. ч. без флагов.

 ## Начало работы

Сначала я решил найти оптимальную для поиска хеш-функцию. В этой части работы я буду сравнивать время работы и равномерность распределения длин списков. Распределение проще просмотреть, если взять размер хеш-таблицы, при котором на список приходится в среднем 10-20 слов; также учтём, что если размер - простое число, то число коллизий снижается. Этим условиям удовлетворяет число **317**, его я и взял за размер.

Первым делом я прогнал текст через [препроцессор](https://github.com/phrolow/Hash-table-optimization/tree/main/src/Preprocessor), заменяющий все символы, не являющиеся буквами, символом '\0'. Это сделано для упрощения загрузки текста в основную программу и исключения таких ситуаций, когда два одинаковых слова могут быть восприняты как разные (на самом деле, не играет большой роли, однако приближает к реальной ситуации).

Далее я запустил основную программу (hasht). Она считывает текст из файла (с рассчётом на то, что слова уже отделены '\0') и сохраняет в предназначенную для этого структуру. Затем запускается цикл, в каждой итерации которого создаётся хеш-таблица с новой хеш-функцией, и в неё загружается текст. После этого происходит замер суммарного времени поиска каждого слова из текста, а в файл **/data/spreading.csv** сохраняется табличная строка с длинами списков хеш-таблицы.

 ## Сравнение хеш-функций

 ### hash1

![hash1](/images/histogram_hash1.png)

Хеш-функция **hash1** возвращает значение **1** независимо от аргумента. Понятное дело, в силу числа коллизий мы имеем ужасное распределение длин списков и достаточно большое время поиска - **510.684 мс**.

 ### hashFirstLetter

![hashFirstLetter](/images/histogram_hashFirstLetter.png)

Хеш-функция **hashFirstLetter** возвращает ASCII-код первой буквы строки. В силу довольно ограниченного диапазона значений опять же наблюдаем множество коллизий, неоптимальное распределение длин списков и далеко не лучшее время поиска - **58,361 мс**.

 ### hashWordLen

![hashWordLen](/images/histogram_hashWordLen.png)

Хеш-функция **hashWordLen** возвращает длину строки (а именно, значение **strlen**). Опять же, диапазон сильно ограничен, коллизий много, распределение плохое (сравнимо с предыдущей функцией), время поиска оказалось даже больше - **75,953 мс**

 ### hashSum

![hashSum](/images/histogram_hashSum.png)

Хеш-функция **hashSum** возвращает сумму ASCII-кодов символов строки. В нашем случае за счёт сравнительно малого размера хеш-таблицы мы получаем не так много коллизий, более равномерное распределение, чем у предыдущих функций, и значительно меньшее время поиска - всего **6,584 мс**. Тем не менее, при достаточно большой хеш-таблице начиная с некоторого номера средняя длина списка бы сильно уменьшилась, и в таком случае функция была бы мало применима для большого числа данных.

 ### hashRol

![hashRol](/images/histogram_hashRol.png)

Хеш-функция **hashRol** вычисляется следующим образом (псевдокод):

> H0 = 0
> Hi+1 = rol(Hi) xor string[i + 1]

, где rol - циклический побитовый сдвиг на один бит влево.

Для более полного понимания привожу код:

```
unsigned int hash = 0;
    
size_t len = strlen(word);

for (size_t i = 0; i < len; ++i)
{
    hash = ((hash >> 31) | (hash << 1)) xor word[i];
}

return hash;
```

Наблюдаем довольно равномерное распределение. Время работы - **5,919 мс**. Я решил проверить, насколько сильно влияет направление циклического сдвига и рассмотрел циклический сдвиг вправо.

 ### hashRor

![hashRor](/images/histogram_hashRor.png)

Хеш-функция **hashRor** отличается от **hashRol** лишь тем, что вместо циклического сдвига влево использует циклический сдвиг вправо.

Время работы - **6,074 мс**. Наблюдаем распределение менее равномерное, чем у **hashRol**; это связано с тем, что ASCII-коды всех букв в двоичном виде имеют единицы в 6 и 7 битах, и если в **hashRol** они уходят влево в пустую область (а сдвигов для любого слова происходит меньше, чем битов в переменной с хешом, т. е. они никогда не попадут в конец двоичной записи), то в **hashRor** при применении побитового XOR они обнуляют младшие единичные биты, что должно создавать больше коллизий. В подтверждение своих рассуждений приведу графики для вариантов функций, где я отнимаю  0x60 от ASCII-кодов символов:

![hashRol](/images/histogram_hashrol_sub0x60.png)

![hashRor](/images/histogram_hashror_sub0x60.png)

<details>
  <summary>Код измененной hashRol</summary>
  
  ```c
  unsigned int hash = 0;
    
    size_t len = strlen(word);

    for (size_t i = 0; i < len; ++i)
    {
        hash = ((hash >> 31) | (hash << 1)) xor word[i];
    }

    return hash;
  ```
  
</details>

Видно, что, избавившись от этих двух налезающих битов, мы получили действительно похожие распределения.
 ### murmurHash2

Далее я решил рассмотреть хеш-функцию, имеющую довольно сложный алгоритм, от которой я ожидаю равномерное распределение.

![murmurHash2](/images/histogram_murmurHash2.png)

Хеш-функция **murmurHash2** имеет следующий код:

```
const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    //unsigned int len = WORLD_LENGTH;
    unsigned int len = strlen(word);
    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *) word;
    unsigned int k = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
        h ^= data[2] << 16;
        case 2:
        h ^= data[1] << 8;
        case 1:
        h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
```

Функция показала лучшее распределение среди всех представленных функций; тем не менее, по времени поиска (**6,677 мс**) такая хеш-таблица проигрывает предыдущим двум. Связано это с объёмом кода функции.

Стоит полагать, что дальнейшие поиски хеш-функции не дадут распределения сильно лучше этого (а оно довольно близко к идеальному). Поэтому я решил закончить рассмотрение хеш-функций.
 ## Промежуточные итоги


| **Функция **      | **Время поиска, мс** |
| ----------------- | -------------------- |
| hash1             | 510.684              |
| hashFirstLetter   | 75.953               |
| hashWordLen       | 6.584                |
| hashRol           | 5.919                |
| hashRor           | 6.074                |
| murmurHash2       | 6.677                |


Из рассмотренных нами хеш-функций практическое применение могут иметь последние четыре, при этом, применение hashSum, как обговорено выше, имеет смысл только на ограниченном диапазоне размеров хеш-таблиц. **hashRor** и **hashRol** довольно хорошо показали себя в наших условиях в силу малого числа инструкций, однако их распределение сложно назвать идеальным, что на большем количестве данных может сыграть не в лучшую сторону. Лучшим вариантом кажется **murmurHash2** за счёт сравнительно малого кода и хорошего распределения - с ней я и планирую работать дальше.

Весь исходный код, написанный для данной части работы, сохранен в ветке part1.

 ## Оптимизация

Выбрав хеш-функцию, далее я намерен оптимизировать остальные детали поиска. Пока что я буду пытаться не использовать вещи, нарушающие кросс-платформенность, а именно явные использования интринсиков из **SIMD**, ассемблерные функции и ассемблерные вставки.

 ### Увеличение размеров таблицы

Поскольку при сравнении хеш-функций я хотел просмотреть распределение слов по спискам, я подбирал такой размер хеш-таблицы, чтобы в одном списке в среднем было 10-20 слов. Теперь же, когда передо мной стоит задача оптимизации, я вправе подобрать размер так, чтобы в списке в среднем было 1-2 слова, как это и делается на практике.

Заново измерив время поиска при размере хеш-таблицы в **317** элементов, я получил время поиска **3,649 мс** для функции **murmurHash2**; установив размер в **4973** элемента, я получил **2,064 мс**. Относительные приросты всех оптимизаций для наглядности я приведу в выводе.
 ### Флаги компиляции

Далее я попробовал различные флаги оптимизации. Ради интереса я также скомпилировал программу с флагом -O0:

| **Набор флагов** | **Время поиска, мс** |
| ---------------- | -------------------- |
| Без флагов       | 2,064                |
| -O0              | 2.530                |
| -O               | 1.405                |
| -O1              | 1.412                |
| -O2              | 1.372                |
| -O3              | 1.389                |
| -Ofast           | 1.376                |

Как видим, компиляция без флагов все равно даёт некоторую оптимизацию. Однако более важно то, что в нашем случае лучший результат показывают уровни **-O2** - **-Ofast**, причём разница в быстродействии незаметна. В дальнейшем я попытаюсь сделать окончательный выбор в пользу одного из флагов **-O3** и **-Ofast**

 ### Исследование производительности при помощи профайлеров

Для дальнейшей оптимизации я решил прогнать программу через **callgrind**. Файл **callgrind.out.50967** содержит данные для варианта, скомпилированного с флагом **-Ofast**, **callgrind.51246** - с **-O3**. Результаты для разных флагов почти не отличаются, поэтому приведу вариант для **-Ofast**:

![Callgrind -Ofast](/images/callgrind_-Ofast.png)

Узким местом является функция поиска элемента в списке. Чтобы оптимизировать её работу, в идеале, нужно переписывать всю библиотеку для работы со списками, на что у меня нет времени; тем не менее, стоит обратить внимание на ассемблерную функцию **__strcasecmp_avx2**, указанную профайлером. Хотя я пока что не хочу явно использовать функции из AVX2, которые лишили бы программу портируемости, в оптимизациях я буду ориентироваться на машины с этим набором инструкций.

Просмотрев исходный код этой функции, я сделал вывод, что узким местом в ней, которое я могу исправить без SIMD-ов и использования ассемблера, является выравнивание адресов. Чтобы адреса были кратны 32, я переписал препроцессор, и теперь он дополняет каждое слово до 32 байт символами '\0'. Заодно я убедился, что это должно решить проблему **__strlen_avx2** в хеш-функции.

 ### Оптимизация для SIMD

Результат работы профайлера - **data/callgrind.out.87982**. Как и ожидалось, **__strlen_avx2** также ускорилась, что и убрало её из графа вызовов.

![Callgrind](/images/callgrind_alignment.png)

Я переписал препроцессор, чтобы он разбивал текст как указано выше. Новое время работы:

| **Набор флагов** | **Время поиска, мс** |
| ---------------- | -------------------- |
| -O3              | 1.015                |
| -Ofast           | 1.003                |

Опять же, различие незначительно. В дальнейшем, если разница во времени работы между флагами **-O3** и **-Ofast** будет мало, я вообще буду опускать это сравнение.
 ### Замена реализации функции

По данным **callgrind**, поиск по списку всё ещё является самым затратным, однако без SIMD-ов его уже не оптимизировать, поэтому я решил переключиться на хеш-функцию.

Я заменил хеш-функцию, написанную под произвольную длину, на [её реализацию с GitHub](https://github.com/explosion/murmurhash/blob/master/murmurhash/MurmurHash2.cpp), установив длину **32**, таким образом убрав необходимость хеш-функции эту длину находить. Время работы уменьшилось до **0.949 мс**; разница между -O3 и -Ofast опять незначительна. 

Фактически, это всё, что я мог получить без использования ассемблера и сишных SIMD-функций. Ниже представлены данные, соответствующие файлу **callgrind.out.12906**.

![Callgrind](/images/callgrind_new_realization.png)

Как видим, основную нагрузку при поиске дают всё те же функции **ListIndexFirst** и **murmurHash2**. Для оптимизации я могу упаковывать слова в 256-битные регистры для **AVX2**, что позволит мне сравнивать строки в считанные инструкции.
 ### Использование SIMD

Я переписал лист (и заодно парсер текста) под тип данных **__m256i** и вставил SIMD-овские интринсики для сравнения элементов листа в **ListIndexFirst**. Новое время работы - **0,840 мс**, ощутимый прирост производительности налицо (**callgrind.out.60879**).

![Callgrind](/images/callgrind_list_simds.png)

Теперь нагрузку даёт хеш-функция. я заменил хеш-функцию **murmurHash2** на **simdCrc32**, которая использует интринсик **_mm_crc32_u32** (**callgrind.out.56986**), время работы сократилось еще сильнее - **0,595 мс** 

![Callgrind](/images/callgrind_simdCrc32.png)
 ### Оптимизации с использованием языка ассемблера

На данном этапе я реализовал все возможности оптимизации без использования языка ассемблера (кроме переписывания списков, на что у меня нет времени). Дальнейшие оптимизации его потребуют, следовательно, на данном этапе код окончательно теряет кросс-платформенность.

Всё, с чем я буду работать дальше - хеш-функция. Я могу либо написать её реализацию на языке ассемблера, что проще дебажить, либо добавить в неё ассемблерные вставки.
 #### Ассмеблерные функции

Я пошёл по простому пути и заменил реализацию **simdCrc32** на ассемблерную (**callgrind.out.74905**). Время сократилось совсем незначительно (хотя при прогонах было стабильно ниже, чем при прошлой оптимизации) - **0,586 мс**. Я полагаю, это связано с тем, что компилятор с -Ofast и так довольно хорошо оптимизирует функцию, поэтому перегнать его - довольно непростая задача. 

С другой стороны, для использования ассемблерной функции мне пришлось добавить флаг компиляции -no-pie, из-за которого исполняемый файл больше не является PIE (*англ.* Poisition Independent Executable - исполняемый файл, где полностью реализована отсноительная адрессация), что понижает защиту программы (в особенности, данных из хеш-таблиц) от взлома. Таким образом, данное решение не стоит использовать на практике, однако в образовательных целях это действие было полезно.

![Callgrind](/images/callgrind_asm_crc32.png)

 #### Ассемблерные вставки

Для сравнения, а также чтобы избежать использование **-no-pie**, я решил добавить в сишную функцию **simdCrc32** ассемблерную вставку:.

```c
asm(
        ".intel_syntax noprefix\n"

        "xor rax, rax\n"

        "mov      eax, DWORD [r8]\n"  
                                        
        "crc32d   eax, DWORD [r8 - 4]\n"   
        "crc32d   eax, DWORD [r8 - 8]\n"
        "crc32d   eax, DWORD [r8 - 12]\n"  
        "crc32d   eax, DWORD [r8 - 16]\n" 
        "crc32d   eax, DWORD [r8 - 20]\n"    
        "crc32d   eax, DWORD [r8 - 24]\n"
        "crc32d   eax, DWORD [r8 - 28]\n"   

        ".att_syntax prefix"
        : "=r" (hash)
        : "r" (ptr)
    );
```

Я не получил значимого прироста производительности; тем не менее, в отличие от ассемблерной функции, я могу сделать сишную функцию инлайном.

Переделывание в инлайн потребовало переписать некоторые участки кода и, в частности, убрать ссылку на функцию из структуры хеш-таблицы, что сокращает универсальность.
 
Новое время выполнения -  **0,454 мс**. Прогон через **callgrind** лежит в **callgrind.out.12561**

![Callgrind](/images/callgrind_inl_asm_crc32.png)

Возможности для оптимизации без переписывания списков исчерпаны.

 ## Выводы

Ниже приведена таблица с результатами оптимизаций. Процент сокращения времени работы высчитывается относительно последней оставленной оптимизации - так, я не оставлял ассемблерную функцию.

| **Оптимизация**                | **Время поиска, мс**  | **Относительное сокращение времени работы, %**   |
| ------------------------------ | --------------------- | ------------------------------------------------ |
| Без оптимизаций                | 3.649                 | -                                                |
| Увеличение хеш-таблицы         | 2.064                 | 43                                               |
| Флаги                          | 1.376                 | 33                                               |
| 32-байтные слова               | 1.003                 | 27                                               |
| Замена реализации хеш-функции  | 0.949                 | 5                                                |
| Использование SIMD             | 0.840                 | 11                                               |
| SIMD-овская хеш-функция        | 0.595                 | 29                                               |
| Ассемблерная хеш-функция       | 0.586                 | 2                                                |
| Ассемблерная вставка           | 0.454                 | 24                                               |

Скорость поиска по хеш-таблице довольно сильно зависит от двух факторов - число инструкций в функции и равномерность распределения значений функции. Именно поэтому в первой части работы лучшее быстродействие показала **hashRol** несмотря на лучшее распределение у **murmurHash2**

Любая оптимизация требует определенных затрат. Переписывание хеш-функции тратит лишь время разработчика, флаги оптимизации и размер хеш-таблицы могут увеличить использование памяти, **inline**- функция увеличивает расход памяти и делает код менее понятным (чтобы функция заработала, мне пришлось добавить её в хедер), использование **SIMD** ограничивает портируемость программы, а вот использование ассемблера может снизить надежность программы (использование ассемблерного файла) и снизить читаемость кода (ассемблерая вставка). В то же время, не каждая оптимизация несёт значимое ускорение, что вынуждает подходить к ним с умом.