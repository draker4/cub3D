# **********************  MINISHELL MAKEFILE  ********************** #

.PHONY			:	all clean fclean re debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	cub3D
NAME_LIBFT		=	libft.a
DEBUG			=	cub3D_debug
DEBUG_LIBFT		=	libft_debug.a

# ----------  Directories  ----------- #

DIR_HEAD			=	./incl/
DIR_SRCS			=	./srcs/
DIR_SRCS_G			=	./srcs/game/
DIR_SRCS_P			=	./srcs/parsing/
DIR_SRCS_S			=	./srcs/sprites/
DIR_SRCS_U			=	./srcs/utils/
DIR_LIBFT			=	./libft/
DIR_MLX				=	./mlx_linux/
DIR_OBJS			=	.build/
DIR_OBJS_G			=	.build/game/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_S			=	.build/sprites/
DIR_OBJS_U			=	.build/utils/
DIR_OBJS_D			=	.build_debug/
DIR_OBJS_D_G		=	.build_debug/game/
DIR_OBJS_D_P		=	.build_debug/parsing/
DIR_OBJS_D_S		=	.build_debug/sprites/
DIR_OBJS_D_U		=	.build_debug/utils/
DIR_DEBUG			=	${NAME}.dSYM

# -------------  Files  -------------- #

HEAD			=	cub3D.h

SRCS			=	cub3D.c

SRCS_G			=	collision_sprites.c		\
					draw_map.c				\
					draw_textures.c			\
					exit_game.c				\
					generate_textures.c		\
					handle_events.c			\
					move_player.c			\
					open_door.c				\
					play_game.c				\
					raycast_floor_ceiling.c	\
					raycast_walls.c

SRCS_P			=	get_data.c				\
					get_elem.c				\
					get_file_line.c			\
					get_map.c				\
					map_to_int.c			\
					parse_cell.c

SRCS_S			=	calcul_sprites.c		\
					draw_sprites.c

SRCS_U			=	error.c					\
					free_data.c				\
					get_time.c				\
					init_game.c				\
					init_parsing.c			\
					lst_obj_utils.c			\
					map_utils.c				\
					mlx_utils.c

SRCS_S			=	anims.c					\
					calcul_sprites.c		\
					draw_boom.c				\
					draw_sprites.c			\
					draw_weapon.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_G			=	${SRCS_G:%.c=${DIR_OBJS_G}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_U			=	${SRCS_U:%.c=${DIR_OBJS_U}%.o}
OBJS_S			=	${SRCS_S:%.c=${DIR_OBJS_S}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_D_G		=	${SRCS_G:%.c=${DIR_OBJS_D_G}%.o}
OBJS_D_P		=	${SRCS_P:%.c=${DIR_OBJS_D_P}%.o}
OBJS_D_U		=	${SRCS_U:%.c=${DIR_OBJS_D_U}%.o}
OBJS_D_S		=	${SRCS_S:%.c=${DIR_OBJS_D_S}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_G			=	${OBJS_G:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_S			=	${OBJS_S:.o=.d}
DEPS_U			=	${OBJS_U:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}
DEPS_D_G		=	${OBJS_D_G:.o=.d}
DEPS_D_P		=	${OBJS_D_P:.o=.d}
DEPS_D_S		=	${OBJS_D_S:.o=.d}
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

${NAME}				:	${OBJS} ${OBJS_G} ${OBJS_P} ${OBJS_S} ${OBJS_U} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_G} ${OBJS_P} ${OBJS_S} ${OBJS_U} -L ${DIR_LIBFT} ${LIBFT} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_G}%.o	:	${DIR_SRCS_G}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_U}%.o	:	${DIR_SRCS_U}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} ${DIR_OBJS_G}
						${MKDIR} ${DIR_OBJS_P}
						${MKDIR} ${DIR_OBJS_U}
						${MKDIR} ${DIR_OBJS_S}

-include ${DEPS}
-include ${DEPS_G}
-include ${DEPS_P}
-include ${DEPS_U}
-include ${DEPS_S}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${OBJS_D_G} ${OBJS_D_P} ${OBJS_D_S} ${OBJS_D_U} ${DIR_LIBFT} ${DIR_MLX}
						${CC} ${CFLAGS} -o ${DEBUG} ${OBJS_D} ${OBJS_D_G} ${OBJS_D_P} ${OBJS_D_S} ${OBJS_D_U} -L ${DIR_LIBFT} ${LIBFT_D} -L ${DIR_MLX} ${MLX} ${LIB_GRAPH} -g3 ${FSANITIZE}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_G}%.o	:	${DIR_SRCS_G}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_U}%.o	:	${DIR_SRCS_U}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_MLX} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}
						${MKDIR} ${DIR_OBJS_D_G}
						${MKDIR} ${DIR_OBJS_D_P}
						${MKDIR} ${DIR_OBJS_D_U}
						${MKDIR} ${DIR_OBJS_D_S}

-include ${DEPS_D}
-include ${DEPS_D_G}
-include ${DEPS_D_P}
-include ${DEPS_D_U}
-include ${DEPS_D_S}

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
						./${NAME} map/map_tuto.cub

run2				:	all
						./${NAME} map/map_subject.cub

runl				:	all
						${LEAKS}./${NAME} map/map_subject.cub

runs				:	debug
						./${DEBUG} map/map_tuto.cub

rund				:	debug
						${LLDB} ./${DEBUG}

runv				:	all
						${VALGRIND} ./${NAME} map/map_tuto.cub
