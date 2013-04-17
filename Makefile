
.PHONY: all
all:
	@$(MAKE) -C build2 $@
	@$(MAKE) -C build $@

.PHONY: install
install:
#	@$(MAKE) -C build2 $@
	@$(MAKE) -C build $@

.PHONY: clean
clean:
	@$(MAKE) -C build2 $@
	@$(MAKE) -C build $@

