DEFAULT_TARGET = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

SRC_DIR = srcs
BOT_DIR = bot
OBJ_DIR = .obj
INCLUDE_DIR = include


SRC_FILES = $(SRC_DIR)/main.cpp \
			$(SRC_DIR)/channel/channel.cpp \
			$(SRC_DIR)/commands/commands.cpp \
			$(SRC_DIR)/commands/join.cpp \
			$(SRC_DIR)/commands/mode.cpp \
			$(SRC_DIR)/server/server.cpp \
			$(SRC_DIR)/server/user.cpp \
			$(SRC_DIR)/utils/debug.cpp \
			$(SRC_DIR)/utils/parsing.cpp \
			$(SRC_DIR)/utils/RPL.cpp \
			$(SRC_DIR)/utils/signal.cpp \
			$(SRC_DIR)/utils/utils.cpp

BOT_FILES = $(BOT_DIR)/bot.cpp


HDR_FILES = $(INCLUDE_DIR)/channel.hpp \
			$(INCLUDE_DIR)/commands.hpp \
			$(INCLUDE_DIR)/irc_exception.hpp \
			$(INCLUDE_DIR)/irc_fct.hpp \
			$(INCLUDE_DIR)/irc.hpp \
			$(INCLUDE_DIR)/server.hpp \
			$(INCLUDE_DIR)/user.hpp \

HDR_BOT_FILES = $(BOT_DIR)/bot.hpp

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_BOT_FILES = $(patsubst $(BOT_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(BOT_FILES))

NUM_FILES = $(words $(SRC_FILES))
CUR_FILE = 0

USAGE		=	@printf "$(CURSIVE)$(CYAN)\t[use $(PURPLE)./$(DEFAULT_TARGET) <port> <password> $(CYAN) to start the program] \n"
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

$(OBJ_DIR)/%.o: $(BOT_DIR)/%.cpp $(HDR_BOT_FILES)
	@mkdir -p $(@D)
	@$(eval CUR_FILE := $(shell echo $$(($(CUR_FILE) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CUR_FILE) * 100 / $(NUM_FILES)))))
	@echo "$(CURSIVE)$(GRAY)[Compiling]$(RESET)$(GRAY) $< $(CURSIVE)[$(CUR_FILE)/$(NUM_FILES) files, $(PERCENT)%]$ \t$(RESET)✔\r"
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

bot : $(OBJ_BOT_FILES) 
	@$(CXX) $(CXXFLAGS) -o ircbot $(BOT_FILES)
	@printf "\n\tCompilation of bot$(CURSIVE)$(GREEN) DONE\n$(RESET)"
	@echo "Compiler flags used: $(CXXFLAGS)"

clean:
	@printf "$(CURSIVE)$(GRAY)- [Removing] $(DEFAULT_TARGET) object ... $(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(CURSIVE)$(GREEN)\t   done\n$(RESET)"
	
fclean: clean
	@printf "$(CURSIVE)$(GRAY)- [Removing] $(DEFAULT_TARGET) executable ... $(RESET)"
	@rm -f $(DEFAULT_TARGET) ircbot
	@printf "$(CURSIVE)$(GREEN)\t done\n$(RESET)\n"

re : fclean all

.PHONY: all clean re