BUILD_DIR = .build
MAKE_LOG = /tmp/make.log
MAKE_LOG = /tmp/ninja.log
PASSH_BUILD = passh -L $(MAKE_LOG)
PASSH_NINJA = passh -L $(NINJA_LOG)
DEBUG = passh rg error: $(NINJA_LOG) --no-line-number --no-filename -A 2 | command bat --style=plain --color=always --theme=1337 --paging=always --italic-text=always

default: all

.PHONY: all

all: clib build test

.PHONY: .FORCE
.FORCE:

clib:
	@clib install

build: 
	@test -d $(BUILD_DIR) && { meson $(BUILD_DIR) --reconfigure; } || { meson $(BUILD_DIR); }

test:
	@meson test -C $(BUILD_DIR) --verbose

rm_bd:
	@test -d $(BUILD_DIR) && rm -rf $(BUILD_DIR)

rm_deps:
	@test -d deps && rm -rf deps

clean: rm_deps rm_bd

debug: build
	@$(PASSH_NINJA) ninja -C $(BUILD_DIR)

install:
	@echo Install OK

tidy:
	@./tidy.sh

pull: git-pull clib build test

git-pull:
	@git pull

push: tidy
	@git commit -am 'automated git commit'
	@git push
