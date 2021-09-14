# Сборка расширения
## Сборка под Ubuntu

### Сборка Postgres
1. Загрузка из git-репозитория PostgreSQL: https://git.postgresql.org/git/postgresql.git
2. Установка зависимостей: binutils, flex, libreadline-dev, libbison-dev
3. Создаем папку в build внутри репозитория postgresql
4. Создаем папку для установки PostgreSQL в /tmp/tmp_pgsql
5. Переходим в неё и выполняем:
../configure --prefix=/tmp/tmp_pgsql
6. Выполняем make
7. Выполняем make install
8. Переходим в папку /tmp/tmp_pgsql и выполняем следующие команды:
```bash
* mkdir data
* bin/initdb -D data
* bin/pg_ctl -D data -l logfile start
* bin/createdb superdb
```

Для подключение к удаленной машине с psql
```bash
* bin/psql -U <user> -p 5432 -h <host> -d superdb
```

### Сборка расширения
1. Переходим в папку расширения
2. Создаем build_<os> и переходим в неё
3. Выполняем команды:
```bash
  * make -f ../Makefile - сборка
  * make -f ../Makefile install - установка
  * make -f ../Makefile installcheck - запуск тестов
```
  
Результаты работы в Ubuntu представлены в папке results

# Сборка под Windows

###
1. Установить msys
2. Установить базовые зависимости и mingw
```bash
  pacman -Syu base-devel mingw-w64-x86_64-toolchain
```
3. Повторить пункты из сборки Ubuntu, исключая пункт 2
  
### Сборка расширения
Идентичная Ubuntu
