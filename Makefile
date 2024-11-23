# decided to write a custom makefile this time, need to learn how to do that, seems important 

CPP = clang++
CPP_FLAGS = -g -Wall -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++17 # still no idea what most of these args are but they seemed important

# compiles and runs the .out file of the program  
# to get the argument to work you have to do "make run FILE=<file_name>"
run: 
	$(CPP) $(CPP_FLAGS) banker.cpp
	./a.out $(FILE)

clean:
	rm -f *.out