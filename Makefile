
.PHONY: all
all:
	@$(MAKE) -C build -f apps.hello.mk

.PHONY: clean
clean:
	@$(MAKE) -C build -f apps.hello.mk clean

