OBJDIR := build
SRCDIR := src
CXX := gcc
WARNINGS := -Wall
ifeq ($(OS), Windows_NT)
	LDLIBS := -Iinclude -Llib -lglfw3 -lglfw3dll -lgdi32 -DGLFW_DLL
	OUTPUT := bin/out.exe
	DELCOM := rm -f
else
	LDLIBS := -lglfw
	OUTPUT := bin/out
	DELCOM := rm -f
endif
CXXFLAGS := $(LDLIBS) $(WARNINGS) -MMD -MP -Wl,-subsystem,console -g
SRCFILES := $(wildcard $(SRCDIR)/*.c)
HDRFILES := $(wildcard $(HDRFILES)/*.h)
NOTFILES := $(patsubst %.c,%.o,$(SRCFILES))
OBJFILES := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(NOTFILES))
DEPFILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CXX) $(OBJFILES) -o $@ $(LDLIBS) 

clean:
	-@$(DELCOM) $(OUTPUT) $(OBJDIR)/*

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@echo building $<...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
-include $(DEPFILES)