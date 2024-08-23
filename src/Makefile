CXX = g++
CFLAGS = -std=c++11 -Wall -O0 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4` -lm
PROG = proposed
SRCS = $(wildcard *.cpp)
# OBJS = $(SRCS:.cpp=.o)
OBJDIR = build
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY:all
all:$(PROG)
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@
# .SUFFIXES: .o .cpp
# .cpp.o:
# 	$(CXX) $(CFLAGS) -c $<

$(PROG): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(PROG)
# clean:
# 	rm -rf $(OBJS) $(PROG)
