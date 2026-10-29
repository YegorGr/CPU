# Read me pleaseность 

## Taskность 
Суть задачи: требуется написать программу assembler, которая переводит текстовое представление кода в двоичное, а также процессор, который поддерживает определенный набор команд и работает на стекности. 

## Архитектурность проекта
```
CPU/
├── README.md
├── common/
│   ├── commands.h       
│   ├── commands.cpp
│   ├── fileinfo.h
│   └── fileinfo.cpp
├── stack/
│   ├── stack.h
│   └── stack.cpp
├── assembler/
│   ├── main.cpp        
│   ├── assembler.h
│   └── assembler.cpp   
├── vm/
│   ├── main.cpp
│   ├── vm.h
│   └── vm.cpp
├── disassembler/  // попозже сделаю     
└── examples/
    ├── q_equation.bin
    └── q_equation.txt 
```
 

> В examples лежат примеры рабочих программ, которые можно использовать, напримпер для того, чтобы проверить насколько корректно выполняется код.
> disassembler пока что не реализован, ждите, дорогие подписчики (my dear subs)

## Commands (возможности ассемблера)
* Aссемблер умеет работать с регистрами (их 4 штуки: AX, BX, CX, DDX) - выбор был обсуловлен удобством их использования для квдаратного уравнения.
* Комметарии можно помечать special символом `;`.
* Йоу
* Существует 19 различных команд, реализованы условные циклы а также рекурсивный вызов "функций".
* Реализованы текстовые пометки вида `mark:`.

## Start программы
> Для процессора (vm):
```text 
g++ -Icommon -Istack vm/main.cpp vm/vm.cpp stack/stack.cpp common/fileinfo.cpp common/commands.cpp -o vm.exe
```

> Для ассемблера:
```text
g++ -Icommon assembler/main.cpp assembler.cpp common/fileinfo.cpp common/commands.cpp -o ass.exe
```

> [!TIP]
> В скором времени планируется расширение с использованием оперативной памяти. Следите за новостями мои дорогие!!!
