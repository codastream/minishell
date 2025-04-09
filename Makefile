NAME		:=	minishell
BONUS_NAME	:=	minishell_bonus
LIBFT		:=	libft.a

#==============================COMPIL===========================#

CC:=		cc
CFLAGS:=	-Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address
endif

MAKEFLAGS	:=	--no-print-directory

#================================COUNT============================#

NB_COMP	:=	1

ifndef RECURSION
TO_COMP :=	$(shell make RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP	:=	1
endif

PERCENT	:= 0

NB_COMP_BONUS := 1
ifndef RECURSION
TO_COMP_BONUS := $(shell make bonus RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP_BONUS := 1
endif


#==============================COLORS==============================#
NOC			= \e[0m
BOLD		= \e[1m
DIM			= \e[2m
UNDERLINE	= \e[4m
BLACK		= \e[1;30m
RED			= \e[1m\e[38;5;196m
GREEN		= \e[1m\e[38;5;76m
YELLOW		= \e[1m\e[38;5;220m
BLUE		= \e[1m\e[38;5;33m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m
SPECIAL		= \e[1m\e[38;5;223m

BLACK_BG 	= \033[0;40m
RED_BG 		= \033[0;41m
GREEN_BG 	= \033[0;42m
YELLOW_BG 	= \033[0;43m
BLUE_BG 	= \033[0;44m
MAGENTA_BG 	= \033[0;45m
CYAN_BG 	= \033[0;46m
WHITE_BG 	= \033[0;47m
RESET_BG	= \033[0m

#================================DIRS============================#

SRC_DIR			:=  srcs
SRC_DIR_BONUS	:=	srcs_bonus
HEADER_DIR		:=	includes
LIBFT_DIR		:=	libft
BUILD_DIR		:=	.build

#==============================SOURCES===========================#

# no duplicates
SRCS_FILES:=	main.c\
				builtins/builtins.c\
				builtins/cd.c\
				builtins/cd_utils.c\
				builtins/echo.c\
				builtins/env.c\
				builtins/exit.c\
				builtins/export.c\
				builtins/export_utils.c\
				builtins/hash_export.c\
				builtins/pwd.c\
				builtins/unset.c\
				parsing/lexing/lexer.c\
				parsing/lexing/lexer_utils.c\
				parsing/lexing/split_utils.c\
				parsing/lexing/tokens_utils.c\
				parsing/lexing/tokens_utils_create.c\
				parsing/lexing/command.c\
				parsing/lexing/command_utils.c\
				parsing/lexing/command_utils_add.c\
				parsing/lexing/command_utils_file.c\
				parsing/lexing/trim.c\
				parsing/lexing/trim_utils.c\
				parsing/lexing/args.c\
				parsing/checking/check_redir.c\
				parsing/checking/check_quote.c\
				parsing/checking/check_pipe.c\
				parsing/checking/check_path.c\
				parsing/checking/check_files.c\
				parsing/checking/path_utils.c\
				execution/exec.c\
				execution/exec_redir.c\
				execution/exec_redir_heredoc.c\
				execution/exec_utils.c\
				execution/exec_utils2.c\
				execution/heredoc.c\
				execution/heredoc_utils.c\
				execution/redir_utils.c\
				execution/navigation.c\
				execution/fds.c\
				execution/fds_utils.c\
				errors/errors.c\
				errors/errors_alloc.c\
				errors/errors_custom.c\
				errors/errors_utils.c\
				errors/errors_print.c\
				errors/errors_print_custom.c\
				signal/signal.c\
				signal/signal_setup.c\
				utils/tree.c\
				utils/tree_utils.c\
				utils/free.c\
				utils/free_utils.c\
				utils/free_combo.c\
				utils/init.c\
				utils/loop.c\
				utils/string_utils.c\
				utils/quote_utils.c\
				utils/debug.c\
				utils/debug_utils.c\
				vars/vars.c\
				vars/return_code.c\
				vars/expand.c\
				vars/expand_heredoc.c\
				vars/expand_utils.c\
				vars/expand_utils2.c\
				vars/sort.c\

SRCS_FILES_BONUS:=	main_bonus.c\
					builtins/builtins_bonus.c\
					builtins/cd_bonus.c\
					builtins/cd_utils_bonus.c\
					builtins/echo_bonus.c\
					builtins/env_bonus.c\
					builtins/exit_bonus.c\
					builtins/export_bonus.c\
					builtins/export_utils_bonus.c\
					builtins/hash_export_bonus.c\
					builtins/pwd_bonus.c\
					builtins/unset_bonus.c\
					parsing/lexing/lexer_bonus.c\
					parsing/lexing/lexer_utils_bonus.c\
					parsing/lexing/split_utils_bonus.c\
					parsing/lexing/tokens_utils_bonus.c\
					parsing/lexing/tokens_utils_create_bonus.c\
					parsing/lexing/command_bonus.c\
					parsing/lexing/command_utils_bonus.c\
					parsing/lexing/command_utils_add_bonus.c\
					parsing/lexing/command_utils_file_bonus.c\
					parsing/lexing/trim_bonus.c\
					parsing/lexing/trim_utils_bonus.c\
					parsing/lexing/args_bonus.c\
					parsing/checking/check_redir_bonus.c\
					parsing/checking/check_quote_bonus.c\
					parsing/checking/check_pipe_bonus.c\
					parsing/checking/check_path_bonus.c\
					parsing/checking/check_files_bonus.c\
					parsing/checking/path_utils_bonus.c\
					execution/exec_bonus.c\
					execution/exec_redir_bonus.c\
					execution/exec_redir_heredoc_bonus.c\
					execution/exec_utils_bonus.c\
					execution/exec_utils2_bonus.c\
					execution/heredoc_bonus.c\
					execution/heredoc_utils_bonus.c\
					execution/redir_utils_bonus.c\
					execution/navigation_bonus.c\
					execution/fds_bonus.c\
					execution/fds_utils_bonus.c\
					errors/errors_bonus.c\
					errors/errors_alloc_bonus.c\
					errors/errors_custom_bonus.c\
					errors/errors_utils_bonus.c\
					errors/errors_print_bonus.c\
					errors/errors_print_custom_bonus.c\
					signal/signal_bonus.c\
					signal/signal_setup_bonus.c\
					utils/tree_bonus.c\
					utils/tree_utils_bonus.c\
					utils/free_bonus.c\
					utils/free_utils_bonus.c\
					utils/free_combo_bonus.c\
					utils/init_bonus.c\
					utils/loop_bonus.c\
					utils/string_utils_bonus.c\
					utils/quote_utils_bonus.c\
					utils/debug_bonus.c\
					utils/debug_utils_bonus.c\
					vars/vars_bonus.c\
					vars/return_code_bonus.c\
					vars/expand_bonus.c\
					vars/expand_heredoc_bonus.c\
					vars/expand_utils_bonus.c\
					vars/expand_utils2_bonus.c\
					vars/sort_bonus.c\
					wildcard/wildcard_args_bonus.c\
					wildcard/wildcard_bonus.c\
					wildcard/wildcard_utils_bonus.c\
					wildcard/wildcard_init_bonus.c\

SRCS:=			$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
SRCS_BONUS:=	$(addprefix $(SRC_DIR_BONUS)/, $(SRCS_FILES_BONUS))

#=============================OBJECTS===========================#

OBJS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o}
OBJS_BONUS:=	${SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR)/bonus/%.o}

#===============================DEPS=============================#

DEPS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d}
DEPS_BONUS:=	${SRCS_BONUS:$(SRC_DIR_BONUSIR)/%.c=$(BUILD_DIR)/bonus/%.d}

#=============================INCLUDES===========================#

INC:=			-I$(HEADER_DIR) -I$(LIBFT_DIR)

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates
DIRS_BONUS		:=	$(sort $(shell dirname $(OBJS_BONUS))) #no duplicates

#===============================RULES============================#

all: $(NAME)

bonus: $(BONUS_NAME)

$(DIRS):
	@mkdir -p $@

$(DIRS_BONUS):
	@mkdir -p $@

$(NAME): $(LIBFT) $(OBJS)
	@echo "\n$(GREEN)Create binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INC) -o $@ -lreadline
	@echo "$(SPECIAL)"
	@echo " ██████   ██████  ███          █████               ████  ████       █████████                                ████ ";
	@echo "░░██████ ██████  ░░░          ░░███               ░░███ ░░███      ███░░░░░███                              ░░███ ";
	@echo " ░███░█████░███  ████   █████  ░███████    ██████  ░███  ░███     ░███    ░███  ████████    ███████  ██████  ░███ ";
	@echo " ░███░░███ ░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███     ░███████████ ░░███░░███  ███░░███ ███░░███ ░███ ";
	@echo " ░███ ░░░  ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███     ░███░░░░░███  ░███ ░███ ░███ ░███░███████  ░███ ";
	@echo " ░███      ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███     ░███    ░███  ░███ ░███ ░███ ░███░███░░░   ░███ ";
	@echo " █████     █████ █████ ██████  ████ █████░░██████  █████ █████    █████   █████ ████ █████░░███████░░██████  █████";
	@echo "░░░░░     ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░    ░░░░░   ░░░░░ ░░░░ ░░░░░  ░░░░░███ ░░░░░░  ░░░░░ ";
	@echo "                                                                                           ███ ░███               ";
	@echo "                                                                                          ░░██████                ";
	@echo "                                                                                           ░░░░░░                 ";
	@echo "$(NOC)"

$(BONUS_NAME): $(LIBFT) $(OBJS_BONUS)
	@echo "\n$(GREEN)The birth of Bonus (wildcard only)$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(INC) -o $@ -lreadline
	@cat bonaive.txt

# $$@D gets directory from cu$(INC) rrent target - pipe prevents from relink
# tput cols to get columns nb of terminal
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	@mkdir -p $(BUILD_DIR)
	@if [ $(NB_COMP) -eq 1 ]; then echo "\n$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP)00 "/" $(TO_COMP)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP)/$(TO_COMP) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))


$(BUILD_DIR)/bonus/%.o: $(SRC_DIR_BONUS)/%.c | $(DIRS_BONUS)
	@mkdir -p $(BUILD_DIR)/bonus/
	@if [ $(NB_COMP_BONUS) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP_BONUS)00 "/" $(TO_COMP_BONUS)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP_BONUS)/$(TO_COMP_BONUS) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP_BONUS=$(shell expr $(NB_COMP_BONUS) + 1))

$(LIBFT_DIR):
	@ mkdir -p $@
	@ git clone "git@github.com:codastream/libft.git" ${LIBFT_DIR}

$(LIBFT): $(LIBFT_DIR)
	@ make -C $(LIBFT_DIR)/
	@ cp $(LIBFT_DIR)/$(LIBFT) ./

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR)
	@rm -f $(LIBFT)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)

re: fclean
	@make

rebonus: fclean
	@make bonus

.PHONY: all clean fclean re rebonus

-include $(DEPS)
