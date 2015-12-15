# This makefile makes all examples.

CHAPTERDIRS = chap_02 chap_03 chap_04 chap_05 chap_07 chap_08 chap_09 chap_10 APPENDIX_A_EXAMPLES

all: $(CHAPTERDIRS)

$(CHAPTERDIRS):
	$(MAKE) -C $@/LINUX_VERSIONS

.PHONY: $(CHAPTERDIRS)
