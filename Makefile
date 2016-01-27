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
.PHONY: all 
all: qtest ta
ta:
	$(q)$(MAKE) -C ta CROSS_COMPILE="$(CROSS_COMPILE_TA)" \
			  q=$(q) \
			  O=$(out-dir)/ta \
			  $@

qtest:
	$(q)$(MAKE) -C app CROSS_COMPILE="$(CROSS_COMPILE_HOST)" \
			     q=$(q) \
			     O=$(out-dir)/quiz_test \
			     $@


	