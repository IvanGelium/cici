#!/bin/bash
set -e

mkdir -p build

FLAGS="-std=c11 -g -O0 -Wall -Wextra -Werror -Wshadow -Wconversion -Wdouble-promotion"
SANITIZERS="-fsanitize=address,undefined"
INCLUDES="-Isrc -isystem third_party"

if [ "$1" = "leaks" ]; then
    echo "Собираем проект для проверки утечек..."
    clang $FLAGS $INCLUDES src/main.c -o build/app_leaks
    echo "Запуск leaks:"
    echo "--------------------------------"
    leaks --atExit -- ./build/app_leaks
else
    echo "Собираем проект (Debug + ASan/UBSan)..."
    clang $FLAGS $SANITIZERS $INCLUDES src/main.c -o build/app
    echo "Сборка успешна! Запуск:"
    echo "--------------------------------"
    ./build/app
fi
