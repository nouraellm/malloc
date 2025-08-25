CC          := cc
CFLAGS      := -Wall -Wextra -Werror -fPIC -fvisibility=hidden -I includes
ifeq ($(shell uname), Darwin)
  LDFLAGS += -Wl,-exported_symbols_list,exported_symbols.txt
endif

SRC_DIR     := src
INC_DIR     := includes
TEST_NAME   := test_malloc
MAIN_FILE   := main.c

SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES   := $(SRC_FILES:.c=.o)

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME    := libft_malloc_$(HOSTTYPE).so
SO_LINK := libft_malloc.so

all: $(NAME) symlink

$(NAME): $(OBJ_FILES)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

symlink:
	@ln -sf $(NAME) $(SO_LINK)

$(TEST_NAME): $(MAIN_FILE)
	$(CC) -Wall -Wextra -Werror -I includes $(MAIN_FILE) -L. -lft_malloc -o $(TEST_NAME)

test: all $(TEST_NAME)
ifeq ($(shell uname), Darwin)
	@echo "[+] Running test with DYLD_INSERT_LIBRARIES"
	DYLD_INSERT_LIBRARIES=./$(SO_LINK) DYLD_FORCE_FLAT_NAMESPACE=1 ./$(TEST_NAME)
else
	@echo "[+] Running test with LD_PRELOAD"
	LD_PRELOAD=./$(SO_LINK) ./$(TEST_NAME)
endif

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME) $(SO_LINK) $(TEST_NAME)

re: fclean all
