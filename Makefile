
CC := g++ # This is the main compiler

SRCDIR := src
HEADERSDIR := include
BUILDDIR := build
TARGET := bin/oberon

SRCEXT := cpp
HEADERSEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCES_TEST := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -name 'oberon.cpp')
HEADERS := $(shell find $(HEADERSDIR) -type f -name *.$(HEADERSEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TEST_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_TEST:.$(SRCEXT)=.o))
CXXFLAGS := -g -W -Wall -Wextra -std=c++11
LIB := -pthread -L lib
INC := -I include
GTEST := ${GTEST_DIR}

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) # $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester: $(TEST_OBJECTS)
	$(CC) $(CXXFLAGS) $(LIB) test/TestOberonLang.cpp $(GTEST)/libgtest.a $(INC) -o bin/tester $^

oberon: $(OBJECTS)
	$(CC) $(CXXFLAGS) $(LIB) -o bin/$@ $(INC) $

# Spikes
#ticket:
#  $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
