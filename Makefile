COMPILER := gcc
SRC := $(wildcard src/*.c)
EXECUTABLE := dist/main
OBJECTS := $(patsubst src/%, objects/%, $(SRC:.c=.o))

build: $(OBJECTS)
	@$(COMPILER) -o $(EXECUTABLE) $^

$(OBJECTS): $(SRC)
	@$(COMPILER) -c $< -o $@

clear:
	@rm -f $(OBJECTS) $(EXECUTABLE)

run: build
	@./$(EXECUTABLE)