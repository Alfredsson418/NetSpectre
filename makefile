CC = gcc

NAME = netspec

BUILD = build
SRC = src

FLAGS = -lpcap -Wall

SRCFILES = $(wildcard $(SRC)/*.c)
OBJFILES = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCFILES))

.PHONY: build dirs clean memCheck

build: $(OBJFILES) 
	@echo "Building $(NAME)"
	@$(CC) $^ -o $(NAME) $(FLAGS)
	@echo "Done!"

$(BUILD)/%.o: $(SRC)/%.c | dirs
	@echo "Compiling $<"
	@$(CC) -c -o $@ $<

dirs: 
	@mkdir -p $(BUILD)

memCheck:
	-sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=log.txt ./$(NAME)

clean:
	@rm -f $(OBJFILES) $(NAME)
	@rm -r $(BUILD)