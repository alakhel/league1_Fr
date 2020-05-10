
.SUFFIXES: .cxx

TARGET         = foot
OBJECTS        = Joueur.o Equipe.o Match.o main.o
SOURCES        = $(OBJECTS:.o=.cxx)

CXX            = g++
CXXFLAGS       = -Wall -pedantic-errors -std=c++11 -I.
LDFLAGS        =
LIBS           =

.cxx.o: $<
	$(CXX) $(CPXXFLAGS) $(CXXFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f ${TARGET} $(OBJECTS) $(SOURCES:.cxx=.h~) $(SOURCES:.cxx=.cxx~) Makefile~
