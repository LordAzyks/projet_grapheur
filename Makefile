lib_glut := $(shell find "/usr/local/lib/libglut.a")
lib_atb := $(shell find "/usr/local/lib/libAntTweakBar.a")

all:
	@echo "make run ou make install"

install:
ifneq (${lib_glut}, /usr/local/lib/libglut.a)
	brew install freeglut
	@echo "La librairie freeglut a ete installee"
else
	@echo "La librairie freeglut est deja installee"
endif
ifneq (${lib_atb}, /usr/local/lib/libAntTweakBar.a)
	brew install anttweakbar
	@echo "La librairie AntTweakBar a ete installee"
else
	@echo "La librairie AntTweakBar est deja installee"
endif
	@gcc part4_graphic/graphic.c part3_evelua/evalua.c part2_syntax/syntax.c part1_lexic/lexic.c -lglut -lm -lAntTweakBar -framework OpenGL -w -o grapheur
	@echo "Compilation réussie !"
	@echo "Executer ./grapheur pour ouvrir le grapheur"

run:
	make install
	./grapheur