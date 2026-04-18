# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iinclude -Wall -Wextra

# Source files
SRC = main.c \
      fcfs.c \
      sjfnp.c \
      rr.c \
      srtf.c \
      priority_np.c \
      priority_p.c \
      csv.c \
      reset_results.c \
      print_table.c \
      ai_rule.c \
      gantt.c

# Output executable
TARGET = scheduler

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

# Clean object files and executable
clean:
	rm -f $(TARGET)
