ifneq ($O,)
	out-dir := $O
else
	# If no build folder has been specified, then create all build files in
	# the current directory under a folder named out.
	out-dir := $(CURDIR)/out
endif

ifneq ($V,1)
	q := @
else
	q :=
endif

all:
	$(q)$(MAKE) -C app CROSS_COMPILE="$(CROSS_COMPILE_HOST)" \
			     q=$(q) \
			     O=$(out-dir)/quiz_test \
			     $@