
.PHONY: all
all:
	@$(MAKE) -C build $@
#	@$(MAKE) -C build -f minimal.mk xen
#	@$(MAKE) -C build -f llamaOS.mk xen
#	@$(MAKE) -C build -f apps.hello.mk xen

.PHONY: clean
clean:
	@$(MAKE) -C build $@
#	@$(MAKE) -C build -f clean.mk

