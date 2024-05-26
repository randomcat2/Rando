#!/bin/bash

# Function to check if a number is a palindrome
is_palindrome() {
    local num=$1
    local reversed=0
    local original=$num

    while [ $num -gt 0 ]; do
        remainder=$((num % 10))
        reversed=$((reversed * 10 + remainder))
        num=$((num / 10))
    done

    if [ $original -eq $reversed ]; then
        echo "$original is a palindrome."
    else
        echo "$original is not a palindrome."
    fi
}

# Function to check if a number is prime
is_prime() {
    local num=$1

    if [ $num -le 1 ]; then
        echo "$num is not a prime number."
        return
    fi

    for ((i = 2; i * i <= num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            echo "$num is not a prime number."
            return
        fi
    done

    echo "$num is a prime number."
}

# Function to generate Fibonacci series up to a given number of terms
generate_fibonacci() {
    local n=$1
    local a=0
    local b=1

    echo "Fibonacci series up to $n terms:"
    for ((i = 0; i < n; i++)); do
        echo -n "$a "
        next=$((a + b))
        a=$b
        b=$next
    done
    echo
}

# Read a number from the user
read -p "Enter a number: " num

# Check if the number is a palindrome
is_palindrome $num

# Check if the number is prime
is_prime $num

# Generate Fibonacci series up to the given number
read -p "Enter the number of terms for the Fibonacci series: " terms
generate_fibonacci $terms
