@mkdir bin
cl /W1 /O2 /Gd /MD /D _WINDLL /EHsc /nologo platdefs.cpp 2048.cpp main.cpp pure_monte_carlo.cpp mcts.cpp /Fobin\ /link /OUT:bin\2048.exe
