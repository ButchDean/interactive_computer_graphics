# This makefile makes all examples.

CHAPTERDIRS = chap_02 chap_03 chap_04 chap_05 chap_07 chap_08 chap_09 chap_10 APPENDIX_A_EXAMPLES

.PHONY: $(CHAPTERDIRS) cleanall

all: $(CHAPTERDIRS)

$(CHAPTERDIRS):
	$(MAKE) -C $@/LINUX_VERSIONS

cleanall:
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example10
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example2
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example3
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example4
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example5
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example6
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example7
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example8
	rm APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example9
	rm chap_02/LINUX_VERSIONS/example1
	rm chap_02/LINUX_VERSIONS/example2
	rm chap_02/LINUX_VERSIONS/example3
	rm chap_02/LINUX_VERSIONS/example4
	rm chap_02/LINUX_VERSIONS/example4b
	rm chap_02/LINUX_VERSIONS/example5
	rm chap_03/LINUX_VERSIONS/example1
	rm chap_03/LINUX_VERSIONS/example2
	rm chap_03/LINUX_VERSIONS/example6
	rm chap_04/LINUX_VERSIONS/example1
	rm chap_04/LINUX_VERSIONS/example2
	rm chap_04/LINUX_VERSIONS/example3
	rm chap_05/LINUX_VERSIONS/example1
	rm chap_05/LINUX_VERSIONS/example2
	rm chap_05/LINUX_VERSIONS/example3
	rm chap_05/LINUX_VERSIONS/example6
	rm chap_07/LINUX_VERSIONS/example1
	rm chap_07/LINUX_VERSIONS/example2
	rm chap_07/LINUX_VERSIONS/example3
	rm chap_08/LINUX_VERSIONS/example1
	rm chap_08/LINUX_VERSIONS/example2
	rm chap_08/LINUX_VERSIONS/example3
	rm chap_09/LINUX_VERSIONS/chap09_6E_example1
	rm chap_09/LINUX_VERSIONS/example1
	rm chap_09/LINUX_VERSIONS/example2
	rm chap_10/LINUX_VERSIONS/example1
	rm chap_10/LINUX_VERSIONS/example2
