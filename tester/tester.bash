#!/bin/bash

BOLD="\e[1m"
YELLOW="\033[0;33m"
GREY="\033[38;5;244m"
PURPLE="\033[0;35m"
BLUE="\033[0;36m"
RED="\e[0;31m"
NOC="\033[0m"

MINISHELL_PATH="../minishell"

chmod 000 ./test_files/invalid_permission
rm -rf ./outfiles/*
rm -rf ./mini_out/*
rm -rf ./bash_out/*
mkdir ./outfiles
mkdir ./mini_out
mkdir ./bash_out

if [[ $1 ]]; then
	testfiles=(
		"$1"
	)
else
	testfiles=(
			"syntax"
			"vars"
			)
fi

function	print_diff_if_errors {
	if [ "$OUTFILES_DIFF" ]; then
		echo "$OUTFILES_DIFF"
		echo mini outfiles:
		cat ./mini_out/*
		echo bash outfiles:
		cat ./bash_out/*
	fi
	if [ "$MINI_OUTPUT" != "$BASH_OUTPUT" ]; then
		echo mini output = \($MINI_OUTPUT\)
		echo bash output = \($BASH_OUTPUT\)
	fi
	if [ "$MINI_EXIT_CODE" != "$BASH_EXIT_CODE" ]; then
		echo mini exit code = $MINI_EXIT_CODE
		echo bash exit code = $BASH_EXIT_CODE
	fi
}

REMOVE_COLORS="sed s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g"
REMOVE_EXIT="grep -v ^exit$"
PROMPT=$(echo -e "\nexit\n" | $MINISHELL_PATH | head -n 1 | sed "s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g")

for testfile in ${testfiles[*]}; do
	printf $BLUE
	echo ______________$testfile
	printf $NOC
	while read line; do
		((i++))
		rm -rf ./outfiles/*
		rm -rf ./mini_out/*
		MINI_OUTPUT=$(echo -e "$line" | $MINISHELL_PATH 2> /dev/null | $REMOVE_COLORS | grep -vF "$PROMPT" | $REMOVE_EXIT )
		MINI_OUTFILES=$(cp ./outfiles/* ./mini_out &>/dev/null)
		MINI_EXIT_CODE=$(echo -e "$MINISHELL_PATH\n$line\necho \$?\nexit\n" | bash 2> /dev/null | $REMOVE_COLORS | grep -vF "$PROMPT" | $REMOVE_EXIT | tail -n 1)

		rm -rf ./outfiles/*
		rm -rf ./bash_out/*
		BASH_OUTPUT=$(echo -e "$line" | bash 2> /dev/null)
		BASH_OUTFILES=$(cp ./outfiles/* ./bash_out &>/dev/null)
		BASH_EXIT_CODE=$(echo $?)

		OUTFILE_DIFFS=$(diff --brief ./mini_out ./bash_out)

		echo -e "$line" | $MINISHELL_PATH 2> /dev/null 1>/dev/null
		MINI_EXIT_CODE=$(echo $?)
		printf $YELLOW
		printf "test %3s: " $i
		if [[ "$MINI_OUTPUT" == "$BASH_OUTPUT" && "$MINI_EXIT_CODE" == "$BASH_EXIT_CODE" && -z "$OUTFILES_DIFF" ]]; then
			printf ✅
			((ok++))
		else
			printf ❌
		fi
		printf "$GREY $line \n$NOC"
		print_diff_if_errors
	done < $testfile
done

chmod 666 ./test_files/invalid_permission
rm -rf ./mini_out
rm -rf ./bash_out
rm -rf ./outfiles

printf $PURPLE
printf $BOLD
echo $ok/$if
printf $NOC
