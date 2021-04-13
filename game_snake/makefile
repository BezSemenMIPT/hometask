OBJ = View.o Tui.o Gui.o Game.o Controller.o Main.o Human.o Dump.o
EXE = Snake
CXXFLAGS += -Wall -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system


all: $(EXE)


$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(CXXFLAGS) $(OBJ) $(LIBS)


clear:
	$(RM) $(OBJ) $(EXE)


depend:
	$(CXX) -MM $(CXXFLAGS) $(OBJ:.o=.cc) > .depend


-include .depend
