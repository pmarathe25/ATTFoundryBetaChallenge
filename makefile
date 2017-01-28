BUILDDIR = build/
INCLUDEDIR = include/
OBJS = $(BUILDDIR)/Server.o $(BUILDDIR)/Group.o $(BUILDDIR)/GroupAllocator.o  $(BUILDDIR)/ServerAllocator.o
TESTDIR = test/
TESTOBJS = $(BUILDDIR)/test.o
LIBDIR = $(CURDIR)/lib/
SRCDIR = src/
CXX = g++
CFLAGS = -fPIC -c -std=c++11 -I$(INCLUDEDIR)
LFLAGS = -shared
TESTLFLAGS =

$(TESTDIR)/test: $(TESTOBJS) $(OBJS) $(LIBDIR)/Text/libtext.so
	$(CXX) $(TESTLFLAGS) $(TESTOBJS) $(OBJS) $(LIBDIR)/Text/libtext.so -o $(TESTDIR)/test

$(BUILDDIR)/test.o: $(TESTDIR)/test.cpp
	$(CXX) $(CFLAGS) $(TESTDIR)/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/Server.o: $(SRCDIR)/Server/Server.cpp $(INCLUDEDIR)/Server/Server.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Server/Server.cpp -o $(BUILDDIR)/Server.o

$(BUILDDIR)/Group.o: $(SRCDIR)/Group/Group.cpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/Group.cpp -o $(BUILDDIR)/Group.o

$(BUILDDIR)/GroupAllocator.o: $(SRCDIR)/Group/GroupAllocator.cpp $(INCLUDEDIR)/Group/GroupAllocator.hpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/GroupAllocator.cpp -o $(BUILDDIR)/GroupAllocator.o

$(BUILDDIR)/ServerAllocator.o: $(SRCDIR)/Server/ServerAllocator.cpp $(INCLUDEDIR)/Server/ServerAllocator.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Server/ServerAllocator.cpp -o $(BUILDDIR)/ServerAllocator.o

test: $(TESTDIR)/test
	$(TESTDIR)/test

clean:
	rm $(OBJS) $(TESTOBJS)
