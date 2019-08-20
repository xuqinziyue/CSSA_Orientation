# CSSA_Orientation

Current implementation include two sections:

1. A parser that parse a log file line by line in real time (parser.h and parser.cpp)
2. A visualizer that prints the parsed contents stored using sdl2 (sdl_helper.h and sdl_helper.cpp)

main function launches a child thread to parse the file and uses main thread for visualization
