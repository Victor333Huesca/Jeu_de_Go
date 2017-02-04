# -----   Options   ----- #
CC = g++
CFLAGS = -std=c++14 -Wall
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# -----  Locations  ----- #
REP_SRC = Sources/
REP_OBJ = Release/
REP_EXE = ../Release/

# -----     SFML    ----- #
REP_SFML = SFML/
REP_INC = $(REP_SFML)include/
REP_LIB = $(REP_SFML)lib/

# -----    Names    ----- #
SRC = $(foreach dir, $(REP_SRC), $(wildcard $(REP_SRC)*.cpp))
OBJ = $(addsuffix .o, $(basename $(subst ${REP_SRC}, ${REP_OBJ}, ${SRC})))
EXE = $(REP_EXE)GoSolver

# -----     Main    ----- #
$(EXE) : $(OBJ)
	$(CC) $^ -o $@ -L $(REP_LIB) $(CXXFLAGS)

# -----     Base    ----- #
$(REP_OBJ)/%.o : $(REP_SRC)/%.cpp
	$(CC) -c $< -o $@ -I $(REP_INC) $(CFLAGS)

# -----    Clean    ----- #
clean :
	rm -f $(OBJ) $(EXE)

# -----   Rebuild   ----- #
all : clean $(EXE)
