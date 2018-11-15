#!/bin/bash
if [ $# -ne 0 ]; then
    echo "Compilinging $1"
    in=$1
    line=$((${#in}-3))
    for k in $(seq 0 $line); do
	d=$d${in:$k:1}
    done
    gcc -c $in
    gcc -o $d $d.o
    if [ -e $in~ ]; then
	rm $in~
    fi
    rm $d.o
else
echo "We will begin compiling a C program"
    ls -l
    echo "Which file would you like to compile?"
    read file
    x=0
    while [ $x -eq 0 ]; do
	if [ -f $file ]; then
	    echo "The file exists"
	    case "$file" in
		*.c) echo "Compiling $file"
		     input=$((${#file} - 3))
		     for j in $(seq 0 $input); do
			 b=$b${file:$j:1}
		     done
		     echo $b
		     gcc -c $file
		     c=$b.o
		     echo $c
		     gcc -o $b $c
		     echo "The file $b is ready to be run"
		     if [ -e $file~ ]; then
			 rm $file~
		     fi
		     exit 1
		     ;;
		*) echo "This is not a C program file, exiting..."
		   exit 1;;
	    esac
	    x=1
	elif [ -d $file ]; then
	    echo "That is a directory, please enter a file"
	    read file
	else
	    echo "The file you entered is incorrect or not readable, try again"
	    read file
	fi
    done
fi
exit 0
