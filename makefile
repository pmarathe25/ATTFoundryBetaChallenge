BUILDDIR = build/
INCLUDEDIR = include/
OBJS = $(BUILDDIR)/Server.o $(BUILDDIR)/Group.o $(BUILDDIR)/GroupAllocator.o
TESTDIR = test/
TESTOBJS = $(BUILDDIR)/test.o
SRCDIR = src/
CXX = g++
CFLAGS = -fPIC -c -std=c++11 -I$(INCLUDEDIR)
LFLAGS = -shared
TESTLFLAGS =

$(TESTDIR)/test: $(TESTOBJS) $(OBJS)
	$(CXX) $(TESTLFLAGS) $(TESTOBJS) $(OBJS) -o $(TESTDIR)/test

$(BUILDDIR)/test.o: $(TESTDIR)/test.cpp
	$(CXX) $(CFLAGS) $(TESTDIR)/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/Server.o: $(SRCDIR)/Server/Server.cpp $(INCLUDEDIR)/Server/Server.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Server/Server.cpp -o $(BUILDDIR)/Server.o

$(BUILDDIR)/Group.o: $(SRCDIR)/Group/Group.cpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/Group.cpp -o $(BUILDDIR)/Group.o

$(BUILDDIR)/GroupAllocator.o: $(SRCDIR)/Group/GroupAllocator.cpp $(INCLUDEDIR)/Group/GroupAllocator.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/GroupAllocator.cpp -o $(BUILDDIR)/GroupAllocator.o

test: $(TESTDIR)/test
	$(TESTDIR)/test

clean:
	rm $(OBJS) $(TESTOBJS)
