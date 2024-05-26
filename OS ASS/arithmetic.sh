#!/bin/bash

# Define two numbers
num1=10
num2=5

# Addition
sum=$((num1 + num2))
echo "Addition: $num1 + $num2 = $sum"

# Subtraction
difference=$((num1 - num2))
echo "Subtraction: $num1 - $num2 = $difference"

# Multiplication
product=$((num1 * num2))
echo "Multiplication: $num1 * $num2 = $product"

# Division
quotient=$((num1 / num2))
echo "Division: $num1 / $num2 = $quotient"

# Modulus
remainder=$((num1 % num2))
echo "Modulus: $num1 % $num2 = $remainder"

# Increment
num1=$((num1 + 1))
echo "Increment: num1 + 1 = $num1"

# Decrement
num2=$((num2 - 1))
echo "Decrement: num2 - 1 = $num2"

# Compound assignment
num1+=2
echo "Compound assignment (num1 += 2): $num1"

num2-=2
echo "Compound assignment (num2 -= 2): $num2"

num1*=3
echo "Compound assignment (num1 *= 3): $num1"

num2/=3
echo "Compound assignment (num2 /= 3): $num2"

# Exponentiation
base=2
exponent=3
result=$((base ** exponent))
echo "Exponentiation: $base ^ $exponent = $result"

# Square root (using bc)
sqrt=$(echo "scale=2; sqrt($num1)" | bc)
echo "Square root of $num1: $sqrt"
