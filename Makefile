CXX      := -c++
CXXFLAGS := -Wall -Wextra
FILES := dispersion.cpp

.PHONY:
	all

all:
	$(CXX) $(CXXFLAGS) -o dispersion $(FILES)

clean:
	rm -f *.o dispersion
