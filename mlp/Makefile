# project name (generate executable with this name)
TARGET   = mlp 

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
INCLUDEDIR = include

CC       = g++
# compiling flags here
CFLAGS   = -std=c++1y -Wall -I$(INCLUDEDIR)

LINKER   = g++
# linking flags here
LFLAGS   = -Wall -I. -lm -lboost_serialization

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDEDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -rf

$(BINDIR)/$(TARGET): $(OBJECTS)
	    @mkdir -p bin 
			@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@ -g
			    @echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	    @mkdir -p obj 
			$(CC) $(CFLAGS) -c $< -o $@ -g
			    @echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(OBJDIR) $(BINDIR)
		@echo "Cleanup complete!"
