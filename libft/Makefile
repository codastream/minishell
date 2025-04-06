NAME:=		libft.a

CC:=		cc
CFLAGS:=	-Wall -Wextra -Werror

ifdef DEBUG
	CFLAGS += -g
endif

ifdef FPIE
	CFLAGS += -fPIE
endif

SRC_DIR:=		srcs
INCLUDE_DIR:= 	includes
LIBFT_DIR:=		libft
BUILD_DIR:= 	.build

SRCS_FILES =	data/array/ft_has_unique_values_array.c\
				data/array/ft_quick_sort.c\
				data/array/ft_count_2dchar_null_ended.c\
				data/array/ft_count_3dchar_null_ended.c\
				data/hash/hash_util.c\
				data/hash/hash_util2.c\
				data/hash/hash.c\
				data/list/ft_lstadd_back.c\
				data/list/ft_lstadd_front.c\
				data/list/ft_lstclear.c\
				data/list/ft_lstdelone.c\
				data/list/ft_lstiter.c\
				data/list/ft_lstlast.c\
				data/list/ft_lstmap.c\
				data/list/ft_lstnew.c\
				data/list/ft_lstsize.c\
				conversion/ft_atoi_base.c\
				conversion/ft_hextoi.c\
				conversion/ft_atoi.c\
				conversion/ft_atol.c\
				conversion/ft_atoll.c\
				conversion/ft_atoull.c\
				conversion/ft_convert_base.c\
				conversion/ft_is_out_of_int_range.c\
				conversion/ft_is_atoistr.c\
				conversion/ft_itoa.c\
				conversion/ft_ltoa.c\
				conversion/ft_lutoa_base.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				math/ft_isprime.c\
				math/ft_iseven.c\
				mem/ft_bzero.c\
				mem/ft_calloc.c\
				mem/ft_free2d.c\
				mem/ft_memchr.c\
				mem/ft_memcmp.c\
				mem/ft_memcpy.c\
				mem/ft_memmove.c\
				mem/ft_memset.c\
				print/ft_print_address.c\
				print/ft_print_array_int.c\
				print/ft_print_tabstr.c\
				print/ft_print_char.c\
				print/ft_print_hexa.c\
				print/ft_print_integer.c\
				print/ft_print_str.c\
				print/ft_print_unsigned.c\
				print/ft_printf.c\
				print/ft_putchar_fd.c\
				print/ft_putendl_fd.c\
				print/ft_putnbr_fd.c\
				print/ft_putstr_fd.c\
				print/ft_puterr.c\
				print/ft_print_color.c\
				printfd/ft_print_address_fd.c\
				printfd/ft_print_char_fd.c\
				printfd/ft_print_hexa_fd.c\
				printfd/ft_print_integer_fd.c\
				printfd/ft_print_str_fd.c\
				printfd/ft_print_unsigned_fd.c\
				printfd/ft_printfd.c\
				splitter/delimiters.c\
				splitter/delimiters2.c\
				splitter/free.c\
				splitter/ft_splitter.c\
				splitter/init.c\
				splitter/separators.c\
				string/ft_isalpha.c\
				string/ft_isalnum.c\
				string/ft_isalnumstr.c\
				string/ft_isdigit.c\
				string/ft_isemptystr.c\
				string/ft_isascii.c\
				string/ft_isnumstr.c\
				string/ft_isprint.c\
				string/ft_split.c\
				string/ft_split_str.c\
				string/ft_split_index.c\
				string/ft_strcat.c\
				string/ft_strcmp.c\
				string/ft_strdup.c\
				string/ft_strndup.c\
				string/ft_striteri.c\
				string/ft_strjoin.c\
				string/ft_strjoinfree.c\
				string/ft_strlcat.c\
				string/ft_strlcpy.c\
				string/ft_strlen.c\
				string/ft_strmapi.c\
				string/ft_strncmp.c\
				string/ft_strnstr.c\
				string/ft_strchr.c\
				string/ft_strchri.c\
				string/ft_strstri.c\
				string/ft_strcharsi.c\
				string/ft_strrchr.c\
				string/ft_strtrim.c\
				string/ft_substr.c\
				string/ft_subst.c\
				string/ft_subst_first.c\
				string/ft_toupper.c\
				string/ft_tolower.c\

SRCS:=			$(addprefix $(SRC_DIR)/, $(SRCS_FILES))

#=============================OBJECTS===========================#

OBJS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o}

#=============================INCLUDES==========================#

INC:=			-I$(INCLUDE_DIR) -I splitter/splitter.h

#================================DIR============================#

DIRS:=			$(sort $(shell dirname $(OBJS))) #no duplicates

#=============================TARGETS===========================#

all: $(NAME)

$(DIRS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
