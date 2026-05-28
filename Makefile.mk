CXX = g++
CXXFLAGS = -Wall -pedantic -Werror -g

SRCS = \
src/core/main.cpp \
src/core/executor.cpp \
src/core/pipeline.cpp \
src/core/IO_redirection.cpp \
src/commands/cdEchoPwd.cpp \
src/commands/ls.cpp \
src/commands/pinfo.cpp \
src/features/history.cpp \
src/features/background_fg.cpp \
src/features/signals.cpp \
src/features/autocomplete.cpp \
src/utilities/display_requirement.cpp \
src/utilities/search.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# ----------------------------
# Compile rule
# ----------------------------
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# ----------------------------
# Link final binary
# ----------------------------
Posix_Shell: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# ----------------------------
# Clean build
# ----------------------------
clean:
	rm -f $(OBJS) Posix_Shell