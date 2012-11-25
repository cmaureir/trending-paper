CXXFLAGS = -Wall -g $(shell wx-config --cxxflags) -Iinclude
LDFLAGS  = $(shell wx-config --libs) -lmathplot -lm
OBJECTS  = DataCreationThread.o PlotRefreshThread.o wmMath.o

all: fps-demo

fps-demo: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	-rm -f *.o

distclean: clean
	-rm -f fps-demo
