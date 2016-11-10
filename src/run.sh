echo "Compiling Project..."
rm ../game
gcc *.c -lm `sdl2-config --cflags --libs` -o game
./game
