BUILDDIR = build/
BINDIR = bin/
INCLUDEDIR = include/
OBJS = $(BUILDDIR)/Server.o $(BUILDDIR)/Group.o $(BUILDDIR)/GroupAllocator.o $(BUILDDIR)/ServerAllocator.o
TESTDIR = test/
TESTOBJS = $(BUILDDIR)/test.o
EXECOBJS = $(BUILDDIR)/AllocateServers.o
SRCDIR = src/
CXX = g++
CFLAGS = -fPIC -c -std=c++11 -I$(INCLUDEDIR)
LFLAGS = -shared
TESTLFLAGS =
EXECLFLAGS =

$(BINDIR)/AllocateServers: $(EXECOBJS) $(OBJS)
	$(CXX) $(EXECLFLAGS) $(EXECOBJS) $(OBJS) -o $(BINDIR)/AllocateServers

$(TESTDIR)/test: $(TESTOBJS) $(OBJS)
	$(CXX) $(TESTLFLAGS) $(TESTOBJS) $(OBJS) -o $(TESTDIR)/test

$(BUILDDIR)/AllocateServers.o: $(SRCDIR)/AllocateServers.cpp
	$(CXX) $(CFLAGS) $(SRCDIR)/AllocateServers.cpp -o $(BUILDDIR)/AllocateServers.o

$(BUILDDIR)/test.o: $(TESTDIR)/test.cpp
	$(CXX) $(CFLAGS) $(TESTDIR)/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/Server.o: $(SRCDIR)/Server/Server.cpp $(INCLUDEDIR)/Server/Server.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Server/Server.cpp -o $(BUILDDIR)/Server.o

$(BUILDDIR)/Group.o: $(SRCDIR)/Group/Group.cpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/Group.cpp -o $(BUILDDIR)/Group.o

$(BUILDDIR)/GroupAllocator.o: $(SRCDIR)/Group/GroupAllocator.cpp $(INCLUDEDIR)/Group/GroupAllocator.hpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Group/GroupAllocator.cpp -o $(BUILDDIR)/GroupAllocator.o

$(BUILDDIR)/ServerAllocator.o: $(SRCDIR)/Server/ServerAllocator.cpp $(INCLUDEDIR)/Server/ServerAllocator.hpp $(INCLUDEDIR)/Group/GroupAllocator.hpp $(INCLUDEDIR)/Server/Server.hpp $(INCLUDEDIR)/Group/Group.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Server/ServerAllocator.cpp -o $(BUILDDIR)/ServerAllocator.o

test: $(TESTDIR)/test
	$(TESTDIR)/test

exec: $(BINDIR)/AllocateServers

clean:
	rm $(OBJS) $(TESTOBJS)
