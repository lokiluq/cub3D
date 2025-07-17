#!/bin/bash

function test() {
	for i in $(find $1 -type f -name "*.cub"); do
		echo -e "\u001b[33mexecuting test: $i\033[0m"
		./cub3D $i
		echo "exit status = $?"
	done
}

test cubfiles

