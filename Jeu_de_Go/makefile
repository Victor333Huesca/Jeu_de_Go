# -----   Options   ----- #
CXXFLAGS = -std=c++14 -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -pthread

# -----  Locations  ----- #
REP_SRC = Sources/
REP_OBJ = Obj/
REP_EXE = ./

# -----     SFML    ----- #
# Mettez ici le repertoire d'instalation de la SFML chez vous sauf si c'est le repertoire par default auquel cas cf. ligne 24
REP_SFML = SFML/
REP_INC = $(REP_SFML)include/
REP_LIB = $(REP_SFML)lib/

# -----    Names    ----- #
TMP_SRC = Sources/ Sources/*/ Sources/*/*/ Sources/*/*/*/ Sources/*/*/*/*/ Sources/*/*/*/*/*/
SRC = $(foreach dir, $(TMP_SRC), $(wildcard $(dir)*.cpp))
OBJ = $(addprefix $(REP_OBJ), $(addsuffix .o, $(notdir $(basename $(SRC)))))
EXE = $(REP_EXE)GoSolver


# -----  HERE GUYS  ----- #
# Supprimez ce qu'il y a � droite du = si vous avez instalé la SFML dans /usr/local
LIBS +=
INCLUDE =

# -----   Target    ----- #
all : $(EXE)

# -----     Main    ----- #
$(EXE) : $(OBJ)
	@echo All files have been compiled with success.
	@echo 
	@echo Start link edition
	$(CXX) $^ -o $@ $(LIBS)

# -----     Base    ----- #
$(OBJ) : | $(REP_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# -----  Object dir ----- #
$(REP_OBJ) :
	@mkdir -p $@


# Engine
$(REP_OBJ)Etat.o: $(REP_SRC)Engine/Etat.cpp $(REP_SRC)Engine/Etat.h
$(REP_SRC)Engine/Etat.h:

$(REP_OBJ)Goban.o: $(REP_SRC)Engine/Goban.cpp $(REP_SRC)Engine/Goban.h
$(REP_SRC)Engine/Goban.h: $(REP_SRC)Engine/Etat.h $(REP_SRC)Engine/Groupe.h

$(REP_OBJ)Groupe.o: $(REP_SRC)Engine/Groupe.cpp $(REP_SRC)Engine/Groupe.h
$(REP_SRC)Engine/Groupe.h: $(REP_SRC)Engine/Etat.h

$(REP_OBJ)History.o: $(REP_SRC)Engine/History.cpp $(REP_SRC)Engine/History.h
$(REP_SRC)Engine/History.h: $(REP_SRC)Graphics/Globals.h $(REP_SRC)Engine/Etat.h

$(REP_OBJ)Parser.o: $(REP_SRC)Engine/Parser.cpp $(REP_SRC)Engine/Parser.h
$(REP_SRC)Engine/Parser.h: $(REP_SRC)Graphics/Globals.h


# Graphics
$(REP_OBJ)Main.o: $(REP_SRC)Graphics/Main.cpp $(REP_SRC)Graphics/Main_window.h $(REP_SRC)Graphics/Globals.h

$(REP_OBJ)Main_window.o: $(REP_SRC)Graphics/Main_window.cpp $(REP_SRC)Graphics/Main_window.h
$(REP_SRC)Graphics/Main_window.h: $(REP_SRC)Graphics/Game/Game_window.h $(REP_SRC)Graphics/Globals.h

# Graphics --> Game
$(REP_OBJ)Board.o: $(REP_SRC)Graphics/Game/Board.cpp $(REP_SRC)Graphics/Game/Board.h
$(REP_SRC)Graphics/Game/Board.h: $(REP_SRC)Graphics/Globals.h $(REP_SRC)Graphics/Game/Square.h $(REP_SRC)Engine/Goban.h

$(REP_OBJ)Game_window.o: $(REP_SRC)Graphics/Game/Game_window.cpp $(REP_SRC)Graphics/Game/Game_window.h
$(REP_SRC)Graphics/Game/Game_window.h: $(REP_SRC)Graphics/Globals.h $(REP_SRC)Graphics/Game/Board.h $(REP_SRC)Graphics/Game/Infos.h

$(REP_OBJ)Infos.o: $(REP_SRC)Graphics/Game/Infos.cpp $(REP_SRC)Graphics/Game/Infos.h
$(REP_SRC)Graphics/Game/Infos.h: $(REP_SRC)Graphics/Globals.h $(REP_SRC)Graphics/Game/Square.h $(REP_SRC)Graphics/Game/Timer.h

$(REP_OBJ)Square.o: $(REP_SRC)Graphics/Game/Square.cpp $(REP_SRC)Graphics/Game/Square.h
$(REP_SRC)Graphics/Game/Square.h: $(REP_SRC)Graphics/Globals.h $(REP_SRC)Engine/Etat.h

$(REP_OBJ)Timer.o: $(REP_SRC)Graphics/Game/Timer.cpp $(REP_SRC)Graphics/Game/Timer.h
$(REP_SRC)Graphics/Game/Timer.h: $(REP_SRC)Graphics/Globals.h



# -----    Clean    ----- #
clean :
	@rm -f $(OBJ) $(EXE)

# -----   Rebuild   ----- #
new : clean $(EXE)
