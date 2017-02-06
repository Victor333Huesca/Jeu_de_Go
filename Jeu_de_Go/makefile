# -----   Options   ----- #
CC = g++
CFLAGS = -std=c++14 -Wall
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# -----  Locations  ----- #
REP_SRC = Sources/ Sources/*/ Sources/*/*/ Sources/*/*/*/ Sources/*/*/*/*/ Sources/*/*/*/*/*/
REP_OBJ = Obj/
REP_EXE = ./

# -----     SFML    ----- #
# Mettez ici le repertoire d'instalation de la SFML chez vous sauf si c'est le repertoire par default auquel cas cf. ligne 24
REP_SFML = SFML/
REP_INC = $(REP_SFML)include/
REP_LIB = $(REP_SFML)lib/

# -----    Names    ----- #
SRC = $(foreach dir, $(REP_SRC), $(wildcard $(dir)*.cpp))
OBJ = $(addprefix $(REP_OBJ), $(addsuffix .o, $(notdir $(basename $(SRC)))))
EXE = $(REP_EXE)GoSolver


# -----  HERE GUYS  ----- #
# Supprimez ce qu'il y a � droite du = si vous avez instalé la SFML dans /usr/local
LIBS = -L $(REP_LIB)
INCLUDE = -I $(REP_INC)

# -----   Target    ----- #
all : $(EXE)

# -----     Main    ----- #
$(EXE) : $(OBJ)
	$(CC) $^ -o $@ $(LIBS) $(CXXFLAGS)

# -----     Base    ----- #
$(REP_OBJ)/%.o : $(REP_SRC)/%.cpp
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

# -----    Clean    ----- #
clean :
	rm -f $(OBJ) $(EXE)

# -----   Rebuild   ----- #
new : clean $(EXE)
