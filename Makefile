DEFAULT_TARGET = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = src
OBJ_DIR = .obj
INCLUDE_DIR = include
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HDR_FILES = $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

NUM_FILES = $(words $(SRC_FILES))
CUR_FILE = 0

USAGE		=	@printf "$(CURSIVE)$(CYAN)\t[use $(PURPLE)./$(DEFAULT_TARGET) $(CYAN) to start the program] \n"
GREEN		=	\033[92;5;118m
HGRN 		=	\033[1;92m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
PURPLE		= 	\033[4;35m
CYAN		=	\033[0;36m
CURSIVE		=	\033[33;3m

all: $(DEFAULT_TARGET)

$(DEFAULT_TARGET): $(OBJ_FILES)
	@$(CXX) $(CXXFLAGS) -o $(DEFAULT_TARGET) $(OBJ_FILES)
	@printf "\n\tCompilation of $(DEFAULT_TARGET)$(CURSIVE)$(GREEN) DONE\n$(RESET)"
	@echo "Compiler flags used: $(CXXFLAGS)"
	$(USAGE)
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)
	@mkdir -p $(@D)
	@$(eval CUR_FILE := $(shell echo $$(($(CUR_FILE) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CUR_FILE) * 100 / $(NUM_FILES)))))
	@echo "$(CURSIVE)$(GRAY)[Compiling]$(RESET)$(GRAY) $< $(CURSIVE)[$(CUR_FILE)/$(NUM_FILES) files, $(PERCENT)%]$ \t$(RESET)✔\r"
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@printf "$(CURSIVE)$(GRAY)- [Removing] $(TARGET) object ... $(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(CURSIVE)$(GREEN)\t   done\n$(RESET)"

fclean: clean
	@printf "$(CURSIVE)$(GRAY)- [Removing] $(TARGET) executable ... $(RESET)"
	@rm -f $(TARGET)
	@printf "$(CURSIVE)$(GREEN)\t done\n$(RESET)\n"

re : fclean all

.PHONY: all clean re