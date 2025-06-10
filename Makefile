CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -I.

# Ejecutables
TEST = test
UHR = uhr

# Fuentes y headers
TEST_SRC = test.cpp
UHR_SRC = uhr-main/uhr.cpp

# Objetos (no se usan archivos .o intermedios aquí)
all: $(TEST) $(UHR)

$(TEST): $(TEST_SRC) EditD.h lcs.h test.h
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC)

$(UHR): $(UHR_SRC) EditD.h lcs.h uhr-main/utils.cpp uhr-main/quartiles_nth.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(UHR_SRC)

clean:
	rm -f $(TEST) $(UHR) *.o *.csv

.PHONY: all clean
