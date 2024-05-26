#!/bin/bash

# String length
str="Hello, World!"
echo "String: $str"
length=${#str}
echo "Length of the string: $length"

# Substring extraction
substr=${str:7:5}
echo "Substring (from index 7, length 5): $substr"

# String replacement
new_str=${str/World/Universe}
echo "String after replacement: $new_str"

# String concatenation
str1="Hello"
str2="Bash"
concat_str="$str1, $str2!"
echo "Concatenated string: $concat_str"

# String comparison
str3="Hello"
str4="Hello"
if [ "$str3" == "$str4" ]; then
    echo "Strings are equal"
else
    echo "Strings are not equal"
fi

str5="Hello"
str6="World"
if [ "$str5" != "$str6" ]; then
    echo "Strings are not equal"
else
    echo "Strings are equal"
fi

# Finding a substring within a string
if [[ "$str" == *"World"* ]]; then
    echo "String contains 'World'"
else
    echo "String does not contain 'World'"
fi

# Convert to uppercase
upper_str=${str^^}
echo "Uppercase string: $upper_str"

# Convert to lowercase
lower_str=${str,,}
echo "Lowercase string: $lower_str"

# Trimming whitespace
whitespace_str="   Hello, World!   "
trimmed_str=$(echo $whitespace_str | xargs)
echo "Trimmed string: '$trimmed_str'"
