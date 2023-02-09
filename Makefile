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
DIR_SRCS_P			=	./srcs/parsing/
DIR_SRCS_U			=	./srcs/utils/
DIR_LIBFT			=	./libft/
DIR_MLX				=	./mlx_linux/
DIR_OBJS			=	.build/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_U			=	.build/utils/
DIR_OBJS_D			=	.build_debug/
DIR_OBJS_D_P		=	.build_debug/parsing/
DIR_OBJS_D_U		=	.build_debug/utils/
DIR_DEBUG			=	${NAME}.dSYM

# -------------  Files  -------------- #

HEAD			=	cub3D.h

SRCS			=	main.c			\
					get_time.c		\
					play_game.c		\
					init_cube.c		\
					raycasting.c	\
					mlx_utils.c		\
					handle_events.c	\
					move_player.c

SRCS_P			=	get_data.c		\
					get_elem.c		\
					get_file_line.c	\
					get_map.c

SRCS_U			=	error.c			\
					free_data.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_U			=	${SRCS_U:%.c=${DIR_OBJS_U}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_D_P		=	${SRCS_P:%.c=${DIR_OBJS_D_P}%.o}
OBJS_D_U		=	${SRCS_U:%.c=${DIR_OBJS_D_U}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}
DEPS_D_P		=	${OBJS_D_P:.o=.d}
DEPS_D_U		=	${OBJS_D_U:.o=.d}

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

${NAME}				:	${OBJS} ${OBJS_P} ${OBJS_U} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_P} ${OBJS_U} -L ${DIR_LIBFT} ${LIBFT} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_U}%.o	:	${DIR_SRCS_U}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} ${DIR_OBJS_P}
						${MKDIR} ${DIR_OBJS_U}

-include ${DEPS}
-include ${DEPS_P}
-include ${DEPS_U}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${OBJS_D_P} ${OBJS_D_U} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${DEBUG} ${OBJS_D} ${OBJS_D_P} ${OBJS_D_U} -L ${DIR_LIBFT} ${LIBFT_D} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH} -g3 ${FSANITIZE}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}
						${MKDIR} ${DIR_OBJS_D_P}
						${MKDIR} ${DIR_OBJS_D_U}

-include ${DEPS_D}
-include ${DEPS_D_P}
-include ${DEPS_D_U}

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
