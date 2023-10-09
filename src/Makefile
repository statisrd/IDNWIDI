
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

BUILD_DIR=build
INSTALL_DIR=/home/`whoami`/.local/share/s21_3dviewer_v1
DESKTOP_FILE_PATH=/home/`whoami`/.local/share/applications/s21_3dviewer_v1.desktop

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    LFLAGSTESTS = -lcheck -pthread -lrt -lm -lsubunit
    LEAKS_RUN = CK_FORK=no valgrind ./tests.out
    OPEN_REPORT = xdg-open out/index.html
else
    LFLAGSTESTS = -lcheck
    LEAKS_RUN = leaks -atExit -- ./tests.out
    OPEN_REPORT = open out/index.html
endif

all: build

build:
	qmake6 -o $(BUILD_DIR)/Makefile ./qt/s21_3dviewer_v1.pro
	make -C $(BUILD_DIR)
ifeq ("$(OS)", "Linux")
install: build
	cp Bases21_3dviewer_v1.desktop s21_3dviewer_v1.desktop
	echo Exec=$(INSTALL_DIR)/s21_3dviewer_v1 >> s21_3dviewer_v1.desktop
	echo Icon=$(INSTALL_DIR)/icon.png >> s21_3dviewer_v1.desktop
	mkdir -p $(INSTALL_DIR)
	cp $(BUILD_DIR)/s21_3dviewer_v1 $(INSTALL_DIR)/
	cp icon.png $(INSTALL_DIR)/icon.png
	cp s21_3dviewer_v1.desktop $(DESKTOP_FILE_PATH)
	rm s21_3dviewer_v1.desktop
uninstall:
	rm -rf $(INSTALL_DIR)
	rm -rf $(DESKTOP_FILE_PATH)
else
install: build
	mkdir -p install_dir
	cp $(BUILD_DIR)/s21_3dviewer_v1.app/Contents/MacOS/s21_3dviewer_v1 install_dir/
uninstall:
	rm -rf install_dir
endif
clean:
	rm -rf $(BUILD_DIR) *.o *.out *.info *.gcda *.gcno out build-* text.aux text.log text.dvi 3dviewer_v1.tgz

dvi: text.dvi
text.dvi: text.txt
	open text.txt

dist:
	tar -czf "3dviewer_v1.tgz" model.* render.* settings.* transformation.c edge_counter.c text.txt Bases21_3dviewer_v1.desktop qt/*.cpp qt/*.h qt/*.pro qt/*.ui Makefile

test: clean
	$(CC) $(CFLAGS) tests.c model.c transformation.c matrix/*.c -o tests.out $(LFLAGSTESTS) $(GCOV_FLAGS)
	./tests.out


gcov_report: test
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	$(OPEN_REPORT)

style:
	clang-format -n --style=Google *.c *.h qt/*.cpp qt/*.h

format:
	clang-format -i --style=Google *.c *.h qt/*.cpp qt/*.h

leaks: test
	$(LEAKS_RUN)

delete_saved_settings:
	rm install_dir/settings.txt
