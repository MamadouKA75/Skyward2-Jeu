cdCCOPTIONS	= -Wall -g
CC			= g++ $(CCOPTIONS)
SRC	= ./src
BIN	= ./bin
OBJ	= ./obj
LINK = -lSDL2 -lSDL2_image  -lSDL2_ttf

all: $(BIN) $(OBJ) jeuTxt jeuSDL testRectangle testPersoPlatObs

all: $(BIN)/ $(BIN)/ $(BIN)/

obj : $(OBJ)/winTxt.o $(OBJ)/Vector2.o $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/plateforme.o  $(OBJ)/personnage.o $(OBJ)/monde.o $(OBJ)/jeusdl2.o

jeuSDL: $(BIN)/jeuSDL

testPersoPlatObs: $(BIN)/testPersoPlatObs 

testRectangle: $(BIN)/testRectangle



jeuTxt: $(BIN)/jeuTxt

$(BIN)/jeuTxt: $(OBJ)/mainTxt.o $(OBJ)/winTxt.o $(OBJ)/jeuTxt.o $(OBJ)/plateforme.o  $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/monde.o $(OBJ)/Vector2.o $(OBJ)/personnage.o
	$(CC) $(OBJ)/mainTxt.o $(OBJ)/winTxt.o $(OBJ)/jeuTxt.o $(OBJ)/plateforme.o  $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/monde.o $(OBJ)/Vector2.o $(OBJ)/personnage.o -o $(BIN)/jeuTxt

$(OBJ)/mainTxt.o: $(SRC)/mainTxt.cpp $(SRC)/jeuTxt.cpp
	$(CC) -c $(SRC)/mainTxt.cpp -o $(OBJ)/mainTxt.o

$(BIN)/testPersoPlatObs: $(OBJ)/plateforme.o  $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/mainPersoPlatObs.o $(OBJ)/Vector2.o $(OBJ)/personnage.o
	$(CC) $(OBJ)/mainPersoPlatObs.o $(OBJ)/plateforme.o $(OBJ)/rectangle.o  $(OBJ)/obstacle.o $(OBJ)/Vector2.o $(OBJ)/personnage.o -o $(BIN)/testPersoPlatObs 
	
$(BIN)/testRectangle: $(OBJ)/rectangle.o $(OBJ)/testRectangle.o $(OBJ)/Vector2.o
	$(CC) $(OBJ)/rectangle.o $(OBJ)/Vector2.o $(OBJ)/testRectangle.o -o $(BIN)/testRectangle

$(OBJ)/mainPersoPlatObs.o: $(SRC)/mainPersoPlatObs.cpp $(SRC)/plateforme.h $(SRC)/obstacle.h $(SRC)/personnage.h 
	$(CC) -c $(SRC)/mainPersoPlatObs.cpp -o $(OBJ)/mainPersoPlatObs.o

$(BIN)/jeuSDL: $(OBJ)/jeusdl2.o $(OBJ)/mainSDL.o $(OBJ)/plateforme.o  $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/monde.o $(OBJ)/Vector2.o $(OBJ)/personnage.o
	$(CC) $(OBJ)/jeusdl2.o $(OBJ)/mainSDL.o $(OBJ)/plateforme.o  $(OBJ)/rectangle.o $(OBJ)/obstacle.o $(OBJ)/monde.o $(OBJ)/Vector2.o $(OBJ)/personnage.o -o $(BIN)/jeuSDL  $(LINK)

$(OBJ)/jeusdl2.o: $(SRC)/jeusdl2.h $(SRC)/jeusdl2.cpp
	$(CC) -c $(SRC)/jeusdl2.cpp -o $(OBJ)/jeusdl2.o $(LINK)

$(OBJ)/mainSDL.o:  $(SRC)/jeusdl2.h $(SRC)/mainSDL.cpp
	$(CC) -c $(SRC)/mainSDL.cpp -o $(OBJ)/mainSDL.o $(LINK)

$(OBJ)/testRectangle.o:  $(SRC)/rectangle.h $(SRC)/testRectangle.cpp
	$(CC) -c $(SRC)/testRectangle.cpp -o $(OBJ)/testRectangle.o $(LINK)


$(OBJ)/personnage.o:  $(SRC)/personnage.h $(SRC)/personnage.cpp $(SRC)/rectangle.h
	$(CC) -c $(SRC)/personnage.cpp -o $(OBJ)/personnage.o 


$(OBJ)/monde.o: $(SRC)/monde.h $(SRC)/monde.cpp 
	$(CC) -c $(SRC)/monde.cpp -o $(OBJ)/monde.o 


$(OBJ)/plateforme.o:  $(SRC)/plateforme.h $(SRC)/plateforme.cpp $(SRC)/rectangle.h
	$(CC) -c $(SRC)/plateforme.cpp -o $(OBJ)/plateforme.o 

$(OBJ)/obstacle.o:  $(SRC)/obstacle.h $(SRC)/obstacle.cpp $(SRC)/rectangle.h
	$(CC) -c $(SRC)/obstacle.cpp -o $(OBJ)/obstacle.o 

$(OBJ)/rectangle.o:  $(SRC)/rectangle.h $(SRC)/rectangle.cpp $(SRC)/Vector2.hpp
	$(CC) -c $(SRC)/rectangle.cpp -o $(OBJ)/rectangle.o 

$(OBJ)/Vector2.o:  $(SRC)/Vector2.hpp $(SRC)/Vector2.cpp
	$(CC) -c $(SRC)/Vector2.cpp -o $(OBJ)/Vector2.o 

$(OBJ)/jeuTxt.o: $(SRC)/jeuTxt.h $(SRC)/jeuTxt.cpp
	$(CC) -c $(SRC)/jeuTxt.cpp -o $(OBJ)/jeuTxt.o

$(OBJ)/winTxt.o:$(SRC)/winTxt.cpp $(SRC)/winTxt.h
	$(CC) -c $(SRC)/winTxt.cpp -o $(OBJ)/winTxt.o



clean:
	rm -r $(OBJ)/*.o $(BIN)/*


init: 
	mkdir obj bin
