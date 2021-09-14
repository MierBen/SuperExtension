MODULES = superextension
EXTENSION = superextension
DATA = superextension--1.0.sql
REGRESS = superextension

BUILD_PATH = /tmp/tmp_pgsql

PG_CONFIG = $(BUILD_PATH)/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
