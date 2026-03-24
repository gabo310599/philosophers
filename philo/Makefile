NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I include

SRCS = \
src/main.c \
src/parsing/parsing_args.c \
src/parsing/parsing_utils.c \
src/init/init_table.c \
src/init/init_forks.c \
src/init/init_philos.c \
src/threads/create_threads.c \
src/threads/monitor.c \
src/threads/philo_routine.c \
src/actions/eat.c \
src/actions/sleep.c \
src/actions/think.c \
src/utils/cleanup.c \
src/utils/mutex_utils.c \
src/utils/print_utils.c \
src/utils/simulation_utils.c \
src/utils/time_utils.c \
src/exit/error_exit.c

OBJS = $(SRCS:.c=.o)

#-----------------------------------------------------------
# Principal
#-----------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "✅ Proyecto compilado correctamente."

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"

#-----------------------------------------------------------
# Bonus (placeholder por ahora)
#-----------------------------------------------------------
bonus: $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "✅ Proyecto compilado con bonus correctamente."

#-----------------------------------------------------------
# Limpieza
#-----------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@echo "🧹 Archivos objeto eliminados."

fclean: clean
	@rm -f $(NAME)
	@echo "🧼 Ejecutable eliminado."

re: fclean all

.PHONY: all clean fclean re bonus