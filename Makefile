# **********************  MINISHELL MAKEFILE  ********************** #

.PHONY			:	all clean fclean re debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	cub3D
NAME_LIBFT		=	libft.a
DEBUG			=	minishell_debug
DEBUG_LIBFT		=	libft_debug.a

# ----------  Directories  ----------- #

DIR_HEAD			=	./incl/
DIR_SRCS			=	./srcs/
DIR_LIBFT			=	./libft/
DIR_MLX				=	./mlx_linux/
DIR_OBJS			=	.build/
DIR_OBJS_D			=	.build_debug/
DIR_DEBUG			=	${NAME}.dSYM

# -------------  Files  -------------- #

HEAD			=	cub3D.h

SRCS			=	main.c				\
					get_time.c			\
					play_game.c			\
					init_cube.c			\
					raycasting.c		\
					mlx_utils.c			\
					handle_events.c		\
					move_player.c		\
					exit_game.c			\
					draw_textures.c		\
					generate_textures.c	\

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}

# --------------  Path  -------------- #

PATH_HEAD		=	${addprefix ${DIR_HEAD}, ${HEAD}}
PATH_LIBFT		=	${addprefix ${DIR_LIBFT}, ${LIBFT_A}}

# ----------  Compilation  ----------- #

CC				=	cc
CFLAGS			= 	-Wall -Wextra -Werror
AR				= 	ar rcs
FSANITIZE		=	-fsanitize=address
OPTI			=	-O3
LIBFT			=	-lft
LIBFT_D			=	-lft_debug
MLX				=	-lmlx
I_MLX			=	-I/usr/include -Imlx_linux -O3
LIB_GRAPH		=	-L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MMD				=	-MMD

# ------------  Commands  ------------ #

RM				=	rm -rf
MKDIR			=	mkdir -p
LEAKS			=	leaks -atExit -- 
LLDB			=	lldb
CP				=	cp
VALGRIND		=	valgrind --leak-check=full --track-origins=yes --show-reachable=no --show-possibly-lost=no --trace-children=yes

# ****************************  RULES  ***************************** #

all					:
						${MAKE} -C ${DIR_LIBFT}
						${MAKE} -C ${DIR_MLX}
						$(MAKE) -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}				:	${OBJS} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${DIR_LIBFT} ${LIBFT} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}

-include ${DEPS}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${DEBUG} ${OBJS_D} -L ${DIR_LIBFT} ${LIBFT_D} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH} -g3 ${FSANITIZE}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}

-include ${DEPS_D}

# ---------  Usual Commands  --------  #

clean				:	
						${RM} ${DIR_OBJS}
						${RM} ${DIR_OBJS_D}
						${RM} ${DIR_DEBUG}

fclean				:	clean
						${RM} ${NAME}
						${RM} ${DEBUG}
						$(MAKE) fclean -C ${DIR_LIBFT}
						${MAKE} clean -C ${DIR_MLX}

re					:
						$(MAKE) fclean
						$(MAKE) all

# ---------  Other Commands  --------- #

debug				:	
						$(MAKE) debug -C ${DIR_LIBFT}
						$(MAKE) -j ${DEBUG}

# -----------  Run Commands  --------- #

run					:	all
						./${NAME}

runl				:	all
						${LEAKS}./${NAME}

runs				:	debug
						./${DEBUG}

rund				:	debug
						${LLDB} ./${DEBUG}

runv				:	all
						${VALGRIND} ./${NAME}
