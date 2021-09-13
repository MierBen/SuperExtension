MODULES = superextension
EXTENSION = superextension
DATA = superextension--1.0.sql
REGRESS = superextension

BIN_PATH = $(HOME)/tmp_pgsql/bin

PG_CONFIG = $(BIN_PATH)/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)