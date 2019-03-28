SUBDIRS = linked_list make_test

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $(@:build-%=%)

clean: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: $(SUBDIRS)
.PHONY: all clean