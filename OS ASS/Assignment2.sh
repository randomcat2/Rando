#BASIC ARITHMETIC
# length=5
# width=3
# height=7
# volume=$((length * width * height))
# echo "Volume of the cuboid: $volume cm^3"

#COMMAND LINE ARGUMENTS
# echo "Enter a number: " 
# read  number
# square=$((number * number))
# echo "Square of the number: $square"

#CONDITIONAL
# echo "Enter a year: " 
# read year
# if [ $((year % 4)) -eq 0 ] && [ $((year % 100)) -ne 0 ] || [ $((year % 400)) -eq 0 ]; then
#     echo "$year is a leap year."
# else
#     echo "$year is not a leap year."
# fi

#STRING
# input_string="Shreya"
# uppercase_string="${input_string^^}"
# lowercase_string="${input_string,,}"
# echo "Original string: $input_string"
# echo "Uppercase string: $uppercase_string"
# echo "Lowercase string: $lowercase_string"

#FUNCTION
# calculate_simple_interest() {
#     principal=$1
#     rate=$2
#     time=$3
#     interest=$((principal * rate * time / 100))
#     echo "Simple Interest: $interest"
# }
# principal_amount=1000
# interest_rate=5
# time_period=2
# calculate_simple_interest $principal_amount $interest_rate $time_period

#FILE
echo "Enter some text (type 'done' to finish):"
read -r input_text

file_path="output.txt"

if [ -e "$file_path" ]; then
    echo "File 'output.txt' already exists. Do you want to overwrite it? (y/n)"
    read -r overwrite
    if [ "$overwrite" != "y" ]; then
        echo "Aborted."
        exit 1
    fi
fi
echo "$input_text" > "$file_path"
echo "Text written to '$file_path'."

#ARRAY
# num=(2 4 6 8 10)
# count=0
# for((i=0;i<5;i++));
# do
# current=${num[i]}
# for((j=i+1;j<5;j++));
# do
# echo "(${current},${num[j]})"
#       ((count++))
# done
# done      

#Execution of linux commands in a shell
# $ls