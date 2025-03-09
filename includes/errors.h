#ifndef ERRORS_H
# define ERRORS_H

# define EXIT_IGNORE 0
# define EXIT_SYNTAX_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_SUCH_FILE_OR_DIRECTORY 127
# define EXIT_HEREDOC_ERROR 130

# define MSG_MEMORY_ERROR "memory error"
# define MSG_FILENAME_ARGUMENT_REQUIRED "filename argument required"
# define MSG_SYNTAX_QUOTE_ERROR "unexpected EOF while looking for matching `\"'"
# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_NO_SUCH_FILE_OR_DIRECTORY "No such file or directory"
# define MSG_TOO_MANY_ARGUMENTS "too many arguments"
# define MSG_NUMERIC_ARGUMENT_REQUIRED "numeric argument required"
# define MSG_NOT_VALID_IDENTIFIER "not a valid identifier"
# define MSG_IS_DIRECTORY "Is a directory"

#endif
