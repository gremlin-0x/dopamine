# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lncurses

# Source and output
SRC = main.c ui.c logic.c storage.c
OUT = dopamine

# Default target
all: $(OUT)

# Link objects
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

# Install target
install: $(OUT)
	mkdir -p ~/.dopamine
	sudo cp $(OUT) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(OUT)
	@echo "Installed $(OUT) to /usr/local/bin"

# Uninstall target
uninstall:
	sudo rm -f /usr/local/bin/$(OUT)
	@echo "Uninstalled $(OUT) from /usr/local/bin"

# Cleanup
clean:
	rm -f $(OUT)

