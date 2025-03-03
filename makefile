# Variables del compilador y flags
CXX      = g++
CXXFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
LDFLAGS  = `pkg-config --libs gtk+-3.0`

# Directorios
SRCDIR   = src
BUILDDIR = build

# Archivos fuente y objetos
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
TARGET   = salida.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf $(BUILDDIR)

run: $(TARGET)
	./$(TARGET)
