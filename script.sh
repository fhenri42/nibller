echo "SFML:"
cd lib/SFML/
g++ -Wall -Wextra -Werror -shared -fPIC -o bin/sfml.so -I include src/initialisation.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$HOME/.brew/lib
echo g++ -Wall -Wextra -Werror -shared -fPIC -o bin/sfml.so -I include src/initialisation.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$HOME/.brew/lib
cd ../SDL/
echo "SDL:"
g++  -shared -fPIC -o bin/sdl.so -I include src/initialisation.cpp `sdl2-config --cflags --libs` -lSDL2_ttf
cd ../../
 # g++ main.cpp `sdl-config --cflags --libs` && ./a.out
