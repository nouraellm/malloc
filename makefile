# **************************************************************************** #
# Makefile for ft_malloc                                                      #
# **************************************************************************** #

# Compiler and flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -fPIC -fvisibility=hidden
CFLAGS      += -I includes
LDFLAGS     :=
ifeq ($(shell uname), Darwin)
  LDFLAGS += -Wl,-exported_symbols_list,exported_symbols.txt
endif

# Directories
SRC_DIR      := src
BUILD_DIR    := build
INC_DIR      := includes
THIRD_PARTY  := third_party
TEST_DIR     := tests
FT_PRINTF_LIB := $(THIRD_PARTY)/libftprintf.a

# Source files organized by module
CORE_SRCS    := $(SRC_DIR)/core/ft_malloc.c \
                $(SRC_DIR)/core/ft_free.c \
                $(SRC_DIR)/core/ft_realloc.c \
                $(SRC_DIR)/core/ft_zone.c \
                $(SRC_DIR)/core/ft_block_utils.c \
                $(SRC_DIR)/core/ft_zone_manager.c

DISPLAY_SRCS := $(SRC_DIR)/display/ft_show_alloc_mem.c \
                $(SRC_DIR)/display/ft_show_alloc_mem_ex.c

UTILS_SRCS   := $(SRC_DIR)/utils/ft_debug.c \
                $(SRC_DIR)/utils/ft_thread.c \
                $(SRC_DIR)/utils/ft_memcpy.c \
                $(SRC_DIR)/utils/ft_malloc_errors.c

SRC_FILES   := $(CORE_SRCS) $(DISPLAY_SRCS) $(UTILS_SRCS)
OBJ_FILES   := $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target names
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME        := libft_malloc_$(HOSTTYPE).so
SO_LINK     := libft_malloc.so
TEST_NAME   := test_malloc
MAIN_FILE   := main.c

# Default target
all: $(NAME) symlink

# Create third_party directory if needed
$(THIRD_PARTY):
	@mkdir -p $(THIRD_PARTY)

# Check if ft_printf library exists
$(FT_PRINTF_LIB): | $(THIRD_PARTY)
	@if [ ! -f $(FT_PRINTF_LIB) ]; then \
		echo "Error: $(FT_PRINTF_LIB) not found!"; \
		echo "Please ensure libftprintf.a is in $(THIRD_PARTY)/"; \
		exit 1; \
	fi

# Create build directory structure
$(BUILD_DIR)/core/%.o: $(SRC_DIR)/core/%.c | $(BUILD_DIR)/core
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/display/%.o: $(SRC_DIR)/display/%.c | $(BUILD_DIR)/display
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c | $(BUILD_DIR)/utils
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/core $(BUILD_DIR)/display $(BUILD_DIR)/utils:
	@mkdir -p $@

# Build shared library
$(NAME): $(FT_PRINTF_LIB) $(OBJ_FILES)
	@$(CC) -shared -o $@ $(OBJ_FILES) $(FT_PRINTF_LIB) $(LDFLAGS)
	@echo "Built: $(NAME)"

# Create symlink
symlink: $(NAME)
	@ln -sf $(NAME) $(SO_LINK)

# Build test executable
$(TEST_NAME): $(TEST_DIR)/main.c $(NAME)
	@$(CC) -Wall -Wextra -Werror -I $(INC_DIR) \
		$(TEST_DIR)/main.c -L. -lft_malloc -o $(TEST_NAME)

# Run tests
test: all $(TEST_NAME)
ifeq ($(shell uname), Darwin)
	@echo "[+] Running test with DYLD_INSERT_LIBRARIES"
	@DYLD_INSERT_LIBRARIES=./$(SO_LINK) DYLD_FORCE_FLAT_NAMESPACE=1 ./$(TEST_NAME)
else
	@echo "[+] Running test with LD_PRELOAD"
	@LD_PRELOAD=./$(SO_LINK) ./$(TEST_NAME)
endif

# Clean build artifacts
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory"

# Full clean
fclean: clean
	@rm -f $(NAME) $(SO_LINK) $(TEST_NAME)
	@echo "Full clean completed"

# Rebuild
re: fclean all

.PHONY: all clean fclean re test symlink
