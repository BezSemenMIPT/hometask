OBJ = View.o Tui.o Gui.o Game.o Main.o Controller.o Human.o Dump.o
EXE = Snake
CXXFLAGS += -Wall -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(CXXFLAGS) $(OBJ) $(LIBS)

depend:
	$(CXX) -MM $(CXXFLAGS) $(OBJ:.o=.cc) > .depend

-include .depend
