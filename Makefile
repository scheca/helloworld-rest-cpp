# Variables
# UNAME		:= $(shell uname -s)

.EXPORT_ALL_VARIABLES:

# this is godly
# https://news.ycombinator.com/item?id=11939200
.PHONY: help
help:	### this screen. Keep it first target to be default
ifeq ($(UNAME), Linux)
	@grep -P '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'
else
	@# this is not tested, but prepared in advance for you, Mac drivers
	@awk -F ':.*###' '$$0 ~ FS {printf "%15s%s\n", $$1 ":", $$2}' \
		$(MAKEFILE_LIST) | grep -v '@awk' | sort
endif

# Targets
#
.PHONY: format
format:
	@bash ./scripts/format.sh

.PHONY: compile
compile:
	@bash ./scripts/compile.sh

.PHONY: test
test:
	@bash ./scripts/test.sh

.PHONY: coverage
coverage:
	@bash ./scripts/coverage.sh

.PHONY: build
build:
	@bash ./scripts/build.sh

.PHONY: run
run:
	@bash ./scripts/run.sh

.PHONY: clean
clean:
	@bash ./scripts/clean.sh
