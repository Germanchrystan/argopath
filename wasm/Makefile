ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)

RAYLIB_DIR := $(ROOT)/native/raylib
SRC_DIR := $(ROOT)/wasm/src
BUILD_DIR := $(ROOT)/wasm/build
OUT_DIR := $(ROOT)/public/wasm

EMCC ?= emcc
EMAR ?= emar

APP_NAME := argopath
APP_JS := $(OUT_DIR)/$(APP_NAME).js
APP_WASM := $(OUT_DIR)/$(APP_NAME).wasm

# Fuentes de C a compilar
APP_SOURCES := $(SRC_DIR)/main.c

CFLAGS := -O2 -I$(RAYLIB_DIR)/src
LDFLAGS := -s MODULARIZE=1 -s EXPORT_ES6=1 -s ENVIRONMENT=web -s ALLOW_MEMORY_GROWTH=1 -s USE_GLFW=3
LDLIBS :=

RAYLIB_LIB := $(RAYLIB_DIR)/src/libraylib.web.a

# Targets
.PHONY: build clean check-env raylib

build: check-env raylib $(APP_JS)

check-env:
	@command -v $(EMCC) >/dev/null 2>&1 || { echo >&2 "Error: emcc no está instalado. Instala Emscripten y asegúrate de que esté en tu PATH."; exit 1; }
	@test -d $(RAYLIB_DIR) || { echo >&2 "Error: No se encontró la carpeta de raylib en $(RAYLIB_DIR). Asegúrate de que raylib esté clonado correctamente."; exit 1; }
	@mkdir -p $(OUT_DIR) $(BUILD_DIR)

raylib:
	$(MAKE) -C "$(RAYLIB_DIR)/src" clean
	$(MAKE) -C "$(RAYLIB_DIR)/src" PLATFORM=PLATFORM_WEB CC=$(EMCC) AR=$(EMAR)

$(APP_JS): $(APP_SOURCES) $(RAYLIB_LIB)
	$(EMCC) $(APP_SOURCES) $(CFLAGS) $(RAYLIB_LIB) -o $(APP_JS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(APP_JS) $(APP_WASM)