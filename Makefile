
# make parameters
MAKEFLAGS = --silent

.PHONY: all
all:
	@$(MAKE) -C build $@

.PHONY: install
install:
	@$(MAKE) -C build $@

.PHONY: clean
clean:
	@$(MAKE) -C build $@

