#!/bin/bash

echo "[*] Cleaning old build..."
rm -f ashell

echo "[*] Compiling all .c files..."

gcc -Wall -Wextra -Werror *.c -o ashell

if [ $? -eq 0 ]; then
    echo "[+] Build successful → ./ashell"
else
    echo "[-] Build failed"
fi
