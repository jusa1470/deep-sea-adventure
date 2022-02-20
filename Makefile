# Top level makefile
SUBDIRS = helloWorldJulia

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(MAKE) -C $(SUBDIRS) clean

.PHONY: $(SUBDIRS)