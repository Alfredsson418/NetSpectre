CC = gcc

NAME = netspec

BUILD = build
SRC = src

CFLAGS = -Wall
LDFLAGS = -lpcap
SRCFILES = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c) 
OBJFILES = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCFILES))

.PHONY: build clean memCheck

build: $(OBJFILES)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)
	@echo "Done!"

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

memCheck:
	-sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=log.txt ./$(NAME)

clean:
	@rm -f $(OBJFILES) $(NAME)
	@rm -r $(BUILD)