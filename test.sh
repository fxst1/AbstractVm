#!/bin/bash

for filename in tests/*; do
	echo $filename;
	./avm $filename
	echo
done
