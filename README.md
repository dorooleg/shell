# Структура проекта
* shell - главная часть проекта. Позволяет получать команды на вход, после чего разбивает их по |. Разделенные команды форкаются, а форкнутые команды связываются через pipe
* wc, cat, echo, pwd - команды подробно описаны в задании. Архитектурные аспекты описаны в комментариях к коду
* Preporocessor - выполняет обновление и подстановку переменных окружения
* Environment - хранит переменные окружения

# Grep (Обоснование выбора библиотеки для работы с аргументами)
Grep разрабатывался на языке C++. Выбор библиотек для работы с аргументами оказался не очень большим. Поэтому для рассмотрения были выбраны две:
### boost::program_options

Преимущества:
- интуитивность (по крайней мере для меня)
- самодостаточность (комментарии, типы, имена и группы из коробки)
- работа с аргументами и конфигурационными файлами (хотя это и не освещалось)

Недостатки:
- скудная документация
- требует линковки бинарников (по сравнению со многими другими пакетами boost)
- только однобуквенные короткие имена аргументов


### posix getopt

Преимущества:
- скорее всего есть по умолчанию в linux
- быстро работают

Недостатки:
- низкоуровневая библиотка
- сложный порог вхождения

Сравнив все преимущества и недостатки библиотек была выбрана boost::program_options
